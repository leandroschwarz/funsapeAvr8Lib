//!
//! \file           timer1.hpp
//! \brief          TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __TIMER1_HPP
#define __TIMER1_HPP                            2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __TIMER1_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __TIMER1_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
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

//!
//! \brief          TIMER1 compare A match interrupt callback function
//! \details        This function is called when the TIMER1 compare A match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1CompareACallback(void);

//!
//! \brief          TIMER1 compare B match interrupt callback function
//! \details        This function is called when the TIMER1 compare B match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1CompareBCallback(void);

//!
//! \brief          TIMER1 Input Capture interrupt callback function
//! \details        This function is called when the TIMER1 input capture
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1InputCaptureCallback(void);

//!
//! \brief          TIMER1 overflow interrupt callback function
//! \details        This function is called when the TIMER1 overflow interrupt
//!                     is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1OverflowCallback(void);

// =============================================================================
// Timer1 Class
// =============================================================================

//!
//! \brief          Timer1 class
//! \details        Timer1 class
//!
class Timer1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ////////////////     TIMER1 Clock Source     /////////////////     //
    //!
    //! \brief      Clock source enumeration
    //! \details    Clock prescaler options associated with TIMER1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                    = 0,    //!< Disables clock, timer is off
        PRESCALER_1                 = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock
        PRESCALER_8                 = 2,    //!< Timer clock frequency will be CPU clock divided by 8
        PRESCALER_64                = 3,    //!< Timer clock frequency will be CPU clock divided by 64
        PRESCALER_256               = 4,    //!< Timer clock frequency will be CPU clock divided by 256
        PRESCALER_1024              = 5,    //!< Timer clock frequency will be CPU clock divided by 1024
        T1_FALLING_EDGE             = 6,    //!< Timer clock will be based on the falling edge of a signal placed on T1 pin
        T1_RISING_EDGE              = 7     //!< Timer clock will be based on the rising edge of a signal placed on T1 pin
    };

    //     ////////////////////     TIMER1 Mode     /////////////////////     //
    //!
    //! \brief      Operation Mode enumeration
    //! \details    Operation Mode options associated with TIMER1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
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

    //     /////////////////     TIMER1 Output Mode    //////////////////     //
    //!
    //! \brief      Output Mode enumeration
    //! \details    Output Mode options associated with TIMER1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                          = 0,    //!< OC1x disabled. Normal port operation
        TOGGLE_ON_COMPARE               = 1,    //!< OC1x will toggle on OCR1x compare match
        CLEAR_ON_COMPARE                = 2,    //!< OC1x will clear on OCR1x compare match
        SET_ON_COMPARE                  = 3,    //!< OC1x will set on OCR1x compare match
        NON_INVERTING_MODE              = 2,    //!< OC1x will produce a non-inverted PWM signal
        INVERTING_MODE                  = 3,    //!< OC1x will produce a inverted PWM signal
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Timer1 class constructor
    //! \details    Creates an Timer1 object
    //!
    Timer1(
            void
    );

    //!
    //! \brief      Timer1 class destructor
    //! \details    Destroys an Timer1 object
    //!
    ~Timer1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the TIMER1 module
    //! \details    Initializes the TIMER1 module.
    //! \param      mode_p              Operation mode
    //! \param      clockSource_p       Clock source and prescaler
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            const Mode mode_p,
            const ClockSource clockSource_p
    );

    //!
    //! \brief      Configures the clock source and the clock prescaler
    //! \details    Configures the clock source and the clock prescaler.
    //! \param      clockSource_p       Clock source and prescaler
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setClockSource(
            const ClockSource clockSource_p
    );

    //!
    //! \brief      Configures the input capture mode
    //! \details    Configures the input capture mode.
    //! \param      edgeSelection_p     edge of the input capture signal
    //! \param      noiseCanceler_p     state of the noise canceler circuit
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setInputCaptureMode(
            const Edge edgeSelection_p,
            cbool_t noiseCanceler_p
    );

    //!
    //! \brief      Configures the operation mode
    //! \details    Configures the operation mode.
    //! \param      mode_p              Operation mode
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setMode(
            const Mode mode_p
    );

    //!
    //! \brief      Configures the desired behavior of OCR1x pins during compare match
    //! \details    Configures the desired behavior of OCR1x pins during compare match.
    //! \param      compA_p             Behavior of OCR1A pin during a compare A match
    //! \param      compB_p             Behavior of OCR1B pin during a compare B match
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setOutputMode(
            const OutputMode compA_p,
            const OutputMode compB_p
    );

    //     /////////////////     CONTROL AND STATUS    //////////////////     //

    //!
    //! \brief      Returns the last error
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation
    //!
    Error getLastError(
            void
    );

    //     /////////////////////     COMPARE A     //////////////////////     //

    //!
    //! \brief      Activates Compare A Match interrupt
    //! \details    Activates Compare A Match interrupt.
    //!
    void inlined activateCompareAInterrupt(
            void
    );

    //!
    //! \brief      Clears Compare A Match interrupt flag
    //! \details    Clears Compare A Match interrupt flag.
    //!
    void inlined clearCompareAInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Compare A Match interrupt
    //! \details    Deactivates Compare A Match interrupt.
    //!
    void inlined deactivateCompareAInterrupt(
            void
    );

    //!
    //! \brief      Forces a Compare A Match condition on output pin
    //! \details    Forces a Compare A Match condition on output pin.
    //!
    void inlined forceCompareA(
            void
    );

    //!
    //! \brief      Gets Compare A Match value
    //! \details    Gets Compare A Match value.
    //!
    uint16_t inlined getCompareAValue(
            void
    );

    //!
    //! \brief      Sets Compare A Match value
    //! \details    Sets Compare A Match value.
    //!
    void inlined setCompareAValue(
            cuint16_t value_p
    );

    //     /////////////////////     COMPARE B     //////////////////////     //

    //!
    //! \brief      Activates Compare B Match interrupt
    //! \details    Activates Compare B Match interrupt.
    //!
    void inlined activateCompareBInterrupt(
            void
    );

    //!
    //! \brief      Clears Compare B Match interrupt flag
    //! \details    Clears Compare B Match interrupt flag.
    //!
    void inlined clearCompareBInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Compare B Match interrupt
    //! \details    Deactivates Compare B Match interrupt.
    //!
    void inlined deactivateCompareBInterrupt(
            void
    );

    //!
    //! \brief      Forces a Compare B Match condition on output pin
    //! \details    Forces a Compare B Match condition on output pin.
    //!
    void inlined forceCompareB(
            void
    );

    //!
    //! \brief      Gets Compare B Match value
    //! \details    Gets Compare B Match value.
    //!
    uint16_t inlined getCompareBValue(
            void
    );

    //!
    //! \brief      Sets Compare B Match value
    //! \details    Sets Compare B Match value.
    //!
    void inlined setCompareBValue(
            cuint16_t value_p
    );

    //     ///////////////////     INPUT CAPTURE     ////////////////////     //

    //!
    //! \brief      Activates Input Capture interrupt
    //! \details    Activates Input Capture interrupt.
    //!
    void inlined activateInputCaptureInterrupt(
            void
    );

    //!
    //! \brief      Clears Input Capture interrupt flag
    //! \details    Clears Input Capture interrupt flag.
    //!
    void inlined clearInputCaptureInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Input Capture interrupt
    //! \details    Deactivates Input Capture interrupt.
    //!
    void inlined deactivateInputCaptureInterrupt(
            void
    );

    //!
    //! \brief      Gets Input Capture value
    //! \details    Gets Input Capture value.
    //!
    uint16_t inlined getInputCaptureValue(
            void
    );

    //!
    //! \brief      Sets Input Capture value
    //! \details    Sets Input Capture value.
    //!
    void inlined setInputCaptureValue(
            cuint16_t value_p
    );

    //     //////////////////////     OVERFLOW    ///////////////////////     //

    //!
    //! \brief      Activates Overflow interrupt
    //! \details    Activates Overflow interrupt.
    //!
    void inlined activateOverflowInterrupt(
            void
    );

    //!
    //! \brief      Clears Compare A Match interrupt flag
    //! \details    Clears Compare A Match interrupt flag.
    //!
    void inlined clearOverflowInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Overflow Match interrupt
    //! \details    Deactivates Overflow Match interrupt.
    //!
    void inlined deactivateOverflowInterrupt(
            void
    );

    //!
    //! \brief      Gets counter value
    //! \details    Gets counter value.
    //!
    uint16_t inlined getCounterValue(
            void
    );

    //!
    //! \brief      Sets counter value
    //! \details    Sets counter value.
    //!
    void inlined setCounterValue(
            cuint16_t value_p
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
void inlined Timer1::activateCompareAInterrupt(void)
{
    setBit(TIMSK1, OCIE1A);
    return;
}

void inlined Timer1::clearCompareAInterruptRequest(void)
{
    setBit(TIFR1, OCF1A);
    return;
}

void inlined Timer1::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK1, OCIE1A);
    return;
}

