/**
 *******************************************************************************
 * @file            timer1.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TIMER1 peripheral control.
 * @details         This file provides peripheral control for the TIMER1 module
 *                      for the FunSAPE++ AVR8 Library.
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

#include "timer1.hpp"
#if !defined(__TIMER1_HPP)
#    error Error 1 - Header file (timer1.hpp) is missing or corrupted!
#elif __TIMER1_HPP != 2508
#    error Error 6 - Build mismatch between header file (timer1.hpp) and source file (timer1.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constOutputModeAOffset         = COM1A0;       //!< Output A bit position offset
cuint8_t constOutputModeAMask           = 0x03;         //!< Output A bit mask
cuint8_t constOutputModeBOffset         = COM1B0;       //!< Output B bit position offset
cuint8_t constOutputModeBMask           = 0x03;         //!< Output B bit mask
cuint8_t constModeOffsetPart1           = WGM10;        //!< Operation mode part 1 bit position offset
cuint8_t constModeMaskPart1             = 0x03;         //!< Operation mode part 1 bit mask
cuint8_t constModeOffsetPart2           = WGM12;        //!< Operation mode part 2 bit position offset
cuint8_t constModeMaskPart2             = 0x03;         //!< Operation mode part 2 bit mask
cuint8_t constClockSourceOffset         = CS10;         //!< Clock source bit position offset
cuint8_t constClockSourceMask           = 0x07;         //!< Clock source bit mask

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

Timer1 timer1;

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

Timer1::Timer1()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::Timer1(void)"), Debug::CodeIndex::TIMER1_MODULE);

    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return;
}

Timer1::~Timer1()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::~Timer1(void)"), Debug::CodeIndex::TIMER1_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Timer1::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Timer1::init(const Mode mode_p, const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::init(const Mode, const ClockSource)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setClockSource(const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setClockSource(const ClockSource)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setInputCaptureMode(const Edge edgeSelection_p, cbool_t noiseCanceler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setInputCaptureMode(const Edge, cbool_t)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure Input Capture
    if(noiseCanceler_p) {
        setBit(auxTccr1B, ICNC1);
    } else {
        clrBit(auxTccr1B, ICNC1);
    }
    if(edgeSelection_p == Edge::RISING) {
        setBit(auxTccr1B, ICES1);
    } else {
        clrBit(auxTccr1B, ICES1);
    }

    // Update registers
    TCCR1B          = auxTccr1B;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setMode(const Mode)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setOutputMode(const OutputMode compA_p, const OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setOutputMode(const OutputMode, const OutputMode)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;

    // Configure outputs
    clrMaskOffset(auxTccr1A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compA_p), constOutputModeAOffset);
    clrMaskOffset(auxTccr1A, constOutputModeBMask, constOutputModeBOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR1A          = auxTccr1A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
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

void weakened timer1CompareACallback(void)
{
    return;
}

void weakened timer1CompareBCallback(void)
{
    return;
}

void weakened timer1InputCaptureCallback(void)
{
    return;
}

void weakened timer1OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(TIMER1_CAPT_vect)
{
    timer1InputCaptureCallback();
}

ISR(TIMER1_COMPA_vect)
{
    timer1CompareACallback();
}

ISR(TIMER1_COMPB_vect)
{
    timer1CompareBCallback();
}

ISR(TIMER1_OVF_vect)
{
    timer1OverflowCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (timer1.cpp)
// =============================================================================
