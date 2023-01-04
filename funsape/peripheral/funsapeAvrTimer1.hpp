//!
//! \file           funsapeAvrTimer1.hpp
//! \brief          TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_TIMER1_HPP
#define __FUNSAPE_AVR_TIMER1_HPP                        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_TIMER1_HPP
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

void timer1CompareACallback(void);
void timer1CompareBCallback(void);
void timer1InputCaptureCallback(void);
void timer1OverflowCallback(void);

// =============================================================================
// Timer1 Class
// =============================================================================

class Timer1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ////////////////     Timer1 Clock Source     /////////////////     //
    //!
    //! \enum           ClockSource
    //!     \details    Clock prescaler options associated with TIMER1.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, timer is off
        PRESCALER_1                     = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock
        PRESCALER_8                     = 2,    //!< Timer clock frequency will be CPU clock divided by 8
        PRESCALER_64                    = 3,    //!< Timer clock frequency will be CPU clock divided by 64
        PRESCALER_256                   = 4,    //!< Timer clock frequency will be CPU clock divided by 256
        PRESCALER_1024                  = 5,    //!< Timer clock frequency will be CPU clock divided by 1024
        T1_FALLING_EDGE                 = 6,    //!< Timer clock will be based on the falling edge of a signal placed on T1 pin
        T1_RISING_EDGE                  = 7     //!< Timer clock will be based on the rising edge of a signal placed on T1 pin
    };
    //     ////////////////////     Timer1 Mode     /////////////////////     //
    //!
    //! \enum           Mode
    //!     \details    Modes associated with TIMER1.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0x00FF / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF)
        PWM_PHASE_CORRECTED_8_BITS      = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x00FF / UPDATE OCR1x = 0x00FF / TOV Flag = 0x0000)
        PWM_PHASE_CORRECTED_9_BITS      = 2,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x01FF / UPDATE OCR1x = 0x01FF / TOV Flag = 0x0000)
        PWM_PHASE_CORRECTED_10_BITS     = 3,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x03FF / UPDATE OCR1x = 0x03FF / TOV Flag = 0x0000)
        CTC_OCRA                        = 4,    //!< CTC mode (direction = UP / TOP = OCR1A / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF)
        PWM_FAST_8_BITS                 = 5,    //!< PWM mode fast (direction = UP / TOP = 0x00FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x00FF)
        PWM_FAST_9_BITS                 = 6,    //!< PWM mode fast (direction = UP / TOP = 0x01FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x01FF)
        PWM_FAST_10_BITS                = 7,    //!< PWM mode fast (direction = UP / TOP = 0x03FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x03FF)
        PWM_PHASE_FREQ_CORRECTED_ICR    = 8,    //!< PWM mode with phase and frequency correction (direction = UP then DOWN / TOP = ICR1 / UPDATE OCR1x = 0x0000 / TOV Flag = 0x0000)
        PWM_PHASE_FREQ_CORRECTED_OCRA   = 9,    //!< PWM mode with phase and frequency correction (direction = UP then DOWN / TOP = OCR1A / UPDATE OCR1x = 0x0000 / TOV Flag = 0x0000)
        PWM_PHASE_CORRECTED_ICR         = 10,   //!< PWM mode with phase correction (direction = DOWN then UP / TOP = ICR1 / UPDATE OCR1x = ICR1 / TOV Flag = 0x0000)
        PWM_PHASE_CORRECTED_OCRA        = 11,   //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR1A / UPDATE OCR1x = OCR1A / TOV Flag = 0x0000)
        CTC_ICR                         = 12,    //!< CTC mode (direction = UP / TOP = ICR1A / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF)
        // RESERVED                     = 13,
        PWM_FAST_ICR                    = 14,   //!< PWM mode fast (direction = UP / TOP = ICR1 / UPDATE OCR1x = 0x0000 / TOV Flag = 0xFFFF)
        PWM_FAST_OCRA                   = 15    //!< PWM mode fast (direction = UP / TOP = OCR1A / UPDATE OCR1x = 0x0000 / TOV Flag = 0xFFFF)
    };
    //     /////////////////     Timer1 Output Mode    //////////////////     //
    //!
    //! \enum           OutputMode
    //!     \details    OC1x behaviour associated with TIMER1.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                      = 0,    //!< OC1x disabled. Normal port operation
        TOGGLE_ON_COMPARE           = 1,    //!< OC1x will toggle on OCR1x compare match
        CLEAR_ON_COMPARE            = 2,    //!< OC1x will clear on OCR1x compare match
        SET_ON_COMPARE              = 3,    //!< OC1x will set on OCR1x compare match
        NON_INVERTING_MODE          = 2,    //!< OC1x will produce a non-inverted PWM signal
        INVERTING_MODE              = 3,    //!< OC1x will produce a inverted PWM signal
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Timer1(
            void
    );
    ~Timer1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \fn         bool_t init(Mode mode_p, ClockSource clockSource_p)
    //!     \brief      Initializes the TIMER1 module.
    //!     \details    Initializes the TIMER1 module.
    //!     \param      mode_p          desired mode for the TIMER1 module.
    //!     \param      clockSource_p   desired clock prescaler for the TIMER1 module.
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t init(
            Mode mode_p,
            ClockSource clockSource_p
    );
    //! \fn bool_t setClockSource(ClockSource clockSource_p)
    //!     \brief      Configures the clock source and the clock prescaler.
    //!     \details    Configures the clock source and the clock prescaler.
    //!     \param      clockSource_p   desired clock source and prescaler.
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t setClockSource(
            ClockSource prescale_p
    );
    //!
    //! \fn bool_t setInputCaptureMode(Edge edgeSelection_p, bool_t noiseCanceler_p)
    //!     \brief      Configures the input capture mode.
    //!     \details    Configures the input capture mode.
    //!     \param      edgeSelection_p edge of the input capture signal
    //!     \param      noiseCanceler_p state of the noise canceler circuit
    //!     \return[TRUE]               Success.
    //!     \return[FALSE]              Failure. Error can be retrieved with getLastError().
    //!
    bool_t setInputCaptureMode(
            Edge edgeSelection_p,
            bool_t noiseCanceler_p
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
    //!     \brief      Configures the desired behavior of OCR1x pins during compare match.
    //!     \details    Configures the desired behavior of OCR1x pins during compare match.
    //!     \param      compA_p         desired behavior of OCR1A pin during a compare A match
    //!     \param      compB_p         desired behavior of OCR1B pin during a compare B match
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
    inlined uint16_t getCompareAValue(
            void
    );
    inlined void    setCompareAValue(
            uint16_t value_p
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
    inlined uint16_t getCompareBValue(
            void
    );
    inlined void    setCompareBValue(
            uint16_t value_p
    );

    //     ///////////////////     INPUT CAPTURE     ////////////////////     //
    inlined void    activateInputCaptureInterrupt(
            void
    );
    inlined void    clearInputCaptureInterruptRequest(
            void
    );
    inlined void    deactivateInputCaptureInterrupt(
            void
    );
    inlined uint16_t getInputCaptureValue(
            void
    );
    inlined void    setInputCaptureValue(
            uint16_t value_p
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
    inlined uint16_t getCounterValue(
            void
    );
    inlined void    setCounterValue(
            uint16_t value_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    ClockSource     _clockSource;
    Mode            _mode;
    Error           _lastError;
}; // class Timer1

// =============================================================================
// Inlined class functions
// =============================================================================

//     ///////////////////////     COMPARE A     ////////////////////////     //
//!
//! \fn         inlined void Timer1::activateCompareAInterrupt(void)
//!     \brief      Activates TIMER1 Compare A Match Interrupt.
//!     \details    Activates TIMER1 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::activateCompareAInterrupt(void)
{
    setBit(TIMSK1, OCIE1A);
    return;
}
//!
//! \fn         inlined void Timer1::clearCompareAInterruptRequest(void)
//!     \brief      Clears TIMER1 Compare A Match Interrupt Request.
//!     \details    Clears TIMER1 Compare A Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::clearCompareAInterruptRequest(void)
{
    setBit(TIFR1, OCF1A);
    return;
}
//!
//! \fn         inlined void Timer1::deactivateCompareAInterrupt(void)
//!     \brief      Deactivates TIMER1 Compare A Match Interrupt.
//!     \details    Deactivates TIMER1 Compare A Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK1, OCIE1A);
    return;
}
//!
//! \fn         inlined void Timer1::forceCompareA(void)
//!     \brief      Forces a Compare A Match.
//!     \details    Forces a Compare A Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::forceCompareA(void)
{
    setBit(TCCR1C, FOC1A);
    return;
}
//!
//! \fn         inlined uint16_t Timer1::getCompareAValue(void)
//!     \brief      Returns current value of the TIMER1 Compare A Match.
//!     \details    Returns current value of the TIMER1 Compare A Match.
//!     \param      NONE
//!     \return     TIMER1 compare A value.
//!
inlined uint16_t Timer1::getCompareAValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1A;
    }
    return aux16;
}
//!
//! \fn         inlined void Timer1::setCompareAValue(uint16_t value_p)
//!     \brief      Sets the TIMER1 Compare A Match value.
//!     \details    Sets the TIMER1 Compare A Match value.
//!     \param      value_p             Value to be written in register.
//!     \return     NONE
//!
inlined void Timer1::setCompareAValue(uint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1A = value_p;
    }
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //
//!
//! \fn         inlined void Timer1::activateCompareBInterrupt(void)
//!     \brief      Activates TIMER1 Compare B Match Interrupt.
//!     \details    Activates TIMER1 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::activateCompareBInterrupt(void)
{
    setBit(TIMSK1, OCIE1B);
    return;
}
//!
//! \fn         inlined void Timer1::clearCompareBInterruptRequest(void)
//!     \brief      Clears TIMER1 Compare B Match Interrupt Request.
//!     \details    Clears TIMER1 Compare B Match Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::clearCompareBInterruptRequest(void)
{
    setBit(TIFR1, OCF1B);
    return;
}
//!
//! \fn         inlined void Timer1::deactivateCompareBInterrupt(void)
//!     \brief      Deactivates TIMER1 Compare B Match Interrupt.
//!     \details    Deactivates TIMER1 Compare B Match Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK1, OCIE1B);
    return;
}
//!
//! \fn         inlined void Timer1::forceCompareB(void)
//!     \brief      Forces a Compare B Match.
//!     \details    Forces a Compare B Match.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::forceCompareB(void)
{
    setBit(TCCR1C, FOC1B);
    return;
}
//!
//! \fn         inlined uint16_t Timer1::getCompareBValue(void)
//!     \brief      Returns current value of the TIMER1 Compare B Match.
//!     \details    Returns current value of the TIMER1 Compare B Match.
//!     \param      NONE
//!     \return     TIMER1 compare B value.
//!
inlined uint16_t Timer1::getCompareBValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1B;
    }
    return aux16;
}
//!
//! \fn         inlined void Timer1::setCompareBValue(uint16_t value_p)
//!     \brief      Sets the TIMER1 Compare B Match value.
//!     \details    Sets the TIMER1 Compare B Match value.
//!     \param      value_p             Value to be written in register.
//!     \return     NONE
//!
inlined void Timer1::setCompareBValue(uint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = value_p;
    }
    return;
}

