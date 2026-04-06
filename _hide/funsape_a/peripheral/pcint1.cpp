/**
 *******************************************************************************
 * @file            pcint1.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt PCINT1 peripheral control.
 * @details         This file provides peripheral control for the PCINT1
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

#include "pcint1.hpp"
#if !defined(__PCINT1_HPP)
#    error Error 1 - Header file (pcint1.hpp) is missing or corrupted!
#elif __PCINT1_HPP != 2508
#    error Error 6 - Build mismatch between header file (pcint1.hpp) and source file (pcint1.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constInterruptPinOffset        = PCINT8;   //!< Interrupt pin offset
cuint8_t constInterruptPinsMask         = 0x7F;     //!< Interrupt pins bit mask

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

Pcint1 pcint1;

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

Pcint1::Pcint1()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::Pcint1(void)"), Debug::CodeIndex::PCINT1_MODULE);

    // Reset data members
    this->_enabledPins                  = (Pcint1::Pin)0;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
    return;
}

Pcint1::~Pcint1()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::~Pcint1(void)"), Debug::CodeIndex::PCINT1_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Pcint1::disablePins(const Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::disablePins(const Pin)"), Debug::CodeIndex::PCINT1_MODULE);

    // Local variables
    uint8_t auxPcmsk1   = PCMSK1;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk1, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK1              = auxPcmsk1;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
    return true;
}

bool_t Pcint1::enablePins(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::enablePins(Pin)"), Debug::CodeIndex::PCINT1_MODULE);

    // Local variables
    uint8_t auxPcmsk1   = PCMSK1;
    uint8_t aux8        = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk1, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK1              = auxPcmsk1;

    // Update class members
    this->_enabledPins  = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
    return true;
}

bool_t Pcint1::init(const Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::init(const Pin)"), Debug::CodeIndex::PCINT1_MODULE);

    // Local variables
    uint8_t auxPcmsk1       = PCMSK1;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk1, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK1                  = auxPcmsk1;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
    return true;
}

bool_t Pcint1::setPinMode(const Pin pinList_p, const PinMode pinMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Pcint1::setPinMode(const Pin, const PinMode)"), Debug::CodeIndex::PCINT1_MODULE);

    // Local variables
    uint8_t auxPinMask      = 0;

    // Pin mask generation
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT8)) {
        auxPinMask |= (1 << PC0);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT9)) {
        auxPinMask |= (1 << PC1);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT10)) {
        auxPinMask |= (1 << PC2);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT11)) {
        auxPinMask |= (1 << PC3);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT12)) {
        auxPinMask |= (1 << PC4);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT13)) {
        auxPinMask |= (1 << PC5);
    }
    if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT14)) {
        auxPinMask |= (1 << PC6);
    }
    // if((bool_t)(pinList_p & Pcint1::Pin::PIN_PCINT15)) {
    //     auxPinMask |= (1 << PC7);
    // }

    // Configure pin
    if(auxPinMask) {
        switch(pinMode_p) {
        case PinMode::INPUT_FLOATING:
            clrMask(DDRC, auxPinMask);
            clrMask(PORTC, auxPinMask);
            break;
        case PinMode::INPUT_PULLED_UP:
            clrMask(DDRC, auxPinMask);
            setMask(PORTC, auxPinMask);
            break;
        case PinMode::OUTPUT_PUSH_PULL:
            setMask(DDRC, auxPinMask);
            break;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PCINT1_MODULE);
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

void weakened pcint1InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(PCINT1_vect)
{
    pcint1InterruptCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (pcint1.cpp)
// =============================================================================
