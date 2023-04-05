//!
//! \file           sevenSegmentsMuxDisplay.cpp
//! \brief          Seven segments multiplexed display controller
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Seven segments multiplexed display controller with support
//!                     to variable number of digits (2 to 8). The library
//!                     supports both common anode and common cathode displays,
//!                     decimal point, and the special characters defined in
//!                     sevenSegmentsDisplay.hpp.
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "sevenSegmentsMuxDisplay.hpp"
#if !defined(__SEVEN_SEGMENTS_MUX_DISPLAY_HPP)
#   error "Header file is corrupted!"
#elif __SEVEN_SEGMENTS_MUX_DISPLAY_HPP != 2304
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY        0xFFFF

cuint8_t constSevenSegmentMuxDisplayMask[] = {0x00, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

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

SevenSegmentsMuxDisplay::SevenSegmentsMuxDisplay(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::SevenSegmentsMuxDisplay(void)", DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Reset data members
    this->_dataDdr                      = nullptr;
    this->_dataPort                     = nullptr;
    this->_controlDdr                   = nullptr;
    this->_controlPort                  = nullptr;
    this->_controlMask                  = 0;
    this->_controlFirst                 = 0;
    this->_digitMax                     = 0;
    this->_digitIndex                   = 0;
    for(uint8_t i = 0; i < 8; i++) {
        this->_digitValue[i]            = (uint8_t)SevenSegmentsCode::OFF;
        this->_digitPoint[i]            = false;
    }
    this->_displayType                  =  SevenSegmentsDisplayType::COMMON_ANODE;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;
    this->_controlActiveLevel           = LogicLevel::HIGH;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
    return;
}

SevenSegmentsMuxDisplay::~SevenSegmentsMuxDisplay(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::~SevenSegmentsMuxDisplay(void)", DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Returns successfully
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t SevenSegmentsMuxDisplay::init(Digits numberOfDigits_p, SevenSegmentsDisplayType displayType_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::init(SevenSegmentsMuxDisplay::Digits, SevenSegmentsDisplayType)",
            DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Local variables
    uint8_t auxMask = 0;

    // Resets data members
    this->_digitMax             = 0;
    this->_digitIndex           = 0;
    this->_controlMask          = 0;
    this->_isInitialized        = false;

    // Check for errors
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        return false;
    }
    if(((uint8_t)numberOfDigits_p < 2) || ((uint8_t)numberOfDigits_p > 8)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        return false;
    }
    if(!isGpioPinIndexValid((uint8_t)numberOfDigits_p + this->_controlFirst - 1)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        return false;
    }

    // Evaluates control mask
    auxMask = constSevenSegmentMuxDisplayMask[(uint8_t)numberOfDigits_p - 1];

    // I/O initialization
    *(this->_dataDdr) = 0xFF;
    setMaskOffset(*(this->_controlDdr), auxMask, this->_controlFirst);
    *(this->_dataPort) = (displayType_p == SevenSegmentsDisplayType::COMMON_ANODE) ? 0xFF : 0x00;
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        clrMaskOffset(*(this->_controlPort), auxMask, this->_controlFirst);
    } else {
        setMaskOffset(*(this->_controlPort), auxMask, this->_controlFirst);
    }

    // Updates data members
    this->_displayType          = displayType_p;
    this->_digitMax             = (uint8_t)numberOfDigits_p - 1;
    this->_controlMask          = auxMask;
    this->_isInitialized        = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
    return true;
}

bool_t SevenSegmentsMuxDisplay::setPorts(ioRegAddress_t dataRegAddress_p, ioRegAddress_t controlRegAddress_p,
        ioPinIndex_t controlFirstPin_p, LogicLevel displayOnLevel_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::setPorts(ioRegAddress_t, ioRegAddress_t, ioPinIndex_t, LogicLevel)",
            DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Resets data members
    this->_dataDdr          = nullptr;
    this->_dataPort         = nullptr;
    this->_controlDdr       = nullptr;
    this->_controlPort      = nullptr;
    this->_controlFirst     = 0;
    this->_isPortsSet       = false;
    this->_digitIndex       = 0;

    // Check for errors
    if(!isGpioAddressValid(dataRegAddress_p)) {
        // Returns error
        debugMessage(Error::GPIO_DATA_PORT_INVALID, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        this->_lastError = Error::GPIO_DATA_PORT_INVALID;
        return false;
    }
    if(!isGpioAddressValid(controlRegAddress_p)) {
        // Returns error
        debugMessage(Error::GPIO_CONTROL_PORT_INVALID, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        this->_lastError = Error::GPIO_CONTROL_PORT_INVALID;
        return false;
    }
    if(!isGpioPinIndexValid(controlFirstPin_p)) {
        // Returns error
        debugMessage(Error::GPIO_PIN_INDEX_INVALID, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        this->_lastError = Error::GPIO_PIN_INDEX_INVALID;
        return false;
    }

    // Updates data members
    this->_dataDdr              = getGpioDdrAddress(dataRegAddress_p);
    this->_dataPort             = getGpioPortAddress(dataRegAddress_p);
    this->_controlDdr           = getGpioDdrAddress(controlRegAddress_p);
    this->_controlPort          = getGpioPortAddress(controlRegAddress_p);
    this->_controlFirst         = controlFirstPin_p;
    this->_controlActiveLevel   = displayOnLevel_p;
    this->_isPortsSet           = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
    return true;
}

bool_t SevenSegmentsMuxDisplay::showNextDigit(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::showNextDigit(void)", DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Checks for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        return false;
    }

    // Turns current digit OFF
    *(this->_dataPort) = (this->_displayType == SevenSegmentsDisplayType::COMMON_ANODE) ? 0xFF : 0x00;
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        clrMaskOffset(*(this->_controlPort), this->_controlMask, this->_controlFirst);
    } else {
        setMaskOffset(*(this->_controlPort), this->_controlMask, this->_controlFirst);
    }

    // Evaluates next digit
    this->_digitIndex = (this->_digitIndex == this->_digitMax) ? 0 : (this->_digitIndex + 1);

    // Send data to port
    *(this->_dataPort) = convertToSevenSegments(this->_digitValue[this->_digitIndex], this->_digitPoint[this->_digitIndex],
                    this->_displayType);
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        setBit(*(this->_controlPort), (this->_controlFirst + this->_digitIndex));
    } else {
        clrBit(*(this->_controlPort), (this->_controlFirst + this->_digitIndex));
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
    return true;
}

bool_t SevenSegmentsMuxDisplay::updateDigitValues(cuint8_t *digitValues_p, cbool_t *digitPoints_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::updateDigitValues(cuint8_t *, cbool_t *)", DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);

    // Check for errors
    if(!isPointerValid(digitValues_p)) {
        // Returns error
        debugMessage(Error::ARGUMENT_POINTER_NULL, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Updates data members
    for(uint8_t i = 0; i < (this->_digitMax + 1); i++) {
        this->_digitValue[i] = digitValues_p[i];
        if(isPointerValid(digitPoints_p)) {
            this->_digitPoint[i] = digitPoints_p[i];
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_SEVEN_SEGMENTS_MUX_DISPLAY);
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
