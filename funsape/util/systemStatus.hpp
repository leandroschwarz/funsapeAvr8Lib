//!
//! \file           systemStatus.hpp
//! \brief          System function support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-27
//! \version        23.04
//! \copyright      license
//! \details        This file provides support to system-wide features for all
//!                     modules of the Funsape AVR8 Library
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __SYSTEM_STATUS_HPP
#define __SYSTEM_STATUS_HPP             2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __SYSTEM_STATUS_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// SystemStatus Class
// =============================================================================

class SystemStatus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ///////////////    SYSTEM CLOCK PRESCALER    /////////////////     //
    //!
    //! \brief          System clock prescaler
    //! \details        Long description
    //!
    enum class ClockPrescaler {
        PRESCALER_1                     = 0,
        PRESCALER_2                     = 1,
        PRESCALER_4                     = 2,
        PRESCALER_8                     = 3,
        PRESCALER_32                    = 4,
        PRESCALER_64                    = 5,
        PRESCALER_128                   = 6,
        PRESCALER_256                   = 7,
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    SystemStatus(
            void
    );

    ~SystemStatus(
            void
    );

    // -------------------------------------------------------------------------
    // Operator overloading ----------------------------------------------------
public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
    //!
    //! \brief          Set system clock prescaler
    //! \details        Set system clock prescaler
    //! \param          prescaler_p             Param description
    //! \return         bool_t                  Return info
    //!
    bool_t setClockPrescaler(
            ClockPrescaler prescaler_p
    );

    //!
    //! \brief          Returns CPU clock
    //! \details        Long description
    //! \return         uint32_t                Return info
    //!
    uint32_t getCpuClock(
            void
    );

    //     //////////////////////    STOPWATCH     //////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         uint32_t              Return info
    //!
    uint32_t readStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void resumeStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void pauseStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void resetStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void setStopwatchMark(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void incrementStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    inlined void stopStopwatch(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    inlined void startStopwatch(
            void
    );

    //!
    //! \brief          Returns elapsed time between marks
    //! \details        Long description
    //! \param          setNewMark              Erase old time mark
    //! \return         uint32_t                Return info
    //!
    uint32_t getElapsedTime(       //
            bool_t setNewMark = true
    );

    //     ////////////////////     CHECK STATUS     ////////////////////     //
    //!
    //! \brief          Returns last error
    //! \details        Returns last error
    //! \return         Error                   Return info
    //!
    Error getLastError(
            void
    );

private:
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          customMark             Param description
    //! \return         uint32_t              Return info
    //!
    uint32_t _elapsedTime(
            uint32_t customMark
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:
    // NONE

private:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
    uint32_t        _sourceClockValue;
    ClockPrescaler  _clockPrescaler;
    uint32_t        _cpuClockValue;

    //     //////////////////////    STOPWATCH     //////////////////////     //
    vuint32_t       _stopwatchValue;
    vuint32_t       _stopwatchMark;
    bool_t          _stopwatchHalted    : 1;

    //     ////////////////////     CHECK STATUS     ////////////////////     //
    Error           _lastError;

protected:
    // NONE

}; // class SystemStatus

// =============================================================================
// SystemStatus - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// SystemStatus - Class inline function definitions
// =============================================================================

inlined void SystemStatus::stopStopwatch(void)
{
    this->pauseStopwatch();

    return;
}

inlined void SystemStatus::startStopwatch(void)
{
    this->resetStopwatch();
    this->resumeStopwatch();

    return;
}

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

//!
//! \brief          Brief description
//! \details        Long description
//!
extern SystemStatus systemStatus;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __SYSTEM_STATUS_HPP

// =============================================================================
// END OF FILE
// =============================================================================
