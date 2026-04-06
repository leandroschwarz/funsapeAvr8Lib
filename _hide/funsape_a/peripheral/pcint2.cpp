/**
 *******************************************************************************
 * @file            pcint2.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt PCINT2 peripheral control.
 * @details         This file provides peripheral control for the PCINT2
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

#include "pcint2.hpp"
#if !defined(__PCINT2_HPP)
#    error Error 1 - Header file (pcint2.hpp) is missing or corrupted!
#elif __PCINT2_HPP != 2508
#    error Error 6 - Build mismatch between header file (pcint2.hpp) and source file (pcint2.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constInterruptPinOffset        = PCINT16;  //!< Interrupt pin offset
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

Pcint2 pcint2;

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

Pcint2::Pcint2(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::Pcint2(void)"), Debug::CodeIndex::PCINT2_MODULE);

    // Reset data members
    this->_enabledPins                  = (Pcint2::Pin)0;
    this->_isInitialized                = false;

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

bool_t Pcint2::disablePins(const Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::disablePins(const Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2   = PCMSK2;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk2, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK2              = auxPcmsk2;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::enablePins(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::enablePins(Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2   = PCMSK2;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk2, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK2              = auxPcmsk2;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::init(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::init(const Pin)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPcmsk2       = PCMSK2;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk2, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK2                  = auxPcmsk2;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT2_MODULE);
    return true;
}

bool_t Pcint2::setPinMode(const Pin pinList_p, const PinMode pinMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint2::setPinMode(const Pin, const PinMode)"), Debug::CodeIndex::PCINT2_MODULE);

    // Local variables
    uint8_t auxPinMask      = 0;

    // Pin mask generation
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT16)) {
        auxPinMask |= (1 << PD0);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT17)) {
        auxPinMask |= (1 << PD1);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT18)) {
        auxPinMask |= (1 << PD2);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT19)) {
        auxPinMask |= (1 << PD3);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT20)) {
        auxPinMask |= (1 << PD4);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT21)) {
        auxPinMask |= (1 << PD5);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT22)) {
        auxPinMask |= (1 << PD6);
    }
    if((bool_t)(pinList_p & Pcint2::Pin::PIN_PCINT23)) {
        auxPinMask |= (1 << PD7);
    }

    // Configure pin
    if(auxPinMask) {
        switch(pinMode_p) {
        case PinMode::INPUT_FLOATING:
            clrMask(DDRD, auxPinMask);
            clrMask(PORTD, auxPinMask);
            break;
        case PinMode::INPUT_PULLED_UP:
            clrMask(DDRD, auxPinMask);
            setMask(PORTD, auxPinMask);
            break;
        case PinMode::OUTPUT_PUSH_PULL:
            setMask(DDRD, auxPinMask);
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

/**
 * @cond
*/

ISR(PCINT2_vect)
{
    pcint2InterruptCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (pcint2.cpp)
// =============================================================================
