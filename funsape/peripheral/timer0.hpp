//!
//! ****************************************************************************
//! @file           timer0.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __TIMER0_HPP
#define __TIMER0_HPP                    2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [timer0.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __TIMER0_HPP
#   error [timer0.hpp] Error 2 - Build mismatch between file (timer0.hpp) and global definitions file!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [timer0.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __TIMER0_HPP
#   error [timer0.hpp] Error 5 - Build mismatch between file (timer0.hpp) and library dependency (debug.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// =============================================================================
// Checks peripheral existance
// =============================================================================

#if !defined(MCU_TIMER0_PERIPHERAL_EXISTS)
#   error [timer0.hpp] Error X - Peripheral TIMER0 is not avalilable in selected device!
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Peripherals
//! @brief          Microcontroller peripherals.
//! @{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Timer0" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Timer0
//! @brief          Timer/Counter 0 (TIMER0) controller module.
//! @{
//!

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
// Interrupt callback functions declarations
// =============================================================================

//!
//! @brief          TIMER0 compare A match interrupt callback function.
//! @details        This function is called when the TIMER0 compare A match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0CompareACallback(void);

//!
//! @brief          TIMER0 compare B match interrupt callback function.
//! @details        This function is called when the TIMER0 compare B match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0CompareBCallback(void);

//!
//! @brief          TIMER0 overflow interrupt callback function.
//! @details        This function is called when the TIMER0 overflow interrupt
//!                     is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0OverflowCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! @brief          Timer0 class
//! @details        This class manages the Timer/Counter 0 (TIMER0) peripheral.
//! @attention      The @ref timer0 instance of this class is already defined as
//!                     a singleton global object.
//!
class Timer0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //!
    //! @enum       ClockSource
    //! @brief      Clock prescaler enumeration.
    //! @details    Clock prescaler options associated with TIMER0.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED = 0,           //!< Disables clock, timer is off.
        PRESCALER_1 = 1,        //!< Disables prescaler, timer clock frequency will be equal to CPU clock.
        PRESCALER_8 = 2,        //!< Timer clock frequency will be CPU clock divided by 8.
        PRESCALER_64 = 3,       //!< Timer clock frequency will be CPU clock divided by 64.
        PRESCALER_256 = 4,      //!< Timer clock frequency will be CPU clock divided by 256.
        PRESCALER_1024 = 5,     //!< Timer clock frequency will be CPU clock divided by 1024.
        T0_FALLING_EDGE = 6,    //!< Timer clock will be based on the falling edge of a signal placed on @c T0 pin.
        T0_RISING_EDGE = 7      //!< Timer clock will be based on the rising edge of a signal placed on @c T0 pin.
    };

    //!
    //! @enum       Mode
    //! @brief      Operation mode enumeration.
    //! @details    Operation mode options associated with TIMER0.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL = 0,                     //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR0x = immediate / TOV Flag = 0xFF).
        PWM_PHASE_CORRECTED_MAX = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR0x = 0xFF / TOV Flag = 0x00).
        CTC_OCRA = 2,                   //!< CTC mode (direction = UP / TOP = MCU_TIMER0_OCR0A_REG / UPDATE OCR0x = immediate / TOV Flag = 0xFF).
        PWM_FAST_MAX = 3,               //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 4,
        PWM_PHASE_CORRECTED_OCRA = 5,   //!< PWM mode fast (direction = UP / TOP = MCU_TIMER0_OCR0A_REG / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 6,
        PWM_FAST_OCRA = 7,              //!< PWM mode with phase correction (direction = DOWN then UP / TOP = MCU_TIMER0_OCR0A_REG / UPDATE OCR0x = MCU_TIMER0_OCR0A_REG / TOV Flag = 0x00).
    };

    //!
    //! @enum       OutputMode
    //! @brief      Output mode enumeration.
    //! @details    Output Mmode options associated with TIMER0.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL_GPIO_OPERATION = 0,      //!< OC0x disabled. Normal GPIO port operation.
        TOGGLE_ON_COMPARE = 1,          //!< OC0x will toggle on OCR0x compare match.
        CLEAR_ON_COMPARE = 2,           //!< OC0x will clear on OCR0x compare match.
        SET_ON_COMPARE = 3,             //!< OC0x will set on OCR0x compare match.
        NON_INVERTING_MODE = 2,         //!< OC0x will produce a non-inverted PWM signal.
        INVERTING_MODE = 3,             //!< OC0x will produce a inverted PWM signal.
    };

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Constructors ------------------------------------------------------------

