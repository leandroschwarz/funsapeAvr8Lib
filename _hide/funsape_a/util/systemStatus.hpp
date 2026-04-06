/**
 *******************************************************************************
 * @file            systemStatus.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __SYSTEM_STATUS_HPP
#define __SYSTEM_STATUS_HPP             2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [systemStatus.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __SYSTEM_STATUS_HPP
#   error [systemStatus.hpp] Error 2 - Build mismatch between file (systemStatus.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

// NONE

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Util"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Util
 * @brief           Utilities.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Util/System_Status"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      System_Status
 * @brief           System Status and Control controller module.
 * @{
*/

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

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           SystemStatus class.
 * @details         This class manages the System Status and Controls the System
 *                      Clock.
 * @attention       The @ref systemStatus instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class SystemStatus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        ClockPrescaler
     * @brief       System Clock prescaler enumeration.
     * @details     Clock prescaler options associated with MCU System.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class ClockPrescaler : uint8_t {
        PRESCALER_1                     = 0,    //!< Prescaler off. System clock is not divided.
        PRESCALER_2                     = 1,    //!< I/O clock frequency will be System Clock divided by 2.
        PRESCALER_4                     = 2,    //!< I/O clock frequency will be System Clock divided by 4.
        PRESCALER_8                     = 3,    //!< I/O clock frequency will be System Clock divided by 8.
        PRESCALER_32                    = 4,    //!< I/O clock frequency will be System Clock divided by 32.
        PRESCALER_64                    = 5,    //!< I/O clock frequency will be System Clock divided by 64.
        PRESCALER_128                   = 6,    //!< I/O clock frequency will be System Clock divided by 128.
        PRESCALER_256                   = 7,    //!< I/O clock frequency will be System Clock divided by 256.
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       SystemStatus class constructor.
     * @details     Creates a SystemStatus object. The object still must be
     *                  initialized before use.
     * @param[in]   mainClock_p         Value of the system main clock.
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    SystemStatus(
            cuint32_t mainClock_p = F_CPU
    );

    /**
     * @brief       SystemStatus class destructor.
     * @details     Destroys a SystemStatus object.
    */
    ~SystemStatus(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

public:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //

    /**
     * @brief       Returns CPU clock.
     * @details     Returns the value of the main CPU clock.
     * @param[out]  cpuClockValue_p     Pointer to store the clock value.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t getCpuClock(
            uint32_t *cpuClockValue_p
    );

    /**
     * @brief       Set system clock prescaler.
     * @details     Set system clock prescaler.
     * @param[in]   prescaler_p         Value of the system clock prescaler.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setClockPrescaler(
            const ClockPrescaler prescaler_p
    );

    //     //////////////////////    STOPWATCH     //////////////////////     //

    /**
     * @brief       Returns the elapsed time between marks.
     * @details     Returns the elapsed time between marks.
     * @param[in]   setNewMark_p        Erase old time mark.
     * @return      uint32_t            Elapsed time between marks.
    */
    uint32_t inlined getElapsedTime(
            cbool_t setNewMark_p = true
    );

    /**
     * @brief       Gets the value of the stopwatch counter.
     * @details     Gets the value of the stopwatch counter.
     * @param[out]  stopwatchValue_p    Pointer to store the clock value.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined getStopwatchValue(
            uint32_t *stopwatchValue_p
    );

    /**
     * @brief       Increments the stopwatch counter.
     * @details     Increments the stopwatch counter.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined incrementStopwatch(
            void
    );

    /**
     * @brief       Resets the stopwatch counter.
     * @details     Resets the stopwatch counter.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined resetStopwatch(
            void
    );

    /**
     * @brief       Sets a time marker at the stopwatch.
     * @details     Sets a time marker at the stopwatch.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined setStopwatchMark(
            void
    );

    /**
     * @brief       Starts the stopwatch counter.
     * @details     Starts the stopwatch counter.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined startStopwatch(
            void
    );

    /**
     * @brief       Stops the stopwatch counter.
     * @details     Stops the stopwatch counter.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t inlined stopStopwatch(
            void
    );

    //     ////////////////////     CHECK STATUS     ////////////////////     //

    //!
    //! \brief      Returns the last error.
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation.
    //!
    Error inlined getLastError(
            void
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //

    uint32_t        _sourceClockValue;
    ClockPrescaler  _clockPrescaler;
    uint32_t        _cpuClockValue;

    //     //////////////////////    STOPWATCH     //////////////////////     //

    bool_t          _initialized                : 1;
    vuint32_t       _stopwatchValue;
    vuint32_t       _stopwatchMark;
    bool_t          _stopwatchHalted            : 1;

    //     ////////////////////     CHECK STATUS     ////////////////////     //

    Error           _lastError;

}; // class SystemStatus

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ////////////////////////    STOPWATCH     ////////////////////////     //

inlined bool_t SystemStatus::getStopwatchValue(uint32_t *stopwatchValue_p)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }
    if(!isPointerValid(stopwatchValue_p)) {
        // Returns error
        this->_lastError                = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Updates value
    *stopwatchValue_p                   = this->_stopwatchValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::incrementStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Increments stopwatch value
    if(!this->_stopwatchHalted) {
        this->_stopwatchValue++;
    }

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::resetStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Resets stopwatch
    this->_stopwatchValue               = 0;
    this->_stopwatchMark                = 0;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

bool_t SystemStatus::setStopwatchMark(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Sets stopwatch mark
    this->_stopwatchMark                = this->_stopwatchValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::stopStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Pauses stopwatch
    this->_stopwatchHalted              = true;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::startStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Resumes stopwatch
    this->_stopwatchHalted              = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

//     //////////////////////     CHECK STATUS     //////////////////////     //

Error inlined SystemStatus::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             systemStatus
 * @brief           SystemStatus peripheral handler object.
 * @details         SystemStatus peripheral handler object. Use this object to
 *                      handle the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern SystemStatus systemStatus;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Utils/System_Status"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
* @}
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Utils"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
*/

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __SYSTEM_STATUS_HPP

// =============================================================================
// End of file (systemStatus.hpp)
// =============================================================================
