//!
//! \file           funsapeLibAds1115.hpp
//! \brief          ADS1115 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2025-12-10
//! \version        24.07
//! \copyright      license
//! \details        ADS1115 ADC module interface
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "ads1115.hpp"
#if !defined(__FUNSAPE_LIB_ADS1115_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_ADS1115_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

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

Ads1115::Ads1115(void)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::Ads1115(void)", Debug::CodeIndex::ADS1115_MODULE);

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_deviceAddress                = (uint8_t)(DeviceAddress::ADDR_GND);
    this->_channel                      = Channel::AIN0_TO_AIN1;
    this->_fullScaleReference           = Reference::REF_2_048_V;
    this->_mode                         = Mode::SINGLE_SHOT;
    this->_comparatorMode               = ComparatorMode::DISABLED;
    this->_readyPinActiveLevel          = LogicLevel::LOW;
    this->_readyPinIsLatched            = false;
    this->_isInitialized                = false;
    this->_triggerConversion            = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return;
}

Ads1115::~Ads1115(void)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::~Ads1115(void)", Debug::CodeIndex::ADS1115_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Ads1115::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Ads1115::init(Bus *busHandler_p, const DeviceAddress deviceAddress_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::init(Bus *, const DeviceAddress)", Debug::CodeIndex::ADS1115_MODULE);

    // Resets data members
    this->_busHandler                   = nullptr;
    this->_deviceAddress                = (uint8_t)(DeviceAddress::ADDR_GND);
    this->_channel                      = Channel::AIN0_TO_AIN1;
    this->_fullScaleReference           = Reference::REF_2_048_V;
    this->_mode                         = Mode::SINGLE_SHOT;
    this->_comparatorMode               = ComparatorMode::DISABLED;
    this->_readyPinActiveLevel          = LogicLevel::LOW;
    this->_readyPinIsLatched            = false;
    this->_isInitialized                = false;
    this->_triggerConversion            = false;

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    } else if(busHandler_p->getBusType() != Bus::BusType::TWI) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
        debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Update data members
    this->_busHandler = busHandler_p;
    this->_isInitialized = true;
    this->_deviceAddress = (uint8_t)deviceAddress_p;

    // Configures device
    if(!this->_configDevice()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::getConversionValue(int16_t *conversionValue_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::getConversionValue(int16_t *)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if(!isPointerValid(conversionValue_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)Register::CONVERSION, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    *conversionValue_p = ((uint8_t)auxBuff[0] << 8);
    // *conversionValue_p <<= 8;
    *conversionValue_p |= (uint8_t)auxBuff[1];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::selectInput(const Channel channel_p, const Reference fullScalReference_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::selectInput(const Channel, const Reference)", Debug::CodeIndex::ADS1115_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Updates data members
    this->_channel              = channel_p;
    this->_fullScaleReference   = fullScalReference_p;

    // Sends configuration to device
    if(!this->_configDevice()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::setMode(const Mode)", Debug::CodeIndex::ADS1115_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Updates data members
    this->_mode                         = mode_p;

    // Sends configuration to device
    if(!this->_configDevice()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::setComparatorMode(const ComparatorMode comparatorMode_p, const LogicLevel activeLevel_p,
        cbool_t isLatched_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::setMode(const ComparatorMode, const LogicLevel, cbool_t)", Debug::CodeIndex::ADS1115_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Updates data members
    this->_comparatorMode               = comparatorMode_p;
    this->_readyPinActiveLevel          = activeLevel_p;
    this->_readyPinIsLatched            = isLatched_p;

    // Sends configuration to device
    if(!this->_configDevice()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::getComparatorLowThreshold(int16_t *lowThresholdValue_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::getComparatorLowThreshold(int16_t *)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if(!isPointerValid(lowThresholdValue_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)Register::THRESHOLD_LOW, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    *lowThresholdValue_p = (int8_t)auxBuff[0];
    *lowThresholdValue_p <<= 8;
    *lowThresholdValue_p |= (int8_t)auxBuff[1];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::getComparatorHighThreshold(int16_t *highThresholdValue_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::getComparatorHighThreshold(int16_t *)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if(!isPointerValid(highThresholdValue_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)Register::THRESHOLD_HIGH, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    *highThresholdValue_p = (int8_t)auxBuff[0];
    *highThresholdValue_p <<= 8;
    *highThresholdValue_p |= (int8_t)auxBuff[1];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::setComparatorLowThreshold(cint16_t lowThresholdValue_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::setComparatorLowThreshold(cint16_t)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    auxBuff[0] = (uint8_t)(lowThresholdValue_p >> 8);
    auxBuff[1] = (uint8_t)(lowThresholdValue_p & 0xFF);

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->writeReg((uint8_t)Register::THRESHOLD_LOW, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::setComparatorHighThreshold(cint16_t highThresholdValue_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::setComparatorHighThreshold(cint16_t)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    auxBuff[0] = (uint8_t)(highThresholdValue_p >> 8);
    auxBuff[1] = (uint8_t)(highThresholdValue_p & 0xFF);

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->writeReg((uint8_t)Register::THRESHOLD_HIGH, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::getStatus(bool_t *isBusy_p)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::getStatus(bool_t *)", Debug::CodeIndex::ADS1115_MODULE);

    // Local variables
    uint8_t auxBuff[2];

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if(!isPointerValid(isBusy_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)Register::CONFIG, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Transfer data
    *isBusy_p = ((auxBuff[0] & 0x80) == 0) ? true : false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

bool_t Ads1115::startSingleConversion(void)
{
    // Mark passage for debugging purpose
    debugMark("Ads1115::startSingleConversion(void)", Debug::CodeIndex::ADS1115_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Updates data members
    this->_triggerConversion            = true;

    // Sends configuration to device
    if(!this->_configDevice()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::ADS1115_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADS1115_MODULE);
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

bool_t Ads1115::_configDevice(void)
{
    // Local variables
    uint8_t auxBuff[2];

    // Prepares Buffer
    auxBuff[0] = this->_triggerConversion << 7;
    this->_triggerConversion = false;
    auxBuff[0] |= (uint8_t)(this->_channel) << 4;
    auxBuff[0] |= (uint8_t)(this->_fullScaleReference) << 1;
    auxBuff[0] |= (this->_mode == Mode::SINGLE_SHOT) ? 1 : 0;

    auxBuff[1] = ((this->_mode == Mode::SINGLE_SHOT) ? 0x0C : (uint8_t)(this->_mode)) << 5;
    auxBuff[1] |= ((this->_readyPinActiveLevel == LogicLevel::LOW) ? 0 : 1) << 3;
    auxBuff[1] |= this->_readyPinIsLatched << 2;
    switch(this->_comparatorMode) {
    case ComparatorMode::DISABLED:
        auxBuff[1] |= 0 << 4;
        auxBuff[1] |= 3 << 0;
        break;
    case ComparatorMode::TRADITIONAL_AFTER_1_CONVERSION:
        auxBuff[1] |= 0 << 4;
        auxBuff[1] |= 0 << 0;
        break;
    case ComparatorMode::TRADITIONAL_AFTER_2_CONVERSIONS:
        auxBuff[1] |= 0 << 4;
        auxBuff[1] |= 1 << 0;
        break;
    case ComparatorMode::TRADITIONAL_AFTER_4_CONVERSIONS:
        auxBuff[1] |= 0 << 4;
        auxBuff[1] |= 2 << 0;
        break;
    case ComparatorMode::WINDOW_AFTER_1_CONVERSION:
        auxBuff[1] |= 1 << 4;
        auxBuff[1] |= 0 << 0;
        break;
    case ComparatorMode::WINDOW_AFTER_2_CONVERSIONS:
        auxBuff[1] |= 1 << 4;
        auxBuff[1] |= 1 << 0;
        break;
    case ComparatorMode::WINDOW_AFTER_4_CONVERSIONS:
        auxBuff[1] |= 1 << 4;
        auxBuff[1] |= 2 << 0;
        break;
    }

    if(!this->_busHandler->setDevice(this->_deviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        return false;
    }
    if(!this->_busHandler->writeReg((uint8_t)Register::CONFIG, auxBuff, 2)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
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
// END OF FILE
// =============================================================================
