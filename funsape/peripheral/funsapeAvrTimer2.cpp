//!
//! \file           funsapeAvrTimer2.hpp
//! \brief          TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// System file dependencies
// =============================================================================

#if __has_include("funsapeAvrTimer2.hpp")
#   include "funsapeAvrTimer2.hpp"
#   if !defined(__FUNSAPE_AVR_TIMER2_HPP)
#       error "Header file is corrupted!"
#   elif __FUNSAPE_AVR_TIMER2_HPP != 220
#       error "Version mismatch between source and header files!"
#   endif
#else
#   error "Header file is missing!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constOutputModeAOffset         = COM2A0;
cuint8_t constOutputModeAMask           = 0x03;
cuint8_t constOutputModeBOffset         = COM2B0;
cuint8_t constOutputModeBMask           = 0x03;
cuint8_t constModeOffsetPart1           = WGM20;
cuint8_t constModeMaskPart1             = 0x03;
cuint8_t constModeOffsetPart2           = WGM22;
cuint8_t constModeMaskPart2             = 0x01;
cuint8_t constClockSourceOffset         = CS20;
cuint8_t constClockSourceMask           = 0x07;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer2 timer2;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer2::Timer2()
{
    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

Timer2::~Timer2()
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer2::init(Mode mode_p, ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer2::setMode(Mode mode_p)
{
    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer2::setClockSource(ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr2B = TCCR2B;

    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer2::setOutputMode(OutputMode compA_p, OutputMode compB_p)
{
    // Local variables
    uint8_t auxTccr2A = TCCR2A;

    // Configure outputs
    clrMaskOffset(auxTccr2A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compB_p), constOutputModeBOffset);
    clrMaskOffset(auxTccr2A, constOutputModeAMask, constOutputModeBOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR2A          = auxTccr2A;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer2::getLastError(void)
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

weakened void timer2CompareACallback(void)
{
    return;
}

weakened void timer2CompareBCallback(void)
{
    return;
}

weakened void timer2OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

ISR(TIMER2_COMPA_vect)
{
    timer2CompareACallback();
}

ISR(TIMER2_COMPB_vect)
{
    timer2CompareBCallback();
}

ISR(TIMER2_OVF_vect)
{
    timer2OverflowCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
