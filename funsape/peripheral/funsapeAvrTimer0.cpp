//!
//! \file           funsapeAvrTimer0.cpp
//! \brief          TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// System file dependencies
// =============================================================================

#if __has_include("funsapeAvrTimer0.hpp")
#   include "funsapeAvrTimer0.hpp"
#   if !defined(__FUNSAPE_AVR_TIMER0_HPP)
#       error "Header file is corrupted!"
#   elif __FUNSAPE_AVR_TIMER0_HPP != 220
#       error "Version mismatch between source and header files!"
#   endif
#else
#   error "Header file is missing!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constOutputModeAOffset         = COM0A0;
cuint8_t constOutputModeAMask           = 0x03;
cuint8_t constOutputModeBOffset         = COM0B0;
cuint8_t constOutputModeBMask           = 0x03;
cuint8_t constModeOffsetPart1           = WGM00;
cuint8_t constModeMaskPart1             = 0x03;
cuint8_t constModeOffsetPart2           = WGM02;
cuint8_t constModeMaskPart2             = 0x01;
cuint8_t constClockSourceOffset         = CS00;
cuint8_t constClockSourceMask           = 0x07;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer0 timer0;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer0::Timer0()
{
    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

Timer0::~Timer0()
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer0::init(Mode mode_p, ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr0A = TCCR0A;
    uint8_t auxTccr0B = TCCR0B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr0B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr0B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr0B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR0A          = auxTccr0A;
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer0::setMode(Mode mode_p)
{
    // Local variables
    uint8_t auxTccr0A = TCCR0A;
    uint8_t auxTccr0B = TCCR0B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr0B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr0B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR0A          = auxTccr0A;
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer0::setClockSource(ClockSource clockSource_p)
{
    // Local variables
    uint8_t auxTccr0B = TCCR0B;

    // Configure clock source
    clrMaskOffset(auxTccr0B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Timer0::setOutputMode(OutputMode compA_p, OutputMode compB_p)
{
    // Local variables
    uint8_t auxTccr0A = TCCR0A;

    // Configure outputs
    clrMaskOffset(auxTccr0A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr0A, ((uint8_t)compB_p), constOutputModeBOffset);
    clrMaskOffset(auxTccr0A, constOutputModeAMask, constOutputModeBOffset);
    setMaskOffset(auxTccr0A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR0A          = auxTccr0A;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer0::getLastError(void)
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

weakened void timer0CompareACallback(void)
{
    return;
}

weakened void timer0CompareBCallback(void)
{
    return;
}

weakened void timer0OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

ISR(TIMER0_COMPA_vect)
{
    timer0CompareACallback();
}

ISR(TIMER0_COMPB_vect)
{
    timer0CompareBCallback();
}

ISR(TIMER0_OVF_vect)
{
    timer0OverflowCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
