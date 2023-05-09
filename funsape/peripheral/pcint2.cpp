//!
//! \file           pcint2.cpp
//! \brief          External Interrupt PCINT2 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt PCINT2 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "pcint2.hpp"
#if !defined(__PCINT2_HPP)
#    error "Header file is corrupted!"
#elif __PCINT2_HPP != 2304
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_PCINT2                    0x2BFF

cuint8_t constInterruptPinOffset        = PCINT16;  //!< Interrupt pin offset
cuint8_t constInterruptPinsMask         = 0xFF;     //!< Interrupt pins bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Pcint2 pcint2;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Pcint2::Pcint2()
{
    // Mark passage for debugging purpose
    debugMark("Pcint2::Pcint2(void)", DEBUG_PCINT2);

    // Reset data members
    this->_enabledPins                  = (Pcint2::Pin)0;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT2);
    return;
}

Pcint2::~Pcint2()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_PCINT2);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Pcint2::init(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint2::init(Pin)", DEBUG_PCINT2);

    // Local variables
    uint8_t auxPcmsk2 = PCMSK2;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk2, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK2          = auxPcmsk2;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT2);
    return true;
}

bool_t Pcint2::enablePins(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint2::enablePins(Pin)", DEBUG_PCINT2);

    // Local variables
    uint8_t auxPcmsk2 = PCMSK2;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk2, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK2          = auxPcmsk2;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT2);
    return true;
}

bool_t Pcint2::disablePins(Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint2::disablePins(Pin)", DEBUG_PCINT2);

    // Local variables
    uint8_t auxPcmsk2 = PCMSK2;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk2, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk2, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK2          = auxPcmsk2;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT2);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Pcint2::getLastError(void)
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

weakened void pcint2InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          PCINT2 interrupt service routine
//! \details        PCINT2 interrupt service routine.
//!
ISR(PCINT2_vect)
{
    pcint2InterruptCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
