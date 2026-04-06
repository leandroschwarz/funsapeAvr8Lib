//!
//! ****************************************************************************
//! @file           timer1.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          TIMER1 peripheral control.
//! @details        This file provides peripheral control for the TIMER1 module
//!                     for the FunSAPE++ AVR8 Library.
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

#include "timer1.hpp"
#if !defined(__TIMER1_HPP)
#    error Error 1 - Header file (timer1.hpp) is missing or corrupted!
#elif __TIMER1_HPP != 2604
#    error Error 6 - Build mismatch between header file (timer1.hpp) and source file (timer1.cpp)!
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

Timer1 Timer1::_instance;

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

Timer1::Timer1() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _clockSource(Timer1::ClockSource::DISABLED),
    _mode(Timer1::Mode::NORMAL)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::Timer1(void)"), Debug::CodeIndex::TIMER1_MODULE);

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

bool_t Timer1::init(const Timer1::Mode mode_p, const Timer1::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::init(const Timer1::Mode, const Timer1::ClockSource)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A   = MCU_TIMER1_CTRL_A_REG;
    uint8_t auxTccr1B   = MCU_TIMER1_CTRL_B_REG;
    uint8_t aux8        = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, MCU_TIMER1_MODE_BIT_0_MASK, MCU_TIMER1_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr1B, MCU_TIMER1_MODE_BIT_2_MASK, MCU_TIMER1_MODE_BIT_2_POS);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), MCU_TIMER1_MODE_BIT_0_POS);
    setMaskOffset(auxTccr1B, (aux8 >> 2), MCU_TIMER1_MODE_BIT_2_POS);
    // Configure clock source
    clrMaskOffset(auxTccr1B, MCU_TIMER1_CLOCK_BIT_MASK, MCU_TIMER1_CLOCK_BIT_POS);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), MCU_TIMER1_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER1_CTRL_A_REG          = auxTccr1A;
    MCU_TIMER1_CTRL_B_REG          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setClockSource(const Timer1::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setClockSource(const Timer1::ClockSource)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1B = MCU_TIMER1_CTRL_B_REG;

    // Configure clock source
    clrMaskOffset(auxTccr1B, MCU_TIMER1_CLOCK_BIT_MASK, MCU_TIMER1_CLOCK_BIT_POS);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), MCU_TIMER1_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER1_CTRL_B_REG          = auxTccr1B;

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
    uint8_t auxTccr1B = MCU_TIMER1_CTRL_B_REG;

    // Configure Input Capture
    if(noiseCanceler_p) {
        setBit(auxTccr1B, MCU_TIMER1_NOISE_CANCELLER_BIT_POS);
    } else {
        clrBit(auxTccr1B, MCU_TIMER1_NOISE_CANCELLER_BIT_POS);
    }
    if(edgeSelection_p == Edge::RISING) {
        setBit(auxTccr1B, MCU_TIMER1_EDGE_SELECT_BIT_POS);
    } else {
        clrBit(auxTccr1B, MCU_TIMER1_EDGE_SELECT_BIT_POS);
    }

    // Update registers
    MCU_TIMER1_CTRL_B_REG          = auxTccr1B;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setMode(const Timer1::Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setMode(const Timer1::Mode)"), Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A = MCU_TIMER1_CTRL_A_REG;
    uint8_t auxTccr1B = MCU_TIMER1_CTRL_B_REG;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, MCU_TIMER1_MODE_BIT_0_MASK, MCU_TIMER1_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr1B, MCU_TIMER1_MODE_BIT_2_MASK, MCU_TIMER1_MODE_BIT_2_POS);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), MCU_TIMER1_MODE_BIT_0_POS);
    setMaskOffset(auxTccr1B, (aux8 >> 2), MCU_TIMER1_MODE_BIT_2_POS);

    // Update registers
    MCU_TIMER1_CTRL_A_REG          = auxTccr1A;
    MCU_TIMER1_CTRL_B_REG          = auxTccr1B;

    // Update class members
    this->_mode     = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER1_MODULE);
    return true;
}

bool_t Timer1::setOutputMode(const Timer1::OutputMode compA_p, const Timer1::OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer1::setOutputMode(const Timer1::OutputMode, const Timer1::OutputMode)"),
            Debug::CodeIndex::TIMER1_MODULE);

    // Local variables
    uint8_t auxTccr1A = MCU_TIMER1_CTRL_A_REG;

    // Configure outputs
    clrMaskOffset(auxTccr1A, MCU_TIMER1_OUTPUT_A_MODE_BIT_MASK, MCU_TIMER1_OUTPUT_A_MODE_BIT_POS);
    setMaskOffset(auxTccr1A, ((uint8_t)compA_p), MCU_TIMER1_OUTPUT_A_MODE_BIT_POS);
    clrMaskOffset(auxTccr1A, MCU_TIMER1_OUTPUT_B_MODE_BIT_MASK, MCU_TIMER1_OUTPUT_B_MODE_BIT_POS);
    setMaskOffset(auxTccr1A, ((uint8_t)compB_p), MCU_TIMER1_OUTPUT_B_MODE_BIT_POS);

    // Update registers
    MCU_TIMER1_CTRL_A_REG          = auxTccr1A;

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

//!
//! @cond
//!

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

//!
//! @endcond
//!

// =============================================================================
// End of file (timer1.cpp)
// =============================================================================
