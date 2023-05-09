//!
//! \file           int1.cpp
//! \brief          External Interrupt INT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt INT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "int1.hpp"
#if !defined(__INT1_HPP)
#    error "Header file is corrupted!"
#elif __INT1_HPP != 2304
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_INT1                      0x2DFF

cuint8_t constSenseModeModeOffset       = ISC10;    //!< Interrupt sense mode bit position offset
cuint8_t constSenseModeMask             = 0x03;     //!< Interrupt sense mode bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Int1 int1;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Int1::Int1()
{
    // Mark passage for debugging purpose
    debugMark("Int1::Int1(void)", DEBUG_INT1);

    // Reset data members
    this->_senseMode                    = SenseMode::LOW_LEVEL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_INT1);
    return;
}

Int1::~Int1()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_INT1);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Int1::init(SenseMode senseMode_p)
{
    // Mark passage for debugging purpose
    debugMark("Int1::init(SenseMode)", DEBUG_INT1);

    // Local variables
    uint8_t auxEicra = EICRA;

    // Configure mode
    clrMaskOffset(auxEicra, constSenseModeMask, constSenseModeModeOffset);
    setMaskOffset(auxEicra, ((uint8_t)senseMode_p), constSenseModeModeOffset);

    // Update registers
    EICRA           = auxEicra;

    // Update class members
    this->_senseMode        = senseMode_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_INT1);
    return true;
}

bool_t Int1::setSenseMode(SenseMode senseMode_p)
{
    // Mark passage for debugging purpose
    debugMark("Int1::setSenseMode(SenseMode)", DEBUG_INT1);

    // Local variables
    uint8_t auxEicra = EICRA;

    // Configure mode
    clrMaskOffset(auxEicra, constSenseModeMask, constSenseModeModeOffset);
    setMaskOffset(auxEicra, ((uint8_t)senseMode_p), constSenseModeModeOffset);

    // Update registers
    EICRA           = auxEicra;

    // Update class members
    this->_senseMode        = senseMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_INT1);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Int1::getLastError(void)
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

weakened void int1InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          INT1 interrupt service routine
//! \details        INT1 interrupt service routine.
//!
ISR(INT1_vect)
{
    int1InterruptCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
