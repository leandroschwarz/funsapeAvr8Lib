/**
 *******************************************************************************
 * @file            int0.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt INT0 peripheral control.
 * @details         This file provides peripheral control for the INT0
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

#include "int0.hpp"
#if !defined(__INT0_HPP)
#    error Error 1 - Header file (int0.hpp) is missing or corrupted!
#elif __INT0_HPP != 2508
#    error Error 6 - Build mismatch between header file (int0.hpp) and source file (int0.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constSenseModeModeOffset       = ISC00;    //!< Interrupt sense mode bit position offset
cuint8_t constSenseModeMask             = 0x03;     //!< Interrupt sense mode bit mask

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

Int0 int0;

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

Int0::Int0()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Int0::Int0(void)"), Debug::CodeIndex::INT0_MODULE);

    // Reset data members
    this->_senseMode                    = SenseMode::LOW_LEVEL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::INT0_MODULE);
    return;
}

Int0::~Int0()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Int0::~Int0(void)"), Debug::CodeIndex::INT0_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::INT0_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Int0::init(const SenseMode senseMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Int0::init(const SenseMode)"), Debug::CodeIndex::INT0_MODULE);

    // Local variables
    uint8_t auxEicra = EICRA;

    // Configure mode
    clrMaskOffset(auxEicra, constSenseModeMask, constSenseModeModeOffset);
    setMaskOffset(auxEicra, ((uint8_t)senseMode_p), constSenseModeModeOffset);

    // Update registers
    EICRA           = auxEicra;

    // Update class members
    this->_senseMode        = senseMode_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::INT0_MODULE);
    return true;
}

bool_t Int0::setPinMode(const PinMode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Int0::setPinMode(const PinMode)"), Debug::CodeIndex::INT0_MODULE);

    // Configure pin
    switch(mode_p) {
    case PinMode::INPUT_FLOATING:
        clrBit(DDRD, PD2);
        clrBit(PORTD, PD2);
        break;
    case PinMode::INPUT_PULLED_UP:
        clrBit(DDRD, PD2);
        setBit(PORTD, PD2);
        break;
    case PinMode::OUTPUT_PUSH_PULL:
        setBit(DDRD, PD2);
        break;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::INT0_MODULE);
    return true;
}

bool_t Int0::setSenseMode(const SenseMode senseMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Int0::setSenseMode(const SenseMode)"), Debug::CodeIndex::INT0_MODULE);

    // Local variables
    uint8_t auxEicra = EICRA;

    // Configure mode
    clrMaskOffset(auxEicra, constSenseModeMask, constSenseModeModeOffset);
    setMaskOffset(auxEicra, ((uint8_t)senseMode_p), constSenseModeModeOffset);

    // Update registers
    EICRA           = auxEicra;

    // Update class members
    this->_senseMode        = senseMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::INT0_MODULE);
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

void weakened int0InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(INT0_vect)
{
    int0InterruptCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (int0.cpp)
// =============================================================================
