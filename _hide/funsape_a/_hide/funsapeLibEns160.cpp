//!
//! \file           funsapeLibEns160.cpp
//! \brief          ENS160 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-13
//! \version        24.07
//! \copyright      license
//! \details        ENS160 Multi-Gas Sensor module interface
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibEns160.hpp"
#if !defined(__FUNSAPE_LIB_ENS160_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_ENS160_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constEns160DeviceAddress1      = 0x52;
cuint8_t constEns160DeviceAddress2      = 0x53;
cuint8_t constEns160DeviceIdLow         = 0x60;
cuint8_t constEns160DeviceIdHigh        = 0x01;
cuint8_t constEns160CommandNop          = 0x00;
cuint8_t constEns160CommandGetAppVer    = 0x0E;
cuint8_t constEns160CommandClrGpr       = 0xCC;

enum class Register : uint8_t {
    ID                                  = 0x00,
    OPMODE                              = 0x10,
    COMMAND                             = 0x12,
    GPR_WRITE_0                         = 0x40,
    GPR_WRITE_1                         = 0x41,
    GPR_WRITE_2                         = 0x42,
    GPR_WRITE_3                         = 0x43,
    GPR_WRITE_4                         = 0x44,
    GPR_WRITE_5                         = 0x45,
    GPR_WRITE_6                         = 0x46,
    GPR_WRITE_7                         = 0x47,
    GPR_READ_0                          = 0x48,
    GPR_READ_1                          = 0x49,
    GPR_READ_2                          = 0x4A,
    GPR_READ_3                          = 0x4B,
    GPR_READ_4                          = 0x4C,
    GPR_READ_5                          = 0x4D,
    GPR_READ_6                          = 0x4E,
    GPR_READ_7                          = 0x4F,
};
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

Ens160::Ens160(void)
{
    // Mark passage for debugging purpose
    debugMark("Ens160::Ens160(void)", Debug::CodeIndex::ENS160_MODULE);

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_useSpiInterface              = false;
    this->_mode                         = Mode::RESET;
    this->_deviceAddress                = constEns160DeviceAddress1;
    this->_firmwareVersionMajor         = 0;
    this->_firmwareVersionMinor         = 0;
    this->_firmwareVersionBuild         = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ENS160_MODULE);
    return;
}

