//!
//! \file           funsapeAvrTimer0.hpp
//! \brief          TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_TIMER0_HPP
#define __FUNSAPE_AVR_TIMER0_HPP                        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_TIMER0_HPP
#       error "Version mismatch between file header and global definitions file!"
#   endif
#else
#   error "Global definitions file is missing!"
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

void timer0CompareACallback();
void timer0CompareBCallback();
void timer0OverflowCallback();

// =============================================================================
// Timer0 Class
// =============================================================================

class Timer0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ////////////////     Timer0 Clock Source     /////////////////     //
    //!
    //! \enum           ClockSource
    //!     \details    Clock prescaler options associated with TIMER0.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                    = 0,    //!< Disables clock, timer is off
        PRESCALER_1                 = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock
        PRESCALER_8                 = 2,    //!< Timer clock frequency will be CPU clock divided by 8
        PRESCALER_64                = 3,    //!< Timer clock frequency will be CPU clock divided by 64
        PRESCALER_256               = 4,    //!< Timer clock frequency will be CPU clock divided by 256
        PRESCALER_1024              = 5,    //!< Timer clock frequency will be CPU clock divided by 1024
        T0_FALLING_EDGE             = 6,    //!< Timer clock will be based on the falling edge of a signal placed on T0 pin
        T0_RISING_EDGE              = 7     //!< Timer clock will be based on the rising edge of a signal placed on T0 pin
    };
    //     ////////////////////     Timer0 Mode     /////////////////////     //
    //!
    //! \enum           Mode
    //!     \details    Modes associated with TIMER0.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                      = 0,    //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR0x = immediate / TOV Flag = 0xFF)
        PWM_PHASE_CORRECTED_MAX     = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR0x = 0xFF / TOV Flag = 0x00)
        CTC_OCRA                    = 2,    //!< CTC mode (direction = UP / TOP = OCR0A / UPDATE OCR0x = immediate / TOV Flag = 0xFF)
        PWM_FAST_MAX                = 3,    //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF)
        // RESERVED                 = 4,
        PWM_PHASE_CORRECTED_OCRA    = 5,    //!< PWM mode fast (direction = UP / TOP = OCR0A / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF)
        // RESERVED                 = 6,
        PWM_FAST_OCRA               = 7,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR0A / UPDATE OCR0x = OCR0A / TOV Flag = 0x00)
    };
    //     /////////////////     Timer0 Output Mode    //////////////////     //
    //!
    //! \enum           OutputMode
    //!     \details    OC0x behaviour associated with TIMER0.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                      = 0,    //!< OC0x disabled. Normal port operation
        TOGGLE_ON_COMPARE           = 1,    //!< OC0x will toggle on OCR0x compare match
        CLEAR_ON_COMPARE            = 2,    //!< OC0x will clear on OCR0x compare match
        SET_ON_COMPARE              = 3,    //!< OC0x will set on OCR0x compare match
        NON_INVERTING_MODE          = 2,    //!< OC0x will produce a non-inverted PWM signal
        INVERTING_MODE              = 3,    //!< OC0x will produce a inverted PWM signal
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Timer0(
            void
    );
    ~Timer0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \fn         bool_t init(Mode mode_p, ClockSource clockSource_p)
    //!     \brief      Initializes the TIMER0 module.
    //!     \details    Initializes the TIMER0 module.
    //!     \param      mode_p          desired mode for the TIMER0 module.
    //!     \param      clockSource_p   desired clock prescaler for the TIMER0 module.
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t          init(
            Mode mode_p,
            ClockSource clockSource_p
    );
    //!
    //! \fn bool_t setClockSource(ClockSource clockSource_p)
    //!     \brief      Configures the clock source and the clock prescaler.
    //!     \details    Configures the clock source and the clock prescaler.
    //!     \param      clockSource_p   desired clock source and prescaler.
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t          setClockSource(
            ClockSource prescale_p
    );
    //!
    //! \fn bool_t setMode(Mode mode_p)
    //!     \brief      Configures the operation mode.
    //!     \details    Configures the operation mode.
    //!     \param      mode_p          desired operation mode.
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t          setMode(
            Mode mode_p
    );
    //!
    //! \fn bool_t setOutputMode(OutputMode compA_p, OutputMode compB_p)
    //!     \brief      Configures the desired behavior of OCR0x pins during compare match.
    //!     \details    Configures the desired behavior of OCR0x pins during compare match.
    //!     \param      compA_p         desired behavior of OCR0A pin during a compare A match
    //!     \param      compB_p         desired behavior of OCR0B pin during a compare B match
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t          setOutputMode(
            OutputMode compA_p,
            OutputMode compB_p
    );

    //     /////////////////     CONTROL AND STATUS    //////////////////     //
    //!
    //! \fn Error getLastError(void)
    //!     \brief      Returns the last error.
    //!     \details    Returns the last error.
    //!     \param      NONE
    //!     \return     Error code
    //!
    Error           getLastError(
            void
    );

    //     /////////////////////     COMPARE A     //////////////////////     //
    inlined void    activateCompareAInterrupt(
            void
    );
    inlined void    clearCompareAInterruptRequest(
            void
    );
    inlined void    deactivateCompareAInterrupt(
            void
    );
    inlined void    forceCompareA(
            void
    );
    inlined uint8_t getCompareAValue(
            void
    );
    inlined void    setCompareAValue(
            uint8_t value_p
    );

    //     /////////////////////     COMPARE B     //////////////////////     //
    inlined void    activateCompareBInterrupt(
            void
    );
    inlined void    clearCompareBInterruptRequest(
            void
    );
    inlined void    deactivateCompareBInterrupt(
            void
    );
    inlined void    forceCompareB(
            void
    );
    inlined uint8_t getCompareBValue(
            void
    );
    inlined void    setCompareBValue(
            uint8_t value_p
    );

    //     //////////////////////     OVERFLOW    ///////////////////////     //
    inlined void    activateOverflowInterrupt(
            void
    );
    inlined void    clearOverflowInterruptRequest(
            void
    );
    inlined void    deactivateOverflowInterrupt(
            void
    );
    inlined uint8_t getCounterValue(
            void
    );
    inlined void    setCounterValue(
            uint8_t value_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    ClockSource     _clockSource        : 3;
    Mode            _mode               : 3;
    Error           _lastError;
}; // class Timer0

