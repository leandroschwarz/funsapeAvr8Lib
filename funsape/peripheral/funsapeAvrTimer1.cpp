//!
//! \file           funsapeAvrTimer1.cpp
//! \brief          TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// System file dependencies
// =============================================================================

#if __has_include("funsapeAvrTimer1.hpp")
#   include "funsapeAvrTimer1.hpp"
#   if !defined(__FUNSAPE_AVR_TIMER1_HPP)
#       error "Header file is corrupted!"
#   elif __FUNSAPE_AVR_TIMER1_HPP != 220
#       error "Version mismatch between source and header files!"
#   endif
#else
#   error "Header file is missing!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constOutputModeAOffset         = COM1A0;
cuint8_t constOutputModeAMask           = 0x03;
cuint8_t constOutputModeBOffset         = COM1B0;
cuint8_t constOutputModeBMask           = 0x03;
cuint8_t constModeOffsetPart1           = WGM10;
cuint8_t constModeMaskPart1             = 0x03;
cuint8_t constModeOffsetPart2           = WGM12;
cuint8_t constModeMaskPart2             = 0x03;
cuint8_t constClockSourceOffset         = CS10;
cuint8_t constClockSourceMask           = 0x07;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer1 timer1;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer1::Timer1()
{
    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

Timer1::~Timer1()
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer1::init(Mode mode_p, ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer1::setMode(Mode mode_p)
{
    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer1::setClockSource(ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer1::setOutputMode(OutputMode compA_p, OutputMode compB_p)
{
    // Local variables
    uint8_t auxTccr1A = TCCR1A;

    // Configure outputs
    clrMaskOffset(auxTccr1A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compB_p), constOutputModeBOffset);
    clrMaskOffset(auxTccr1A, constOutputModeAMask, constOutputModeBOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR1A          = auxTccr1A;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer1::setInputCaptureMode(Edge edgeSelection_p, bool_t noiseCanceler_p)
{
    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure Input Capture
    if (noiseCanceler_p) {
        setBit(auxTccr1B, ICNC1);
    } else {
        clrBit(auxTccr1B, ICNC1);
    }
    if (edgeSelection_p == Edge::RISING) {
        setBit(auxTccr1B, ICES1);
    } else {
        clrBit(auxTccr1B, ICES1);
    }

    // Update registers
    TCCR1B          = auxTccr1B;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer1::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

weakened void timer1CompareACallback(void)
{
    return;
}

weakened void timer1CompareBCallback(void)
{
    return;
}

weakened void timer1InputCaptureCallback(void)
{
    return;
}

weakened void timer1OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

ISR(TIMER1_COMPA_vect)
{
    timer1CompareACallback();
}

ISR(TIMER1_COMPB_vect)
{
    timer1CompareBCallback();
}

ISR(TIMER1_CAPT_vect)
{
    timer1InputCaptureCallback();
}

ISR(TIMER1_OVF_vect)
{
    timer1OverflowCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
