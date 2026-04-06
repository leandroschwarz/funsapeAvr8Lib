//!
//! ****************************************************************************
//! @file           pcint2.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Pin Change Interrupt 2 PCINT2 peripheral control.
//! @details        This file provides peripheral control for the PCINT2
//!                     peripheral control for the FunSAPE++ AVR8 Library.
//! @date           2026-04-03
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @bug            No bugs detected yet.
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

#include "pcint2.hpp"
#if !defined(__PCINT2_HPP)
#    error Error 1 - Header file (pcint2.hpp) is missing or corrupted!
#elif __PCINT2_HPP != 2604
#    error Error 6 - Build mismatch between header file (pcint2.hpp) and source file (pcint2.cpp)!
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

Pcint2 Pcint2::_instance;

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

Pcint2::Pcint2() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _enabledPins((Pcint2::Pin)0)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::Pcint2(void)"), Debug::CodeIndex::PCINT2_MODULE);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return;
}

Pcint2::~Pcint2()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::~Pcint2(void)"), Debug::CodeIndex::PCINT2_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Pcint2::disablePins(const Pcint2::Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::disablePins(const Pcint2::Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2   = MCU_PCINT2_SELECTION_REG;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, MCU_PCINT2_SELECTION_BIT_MASK, MCU_PCINT2_SELECTION_BIT_POS);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk2, aux8, MCU_PCINT2_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT2_SELECTION_REG            = auxPcmsk2;

    // Update class members
    this->_enabledPins  = (Pcint2::Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::enablePins(const Pcint2::Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::enablePins(Pcint2::Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2   = MCU_PCINT2_SELECTION_REG;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, MCU_PCINT2_SELECTION_BIT_MASK, MCU_PCINT2_SELECTION_BIT_POS);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk2, aux8, MCU_PCINT2_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT2_SELECTION_REG            = auxPcmsk2;

    // Update class members
    this->_enabledPins  = (Pcint2::Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::init(const Pcint2::Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::init(const Pcint2::Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2       = MCU_PCINT2_SELECTION_REG;

    // Configure mode
    clrMaskOffset(auxPcmsk2, MCU_PCINT2_SELECTION_BIT_MASK, MCU_PCINT2_SELECTION_BIT_POS);
    setMaskOffset(auxPcmsk2, ((uint8_t)enablePins_p), MCU_PCINT2_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT2_SELECTION_REG            = auxPcmsk2;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::setPinMode(const Pcint2::Pin pinList_p, const PinMode pinMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::setPinMode(const Pcint2::Pin, const PinMode)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPinMask      = 0;

    // Pin mask generation
#if defined(MCU_PCINT2_PIN_16_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT16)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT16_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_17_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT17)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT17_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_18_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT18)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT18_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_19_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT19)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT19_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_20_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT20)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT20_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_21_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT21)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT21_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_22_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT22)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT22_BIT);
    }
#endif
#if defined(MCU_PCINT2_PIN_23_EXISTS)
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT23)) {
        auxPinMask |= (1 << MCU_PCINT2_GPIO_PCINT23_BIT);
    }
#endif

    // Configure pin
    if(auxPinMask) {
        switch(pinMode_p) {
        case PinMode::INPUT_FLOATING:
            clrMask(MCU_PCINT2_GPIO_REG_DIR, auxPinMask);
            clrMask(MCU_PCINT2_GPIO_REG_OUT, auxPinMask);
            break;
        case PinMode::INPUT_PULLED_UP:
            clrMask(MCU_PCINT2_GPIO_REG_DIR, auxPinMask);
            setMask(MCU_PCINT2_GPIO_REG_OUT, auxPinMask);
            break;
        case PinMode::OUTPUT_PUSH_PULL:
            setMask(MCU_PCINT2_GPIO_REG_DIR, auxPinMask);
            break;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
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

void weakened pcint2InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! @cond
//!

ISR(PCINT2_vect)
{
    pcint2InterruptCallback();
}

//!
//! @endcond
//!

// =============================================================================
// End of file (pcint2.cpp)
// =============================================================================