Ens160::~Ens160(void)
{
    // Mark passage for debugging purpose
    debugMark("Ens160::~Ens160(void)", Debug::CodeIndex::ENS160_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::ENS160_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Ens160::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Ens160::init(Bus *busHandler_p, cbool_t busOption_p)
{
    // Mark passage for debugging purpose
    debugMark("Ens160::init(Bus *, cbool_t)", Debug::CodeIndex::ENS160_MODULE);

    // Local variables
    uint8_t auxBuffer[3];

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_useSpiInterface              = false;
    this->_deviceAddress                = (busOption_p)
            ? (constEns160DeviceAddress2)
            : (constEns160DeviceAddress1);

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::ENS160_MODULE);
        return false;
    } else {
        Bus::BusType auxBusType = busHandler_p->getBusType();
        switch(auxBusType) {
        case Bus::BusType::TWI:
            this->_useSpiInterface = false;
            break;
        case Bus::BusType::SPI:
            this->_useSpiInterface = true;
            // Returns error
            this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::ENS160_MODULE);
            return false;
        // break;
        default:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::ENS160_MODULE);
            return false;
        }
    }

    // Update data members
    this->_busHandler                   = busHandler_p;

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Resets device
    auxBuffer[0] = (uint8_t)(Mode::RESET);
    if(!this->_busHandler->writeReg((uint8_t)(Register::OPMODE), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }
    this->_mode = Mode::RESET;

    // Checks device id
    if(!this->_busHandler->readReg((uint8_t)(Register::ID), auxBuffer, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }
    if((auxBuffer[0] != constEns160DeviceIdLow) && (auxBuffer[1] != constEns160DeviceIdHigh)) {
        // Returns error
        this->_lastError = Error::DEVICE_ID_MATCH_FAILED;
        debugMessage(Error::DEVICE_ID_MATCH_FAILED, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Sets mode to IDLE
    auxBuffer[0] = (uint8_t)(Mode::IDLE);
    if(!this->_busHandler->writeReg((uint8_t)(Register::OPMODE), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }
    this->_mode = Mode::IDLE;

    // Clears command register
    auxBuffer[0] = constEns160CommandNop;
    if(!this->_busHandler->writeReg((uint8_t)(Register::COMMAND), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Clears GPR registers
    auxBuffer[0] = constEns160CommandClrGpr;
    if(!this->_busHandler->writeReg((uint8_t)(Register::COMMAND), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Reads firmware version
    auxBuffer[0] = constEns160CommandGetAppVer;
    if(!this->_busHandler->writeReg((uint8_t)(Register::COMMAND), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)(Register::GPR_READ_4), auxBuffer, 3)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }
    this->_firmwareVersionMajor = auxBuffer[0];
    this->_firmwareVersionMinor = auxBuffer[1];
    this->_firmwareVersionBuild = auxBuffer[2];

    // Marks device as initialized
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ENS160_MODULE);
    return true;
}

bool_t Ens160::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Ens160::setMode(const Mode)", Debug::CodeIndex::ENS160_MODULE);

    // Local variables
    uint8_t auxBuffer = 0;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Sends data to device
    auxBuffer = (uint8_t)mode_p;
    if(!this->_busHandler->writeReg((uint8_t)(Register::OPMODE), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ENS160_MODULE);
        return false;
    }

    // Updates data members
    this->_mode = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ENS160_MODULE);
    return true;
}


// Initialize definition of custom mode with <n> steps
bool Ens160::initCustomMode(uint16_t stepNum)
{
    uint8_t result;

    if(stepNum > 0) {
        this->_stepCount = stepNum;

        result = this->setMode(Mode::IDLE);
        result = this->_clearCommand();

        result = this->_write8(_slaveaddr, (uint8_t)(Register::COMMAND), ENS160_COMMAND_SETSEQ);
    } else {
        result = 1;
    }
    delayMs(ENS160_BOOTING);                   // Wait to boot after reset

    return result == 0;
}

// Add a step to custom measurement profile with definition of duration, enabled data acquisition and temperature for each hotplate
bool Ens160::addCustomStep(uint16_t time, bool measureHP0, bool measureHP1, bool measureHP2, bool measureHP3,
        uint16_t tempHP0, uint16_t tempHP1, uint16_t tempHP2, uint16_t tempHP3)
{
    uint8_t seq_ack;
    uint8_t temp;

    if(debugENS160) {
        // Serial.print("setCustomMode() write step ");
        // Serial.println(this->_stepCount);
    }
    delayMs(ENS160_BOOTING);                   // Wait to boot after reset

    temp = (uint8_t)(((time / 24) - 1) << 6);
    if(measureHP0) {
        temp = temp | 0x20;
    }
    if(measureHP1) {
        temp = temp | 0x10;
    }
    if(measureHP2) {
        temp = temp | 0x8;
    }
    if(measureHP3) {
        temp = temp | 0x4;
    }
    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_0), temp);

    temp = (uint8_t)(((time / 24) - 1) >> 2);
    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_1), temp);

    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_2), (uint8_t)(tempHP0 / 2));
    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_3), (uint8_t)(tempHP1 / 2));
    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_4), (uint8_t)(tempHP2 / 2));
    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_5), (uint8_t)(tempHP3 / 2));

    this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_6), (uint8_t)(this->_stepCount - 1));

    if(this->_stepCount == 1) {
        this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_7), 128);
    } else {
        this->_write8(_slaveaddr, (uint8_t)(Register::GPR_WRITE_7), 0);
    }
    delayMs(ENS160_BOOTING);

    seq_ack = this->_read8(_slaveaddr, (uint8_t)(Register::GPR_READ_7));
    delayMs(ENS160_BOOTING);                   // Wait to boot after reset

    if((ENS160_SEQ_ACK_COMPLETE | this->_stepCount) != seq_ack) {
        this->_stepCount = this->_stepCount - 1;
        return 0;
    } else {
        return 1;
    }

}

// Perform prediction measurement and stores result in internal variables
bool Ens160::measure(bool waitForNew)
{
    uint8_t i2cbuf[8];
    uint8_t status;
    bool newData = false;

    // Set default status for early bail out
    if(debugENS160) {
        // Serial.println("Start measurement");
    }

    if(waitForNew) {
        do {
            delayMs(1);
            status = this->_read8(_slaveaddr, ENS160_REG_DATA_STATUS);

            if(debugENS160) {
                // Serial.print("Status: ");
                // Serial.println(status);
            }

        } while(!IS_NEWDAT(status));
    } else {
        status = this->_read8(_slaveaddr, ENS160_REG_DATA_STATUS);
    }

    // Read predictions
    if(IS_NEWDAT(status)) {
        newData = true;
        this->_read(_slaveaddr, ENS160_REG_DATA_AQI, i2cbuf, 7);
        _data_aqi = i2cbuf[0];
        _data_tvoc = i2cbuf[1] | ((uint16_t)i2cbuf[2] << 8);
        _data_eco2 = i2cbuf[3] | ((uint16_t)i2cbuf[4] << 8);
        if(_revENS16x > 0) {
            _data_aqi500 = ((uint16_t)i2cbuf[5]) | ((uint16_t)i2cbuf[6] << 8);
        } else {
            _data_aqi500 = 0;
        }
    }

    return newData;
}