public:
    //!
    //! @brief      Timer0 class destructor.
    //! @details    Destroys a Timer0 object.
    //!
    ~Timer0(
            void
    );

private:
    //!
    //! @brief      Timer0 class constructor.
    //! @details    Creates a Timer0 object. The object is loaded with the
    //!                 default register values:
    //!                 @ref Timer0::ClockSource::DISABLED and
    //!                 @ref Timer0::Mode::NORMAL. The object still must be
    //!                 initialized before use.
    //! @see        init(const Timer0::Mode mode_p, const Timer0::ClockSource clockSource_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                           |
    //! |: ----------------|: ---------------------------------|
    //! | @ref Error::NONE | Success. No errors were detected. |
    //!
    Timer0(
            void
    );

    //!
    //! @brief      Copy constructor (deleted).
    //! @details    Deleted to prevent cloning the Singleton instance.
    //!
    Timer0(
            const Timer0 &
    ) = delete;

    //!
    //! @brief      Copy assignment operator (deleted).
    //! @details    Deleted to prevent assignment of the Singleton instance.
    //!
    Timer0 &operator=(
            const Timer0 &
    ) = delete;

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

public:
    //     ///////////////////    SINGLETON ACCESS    ///////////////////     //

    //!
    //! @brief      Returns the Singleton instance.
    //! @details    Provides global access to the single instance of the Timer0
    //!                 class. This method is tightly inlined to ensure
    //!                 zero-overhead during execution.
    //! @return     Reference to the single Timer0 instance.
    //!
    static inlined Timer0 &getInstance(
            void
    );

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    //!
    //! @brief      Returns the last error.
    //! @details    Returns the last error.
    //! @return     @ref Error          Error status of the last operation.
    //!
    Error inlined getLastError(
            void
    ) const;

    //!
    //! @brief      Initializes the Timer0 module.
    //! @details    Initializes the Timer0 module.
    //! @param[in]  mode_p              Operation mode.
    //! @param[in]  clockSource_p       Clock source and prescaler.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Timer0::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t init(
            const Timer0::Mode mode_p,
            const Timer0::ClockSource clockSource_p
    );

    //!
    //! @brief       Configures the clock source and prescaler.
    //! @details     Configures the clock source and prescaler.
    //! @param[in]   clockSource_p       Clock source and prescaler.
    //! @retval      true                if success.
    //! @retval      false               if an error occurred. Retrieve the error
    //!                                      by calling
    //!                                     @ref Timer0::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setClockSource(
            const Timer0::ClockSource clockSource_p
    );

    //!
    //! @brief      Configures the operation mode.
    //! @details    Configures the operation mode.
    //! @param[in]  mode_p              Operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Timer0::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setMode(
            const Timer0::Mode mode_p
    );

    //!
    //! @brief      Configures the output compare pins mode.
    //! @details    Configures the desired behavior of @c OC0x pins during
    //!                 compare match.
    //! @param[in]  compA_p             Behavior of @c OC0A pin during a compare
    //!                                     A match.
    //! @param[in]  compB_p             Behavior of @c OC0B pin during a compare
    //!                                     B match.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Timer0::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setOutputMode(
            const Timer0::OutputMode compA_p,
            const Timer0::OutputMode compB_p
    );

    //     /////////////////////     COMPARE A     //////////////////////     //

    //!
    //! @brief      Activates Compare A Match interrupt.
    //! @details    Activates Compare A Match interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling
    //!                 @ref Timer0::clearCompareAInterruptRequest() function
    //!                 imediatelly before activating the interrupt.
    //!
    void inlined activateCompareAInterrupt(
            void
    ) const;

    //!
    //! @brief      Clears Compare A Match interrupt flag.
    //! @details    Clears Compare A Match interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearCompareAInterruptRequest(
            void
    ) const;

    //!
    //! @brief      Deactivates Compare A Match interrupt.
    //! @details    Deactivates Compare A Match interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateCompareAInterrupt(
            void
    ) const;

    //!
    //! @brief      Forces a Compare A Match condition on output pin.
    //! @details    Forces a Compare A Match condition on output pin. No
    //!                 interrupt will be generated.
    //!
    void inlined forceCompareA(
            void
    ) const;

    //!
    //! @brief      Returns the Compare A Match value.
    //! @details    Returns the Compare A Match value at @c OCR0A register.
    //! @return     the value of the Compare A Match, i.e. the value of @c OCR0A
    //!                 register.
    //!
    uint8_t inlined getCompareAValue(
            void
    ) const;

    //!
    //! @brief      Sets the Compare A Match value.
    //! @details    Sets the Compare A Match value at @c OCR0A register.
    //! @param[in]  value_p             Compare A Match value.
    //!
    void inlined setCompareAValue(
            cuint8_t value_p
    ) const;

    //     /////////////////////     COMPARE B     //////////////////////     //

    //!
    //! @brief      Activates Compare B Match interrupt.
    //! @details    Activates Compare B Match interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling
    //!                 @ref Timer0::clearCompareBInterruptRequest() function
    //!                 imediatelly before activating the interrupt.
    //!
    void inlined activateCompareBInterrupt(
            void
    ) const;

    //!
    //! @brief      Clears Compare B Match interrupt flag.
    //! @details    Clears Compare B Match interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearCompareBInterruptRequest(
            void
    ) const;

    //!
    //! @brief      Deactivates Compare B Match interrupt.
    //! @details    Deactivates Compare B Match interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateCompareBInterrupt(
            void
    ) const;

    //!
    //! @brief      Forces a Compare B Match condition on output pin.
    //! @details    Forces a Compare B Match condition on output pin. No
    //!                 interrupt will be generated.
    //!
    void inlined forceCompareB(
            void
    ) const;

    //!
    //! @brief      Returns the Compare B Match value.
    //! @details    Returns the Compare B Match value at @c OCR0B register.
    //! @return     the value of the Compare B Match, i.e. the value of @c OCR0B
    //!                 register.
    //!
    uint8_t inlined getCompareBValue(
            void
    ) const;

    //!
    //! @brief      Sets the Compare B Match value.
    //! @details    Sets the Compare B Match value at @c OCR0B register.
    //! @param[in]  value_p             Compare B Match value.
    //!
    void inlined setCompareBValue(
            cuint8_t value_p
    ) const;

    //     //////////////////////     OVERFLOW    ///////////////////////     //

    //!
    //! @brief      Activates Timer Overflow interrupt.
    //! @details    Activates Timer Overflow interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling
    //!                 @ref Timer0::clearOverflowInterruptRequest() function
    //!                 imediatelly before activating the interrupt.
    //!
    void inlined activateOverflowInterrupt(
            void
    ) const;

    //!
    //! @brief      Clears Timer Overflow interrupt flag.
    //! @details    Clears Timer Overflow interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearOverflowInterruptRequest(
            void
    ) const;

    //!
    //! @brief      Deactivates Timer Overflow interrupt.
    //! @details    Deactivates Timer Overflow interrupt. This function does not
    //!                 clears any pending interrupt request.
    //!
    void inlined deactivateOverflowInterrupt(
            void
    ) const;

    //!
    //! @brief      Returns the Timer Counter value.
    //! @details    Returns the Timer Counter value at @c TCNT0 register.
    //! @return     the value of the Timer Counter, i.e. the value of @c TCNT0
    //!                 register.
    //!
    uint8_t inlined getCounterValue(
            void
    ) const;

    //!
    //! @brief      Sets the Timer Counter value.
    //! @details    Sets the Timer Counter value at @c TCNT0 register.
    //! @param[in]  value_p             Timer Counter value.
    //!
    void inlined setCounterValue(
            cuint8_t value_p
    ) const;

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Properties --------------------------------------------------------------

