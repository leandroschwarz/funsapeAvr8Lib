//!
//! ****************************************************************************
//! @file           gpioPin.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          GPIO single pin peripheral control.
//! @details        This file provides driver interface with the GPIO module to
//!                     single pin peripheral control for the FunSAPE++ AVR8
//!                     Library.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @warning        When the user calls GpioPin::clr(), GpioPin::cpl(),
//!                     GpioPin::set(), GpioPin::low(), GpioPin::high() or
//!                     GpioPin::toggle() and the pin is in
//!                     PinMode::INPUT_FLOATING mode or in
//!                     PinMode::INPUT_PULLED_UP mode, the mode is changed which
//!                     could lead to some undefined behavior.
//! ****************************************************************************
//! @attention
//!
//! MIT License
//!
//! Copyright (c) 2026 Leandro Schwarz
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//!     of this software and associated documentation files (the "Software"), to
//!     deal in the Software without restriction, including without limitation
//!     the rights to use, copy, modify, merge, publish, distribute, sublicense,
//!     and/or sell copies of the Software, and to permit persons to whom the
//!     Software is furnished to do so, subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in
//!     all copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//!     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//!     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//!     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//!     OTHER DEALINGS IN THE SOFTWARE.
//!
//! ****************************************************************************
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "gpioPin.hpp"
#if !defined(__GPIO_PIN_HPP)
#    error Error 1 - Header file (gpioPin.hpp) is missing or corrupted!
#elif __GPIO_PIN_HPP != 2604
#    error Error 6 - Build mismatch between header file (gpioPin.hpp) and source file (gpioPin.cpp)!
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

GpioPin::GpioPin(void) :
    _regDir(nullptr),
    _regOut(nullptr),
    _regIn(nullptr),
    _pinMask(0x00),
    _isInitialized(false),
    _lastError(Error::NONE)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioPin::GpioPin(void)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return;
}

GpioPin::~GpioPin(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioPin::~GpioPin(void)"), Debug::CodeIndex::GPIO_BUS_MODULE);

    // Returns successfully
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t GpioPin::init(ioRegAddress_t gpioPortAddress_p, const PinIndex gpioPinIndex_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioPin::init(ioRegAddress_t, const PinIndex)"), Debug::CodeIndex::GPIO_PIN_MODULE);

    // Local variables
    ioRegAddress_t auxDir = nullptr;
    ioRegAddress_t auxOut = nullptr;

    // CHECK FOR ERROR - port address invalid
    if(!isGpioAddressValid(gpioPortAddress_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::GPIO_PIN_MODULE);
        return false;
    }

    // Evaluates pin addresses
    auxDir = getGpioDdrAddress(gpioPortAddress_p);
    auxOut = getGpioPortAddress(gpioPortAddress_p);

    // Update data members
    this->_regDir                       = auxDir;
    this->_regOut                       = auxOut;
    this->_regIn                        = getGpioPinAddress(gpioPortAddress_p);
    this->_pinMask                      = (ioPinMask_t)(1 << (uint8_t)gpioPinIndex_p);
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return true;
}

//     ///////////////////    PIN RELATED METHODS     ///////////////////     //

bool_t GpioPin::setMode(const PinMode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("GpioPin::setMode(const PinMode)"), Debug::CodeIndex::GPIO_PIN_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::GPIO_PIN_MODULE);
        return false;
    }

    // Configure pin
    switch(mode_p) {
    case PinMode::INPUT_FLOATING:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        clrMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case PinMode::INPUT_PULLED_UP:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        setMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case PinMode::OUTPUT_PUSH_PULL:
        setMask(*(this->_regDir), (uint8_t)this->_pinMask);
        break;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return true;
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
// End of file (gpioPin.cpp)
// =============================================================================
