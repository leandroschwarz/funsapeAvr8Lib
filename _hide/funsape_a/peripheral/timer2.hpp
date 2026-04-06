/**
 *******************************************************************************
 * @file            timer2.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __TIMER2_HPP
#define __TIMER2_HPP                    2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [timer2.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __TIMER2_HPP
#   error [timer2.hpp] Error 2 - Build mismatch between file (timer2.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [timer2.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __TIMER2_HPP
#   error [timer2.hpp] Error 5 - Build mismatch between file (timer2.hpp) and library dependency (debug.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Peripherals
 * @brief           Microcontroller peripherals.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Timer2"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Timer2
 * @brief           Timer/Counter 2 (TIMER2) controller module.
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

/**
 * @brief           TIMER2 compare A match interrupt callback function.
 * @details         This function is called when the TIMER2 compare A match
 *                      interrupt is treated. It is a weak function that can be
 *                      overwritten by user code.
*/
void timer2CompareACallback(void);

/**
 * @brief           TIMER2 compare B match interrupt callback function.
 * @details         This function is called when the TIMER2 compare B match
 *                      interrupt is treated. It is a weak function that can be
 *                      overwritten by user code.
*/
void timer2CompareBCallback(void);

/**
 * @brief           TIMER2 overflow interrupt callback function.
 * @details         This function is called when the TIMER2 overflow interrupt
 *                      is treated. It is a weak function that can be
 *                      overwritten by user code.
*/
void timer2OverflowCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Timer2 class.
 * @details         This class manages the Timer/Counter 2 (TIMER2) peripheral.
 * @attention       The @ref timer2 instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Timer2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        ClockSource
     * @brief       Clock prescaler enumeration.
     * @details     Clock prescaler options associated with TIMER2.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class ClockSource : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, timer is off.
        PRESCALER_1                     = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock.
        PRESCALER_8                     = 2,    //!< Timer clock frequency will be CPU clock divided by 8.
        PRESCALER_32                    = 3,    //!< Timer clock frequency will be CPU clock divided by 32.
        PRESCALER_64                    = 4,    //!< Timer clock frequency will be CPU clock divided by 64.
        PRESCALER_128                   = 5,    //!< Timer clock frequency will be CPU clock divided by 128.
        PRESCALER_256                   = 6,    //!< Timer clock frequency will be CPU clock divided by 256.
        PRESCALER_1024                  = 7     //!< Timer clock frequency will be CPU clock divided by 1024.
    };

    /**
     * @enum        Mode
     * @brief       Operation mode enumeration.
     * @details     Operation mode options associated with TIMER2.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR2x = immediate / TOV Flag = 0xFF).
        PWM_PHASE_CORRECTED_MAX         = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR2x = 0xFF / TOV Flag = 0x00).
        CTC_OCRA                        = 2,    //!< CTC mode (direction = UP / TOP = OCR2A / UPDATE OCR2x = immediate / TOV Flag = 0xFF).
        PWM_FAST_MAX                    = 3,    //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 4,
        PWM_PHASE_CORRECTED_OCRA        = 5,    //!< PWM mode fast (direction = UP / TOP = OCR2A / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 6,
        PWM_FAST_OCRA                   = 7,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR2A / UPDATE OCR2x = OCR2A / TOV Flag = 0x00).
    };

    /**
     * @enum        OutputMode
     * @brief       Output mode enumeration.
     * @details     Output Mmode options associated with TIMER2.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class OutputMode : uint8_t {
        NORMAL_GPIO_OPERATION           = 0,    //!< OC2x disabled. Normal GPIO port operation.
        TOGGLE_ON_COMPARE               = 1,    //!< OC2x will toggle on OCR2x compare match.
        CLEAR_ON_COMPARE                = 2,    //!< OC2x will clear on OCR2x compare match.
        SET_ON_COMPARE                  = 3,    //!< OC2x will set on OCR2x compare match.
        NON_INVERTING_MODE              = 2,    //!< OC2x will produce a non-inverted PWM signal.
        INVERTING_MODE                  = 3,    //!< OC2x will produce a inverted PWM signal.
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Timer2 class constructor.
     * @details     Creates a Timer2 object. The object is loaded with the
     *                  default register values: @ref ClockSource::DISABLED and
     *                  @ref Mode::NORMAL. The object still must be initialized
     *                  before use.
     * @see         init(const Mode mode_p, const ClockSource clockSource_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Timer2(
            void
    );

    /**
     * @brief       Timer2 class destructor.
     * @details     Destroys a Timer2 object.
    */
    ~Timer2(
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
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
    */
    Error           getLastError(
            void
    );

    /**
     * @brief       Initializes the Timer2 module.
     * @details     Initializes the Timer2 module.
     * @param[in]   mode_p              Operation mode.
     * @param[in]   clockSource_p       Clock source and prescaler.
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
    bool_t init(
            const Mode mode_p,
            const ClockSource clockSource_p
    );

    /**
     * @brief       Configures the clock source and prescaler.
     * @details     Configures the clock source and prescaler.
     * @param[in]   clockSource_p       Clock source and prescaler.
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
    bool_t setClockSource(
            const ClockSource clockSource_p
    );

    /**
     * @brief       Configures the operation mode.
     * @details     Configures the operation mode.
     * @param[in]   mode_p              Operation mode.
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
    bool_t setMode(
            const Mode mode_p
    );

    /**
     * @brief       Configures the output compare pins mode.
     * @details     Configures the desired behavior of @c OC2x pins during
     *                  compare match.
     * @param[in]   compA_p             Behavior of @c OC2A pin during a compare
     *                                      A match.
     * @param[in]   compB_p             Behavior of @c OC2B pin during a compare
     *                                      B match.
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
    bool_t setOutputMode(
            const OutputMode compA_p,
            const OutputMode compB_p
    );

    //     /////////////////////     COMPARE A     //////////////////////     //

    /**
     * @brief       Activates Compare A Match interrupt.
     * @details     Activates Compare A Match interrupt. If an interrupt request
     *                  is pending, an interrupt will be triggered when
     *                  activated. In most applications, it is recommended to
     *                  ignore an old interrupt request prior to activate the
     *                  interrupt. This can be done by calling
     *                  @ref clearCompareAInterruptRequest() function
     *                  imediatelly before activating the interrupt.
    */
    void inlined activateCompareAInterrupt(
            void
    );

    /**
     * @brief       Clears Compare A Match interrupt flag.
     * @details     Clears Compare A Match interrupt flag, dismissing any
     *                  pending interrupt request.
    */
    void inlined clearCompareAInterruptRequest(
            void
    );

    /**
     * @brief       Deactivates Compare A Match interrupt.
     * @details     Deactivates Compare A Match interrupt. This function does
     *                  not clears any pending interrupt request.
    */
    void inlined deactivateCompareAInterrupt(
            void
    );

    /**
     * @brief       Forces a Compare A Match condition on output pin.
     * @details     Forces a Compare A Match condition on output pin. No
     *                  interrupt will be generated.
    */
    void inlined forceCompareA(
            void
    );

    /**
     * @brief       Returns the Compare A Match value.
     * @details     Returns the Compare A Match value at @c OCR2A register.
     * @return      the value of the Compare A Match, i.e. the value of @c OCR2A
     *                  register.
    */
    uint8_t inlined getCompareAValue(
            void
    );

    /**
     * @brief       Sets the Compare A Match value.
     * @details     Sets the Compare A Match value at @c OCR2A register.
     * @param[in]   value_p             Compare A Match value.
    */
    void inlined setCompareAValue(
            cuint8_t value_p
    );

    //     /////////////////////     COMPARE B     //////////////////////     //

    /**
     * @brief       Activates Compare B Match interrupt.
     * @details     Activates Compare B Match interrupt. If an interrupt request
     *                  is pending, an interrupt will be triggered when
     *                  activated. In most applications, it is recommended to
     *                  ignore an old interrupt request prior to activate the
     *                  interrupt. This can be done by calling
     *                  @ref clearCompareBInterruptRequest() function
     *                  imediatelly before activating the interrupt.
    */
    void inlined activateCompareBInterrupt(
            void
    );

    /**
     * @brief       Clears Compare B Match interrupt flag.
     * @details     Clears Compare B Match interrupt flag, dismissing any
     *                  pending interrupt request.
    */
    void inlined clearCompareBInterruptRequest(
            void
    );

    /**
     * @brief       Deactivates Compare B Match interrupt.
     * @details     Deactivates Compare B Match interrupt. This function does
     *                  not clears any pending interrupt request.
    */
    void inlined deactivateCompareBInterrupt(
            void
    );

    /**
     * @brief       Forces a Compare B Match condition on output pin.
     * @details     Forces a Compare B Match condition on output pin. No
     *                  interrupt will be generated.
    */
    void inlined forceCompareB(
            void
    );

    /**
     * @brief       Returns the Compare B Match value.
     * @details     Returns the Compare B Match value at @c OCR2B register.
     * @return      the value of the Compare B Match, i.e. the value of @c OCR2B
     *                  register.
    */
    uint8_t inlined getCompareBValue(
            void
    );

    /**
     * @brief       Sets the Compare B Match value.
     * @details     Sets the Compare B Match value at @c OCR2B register.
     * @param[in]   value_p             Compare B Match value.
    */
    void inlined setCompareBValue(
            cuint8_t value_p
    );

    //     //////////////////////     OVERFLOW    ///////////////////////     //

    /**
     * @brief       Activates Timer Overflow interrupt.
     * @details     Activates Timer Overflow interrupt. If an interrupt request
     *                  is pending, an interrupt will be triggered when
     *                  activated. In most applications, it is recommended to
     *                  ignore an old interrupt request prior to activate the
     *                  interrupt. This can be done by calling
     *                  @ref clearOverflowInterruptRequest() function
     *                  imediatelly before activating the interrupt.
    */
    void inlined activateOverflowInterrupt(
            void
    );

    /**
     * @brief       Clears Timer Overflow interrupt flag.
     * @details     Clears Timer Overflow interrupt flag, dismissing any
     *                  pending interrupt request.
    */
    void inlined clearOverflowInterruptRequest(
            void
    );

    /**
     * @brief       Deactivates Timer Overflow interrupt.
     * @details     Deactivates Timer Overflow interrupt. This function does not
     *                  clears any pending interrupt request.
    */
    void inlined deactivateOverflowInterrupt(
            void
    );

    /**
     * @brief       Returns the Timer Counter value.
     * @details     Returns the Timer Counter value at @c TCNT2 register.
     * @return      the value of the Timer Counter, i.e. the value of @c TCNT2
     *                  register.
    */
    uint8_t inlined getCounterValue(
            void
    );

    /**
     * @brief       Sets the Timer Counter value.
     * @details     Sets the Timer Counter value at @c TCNT2 register.
     * @param[in]   value_p             Timer Counter value.
    */
    void inlined setCounterValue(
            cuint8_t value_p
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //

    ClockSource     _clockSource;               //!< Clock source and prescaler.
    Mode            _mode;                      //!< Operation mode.

protected:
    // NONE

}; // class Timer2

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////////     COMPARE A     ////////////////////////     //

void inlined Timer2::activateCompareAInterrupt(void)
{
    setBit(TIMSK2, OCIE2A);
    return;
}

void inlined Timer2::clearCompareAInterruptRequest(void)
{
    setBit(TIFR2, OCF2A);
    return;
}

void inlined Timer2::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK2, OCIE2A);
    return;
}

