//!
//! \file           funsapeAvrTimer2.hpp
//! \brief          TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_TIMER2_HPP
#define __FUNSAPE_AVR_TIMER2_HPP                        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_TIMER2_HPP
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

void timer2CompareACallback();
void timer2CompareBCallback();
void timer2OverflowCallback();

// =============================================================================
// Timer2 Class
// =============================================================================

class Timer2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ////////////////     Timer2 Clock Source     /////////////////     //
    //!
    //! \enum           ClockSource
    //!     \details    Clock prescaler options associated with TIMER2.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, timer is off
        PRESCALER_1                     = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock
        PRESCALER_8                     = 2,    //!< Timer clock frequency will be CPU clock divided by 8
        PRESCALER_32                    = 3,    //!< Timer clock frequency will be CPU clock divided by 32
        PRESCALER_64                    = 4,    //!< Timer clock frequency will be CPU clock divided by 64
        PRESCALER_128                   = 5,    //!< Timer clock frequency will be CPU clock divided by 128
        PRESCALER_256                   = 6,    //!< Timer clock frequency will be CPU clock divided by 256
        PRESCALER_1024                  = 7     //!< Timer clock frequency will be CPU clock divided by 1024
    };
    //     ////////////////////     Timer2 Mode     /////////////////////     //
    //!
    //! \enum           Mode
    //!     \details    Modes associated with TIMER2.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR2x = immediate / TOV Flag = 0xFF)
        PWM_PHASE_CORRECTED_MAX         = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR2x = 0xFF / TOV Flag = 0x00)
        CTC_OCRA                        = 2,    //!< CTC mode (direction = UP / TOP = OCR2A / UPDATE OCR2x = immediate / TOV Flag = 0xFF)
        PWM_FAST_MAX                    = 3,    //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF)
        // RESERVED                     = 4,
        PWM_PHASE_CORRECTED_OCRA        = 5,    //!< PWM mode fast (direction = UP / TOP = OCR2A / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF)
        // RESERVED                     = 6,
        PWM_FAST_OCRA                   = 7,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR2A / UPDATE OCR2x = OCR2A / TOV Flag = 0x00)
    };
    //     /////////////////     Timer2 Output Mode    //////////////////     //
    //!
    //! \enum           OutputMode
    //!     \details    OC2x behaviour associated with TIMER2.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                      = 0,    //!< OC2x disabled. Normal port operation
        TOGGLE_ON_COMPARE           = 1,    //!< OC2x will toggle on OCR2x compare match
        CLEAR_ON_COMPARE            = 2,    //!< OC2x will clear on OCR2x compare match
        SET_ON_COMPARE              = 3,    //!< OC2x will set on OCR2x compare match
        NON_INVERTING_MODE          = 2,    //!< OC2x will produce a non-inverted PWM signal
        INVERTING_MODE              = 3,    //!< OC2x will produce a inverted PWM signal
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Timer2(
            void
    );
    ~Timer2(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \fn         bool_t init(Mode mode_p, ClockSource clockSource_p)
    //!     \brief      Initializes the TIMER2 module.
    //!     \details    Initializes the TIMER2 module.
    //!     \param      mode_p          desired mode for the TIMER2 module.
    //!     \param      clockSource_p   desired clock prescaler for the TIMER2 module.
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
    //!     \brief      Configures the desired behavior of OCR2x pins during compare match.
    //!     \details    Configures the desired behavior of OCR2x pins during compare match.
    //!     \param      compA_p         desired behavior of OCR2A pin during a compare A match
    //!     \param      compB_p         desired behavior of OCR2B pin during a compare B match
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
    ClockSource     _clockSource;
    Mode            _mode;
    Error           _lastError;
}; // class Timer2

// =============================================================================
// Inlined class functions
// =============================================================================