void inlined Timer1::forceCompareA(void)
{
    setBit(TCCR1C, FOC1A);
    return;
}

uint16_t inlined Timer1::getCompareAValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1A;
    }
    return aux16;
}

void inlined Timer1::setCompareAValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1A = value_p;
    }
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer1::activateCompareBInterrupt(void)
{
    setBit(TIMSK1, OCIE1B);
    return;
}

void inlined Timer1::clearCompareBInterruptRequest(void)
{
    setBit(TIFR1, OCF1B);
    return;
}

void inlined Timer1::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK1, OCIE1B);
    return;
}

void inlined Timer1::forceCompareB(void)
{
    setBit(TCCR1C, FOC1B);
    return;
}

uint16_t inlined Timer1::getCompareBValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1B;
    }
    return aux16;
}

void inlined Timer1::setCompareBValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = value_p;
    }
    return;
}

//     /////////////////////     INPUT CAPTURE     //////////////////////     //

inlined void Timer1::activateInputCaptureInterrupt(void)
{
    setBit(TIMSK1, ICIE1);
    return;
}

inlined void Timer1::clearInputCaptureInterruptRequest(void)
{
    setBit(TIFR1, ICF1);
    return;
}

inlined void Timer1::deactivateInputCaptureInterrupt(void)
{
    clrBit(TIMSK1, ICIE1);
    return;
}

inlined uint16_t Timer1::getInputCaptureValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = ICR1;
    }
    return aux16;
}

inlined void Timer1::setInputCaptureValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ICR1 = value_p;
    }
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer1::activateOverflowInterrupt(void)
{
    setBit(TIMSK1, TOIE1);
    return;
}

void inlined Timer1::clearOverflowInterruptRequest(void)
{
    setBit(TIFR1, TOV1);
    return;
}

void inlined Timer1::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK1, TOIE1);
    return;
}

uint16_t inlined Timer1::getCounterValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = TCNT1;
    }
    return aux16;
}

void inlined Timer1::setCounterValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TCNT1 = value_p;
    }
    return;
}

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Timer1 peripheral handler object
//! \details        Timer1 peripheral handler object
//!
extern Timer1 timer1;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __TIMER1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
