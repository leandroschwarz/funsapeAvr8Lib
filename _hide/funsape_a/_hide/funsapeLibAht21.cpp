//!
//! \file           funsapeLibAht21.cpp
//! \brief          AHT21 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-11
//! \version        24.07
//! \copyright      license
//! \details        AHT21 Humidity and Temperature Sensor module interface
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibAht21.hpp"
#if !defined(__FUNSAPE_LIB_AHT21_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_AHT21_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constAht21DeviceAddress       = 0x38;

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

Aht21::Aht21(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::Aht21(void)", Debug::CodeIndex::AHT21_MODULE);

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_isCalibrated                 = false;
    this->_isDataValid                  = false;
    this->_newDataReady                 = false;
    this->_humidity                     = 0;
    this->_temperature                  = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return;
}

Aht21::~Aht21(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::~Aht21(void)", Debug::CodeIndex::AHT21_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Aht21::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Aht21::init(Bus *busHandler_p)
{

    // Mark passage for debugging purpose
    debugMark("Aht21::init(Bus *)", Debug::CodeIndex::AHT21_MODULE);

    // Local variables
    uint8_t auxBuffer[3];

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_isCalibrated                 = false;
    this->_isDataValid                  = false;
    this->_newDataReady                 = false;
    this->_humidity                     = 0;
    this->_temperature                  = 0;

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::AHT21_MODULE);
        return false;
    } else if(busHandler_p->getBusType() != Bus::BusType::TWI) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
        debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Update data members
    this->_busHandler                   = busHandler_p;
    this->_isInitialized                = true;

    // Selects device
    if(!this->_busHandler->setDevice(constAht21DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Gets status
    if(!this->_busHandler->read(auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }
    if((auxBuffer[0] & 0x18) != 0x18) {
        if(!this->reset()) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
            return false;
        }
        delayMs(10);
    }

    // Sets normal mode
    auxBuffer[0] = 0x00;
    auxBuffer[1] = 0x00;
    if(!this->_busHandler->writeReg(0xA8, auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }
    delayMs(10);

    // Calibrate
    if(!this->calibrate()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

bool_t Aht21::checkStatus(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::checkStatus(void)", Debug::CodeIndex::AHT21_MODULE);

    // Local variables
    uint8_t auxBuffer[7];
    uint32_t aux32 = 0;

    // Updates data members
    this->_isDataValid                  = false;
    this->_isCalibrated                 = false;
    this->_newDataReady                 = false;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(constAht21DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Gets data from device
    if(!this->_busHandler->read(auxBuffer, 7)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Process result
    this->_newDataReady = !((bool_t)(auxBuffer[0] & 0x80));
    this->_isCalibrated = (bool_t)(auxBuffer[0] & 0x08);
    aux32 = 0;
    aux32 |= auxBuffer[1];
    aux32 <<= 8;
    aux32 |= auxBuffer[2];
    aux32 <<= 8;
    aux32 |= auxBuffer[3];
    aux32 >>= 4;
    aux32 *= 625;
    aux32 >>= 16;
    this->_humidity = (uint16_t)aux32;
    aux32 = 0;
    aux32 |= auxBuffer[3];
    aux32 <<= 8;
    aux32 |= auxBuffer[4];
    aux32 <<= 8;
    aux32 |= auxBuffer[5];
    aux32 &= 0x000FFFFF;
    aux32 *= 625;
    aux32 >>= 15;
    aux32 -= 5000;
    this->_temperature = (uint16_t)aux32;

    // Checks CRC
    if(this->_evaluateCrc(auxBuffer) != auxBuffer[6]) {
        this->_isDataValid = false;
    } else {
        this->_isDataValid = true;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

bool_t Aht21::startMeasurement(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::startMeasurement(void)", Debug::CodeIndex::AHT21_MODULE);

    // Local variables
    uint8_t auxBuffer[2];

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(constAht21DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Sends data to device
    auxBuffer[0] = 0x33;
    auxBuffer[1] = 0x00;
    if(!this->_busHandler->writeReg(0xAC, auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

bool_t Aht21::getData(uint16_t *temp_p, uint16_t *humi_p)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::getData(uint16_t *, uint16_t *)", Debug::CodeIndex::AHT21_MODULE);

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }
    // Check for errors - Buffer pointer
    if((!isPointerValid(temp_p)) || (!isPointerValid(humi_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }
    // Check for errors - Data not ready
    if(!this->isReady()) {
        // Returns error
        this->_lastError = Error::NOT_READY;
        debugMessage(Error::NOT_READY, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Gets sensor data
    *temp_p = this->_temperature;
    *humi_p = this->_humidity;

    // Updates data members
    this->_newDataReady = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

bool_t Aht21::reset(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::reset(void)", Debug::CodeIndex::AHT21_MODULE);

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Resets register 0x1B
    if(!this->_resetRegister(0x1B)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Resets register 0x1C
    if(!this->_resetRegister(0x1C)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Resets register 0x1E
    if(!this->_resetRegister(0x1E)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

bool_t Aht21::calibrate(void)
{
    // Mark passage for debugging purpose
    debugMark("Aht21::calibrate(void)", Debug::CodeIndex::AHT21_MODULE);

    // Local variables
    uint8_t auxBuffer[2];

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(constAht21DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Sends data to device
    auxBuffer[0] = 0x08;
    auxBuffer[1] = 0x00;
    if(!this->_busHandler->writeReg(0xBE, auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Waits 10 ms
    delayMs(10);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

bool_t Aht21::_resetRegister(uint8_t register_p)
{
    // Local variables
    uint8_t auxBuffer[3];

    // Selects device
    if(!this->_busHandler->setDevice(constAht21DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Sends data to device
    auxBuffer[0] = 0x00;
    auxBuffer[1] = 0x00;
    if(!this->_busHandler->writeReg(register_p, auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Waits 5 ms
    delayMs(5);

    // Gets data from device
    if(!this->_busHandler->read(auxBuffer, 3)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Waits 10 ms
    delayMs(10);

    // Sends data to device
    auxBuffer[0] = auxBuffer[1];
    auxBuffer[1] = auxBuffer[2];
    if(!this->_busHandler->writeReg(0xB0 | register_p, auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::AHT21_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::AHT21_MODULE);
    return true;
}

uint8_t Aht21::_evaluateCrc(uint8_t *data_p)
{
    // Local variables
    uint8_t auxCrc = 0xFF;

    // Evaluates CRC value
    for(uint8_t byte = 0; byte < 6; byte++) {
        auxCrc ^= (data_p[byte]);
        for(uint8_t i = 8; i > 0; --i) {
            if(auxCrc & 0x80) {
                auxCrc = (auxCrc << 1) ^ 0x31;
            } else {
                auxCrc = (auxCrc << 1);
            }
        }
    }

    // Returns value
    return auxCrc;
}

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
// END OF FILE - funsapeLibAht21.cpp
// =============================================================================
