//!
//! ****************************************************************************
//! @file           timer2.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          TIMER2 peripheral control.
//! @details        This file provides peripheral control for the TIMER2 module
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

#include "timer2.hpp"
#if !defined(__TIMER2_HPP)
#    error Error 1 - Header file (timer2.hpp) is missing or corrupted!
#elif __TIMER2_HPP != 2604
#    error Error 6 - Build mismatch between header file (timer2.hpp) and source file (timer2.cpp)!
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

Timer2 Timer2::_instance;

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

Timer2::Timer2() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _clockSource(Timer2::ClockSource::DISABLED),
    _mode(Timer2::Mode::NORMAL)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::Timer2(void)"), Debug::CodeIndex::TIMER2_MODULE);

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

bool_t Timer2::init(const Timer2::Mode mode_p, const Timer2::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::init(const Timer2::Mode, const Timer2::ClockSource)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A   = MCU_TIMER2_CTRL_A_REG;
    uint8_t auxTccr2B   = MCU_TIMER2_CTRL_B_REG;
    uint8_t aux8        = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, MCU_TIMER2_MODE_BIT_0_MASK, MCU_TIMER2_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr2B, MCU_TIMER2_MODE_BIT_2_MASK, MCU_TIMER2_MODE_BIT_2_POS);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), MCU_TIMER2_MODE_BIT_0_POS);
    setMaskOffset(auxTccr2B, (aux8 >> 2), MCU_TIMER2_MODE_BIT_2_POS);
    // Configure clock source
    clrMaskOffset(auxTccr2B, MCU_TIMER2_CLOCK_BIT_MASK, MCU_TIMER2_CLOCK_BIT_POS);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), MCU_TIMER2_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER2_CTRL_A_REG          = auxTccr2A;
    MCU_TIMER2_CTRL_B_REG          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setClockSource(const Timer2::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setClockSource(const Timer2::ClockSource)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2B = MCU_TIMER2_CTRL_B_REG;

    // Configure clock source
    clrMaskOffset(auxTccr2B, MCU_TIMER2_CLOCK_BIT_MASK, MCU_TIMER2_CLOCK_BIT_POS);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), MCU_TIMER2_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER2_CTRL_B_REG          = auxTccr2B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setMode(const Timer2::Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setMode(const Timer2::Mode)"), Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A = MCU_TIMER2_CTRL_A_REG;
    uint8_t auxTccr2B = MCU_TIMER2_CTRL_B_REG;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, MCU_TIMER2_MODE_BIT_0_MASK, MCU_TIMER2_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr2B, MCU_TIMER2_MODE_BIT_2_MASK, MCU_TIMER2_MODE_BIT_2_POS);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), MCU_TIMER2_MODE_BIT_0_POS);
    setMaskOffset(auxTccr2B, (aux8 >> 2), MCU_TIMER2_MODE_BIT_2_POS);

    // Update registers
    MCU_TIMER2_CTRL_A_REG          = auxTccr2A;
    MCU_TIMER2_CTRL_B_REG          = auxTccr2B;

    // Update class members
    this->_mode     = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER2_MODULE);
    return true;
}

bool_t Timer2::setOutputMode(const Timer2::OutputMode compA_p, const Timer2::OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer2::setOutputMode(const Timer2::OutputMode, const Timer2::OutputMode)"),
            Debug::CodeIndex::TIMER2_MODULE);

    // Local variables
    uint8_t auxTccr2A = MCU_TIMER2_CTRL_A_REG;

    // Configure outputs
    clrMaskOffset(auxTccr2A, MCU_TIMER2_OUTPUT_A_MODE_BIT_MASK, MCU_TIMER2_OUTPUT_A_MODE_BIT_POS);
    setMaskOffset(auxTccr2A, ((uint8_t)compA_p), MCU_TIMER2_OUTPUT_A_MODE_BIT_POS);
    clrMaskOffset(auxTccr2A, MCU_TIMER2_OUTPUT_B_MODE_BIT_MASK, MCU_TIMER2_OUTPUT_B_MODE_BIT_POS);
    setMaskOffset(auxTccr2A, ((uint8_t)compB_p), MCU_TIMER2_OUTPUT_B_MODE_BIT_POS);

    // Update registers
    MCU_TIMER2_CTRL_A_REG          = auxTccr2A;

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

//!
//! @cond
//!

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

//!
//! @endcond
//!

// =============================================================================
// End of file (timer2.cpp)
// =============================================================================