//     /////////////////////     INPUT CAPTURE     //////////////////////     //
//!
//! \fn         inlined void Timer1::activateInputCaptureInterrupt(void)
//!     \brief      Activates TIMER1 Input Capture Interrupt.
//!     \details    Activates TIMER1 Input Capture Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::activateInputCaptureInterrupt(void)
{
    setBit(TIMSK1, ICIE1);
    return;
}
//!
//! \fn         inlined void Timer1::clearInputCaptureInterruptRequest(void)
//!     \brief      Clears TIMER1 Input Capture Interrupt Request.
//!     \details    Clears TIMER1 Input Capture Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::clearInputCaptureInterruptRequest(void)
{
    setBit(TIFR1, ICF1);
    return;
}
//!
//! \fn         inlined void Timer1::deactivateInputCaptureInterrupt(void)
//!     \brief      Deactivates TIMER1 Incput Capture Interrupt.
//!     \details    Deactivates TIMER1 Incput Capture Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::deactivateInputCaptureInterrupt(void)
{
    clrBit(TIMSK1, ICIE1);
    return;
}
//!
//! \fn         uint16_t getInputCaptureValue(void)
//!     \brief      Returns current value of the TIMER1 counter.
//!     \details    Returns current value of the TIMER1 counter.
//!     \param      NONE
//!     \return     TIMER1 counter value.
//!
inlined uint16_t Timer1::getInputCaptureValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = ICR1;
    }
    return aux16;
}
//!
//! \fn         void setInputCaptureValue(uint16_t value)
//!     \brief      Sets the TIMER1 input capture value.
//!     \details    Sets the TIMER1 input capture value.
//!     \param      value_p             Value to be written in register.
//!     \return     NONE
//!
inlined void Timer1::setInputCaptureValue(uint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ICR1 = value_p;
    }
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //
//!
//! \fn         inlined void Timer1::activateOverflowInterrupt(void)
//!     \brief      Activates TIMER1 Overflow Interrupt.
//!     \details    Activates TIMER1 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::activateOverflowInterrupt(void)
{
    setBit(TIMSK1, TOIE1);
    return;
}
//!
//! \fn         inlined void Timer1::clearOverflowInterruptRequest(void)
//!     \brief      Clears TIMER1 Overflow Interrupt Request.
//!     \details    Clears TIMER1 Overflow Interrupt Request.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::clearOverflowInterruptRequest(void)
{
    setBit(TIFR1, TOV1);
    return;
}
//!
//! \fn         inlined void Timer1::deactivateOverflowInterrupt(void)
//!     \brief      Deactivates TIMER1 Overflow Interrupt.
//!     \details    Deactivates TIMER1 Overflow Interrupt.
//!     \param      NONE
//!     \return     NONE
//!
inlined void Timer1::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK1, TOIE1);
    return;
}
//!
//! \fn         uint16_t timer1GetCounterValue(void)
//!     \brief      Returns current value of the TIMER1 counter.
//!     \details    Returns current value of the TIMER1 counter.
//!     \param      NONE
//!     \return     TIMER1 counter value.
//!
inlined uint16_t Timer1::getCounterValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = TCNT1;
    }
    return aux16;
}
//!
//! \fn         void timer1SetCounterValue(uint16_t value)
//!     \brief      Sets the TIMER1 counter value.
//!     \details    Sets the TIMER1 counter value.
//!     \param      value_p             Value to be written in register.
//!     \return     NONE
//!
inlined void Timer1::setCounterValue(uint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TCNT1 = value_p;
    }
    return;
}

// =============================================================================
// External global variables
// =============================================================================

extern Timer1 timer1;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_TIMER1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