private:
    //     /////////////////    SINGLETON INSTANCE     //////////////////     //
    static Timer0   _instance;                  //|< Static private instance

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //
    Timer0::ClockSource     _clockSource;       //!< Clock source and prescaler.
    Timer0::Mode            _mode;              //!< Operation mode.

protected:
    // NONE

}; // class Timer0

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////////    SINGLETON ACCESS    /////////////////////     //

Timer0 inlined &Timer0::getInstance(void)
{
    return Timer0::_instance;
}

//     ///////////////////////     COMPARE A     ////////////////////////     //

void inlined Timer0::activateCompareAInterrupt(void) const
{
    setBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_COMPA_BIT_OFFSET);
    return;
}

void inlined Timer0::clearCompareAInterruptRequest(void) const
{
    setBit(MCU_TIMER0_FLAG_REG, MCU_TIMER0_FLAG_COMPA_BIT_POS);
    return;
}

void inlined Timer0::deactivateCompareAInterrupt(void) const
{
    clrBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_COMPA_BIT_OFFSET);
    return;
}

void inlined Timer0::forceCompareA(void) const
{
    setBit(MCU_TIMER0_CTRL_B_REG, MCU_TIMER0_FORCE_COMPA_BIT_OFFSET);
    return;
}

uint8_t inlined Timer0::getCompareAValue(void) const
{
    return MCU_TIMER0_OCR0A_REG;
}

