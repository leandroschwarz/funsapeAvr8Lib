/**
 *******************************************************************************
 * @file            timer2.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TIMER2 peripheral control.
 * @details         This file provides peripheral control for the TIMER2 module
 *                      for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            ASSR and GTCCR2 registers.
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

#include "timer2.hpp"
#if !defined(__TIMER2_HPP)
#    error Error 1 - Header file (timer2.hpp) is missing or corrupted!
#elif __TIMER2_HPP != 2508
#    error Error 6 - Build mismatch between header file (timer2.hpp) and source file (timer2.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constOutputModeAOffset         = COM2A0;   //!< Output A bit position offset
cuint8_t constOutputModeAMask           = 0x03;     //!< Output A bit mask
cuint8_t constOutputModeBOffset         = COM2B0;   //!< Output B bit position offset
cuint8_t constOutputModeBMask           = 0x03;     //!< Output B bit mask
cuint8_t constModeOffsetPart1           = WGM20;    //!< Operation mode part 1 bit position offset
cuint8_t constModeMaskPart1             = 0x03;     //!< Operation mode part 1 bit mask
cuint8_t constModeOffsetPart2           = WGM22;    //!< Operation mode part 2 bit position offset
cuint8_t constModeMaskPart2             = 0x01;     //!< Operation mode part 2 bit mask
cuint8_t constClockSourceOffset         = CS20;     //!< Clock source bit position offset
cuint8_t constClockSourceMask           = 0x07;     //!< Clock source bit mask

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

Timer2 timer2;

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

Timer2::Timer2()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::Timer2(void)"), Debug::CodeIndex::TIMER2_MODULE);

    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return;
}

Timer2::~Timer2()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::~Timer2(void)"), Debug::CodeIndex::TIMER2_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Timer2::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Timer2::init(const Mode mode_p, const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::init(const Mode, const ClockSource)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setClockSource(const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setClockSource(const ClockSource)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2B = TCCR2B;

    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setMode(const Mode)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setOutputMode(const OutputMode compA_p, const OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setOutputMode(const OutputMode, const OutputMode)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;

    // Configure outputs
    clrMaskOffset(auxTccr2A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compA_p), constOutputModeAOffset);
    clrMaskOffset(auxTccr2A, constOutputModeBMask, constOutputModeBOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR2A          = auxTccr2A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
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

void weakened timer2CompareACallback(void)
{
    return;
}

void weakened timer2CompareBCallback(void)
{
    return;
}

void weakened timer2OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(TIMER2_COMPA_vect)
{
    timer2CompareACallback();
}

ISR(TIMER2_COMPB_vect)
{
    timer2CompareBCallback();
}

ISR(TIMER2_OVF_vect)
{
    timer2OverflowCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (timer2.cpp)
// =============================================================================
