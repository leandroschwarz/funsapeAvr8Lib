/**
 *******************************************************************************
 * @file            gpioBus.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           GPIO bus peripheral control.
 * @details         This file provides driver interface with the GPIO module to
 *                      multiple sequential pins for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
 * @bug             When the user calls GpioBus::clr(), GpioBus::cpl(),
 *                      GpioBus::set(), GpioBus::low(), GpioBus::high(),
 *                      GpioBus::toggle() or GpioBus::write() and the bus is in
 *                      GpioBus::Mode::INPUT_FLOATING mode or in
 *                      GpioBus::Mode::INPUT_PULLED_UP mode, the mode is changed
 *                      without knowledge of the class, so the GpioBus::_mode
 *                      internal member is not updated, which could lead to some
 *                      undefined behavior.
 *
 *******************************************************************************
 * @attention
 *
 * MIT License
 *
 * Copyright (c) 2025 Leandro Schwarz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *      of this software and associated documentation files (the "Software"), to
 *      deal in the Software without restriction, including without limitation
 *      the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *      and/or sell copies of the Software, and to permit persons to whom the
 *      Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *      all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *      THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *      OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *      ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *      OTHER DEALINGS IN THE SOFTWARE.
 *
 *******************************************************************************
*/

// =============================================================================
// System file dependencies
// =============================================================================

#include "gpioBus.hpp"
#if !defined(__GPIO_BUS_HPP)
#    error Error 1 - Header file (gpioBus.hpp) is missing or corrupted!
#elif __GPIO_BUS_HPP != 2508
#    error Error 6 - Build mismatch between header file (gpioBus.hpp) and source file (gpioBus.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Public function definitions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

GpioBus::GpioBus(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioBus::GpioBus(void)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // Resets data members
    this->_regDir                       = nullptr;
    this->_regOut                       = nullptr;
    this->_regIn                        = nullptr;
    this->_pinMask                      = (PinMask)0;
    this->_pinIndex                     = PinIndex::P0;
    this->_isInitialized                = false;
    this->_mode                         = Mode::INPUT_FLOATING;
    this->_busSize                      = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return;
}

GpioBus::~GpioBus(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioBus::~GpioBus(void)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t GpioBus::init(ioRegAddress_t gpioPortAddress_p, PinIndex gpioBusIndex_p, cuint8_t gpioBusSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioBus::init(ioRegAddress_t, PinIndex, cuint8_t)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // CHECK FOR ERROR - port address invalid
    if(!isGpioAddressValid(gpioPortAddress_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::GPIO_PIN_MODULE);
        return false;
    }
    // CHECK FOR ERROR - bus size invalid
    if((gpioBusSize_p == 0) || (gpioBusSize_p > 8)) {
        // Returns error
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }
    // CHECK FOR ERROR - bus out of boundaries
    if(((uint8_t)gpioBusIndex_p + gpioBusSize_p) > 8) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_OUT_OF_BOUNDARIES, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxPinMask = (((1 << gpioBusSize_p) - 1) << (uint8_t)gpioBusIndex_p);

    // Update data members
    this->_regDir                       = getGpioDdrAddress(gpioPortAddress_p);
    this->_regOut                       = getGpioPortAddress(gpioPortAddress_p);
    this->_regIn                        = getGpioPinAddress(gpioPortAddress_p);
    this->_pinMask                      = (PinMask)auxPinMask;
    this->_pinIndex                     = gpioBusIndex_p;
    this->_isInitialized                = true;
    this->_busSize                      = gpioBusSize_p;

    // Configure pins as input floating
    clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
    clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

//     ///////////////////    PIN RELATED METHODS     ///////////////////     //

bool_t GpioBus::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioBus::setMode(const GpioBus::Mode)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    // Nothing to do!
    if(this->_mode == mode_p) {
        // Returns successfully
        this->_lastError = Error::NONE;
        debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
        return true;
    }

    // Configure pin
    switch(mode_p) {
    case Mode::INPUT_FLOATING:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        clrMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case Mode::INPUT_PULLED_UP:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        setMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case Mode::OUTPUT_PUSH_PULL:
        setMask(*(this->_regDir), (uint8_t)this->_pinMask);
        break;
    }

    // Update data members
    this->_mode = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

bool_t GpioBus::write(cuint8_t data_p)
{
    // Local variables
    uint8_t aux8 = 0;

    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    aux8 = *(this->_regOut);
    clrMask(aux8, (uint8_t)(this->_pinMask));
    aux8 |= ((data_p << (uint8_t)this->_pinIndex) & (uint8_t)(this->_pinMask));
    *(this->_regOut) = aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

uint8_t GpioBus::getBusSize(void)
{
    if(!this->_isInitialized) {
        // Returns error
        return 0;
    }

    // Returns value
    return this->_busSize;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

// NONE

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// End of file (gpioBus.cpp)
// =============================================================================