void inlined Timer2::forceCompareA(void)
{
    setBit(TCCR2B, FOC2A);
    return;
}

uint8_t inlined Timer2::getCompareAValue(void)
{
    return OCR2A;
}

void inlined Timer2::setCompareAValue(cuint8_t value_p)
{
    OCR2A = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer2::activateCompareBInterrupt(void)
{
    setBit(TIMSK2, OCIE2B);
    return;
}

void inlined Timer2::clearCompareBInterruptRequest(void)
{
    setBit(TIFR2, OCF2B);
    return;
}

void inlined Timer2::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK2, OCIE2B);
    return;
}

void inlined Timer2::forceCompareB(void)
{
    setBit(TCCR2B, FOC2B);
    return;
}

uint8_t inlined Timer2::getCompareBValue(void)
{
    return OCR2B;
}

void inlined Timer2::setCompareBValue(cuint8_t value_p)
{
    OCR2B = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer2::activateOverflowInterrupt(void)
{
    setBit(TIMSK2, TOIE2);
    return;
}

void inlined Timer2::clearOverflowInterruptRequest(void)
{
    setBit(TIFR2, TOV2);
    return;
}

void inlined Timer2::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK2, TOIE2);
    return;
}

uint8_t inlined Timer2::getCounterValue(void)
{
    return TCNT2;
}

void inlined Timer2::setCounterValue(cuint8_t value_p)
{
    TCNT2 = value_p;
    return;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             timer2
 * @brief           Timer2 peripheral handler object.
 * @details         Timer2 peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern Timer2 timer2;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Timer2"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
* @}
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
*/

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __TIMER2_HPP

// =============================================================================
// End of file (timer2.hpp)
// =============================================================================
