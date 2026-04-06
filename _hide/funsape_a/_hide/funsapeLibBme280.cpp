//!
//! \file           funsapeLibBme280.cpp
//! \brief          BME280 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-11
//! \version        24.07
//! \copyright      license
//! \details        BME280 Barometric Pressure, Humidity and Temperature Sensor
//!                     module interface
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibBme280.hpp"
#if !defined(__FUNSAPE_LIB_BME280_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_BME280_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constBme280DeviceAddress1      = 0x76;
cuint8_t constBme280DeviceAddress2      = 0x77;
cuint8_t constBme280DeviceId            = 0x60;
cuint8_t constBme280CommandReset        = 0xB6;

enum class Register : uint8_t {
    CALIBRATION_1                       = 0x88,
    ID                                  = 0xD0,
    RESET                               = 0xE0,
    CALIBRATION_2                       = 0xE1,
    CTRL_HUM                            = 0xF2,
    STATUS                              = 0xF3,
    CTRL_MEAS                           = 0xF4,
    CONFIG                              = 0xF5,
    PRESSURE                            = 0xF7,
    TEMPERATURE                         = 0xFA,
    HUMIDITY                            = 0xFC,
};

enum class BitPos : uint8_t {
    // CTRL_HUM register
    CTRL_HUM_OSRS_H                     = 0,    // Oversampling of humidity

    // STATUS register
    STATUS_MEASURING                    = 3,    // 1 during measuring, 0 data ready
    STATUS_IM_UPDATE                    = 0,    // 1 during data copy, 0 copy done

    // CTRL_MEAS register
    CTRL_MEAS_OSRS_T                    = 5,    // Oversampling of temperature
    CTRL_MEAS_OSRS_P                    = 2,    // Oversampling of pressure
    CTRL_MEAS_MODE                      = 0,    // Power mode