void inlined Timer0::setCompareAValue(cuint8_t value_p) const
{
    MCU_TIMER0_OCR0A_REG = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer0::activateCompareBInterrupt(void) const
{
    setBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_COMPB_BIT_OFFSET);
    return;
}

void inlined Timer0::clearCompareBInterruptRequest(void) const
{
    setBit(MCU_TIMER0_FLAG_REG, MCU_TIMER0_FLAG_COMPB_BIT_POS);
    return;
}

void inlined Timer0::deactivateCompareBInterrupt(void) const
{
    clrBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_COMPB_BIT_OFFSET);
    return;
}

void inlined Timer0::forceCompareB(void) const
{
    setBit(MCU_TIMER0_CTRL_B_REG, MCU_TIMER0_FORCE_COMPB_BIT_OFFSET);
    return;
}

uint8_t inlined Timer0::getCompareBValue(void) const
{
    return MCU_TIMER0_OCR0B_REG;
}

void inlined Timer0::setCompareBValue(cuint8_t value_p) const
{
    MCU_TIMER0_OCR0B_REG = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer0::activateOverflowInterrupt(void) const
{
    setBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_OVF_BIT_OFFSET);
    return;
}

void inlined Timer0::clearOverflowInterruptRequest(void) const
{
    setBit(MCU_TIMER0_FLAG_REG, MCU_TIMER0_FLAG_OVF_BIT_POS);
    return;
}

void inlined Timer0::deactivateOverflowInterrupt(void) const
{
    clrBit(MCU_TIMER0_ENABLE_REG, MCU_TIMER0_ENABLE_OVF_BIT_OFFSET);
    return;
}

uint8_t inlined Timer0::getCounterValue(void) const
{
    return MCU_TIMER0_COUNTER_REG;
}

void inlined Timer0::setCounterValue(cuint8_t value_p) const
{
    MCU_TIMER0_COUNTER_REG = value_p;
    return;
}

//!
//! @endcond
//!

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Singleton Access Macro
// =============================================================================

//!
//! @def            timer0
//! @brief          Timer0 peripheral handler macro.
//! @details        Macro to access the single instance of the Timer0 class.
//!                     Use this macro to handle the peripheral. It replaces
//!                     the old external object instantiation to ensure
//!                     architectural safety and zero-overhead execution while
//!                     keeping the traditional lowercase syntax.
//!
#define timer0 (Timer0::getInstance())

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Timer0" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __TIMER0_HPP

// =============================================================================
// End of file (timer0.hpp)
// =============================================================================
