/**
 *******************************************************************************
 * @file            systemStatus.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           System function support.
 * @details         This file provides support to system-wide features for all
 *                      modules of the FunSAPE++ AVR8 Library.
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

#include "systemStatus.hpp"
#if !defined(__SYSTEM_STATUS_HPP)
#    error Error 1 - Header file (systemStatus.hpp) is missing or corrupted!
#elif __SYSTEM_STATUS_HPP != 2508
#    error Error 6 - Build mismatch between header file (systemStatus.hpp) and source file (systemStatus.cpp)!
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

SystemStatus systemStatus;

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

SystemStatus::SystemStatus(uint32_t mainClock_p)
{
    // Reset data members
    this->_initialized                  = false;
    this->_cpuClockValue                = 0;
    this->_sourceClockValue             = 0;
    this->_clockPrescaler               = ClockPrescaler::PRESCALER_1;
    this->_stopwatchMark                = 0;
    this->_stopwatchValue               = 0;
    this->_stopwatchHalted              = false;

    // Checks for errors
    if(mainClock_p == 0) {
        this->_lastError                = Error::CLOCK_SPEED_TOO_LOW;
        return;
    }

    // Updates data members
    this->_sourceClockValue             = mainClock_p;
    this->_cpuClockValue                = this->_sourceClockValue;
    this->_initialized                  = true;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

SystemStatus::~SystemStatus(void)
{
    // Returns successfully
    return;
}

//     ///////////////     SYSTEM CLOCK AND PRESCALER     ///////////////     //

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////     SYSTEM CLOCK AND PRESCALER     ///////////////     //

bool_t SystemStatus::getCpuClock(uint32_t *cpuClockValue_p)
{
    // Checks for errors
    if(!isPointerValid(cpuClockValue_p)) {
        // Returns error
        this->_lastError                = Error::ARGUMENT_POINTER_NULL;
        return false;
    }
    // Updates value
    *cpuClockValue_p                    = this->_cpuClockValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

bool_t SystemStatus::setClockPrescaler(const ClockPrescaler prescaler_p)
{
    // Local variables
    uint8_t aux8 = 0;
    uint16_t aux16 = 0;

    // Decodes prescaler
    switch(prescaler_p) {
    case ClockPrescaler::PRESCALER_1:
        aux8 = 0;
        aux16 = 1;
        break;
    case ClockPrescaler::PRESCALER_2:
        aux8 = 1;
        aux16 = 2;
        break;
    case ClockPrescaler::PRESCALER_4:
        aux8 = 2;
        aux16 = 4;
        break;
    case ClockPrescaler::PRESCALER_8:
        aux8 = 3;
        aux16 = 8;
        break;
    case ClockPrescaler::PRESCALER_32:
        aux8 = 4;
        aux16 = 32;
        break;
    case ClockPrescaler::PRESCALER_64:
        aux8 = 5;
        aux16 = 64;
        break;
    case ClockPrescaler::PRESCALER_128:
        aux8 = 6;
        aux16 = 128;
        break;
    case ClockPrescaler::PRESCALER_256:
        aux8 = 7;
        aux16 = 256;
        break;
    default:
        this->_lastError = Error::CLOCK_PRESCALER_NOT_SUPPORTED;
        return false;
    }

    // Changes system clock prescaler
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        CLKPR = 0b10000000;
        CLKPR = aux8;
    }

    // Verifies if the change was successful
    doNop();
    if((CLKPR & 0x7F) != aux8) {
        this->_lastError = Error::CLOCK_PRESCALER_CHANGE_FAILED;
        return false;
    }

    // Update member data
    this->_clockPrescaler = prescaler_p;
    this->_cpuClockValue = this->_sourceClockValue / aux16;

    // Return successfully
    this->_lastError = Error::NONE;
    return true;
}

//     ////////////////////////    STOPWATCH     ////////////////////////     //