    // CONFIG register
    CONFIG_T_SB                         = 5,    // Standby duration in normal mode
    CONFIG_FILTER                       = 2,    // Time constant fo IIR filter
    CONFIG_SPI3W_EN                     = 0,    // 1 enables 3-wire SPI interface
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

Bme280::Bme280(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::Bme280(void)", Debug::CodeIndex::BME280_MODULE);

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_useSpiInterface              = false;
    this->_useSpiInterface3Wire         = false;
    this->_newDataReady                 = false;
    this->_deviceAddress                = constBme280DeviceAddress1;
    this->_temperatureResolution        = Resolution::DISABLE_MEASUREMENT;
    this->_pressureResolution           = Resolution::DISABLE_MEASUREMENT;
    this->_humidityResolution           = Resolution::DISABLE_MEASUREMENT;
    this->_filterCoefficient            = FilterCoeff::FILTER_OFF;
    this->_operationMode                = Mode::SLEEP;
    this->_standbyTime                  = StandbyTime::STANDBY_500_US;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return;
}

Bme280::~Bme280(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::~Bme280(void)", Debug::CodeIndex::BME280_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Bme280::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Bme280::init(Bus *busHandler_p, cbool_t busOption_p)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::init(Bus *, cbool_t)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer[26];

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_isInitialized                = false;
    this->_useSpiInterface              = false;
    this->_newDataReady                 = false;
    this->_useSpiInterface3Wire         = busOption_p;
    this->_deviceAddress                = (busOption_p)
            ? (constBme280DeviceAddress2)
            : (constBme280DeviceAddress1);

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::BME280_MODULE);
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
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::BME280_MODULE);
            return false;
        // break;
        default:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::BME280_MODULE);
            return false;
        }
    }

    // Update data members
    this->_busHandler                   = busHandler_p;

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Checks device id
    if(!this->_busHandler->readReg((uint8_t)(Register::ID), auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }
    if(auxBuffer[0] != constBme280DeviceId) {
        // Returns error
        this->_lastError = Error::DEVICE_ID_MATCH_FAILED;
        debugMessage(Error::DEVICE_ID_MATCH_FAILED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Gets calibration values (temperature and pressure)
    if(!this->_busHandler->readReg((uint8_t)(Register::CALIBRATION_1), auxBuffer, 26)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }
    // Process calibration values
    this->_calibDigT1   = (((uint16_t)auxBuffer[1] << 8)    | (uint16_t)auxBuffer[0]);
    this->_calibDigT2   = (((int16_t)auxBuffer[3] << 8)     | (int16_t)auxBuffer[2]);
    this->_calibDigT3   = (((int16_t)auxBuffer[5] << 8)     | (int16_t)auxBuffer[4]);
    this->_calibDigP1   = (((uint16_t)auxBuffer[7] << 8)    | (uint16_t)auxBuffer[6]);
    this->_calibDigP2   = (((int16_t)auxBuffer[9] << 8)     | (int16_t)auxBuffer[8]);
    this->_calibDigP3   = (((int16_t)auxBuffer[11] << 8)    | (int16_t)auxBuffer[10]);
    this->_calibDigP4   = (((int16_t)auxBuffer[13] << 8)    | (int16_t)auxBuffer[12]);
    this->_calibDigP5   = (((int16_t)auxBuffer[15] << 8)    | (int16_t)auxBuffer[14]);
    this->_calibDigP6   = (((int16_t)auxBuffer[17] << 8)    | (int16_t)auxBuffer[16]);
    this->_calibDigP7   = (((int16_t)auxBuffer[19] << 8)    | (int16_t)auxBuffer[18]);
    this->_calibDigP8   = (((int16_t)auxBuffer[21] << 8)    | (int16_t)auxBuffer[20]);
    this->_calibDigP9   = (((int16_t)auxBuffer[23] << 8)    | (int16_t)auxBuffer[22]);
    this->_calibDigH1   = auxBuffer[25];

    // Gets calibration values (humidity)
    if(!this->_busHandler->readReg((uint8_t)(Register::CALIBRATION_2), auxBuffer, 16)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }
    // Process calibration values
    this->_calibDigH2   = (((int16_t)auxBuffer[1] << 8)     | (int16_t)auxBuffer[0]);
    this->_calibDigH3   = auxBuffer[2];
    this->_calibDigH4   = (((int16_t)auxBuffer[3] << 4)     | (int16_t)(auxBuffer[4] & 0x0F));
    this->_calibDigH5   = (((int16_t)auxBuffer[5] << 4)     | (int16_t)(auxBuffer[4] & 0x0F));
    this->_calibDigH6   = (int8_t)auxBuffer[6];

    // Marks device as initialized
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::setResolution(const Resolution pressureRes_p, const Resolution temperatureRes_p,
        const Resolution humidityRes_p)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::setResolution(const Resolution, const Resolution, const Resolution)",
            Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Sends data to device
    auxBuffer = (uint8_t)(humidityRes_p) << (uint8_t)(BitPos::CTRL_HUM_OSRS_H);
    if(!this->_busHandler->writeReg((uint8_t)(Register::CTRL_HUM), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(temperatureRes_p), (uint8_t)(BitPos::CTRL_MEAS_OSRS_T));
    setMaskOffset(auxBuffer, (uint8_t)(pressureRes_p), (uint8_t)(BitPos::CTRL_MEAS_OSRS_P));
    setMaskOffset(auxBuffer, (uint8_t)(this->_operationMode), (uint8_t)(BitPos::CTRL_MEAS_MODE));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CTRL_MEAS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_pressureResolution           = pressureRes_p;
    this->_temperatureResolution        = temperatureRes_p;
    this->_humidityResolution           = humidityRes_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::setStandbyTime(const StandbyTime standbyTime_p)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::setStandbyTime(const StandbyTime)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(standbyTime_p), (uint8_t)(BitPos::CONFIG_T_SB));
    setMaskOffset(auxBuffer, (uint8_t)(this->_filterCoefficient), (uint8_t)(BitPos::CONFIG_FILTER));
    setMaskOffset(auxBuffer, (uint8_t)(this->_useSpiInterface3Wire), (uint8_t)(BitPos::CONFIG_SPI3W_EN));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CONFIG), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_standbyTime                  = standbyTime_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::setFilterCoefficients(const FilterCoeff filterCoeff_p)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::setFilterCoefficients(const FilterCoeff)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(this->_standbyTime), (uint8_t)(BitPos::CONFIG_T_SB));
    setMaskOffset(auxBuffer, (uint8_t)(filterCoeff_p), (uint8_t)(BitPos::CONFIG_FILTER));
    setMaskOffset(auxBuffer, (uint8_t)(this->_useSpiInterface3Wire), (uint8_t)(BitPos::CONFIG_SPI3W_EN));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CONFIG), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_filterCoefficient            = filterCoeff_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::reset(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::reset(void)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer = constBme280CommandReset;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::RESET), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_useSpiInterface3Wire         = false;
    this->_newDataReady                 = false;
    this->_temperatureResolution        = Resolution::DISABLE_MEASUREMENT;
    this->_pressureResolution           = Resolution::DISABLE_MEASUREMENT;
    this->_filterCoefficient            = FilterCoeff::FILTER_OFF;
    this->_operationMode                = Mode::SLEEP;
    this->_standbyTime                  = StandbyTime::STANDBY_500_US;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::checkStatus(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::checkStatus(void)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Updates data members
    this->_newDataReady                 = false;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Gets data from device
    if(!this->_busHandler->readReg((uint8_t)(Register::STATUS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Process result
    this->_newDataReady = (isBitSet(auxBuffer, (uint8_t)(BitPos::STATUS_MEASURING)))
            ? false
            : true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::startMeasurement(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::startMeasurement(void)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(this->_temperatureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_T));
    setMaskOffset(auxBuffer, (uint8_t)(this->_pressureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_P));
    setMaskOffset(auxBuffer, (uint8_t)(Mode::FORCED), (uint8_t)(BitPos::CTRL_MEAS_MODE));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CTRL_MEAS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_operationMode                = Mode::FORCED;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::getData(uint32_t *pres_p, int16_t *temp_p, uint16_t *humi_p)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::getData(uint32_t *, int16_t *, uint16_t *)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer[8];
    uint32_t aux32 = 0;
    int32_t auxPressure = 0;
    int32_t auxTemperature = 0;
    int32_t auxHumidity = 0;
    int32_t auxTempFine = 0;
    int32_t var1 = 0;
    int32_t var2 = 0;
    int16_t temperature = 0;
    uint32_t pressure = 0;
    uint16_t humidity = 0;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }
    // Check for errors - Buffer pointer
    if((!isPointerValid(pres_p)) || (!isPointerValid(temp_p)) || (!isPointerValid(humi_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Reads data from device
    if(!this->_busHandler->readReg((uint8_t)(Register::PRESSURE), auxBuffer, 8)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Process temperature value
    aux32 = ((uint32_t)(auxBuffer[3]) << 16) | ((uint32_t)(auxBuffer[4]) << 8) | (uint32_t)(auxBuffer[5]);
    aux32 >>= 4;
    auxTemperature = (int32_t)aux32;
    var1 = ((((auxTemperature >> 3) - ((int32_t)this->_calibDigT1 << 1))) * ((int32_t)this->_calibDigT2)) >> 11;
    var2 = (((((auxTemperature >> 4) - ((int32_t)this->_calibDigT1)) * ((auxTemperature >> 4) - (
            (int32_t)this->_calibDigT1))) >> 12) * ((int32_t)this->_calibDigT3)) >> 14;
    auxTempFine = var1 + var2;
    temperature = (int16_t)((auxTempFine * 5 + 128) >> 8);

    // Process pressure value
    aux32 = ((uint32_t)(auxBuffer[0]) << 16) | ((uint32_t)(auxBuffer[1]) << 8) | (uint32_t)(auxBuffer[2]);
    aux32 >>= 4;
    auxPressure = (int32_t)aux32;
    var1 = (((int32_t)auxTempFine) >> 1) - (int32_t)64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)this->_calibDigP6);
    var2 = var2 + ((var1 * ((int32_t)this->_calibDigP5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)this->_calibDigP4) << 16);
    var1 = (((this->_calibDigP3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + ((((int32_t)this->_calibDigP2) * var1) >> 1))
            >> 18;
    var1 = ((((32768 + var1)) * ((int32_t)this->_calibDigP1)) >> 15);
    if(var1 == 0) {
        pressure = 0;                   // avoid exception caused by division by zero
    } else {
        pressure = (((uint32_t)(((int32_t)1048576) - auxPressure) - (var2 >> 12))) * 3125;
        if(pressure < 0x80000000) {
            pressure = (pressure << 1) / ((uint32_t)var1);
        } else {
            pressure = (pressure / (uint32_t)var1) * 2;
        }
        var1 = (((int32_t)this->_calibDigP9) * ((int32_t)(((pressure >> 3) * (pressure >> 3)) >> 13))) >> 12;
        var2 = (((int32_t)(pressure >> 2)) * ((int32_t)this->_calibDigP8)) >> 13;
        pressure = (uint32_t)((int32_t)pressure + ((var1 + var2 + this->_calibDigP7) >> 4));
    }

    // Process humidity value
    aux32 = ((uint32_t)(auxBuffer[6]) << 8) | (uint32_t)(auxBuffer[7]);
    auxHumidity = (int32_t)aux32;
    var1 = (auxTempFine - ((int32_t)76800));
    var1 = (((((auxHumidity << 14) - (((int32_t)this->_calibDigH4) << 20) - (((int32_t)this->_calibDigH5) * var1)) + (
                                            (int32_t)16384)) >> 15) * (((((((var1 * ((int32_t)this->_calibDigH6)) >> 10) * (((var1 * (
                                                    (int32_t)this->_calibDigH3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * (
                                            (int32_t)this->_calibDigH2) + 8192) >> 14));
    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t)this->_calibDigH1)) >> 4));
    var1 = (var1 < 0) ? (0) : (var1);
    var1 = (var1 > 419430400) ? (419430400) : (var1);
    var1 >>= 12;
    aux32 = (uint32_t)var1;
    aux32 *= 100;
    aux32 /= 1024;
    humidity = (uint16_t)aux32;

    // Copies values to variables
    *temp_p = temperature;
    *pres_p = pressure;
    *humi_p = humidity;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::setSleepMode(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::setSleepMode(void)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(this->_temperatureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_T));
    setMaskOffset(auxBuffer, (uint8_t)(this->_pressureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_P));
    setMaskOffset(auxBuffer, (uint8_t)(Mode::SLEEP), (uint8_t)(BitPos::CTRL_MEAS_MODE));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CTRL_MEAS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_operationMode                = Mode::SLEEP;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
    return true;
}

bool_t Bme280::setNormalMode(void)
{
    // Mark passage for debugging purpose
    debugMark("Bme280::setNormalMode(void)", Debug::CodeIndex::BME280_MODULE);

    // Local variables
    uint8_t auxBuffer;

    // Check for errors - Not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Selects device
    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Retrieve data from class members
    auxBuffer = 0;
    setMaskOffset(auxBuffer, (uint8_t)(this->_temperatureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_T));
    setMaskOffset(auxBuffer, (uint8_t)(this->_pressureResolution), (uint8_t)(BitPos::CTRL_MEAS_OSRS_P));
    setMaskOffset(auxBuffer, (uint8_t)(Mode::NORMAL), (uint8_t)(BitPos::CTRL_MEAS_MODE));

    // Sends data to device
    if(!this->_busHandler->writeReg((uint8_t)(Register::CTRL_MEAS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::BME280_MODULE);
        return false;
    }

    // Updates data members
    this->_operationMode                = Mode::NORMAL;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::BME280_MODULE);
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
// END OF FILE - funsapeLibBme280.cpp
// =============================================================================
