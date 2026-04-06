//!
//! \file           funsapeLibNunchuk.cpp
//! \brief          Wii Nunchuk extension controller module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2025-10-27
//! \version        24.07
//! \copyright      license
//! \details        Wii Nunchuk extension controller module interface for the
//!                     FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibNunchuk.hpp"
#if !defined(__FUNSAPE_LIB_NUNCHUK_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_NUNCHUK_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constNunchukDeviceAddress     = 0x52;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Nunchuk::Nunchuk(void)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::Nunchuk(void)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Resets data members
    this->_accX = 0;
    this->_accY = 0;
    this->_accZ = 0;
    this->_busHandler = nullptr;
    this->_buttonC = false;
    this->_buttonZ = false;
    this->_isInitialized = false;
    this->_joyX = 0;
    this->_joyY = 0;
    this->_debug = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return;
}

Nunchuk::~Nunchuk(void)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::~Nunchuk(void)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Nunchuk::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Nunchuk::init(Bus *busHandler_p)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::init(Bus *)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Local variables
    uint8_t auxBuffer = 0;

    // Resets data members
    this->_accX = 0;
    this->_accY = 0;
    this->_accZ = 0;
    this->_busHandler = nullptr;
    this->_buttonC = false;
    this->_buttonZ = false;
    this->_isInitialized = false;
    this->_joyX = 0;
    this->_joyY = 0;

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_debug = 1;
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    } else if(busHandler_p->getBusType() != Bus::BusType::TWI) {
        // Returns error
        this->_debug = 2;
        this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
        debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Update data members
    this->_busHandler = busHandler_p;

    // Disables data encryption
    if(!this->_busHandler->setDevice(constNunchukDeviceAddress)) {
        // Returns error
        this->_debug = 3;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    auxBuffer = 0x55;
    if(!this->_busHandler->writeReg(0xF0, &auxBuffer, 1)) {
        // Returns error
        this->_debug = 4;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    delayMs(10);
    auxBuffer = 0x00;
    if(!this->_busHandler->writeReg(0xFB, &auxBuffer, 1)) {
        // Returns error
        this->_debug = 5;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    delayMs(10);

    // Update data members
    this->_isInitialized = true;

    // Returns successfully
    this->_debug = 6;
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return true;
}

bool_t Nunchuk::startAcquisition(void)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::startAcquisition(void)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Local variables
    uint8_t auxBuffer = 0;

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_debug = 7;
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Starts data acquisition
    if(!this->_busHandler->setDevice(constNunchukDeviceAddress)) {
        // Returns error
        this->_debug = 8;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    if(!this->_busHandler->writeReg(0x00, &auxBuffer, 0)) {
        // Returns error
        this->_debug = 9;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Returns successfully
    this->_debug = 10;
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return true;
}

bool_t Nunchuk::read(void)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::read(void)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Local variables
    uint8_t auxBuffer[6] = {0, 0, 0, 0, 0, 0};

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_debug = 11;
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Reads data from device
    if(!this->_busHandler->setDevice(constNunchukDeviceAddress)) {
        // Returns error
        this->_debug = 12;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    if(!this->_busHandler->read(auxBuffer, 6)) {
        // Returns error
        this->_debug = 13;
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Update data members
    this->_joyX = auxBuffer[0];
    this->_joyY = auxBuffer[1];
    this->_accX = (uint16_t)auxBuffer[2];
    this->_accX <<= 2;
    this->_accX |= (((uint16_t)auxBuffer[5] >> 6) & 0x03);
    this->_accY = auxBuffer[3];
    this->_accY <<= 2;
    this->_accY |= (((uint16_t)auxBuffer[5] >> 4) & 0x03);
    this->_accZ = auxBuffer[4];
    this->_accZ <<= 2;
    this->_accZ |= (((uint16_t)auxBuffer[5] >> 2) & 0x03);
    this->_buttonC = isBitSet(auxBuffer[5], 1);
    this->_buttonZ = isBitSet(auxBuffer[5], 0);

    // Returns successfully
    this->_debug = 14;
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return true;
}

//     /////////////////    DATA HANDLING FUNCTIONS     /////////////////     //

bool_t Nunchuk::getAccData(uint16_t *accX_p, uint16_t *accY_p, uint16_t *accZ_p)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::getAccData(uint16_t *, uint16_t *, uint16_t *)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_debug = 15;
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if((!isPointerValid(accX_p)) || (!isPointerValid(accX_p)) || (!isPointerValid(accX_p))) {
        // Returns error
        this->_debug = 16;
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Retrieve data
    *accX_p = this->_accX;
    *accY_p = this->_accY;
    *accZ_p = this->_accZ;

    // Returns successfully
    this->_debug = 17;
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return true;
}

bool_t Nunchuk::getJoyData(uint8_t *joyX_p, uint8_t *joyY_p, bool_t *btnC_p, bool_t *btnZ_p)
{
    // Mark passage for debugging purpose
    debugMark("Nunchuk::getJoyData(uint8_t *, uint8_t *, bool_t *, bool_t *)", Debug::CodeIndex::NUNCHUK_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_debug = 18;
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if((!isPointerValid(joyX_p)) || (!isPointerValid(joyY_p)) || (!isPointerValid(btnC_p)) || (!isPointerValid(btnZ_p))) {
        // Returns error
        this->_debug = 19;
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::NUNCHUK_MODULE);
        return false;
    }

    // Retrieve data
    *joyX_p = this->_joyX;
    *joyY_p = this->_joyY;
    *btnC_p = this->_buttonC;
    *btnZ_p = this->_buttonZ;

    // Returns successfully
    this->_debug = 20;
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NUNCHUK_MODULE);
    return true;
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

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
