//!
//! ****************************************************************************
//! @file           timer0.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          TIMER0 peripheral control.
//! @details        This file provides peripheral control for the TIMER0 module
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

#include "timer0.hpp"
#if !defined(__TIMER0_HPP)
#    error Error 1 - Header file (timer0.hpp) is missing or corrupted!
#elif __TIMER0_HPP != 2604
#    error Error 6 - Build mismatch between header file (timer0.hpp) and source file (timer0.cpp)!
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

Timer0 Timer0::_instance;

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

Timer0::Timer0() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _clockSource(Timer0::ClockSource::DISABLED),
    _mode(Timer0::Mode::NORMAL)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::Timer0(void)"), Debug::CodeIndex::TIMER0_MODULE);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
    return;
}

Timer0::~Timer0()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::~Timer0(void)"), Debug::CodeIndex::TIMER0_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Timer0::init(const Timer0::Mode mode_p, const Timer0::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::init(const Timer0::Mode, const Timer0::ClockSource)"), Debug::CodeIndex::TIMER0_MODULE);

    // Local variables
    uint8_t auxTccr0A   = MCU_TIMER0_CTRL_A_REG;
    uint8_t auxTccr0B   = MCU_TIMER0_CTRL_B_REG;
    uint8_t aux8        = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, MCU_TIMER0_MODE_BIT_0_MASK, MCU_TIMER0_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr0B, MCU_TIMER0_MODE_BIT_2_MASK, MCU_TIMER0_MODE_BIT_2_POS);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), MCU_TIMER0_MODE_BIT_0_POS);
    setMaskOffset(auxTccr0B, (aux8 >> 2), MCU_TIMER0_MODE_BIT_2_POS);
    // Configure clock source
    clrMaskOffset(auxTccr0B, MCU_TIMER0_CLOCK_BIT_MASK, MCU_TIMER0_CLOCK_BIT_POS);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), MCU_TIMER0_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER0_CTRL_A_REG          = auxTccr0A;
    MCU_TIMER0_CTRL_B_REG          = auxTccr0B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
    return true;
}

bool_t Timer0::setClockSource(const Timer0::ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::setClockSource(const Timer0::ClockSource)"), Debug::CodeIndex::TIMER0_MODULE);

    // Local variables
    uint8_t auxTccr0B = MCU_TIMER0_CTRL_B_REG;

    // Configure clock source
    clrMaskOffset(auxTccr0B, MCU_TIMER0_CLOCK_BIT_MASK, MCU_TIMER0_CLOCK_BIT_POS);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), MCU_TIMER0_CLOCK_BIT_POS);

    // Update registers
    MCU_TIMER0_CTRL_B_REG          = auxTccr0B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
    return true;
}

bool_t Timer0::setMode(const Timer0::Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::setMode(const Timer0::Mode)"), Debug::CodeIndex::TIMER0_MODULE);

    // Local variables
    uint8_t auxTccr0A = MCU_TIMER0_CTRL_A_REG;
    uint8_t auxTccr0B = MCU_TIMER0_CTRL_B_REG;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, MCU_TIMER0_MODE_BIT_0_MASK, MCU_TIMER0_MODE_BIT_0_POS);
    clrMaskOffset(auxTccr0B, MCU_TIMER0_MODE_BIT_2_MASK, MCU_TIMER0_MODE_BIT_2_POS);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), MCU_TIMER0_MODE_BIT_0_POS);
    setMaskOffset(auxTccr0B, (aux8 >> 2), MCU_TIMER0_MODE_BIT_2_POS);

    // Update registers
    MCU_TIMER0_CTRL_A_REG          = auxTccr0A;
    MCU_TIMER0_CTRL_B_REG          = auxTccr0B;

    // Update class members
    this->_mode     = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
    return true;
}

bool_t Timer0::setOutputMode(const Timer0::OutputMode compA_p, const Timer0::OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Timer0::setOutputMode(const Timer0::OutputMode, const Timer0::OutputMode)"),
            Debug::CodeIndex::TIMER0_MODULE);

    // Local variables
    uint8_t auxTccr0A = MCU_TIMER0_CTRL_A_REG;

    // Configure outputs
    clrMaskOffset(auxTccr0A, MCU_TIMER0_OUTPUT_A_MODE_BIT_MASK, MCU_TIMER0_OUTPUT_A_MODE_BIT_POS);
    setMaskOffset(auxTccr0A, ((uint8_t)compA_p), MCU_TIMER0_OUTPUT_A_MODE_BIT_POS);
    clrMaskOffset(auxTccr0A, MCU_TIMER0_OUTPUT_B_MODE_BIT_MASK, MCU_TIMER0_OUTPUT_B_MODE_BIT_POS);
    setMaskOffset(auxTccr0A, ((uint8_t)compB_p), MCU_TIMER0_OUTPUT_B_MODE_BIT_POS);

    // Update registers
    MCU_TIMER0_CTRL_A_REG          = auxTccr0A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TIMER0_MODULE);
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

void weakened timer0CompareACallback(void)
{
    return;
}

void weakened timer0CompareBCallback(void)
{
    return;
}

void weakened timer0OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! @cond
//!

ISR(TIMER0_COMPA_vect)
{
    timer0CompareACallback();
}

ISR(TIMER0_COMPB_vect)
{
    timer0CompareBCallback();
}

ISR(TIMER0_OVF_vect)
{
    timer0OverflowCallback();
}

//!
//! @endcond
//!

// =============================================================================
// End of file (timer0.cpp)
// =============================================================================