// Perfrom raw measurement and stores result in internal variables
bool Ens160::measureRaw(bool waitForNew)
{
    uint8_t i2cbuf[8];
    uint8_t status;
    bool newData = false;

    // Set default status for early bail out
    if(debugENS160) {
        // Serial.println("Start measurement");
    }

    if(waitForNew) {
        do {
            delayMs(1);
            status = this->_read8(_slaveaddr, ENS160_REG_DATA_STATUS);

            if(debugENS160) {
                // Serial.print("Status: ");
                // Serial.println(status);
            }
        } while(!IS_NEWGPR(status));
    } else {
        status = this->_read8(_slaveaddr, ENS160_REG_DATA_STATUS);
    }

    if(IS_NEWGPR(status)) {
        newData = true;

        // Read raw resistance values
        this->_read(_slaveaddr, (uint8_t)(Register::GPR_READ_0), i2cbuf, 8);
        _hp0_rs = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[0] | ((uint16_t)i2cbuf[1] << 8)));
        _hp1_rs = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[2] | ((uint16_t)i2cbuf[3] << 8)));
        _hp2_rs = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[4] | ((uint16_t)i2cbuf[5] << 8)));
        _hp3_rs = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[6] | ((uint16_t)i2cbuf[7] << 8)));

        // Read baselines
        this->_read(_slaveaddr, ENS160_REG_DATA_BL, i2cbuf, 8);
        _hp0_bl = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[0] | ((uint16_t)i2cbuf[1] << 8)));
        _hp1_bl = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[2] | ((uint16_t)i2cbuf[3] << 8)));
        _hp2_bl = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[4] | ((uint16_t)i2cbuf[5] << 8)));
        _hp3_bl = CONVERT_RS_RAW2OHMS_F((uint32_t)(i2cbuf[6] | ((uint16_t)i2cbuf[7] << 8)));

        this->_read(_slaveaddr, ENS160_REG_DATA_MISR, i2cbuf, 1);
        _misr = i2cbuf[0];
    }

    return newData;
}


// Writes t (degC) and h (%rh) to ENV_DATA. Returns false on I2C problems.
bool Ens160::set_envdata(float t, float h)
{

    uint16_t t_data = (uint16_t)((t + 273.15f) * 64.0f);

    uint16_t rh_data = (uint16_t)(h * 512.0f);

    return this->set_envdata210(t_data, rh_data);
}

// Writes t and h (in ENS210 format) to ENV_DATA. Returns false on I2C problems.
bool Ens160::set_envdata210(uint16_t t, uint16_t h)
{
    //uint16_t temp;
    uint8_t trh_in[4];

    //temp = (uint16_t)((t + 273.15f) * 64.0f);
    trh_in[0] = t & 0xff;
    trh_in[1] = (t >> 8) & 0xff;

    //temp = (uint16_t)(h * 512.0f);
    trh_in[2] = h & 0xff;
    trh_in[3] = (h >> 8) & 0xff;

    uint8_t result = this->_write(_slaveaddr, ENS160_REG_TEMP_IN, trh_in, 4);

    return result;
}

/**************************************************************************/

void Ens160::_i2c_init()
{
    if(this->_sdaPin != this->_sclPin) {
        // Wire.begin(this->_sdaPin, this->_sclPin);
    } else {
        // Wire.begin();
    }
}

/**************************************************************************/

uint8_t Ens160::_read8(uint8_t addr, uint8_t reg)
{
    uint8_t ret = 0;
    this->_read(addr, reg, &ret, 1);

    return ret;
}

uint8_t Ens160::_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t num)
{
    uint8_t pos = 0;
    uint8_t result = 0;

    if(debugENS160) {
        // Serial.print("I2C read address: 0x");
        // Serial.print(addr, HEX);
        // Serial.print(" - register: 0x");
        // Serial.println(reg, HEX);
    }

    //on arduino we need to read in 32 uint8_t chunks
    while(pos < num) {

        uint8_t read_now = getMinimumOf((uint8_t)32, (uint8_t)(num - pos));
        // Wire.beginTransmission((uint8_t)addr);

        // Wire.write((uint8_t)reg + pos);
        // result = Wire.endTransmission();
        // Wire.requestFrom((uint8_t)addr, read_now);

        for(int i = 0; i < read_now; i++) {
            // buf[pos] = Wire.read();
            pos++;
        }
    }
    return result;
}

/**************************************************************************/

uint8_t Ens160::_write8(uint8_t addr, uint8_t reg, uint8_t value)
{
    uint8_t result = this->_write(addr, reg, &value, 1);
    return result;
}

uint8_t Ens160::_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t num)
{
    if(debugENS160) {
        // Serial.print("I2C write address: 0x");
        // Serial.print(addr, HEX);
        // Serial.print(" - register: 0x");
        // Serial.print(reg, HEX);
        // Serial.print(" -  value:");
        for(int i = 0; i < num; i++) {
            // Serial.print(" 0x");
            // Serial.print(buf[i], HEX);
        }
        // Serial.println();
    }

    // Wire.beginTransmission((uint8_t)addr);
    // Wire.write((uint8_t)reg);
    // Wire.write((uint8_t *)buf, num);
    uint8_t result = 0;
    // result = Wire.endTransmission();
    return result;
}

/**************************************************************************/
