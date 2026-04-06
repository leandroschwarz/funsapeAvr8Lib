/**
 *******************************************************************************
 * @file            pcint0.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt PCINT0 peripheral control.
 * @details         This file provides peripheral control for the PCINT0
 *                      peripheral control for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
 * @bug             No bugs detected yet.
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

#include "pcint0.hpp"
#if !defined(__PCINT0_HPP)
#    error Error 1 - Header file (pcint0.hpp) is missing or corrupted!
#elif __PCINT0_HPP != 2508
#    error Error 6 - Build mismatch between header file (pcint0.hpp) and source file (pcint0.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constInterruptPinOffset        = PCINT0;   //!< Interrupt pin offset
cuint8_t constInterruptPinsMask         = 0xFF;     //!< Interrupt pins bit mask

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

Pcint0 pcint0;

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

Pcint0::Pcint0()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::Pcint0(void)"), Debug::CodeIndex::PCINT0_MODULE);

    // Reset data members
    this->_enabledPins                  = (Pcint0::Pin)0;
    this->_isInitialized                = false;

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

bool_t Pcint0::disablePins(const Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::disablePins(const Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0   = PCMSK0;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk0, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK0              = auxPcmsk0;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::enablePins(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::enablePins(Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0   = PCMSK0;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk0, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK0              = auxPcmsk0;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::init(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::init(const Pin)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPcmsk0       = PCMSK0;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk0, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK0                  = auxPcmsk0;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT0_MODULE);
    return true;
}

bool_t Pcint0::setPinMode(const Pin pinList_p, const PinMode pinMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint0::setPinMode(const Pin, const PinMode)"), Debug::CodeIndex::PCINT0_MODULE);

    // Local variables
    uint8_t auxPinMask      = 0;

    // Pin mask generation
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT0)) {
        auxPinMask |= (1 << PB0);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT1)) {
        auxPinMask |= (1 << PB1);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT2)) {
        auxPinMask |= (1 << PB2);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT3)) {
        auxPinMask |= (1 << PB3);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT4)) {
        auxPinMask |= (1 << PB4);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT5)) {
        auxPinMask |= (1 << PB5);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT6)) {
        auxPinMask |= (1 << PB6);
    }
    if((bool_t)(pinList_p & Pcint0::Pin::PIN_PCINT7)) {
        auxPinMask |= (1 << PB7);
    }

    // Configure pin
    if(auxPinMask) {
        switch(pinMode_p) {
        case PinMode::INPUT_FLOATING:
            clrMask(DDRB, auxPinMask);
            clrMask(PORTB, auxPinMask);
            break;
        case PinMode::INPUT_PULLED_UP:
            clrMask(DDRB, auxPinMask);
            setMask(PORTB, auxPinMask);
            break;
        case PinMode::OUTPUT_PUSH_PULL:
            setMask(DDRB, auxPinMask);
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
// Interrupt callback functions
// =============================================================================

void weakened pcint0InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(PCINT0_vect)
{
    pcint0InterruptCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (pcint0.cpp)
// =============================================================================
