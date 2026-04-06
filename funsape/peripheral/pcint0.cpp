//!
//! ****************************************************************************
//! @file           pcint0.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Pin Change Interrupt 0 PCINT0 peripheral control.
//! @details        This file provides peripheral control for the PCINT0
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

#include "pcint0.hpp"
#if !defined(__PCINT0_HPP)
#    error Error 1 - Header file (pcint0.hpp) is missing or corrupted!
#elif __PCINT0_HPP != 2604
#    error Error 6 - Build mismatch between header file (pcint0.hpp) and source file (pcint0.cpp)!
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

Pcint0 Pcint0::_instance;

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

Pcint0::Pcint0() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _enabledPins((Pcint0::Pin)0)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::Pcint0(void)"), Debug::CodeIndex::PCINT0_MODULE);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return;
}

Pcint0::~Pcint0()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::~Pcint0(void)"), Debug::CodeIndex::PCINT0_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Pcint0::disablePins(const Pcint0::Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::disablePins(const Pcint0::Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0   = MCU_PCINT0_SELECTION_REG;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, MCU_PCINT0_SELECTION_BIT_MASK, MCU_PCINT0_SELECTION_BIT_POS);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk0, aux8, MCU_PCINT0_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT0_SELECTION_REG            = auxPcmsk0;

    // Update class members
    this->_enabledPins  = (Pcint0::Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::enablePins(const Pcint0::Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::enablePins(Pcint0::Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0   = MCU_PCINT0_SELECTION_REG;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, MCU_PCINT0_SELECTION_BIT_MASK, MCU_PCINT0_SELECTION_BIT_POS);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk0, aux8, MCU_PCINT0_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT0_SELECTION_REG            = auxPcmsk0;

    // Update class members
    this->_enabledPins  = (Pcint0::Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::init(const Pcint0::Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::init(const Pcint0::Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0       = MCU_PCINT0_SELECTION_REG;

    // Configure mode
    clrMaskOffset(auxPcmsk0, MCU_PCINT0_SELECTION_BIT_MASK, MCU_PCINT0_SELECTION_BIT_POS);
    setMaskOffset(auxPcmsk0, ((uint8_t)enablePins_p), MCU_PCINT0_SELECTION_BIT_POS);

    // Update registers
    MCU_PCINT0_SELECTION_REG            = auxPcmsk0;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::setPinMode(const Pcint0::Pin pinList_p, const PinMode pinMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::setPinMode(const Pcint0::Pin, const PinMode)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPinMask      = 0;

    // Pin mask generation
#if defined(MCU_PCINT0_PIN_0_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT0)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT0_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_1_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT1)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT1_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_2_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT2)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT2_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_3_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT3)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT3_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_4_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT4)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT4_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_5_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT5)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT5_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_6_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT6)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT6_BIT);
    }
#endif
#if defined(MCU_PCINT0_PIN_7_EXISTS)
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT7)) {
        auxPinMask |= (1 << MCU_PCINT0_GPIO_PCINT7_BIT);
    }
#endif

    // Configure pin
    if(auxPinMask) {
        switch(pinMode_p) {
        case PinMode::INPUT_FLOATING:
            clrMask(MCU_PCINT0_GPIO_REG_DIR, auxPinMask);
            clrMask(MCU_PCINT0_GPIO_REG_OUT, auxPinMask);
            break;
        case PinMode::INPUT_PULLED_UP:
            clrMask(MCU_PCINT0_GPIO_REG_DIR, auxPinMask);
            setMask(MCU_PCINT0_GPIO_REG_OUT, auxPinMask);
            break;
        case PinMode::OUTPUT_PUSH_PULL:
            setMask(MCU_PCINT0_GPIO_REG_DIR, auxPinMask);
            break;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
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

void weakened pcint0InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! @cond
//!

ISR(PCINT0_vect)
{
    pcint0InterruptCallback();
}

//!
//! @endcond
//!

// =============================================================================
// End of file (pcint0.cpp)
// =============================================================================