//     ///////////////////////     COMPARE A     ////////////////////////     //
//!
//! \fn         inlined void Timer2::activateCompareAInterrupt(void)
//!     \brief      Activates TIMER2 Compare A Match Interrupt.
//!     \details    Activates TIMER2 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::activateCompareAInterrupt(void)
{
    setBit(TIMSK2, OCIE2A);
    return;
}
//!
//! \fn         inlined void Timer2::clearCompareAInterruptRequest(void)
//!     \brief      Clears TIMER2 Compare A Match Interrupt Request.
//!     \details    Clears TIMER2 Compare A Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::clearCompareAInterruptRequest(void)
{
    setBit(TIFR2, OCF2A);
    return;
}
//!
//! \fn         inlined void Timer2::deactivateCompareAInterrupt(void)
//!     \brief      Deactivates TIMER2 Compare A Match Interrupt.
//!     \details    Deactivates TIMER2 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK2, OCIE2A);
    return;
}
//!
//! \fn         inlined void Timer2::forceCompareA(void)
//!     \brief      Forces a Compare A Match.
//!     \details    Forces a Compare A Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::forceCompareA(void)
{
    setBit(TCCR2B, FOC2A);
    return;
}
//!
//! \fn         inlined uint8_t Timer2::getCompareAValue(void)
//!     \brief      Returns current value of the TIMER2 Compare A Match
//!     \details    Returns current value of the TIMER2 Compare A Match
//!     \param      NONE
//!     \return     TIMER2 compare A value
//!
inlined uint8_t Timer2::getCompareAValue(void)
{
    return OCR2A;
}
//!
//! \fn         inlined void Timer2::setCompareAValue(uint8_t value_p)
//!     \brief      Sets the TIMER2 Compare A Match value
//!     \details    Sets the TIMER2 Compare A Match value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer2::setCompareAValue(uint8_t value_p)
{
    OCR2A = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //
//!
//! \fn         inlined void Timer2::activateCompareBInterrupt(void)
//!     \brief      Activates TIMER2 Compare B Match Interrupt.
//!     \details    Activates TIMER2 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::activateCompareBInterrupt(void)
{
    setBit(TIMSK2, OCIE2B);
    return;
}
//!
//! \fn         inlined void Timer2::clearCompareBInterruptRequest(void)
//!     \brief      Clears TIMER2 Compare B Match Interrupt Request.
//!     \details    Clears TIMER2 Compare B Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::clearCompareBInterruptRequest(void)
{
    setBit(TIFR2, OCF2B);
    return;
}
//!
//! \fn         inlined void Timer2::deactivateCompareBInterrupt(void)
//!     \brief      Deactivates TIMER2 Compare B Match Interrupt.
//!     \details    Deactivates TIMER2 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK2, OCIE2B);
    return;
}
//!
//! \fn         inlined void Timer2::forceCompareB(void)
//!     \brief      Forces a Compare B Match.
//!     \details    Forces a Compare B Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::forceCompareB(void)
{
    setBit(TCCR2B, FOC2B);
    return;
}
//!
//! \fn         inlined uint8_t Timer2::getCompareBValue(void)
//!     \brief      Returns current value of the TIMER2 Compare B Match
//!     \details    Returns current value of the TIMER2 Compare B Match
//!     \param      NONE
//!     \return     TIMER2 compare B value
//!
inlined uint8_t Timer2::getCompareBValue(void)
{
    return OCR2B;
}
//!
//! \fn         inlined void Timer2::setCompareBValue(uint8_t value_p)
//!     \brief      Sets the TIMER2 Compare B Match value
//!     \details    Sets the TIMER2 Compare B Match value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer2::setCompareBValue(uint8_t value_p)
{
    OCR2B = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //
//!
//! \fn         inlined void Timer2::activateOverflowInterrupt(void)
//!     \brief      Activates TIMER2 Overflow Interrupt.
//!     \details    Activates TIMER2 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::activateOverflowInterrupt(void)
{
    setBit(TIMSK2, TOIE2);
    return;
}
//!
//! \fn         inlined void Timer2::clearOverflowInterruptRequest(void)
//!     \brief      Clears TIMER2 Overflow Interrupt Request.
//!     \details    Clears TIMER2 Overflow Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::clearOverflowInterruptRequest(void)
{
    setBit(TIFR2, TOV2);
    return;
}
//!
//! \fn         inlined void Timer2::deactivateOverflowInterrupt(void)
//!     \brief      Deactivates TIMER2 Overflow Interrupt.
//!     \details    Deactivates TIMER2 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer2::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK2, TOIE2);
    return;
}
//!
//! \fn         uint8_t timer2GetCounterValue(void);
//!     \brief      Returns current value of the TIMER2 counter
//!     \details    Returns current value of the TIMER2 counter
//!     \param      NONE
//!     \return     TIMER2 counter value
//!
inlined uint8_t Timer2::getCounterValue(void)
{
    return TCNT2;
}
//!
//! \fn         void timer2SetCounterValue(uint8_t value);
//!     \brief      Sets the TIMER2 counter value
//!     \details    Sets the TIMER2 counter value
//!     \param      value_p             Value to be written in register
//!     \return     NONE
//!
inlined void Timer2::setCounterValue(uint8_t value_p)
{
    TCNT2 = value_p;
    return;
}

// TODO: ASSR register
// TODO: GTCCR2 register

// =============================================================================
// External global variables
// =============================================================================

extern Timer2 timer2;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_TIMER2_HPP

// =============================================================================
// END OF FILE
// =============================================================================
