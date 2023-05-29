//!
//! \file           systemStatus.cpp
//! \brief          System function support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-27
//! \version        23.04
//! \copyright      license
//! \details        This file provides support to system-wide features for all
//!                     modules of the Funsape AVR8 Library
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "systemStatus.hpp"
#if !defined(__SYSTEM_STATUS_HPP)
#    error "Header file is corrupted!"
#elif __SYSTEM_STATUS_HPP != 2304
#    error "Version mismatch between source and header files!"
#endif

#include <util/atomic.h>

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

SystemStatus systemStatus;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

SystemStatus::SystemStatus(void)
{
    // Reset data members
    this->_cpuClockValue    = F_CPU;
    this->_sourceClockValue = F_CPU;
    this->_clockPrescaler   = ClockPrescaler::PRESCALER_1;
    this->_stopwatchMark    = 0;
    this->_stopwatchHalted  = false;

    // Return successfully
    this->_lastError        = Error::NONE;
    return;
}

SystemStatus::~SystemStatus(void)
{
    // Return successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t SystemStatus::setClockPrescaler(ClockPrescaler prescaler_p)
{
    uint8_t aux8 = 0;
    uint16_t aux16 = 0;

    // Decode prescaler
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

uint32_t SystemStatus::getCpuClock(void)
{
    // Returns value
    return this->_cpuClockValue;
}

Error SystemStatus::getLastError(void)
{
    // Returns value
    return this->_lastError;
}

uint32_t SystemStatus::readStopwatch(void)
{
    // Returns value
    return this->_stopwatchValue;
}

void SystemStatus::resumeStopwatch(void)
{
    // Resumes stopwatch
    this->_stopwatchHalted = false;

    // Returns successfully
    return;
}

void SystemStatus::pauseStopwatch(void)
{
    // Pauses stopwatch
    this->_stopwatchHalted = true;

    // Returns successfully
    return;
}

void SystemStatus::resetStopwatch(void)
{
    // Resets stopwatch
    this->_stopwatchValue = 0;
    this->_stopwatchMark = 0;

    // Returns successfully
    return;
}

void SystemStatus::setStopwatchMark(void)
{
    // Sets stopwatch mark
    this->_stopwatchMark = this->_stopwatchValue;

    // Returns successfully
    return;
}

void SystemStatus::incrementStopwatch(void)
{
    // Increments stopwatch value
    if(!this->_stopwatchHalted) {
        this->_stopwatchValue++;
    }

    // Returns successfully
    return;
}

uint32_t SystemStatus::getElapsedTime(bool_t setNewMark)
{
    // Local variables
    uint32_t start = this->_stopwatchMark;
    uint32_t current = this->_stopwatchValue;
    uint32_t elapsed = 0;

    // Evaluate time elapsed between marks
    elapsed = (current > start) ? (current - start) : (((0xFFFFFFFF - start)  + current) + 1);

    // Sets new stopwatch mark
    if(setNewMark) {
        this->_stopwatchMark = current;
    }

    // Returns value
    return elapsed;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

// =============================================================================
// Class public methods
// =============================================================================

// NONE