// =============================================================================
// Inlined class functions
// =============================================================================

//     ///////////////////////     COMPARE A     ////////////////////////     //
//!
//! \fn         inlined void Timer0::activateCompareAInterrupt(void)
//!     \brief      Activates TIMER0 Compare A Match Interrupt.
//!     \details    Activates TIMER0 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::activateCompareAInterrupt(void)
{
    setBit(TIMSK0, OCIE0A);
    return;
}
//!
//! \fn         inlined void Timer0::clearCompareAInterruptRequest(void)
//!     \brief      Clears TIMER0 Compare A Match Interrupt Request.
//!     \details    Clears TIMER0 Compare A Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::clearCompareAInterruptRequest(void)
{
    setBit(TIFR0, OCF0A);
    return;
}
//!
//! \fn         inlined void Timer0::deactivateCompareAInterrupt(void)
//!     \brief      Deactivates TIMER0 Compare A Match Interrupt.
//!     \details    Deactivates TIMER0 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK0, OCIE0A);
    return;
}
//!
//! \fn         inlined void Timer0::forceCompareA(void)
//!     \brief      Forces a Compare A Match.
//!     \details    Forces a Compare A Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::forceCompareA(void)
{
    setBit(TCCR0B, FOC0A);
    return;
}
//!
//! \fn         inlined uint8_t Timer0::getCompareAValue(void)
//!     \brief      Returns current value of the TIMER0 Compare A Match
//!     \details    Returns current value of the TIMER0 Compare A Match
//!     \param      NONE
//!     \return     TIMER0 compare A value
//!
inlined uint8_t Timer0::getCompareAValue(void)
{
    return OCR0A;
}
//!
//! \fn         inlined void Timer0::setCompareAValue(uint8_t value_p)
//!     \brief      Sets the TIMER0 Compare A Match value
//!     \details    Sets the TIMER0 Compare A Match value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer0::setCompareAValue(uint8_t value_p)
{
    OCR0A = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //
//!
//! \fn         inlined void Timer0::activateCompareBInterrupt(void)
//!     \brief      Activates TIMER0 Compare B Match Interrupt.
//!     \details    Activates TIMER0 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::activateCompareBInterrupt(void)
{
    setBit(TIMSK0, OCIE0B);
    return;
}
//!
//! \fn         inlined void Timer0::clearCompareBInterruptRequest(void)
//!     \brief      Clears TIMER0 Compare B Match Interrupt Request.
//!     \details    Clears TIMER0 Compare B Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::clearCompareBInterruptRequest(void)
{
    setBit(TIFR0, OCF0B);
    return;
}
//!
//! \fn         inlined void Timer0::deactivateCompareBInterrupt(void)
//!     \brief      Deactivates TIMER0 Compare B Match Interrupt.
//!     \details    Deactivates TIMER0 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK0, OCIE0B);
    return;
}
//!
//! \fn         inlined void Timer0::forceCompareB(void)
//!     \brief      Forces a Compare B Match.
//!     \details    Forces a Compare B Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::forceCompareB(void)
{
    setBit(TCCR0B, FOC0B);
    return;
}
//!
//! \fn         inlined uint8_t Timer0::getCompareBValue(void)
//!     \brief      Returns current value of the TIMER0 Compare B Match
//!     \details    Returns current value of the TIMER0 Compare B Match
//!     \param      NONE
//!     \return     TIMER0 compare B value
//!
inlined uint8_t Timer0::getCompareBValue(void)
{
    return OCR0B;
}
//!
//! \fn         inlined void Timer0::setCompareBValue(uint8_t value_p)
//!     \brief      Sets the TIMER0 Compare B Match value
//!     \details    Sets the TIMER0 Compare B Match value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer0::setCompareBValue(uint8_t value_p)
{
    OCR0B = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //
//!
//! \fn         inlined void Timer0::activateOverflowInterrupt(void)
//!     \brief      Activates TIMER0 Overflow Interrupt.
//!     \details    Activates TIMER0 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::activateOverflowInterrupt(void)
{
    setBit(TIMSK0, TOIE0);
    return;
}
//!
//! \fn         inlined void Timer0::clearOverflowInterruptRequest(void)
//!     \brief      Clears TIMER0 Overflow Interrupt Request.
//!     \details    Clears TIMER0 Overflow Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::clearOverflowInterruptRequest(void)
{
    setBit(TIFR0, TOV0);
    return;
}
//!
//! \fn         inlined void Timer0::deactivateOverflowInterrupt(void)
//!     \brief      Deactivates TIMER0 Overflow Interrupt.
//!     \details    Deactivates TIMER0 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer0::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK0, TOIE0);
    return;
}
//!
//! \fn         uint8_t timer0GetCounterValue(void);
//!     \brief      Returns current value of the TIMER0 counter
//!     \details    Returns current value of the TIMER0 counter
//!     \param      NONE
//!     \return     TIMER0 counter value
//!
inlined uint8_t Timer0::getCounterValue(void)
{
    return TCNT0;
}
//!
//! \fn         void timer0SetCounterValue(uint8_t value);
//!     \brief      Sets the TIMER0 counter value
//!     \details    Sets the TIMER0 counter value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer0::setCounterValue(uint8_t value_p)
{
    TCNT0 = value_p;
    return;
}

// =============================================================================
// External global variables
// =============================================================================

extern Timer0 timer0;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_TIMER0_HPP

// =============================================================================
// END OF FILE
// =============================================================================
