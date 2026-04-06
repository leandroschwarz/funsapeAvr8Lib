//!
//! ****************************************************************************
//! @file           adc.cpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Analog-to-Digital Converter peripheral control.
//! @details        This file provides peripheral control for the ADC
//!                     peripheral control for the FunSAPE++ AVR8 Library.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @bug            No bugs detected yet.
//! ****************************************************************************
//! @attention
//!
//! MIT License
//!
//! Copyright (c) 2026 Leandro Schwarz
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//!     of this software and associated documentation files (the "Software"), to
//!     deal in the Software without restriction, including without limitation
//!     the rights to use, copy, modify, merge, publish, distribute, sublicense,
//!     and/or sell copies of the Software, and to permit persons to whom the
//!     Software is furnished to do so, subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in
//!     all copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//!     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//!     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//!     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//!     OTHER DEALINGS IN THE SOFTWARE.
//!
//! ****************************************************************************
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "adc.hpp"
#if !defined(__ADC_HPP)
#    error Error 1 - Header file (adc.hpp) is missing or corrupted!
#elif __ADC_HPP != 2604
#    error Error 6 - Build mismatch between header file (adc.hpp) and source file (adc.cpp)!
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
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

Adc Adc::_instance;

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Public function definitions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Adc::Adc() :
    _isInitialized(false),
    _lastError(Error::NONE),
    _isEnabled(false),
    _prescaler(Adc::Prescaler::DISABLED),
    _reference(Adc::Reference::EXTERNAL),
    _channel(Adc::Channel::CHANNEL_0),
    _mode(Adc::Mode::SINGLE_CONVERSION),
    _dataAdjust(Adc::DataPresetation::RIGHT)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::Adc(void)"), Debug::CodeIndex::ADC_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return;
}

Adc::~Adc()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::~Adc(void)"), Debug::CodeIndex::ADC_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Adc::init(const Adc::Mode mode_p, const Adc::Reference reference_p, const Adc::Prescaler prescaler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::init(const Adc::Mode, const Adc::Reference, const Adc::Prescaler)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA   = MCU_ADC_CONTROL_A_REG;
    uint8_t auxAdcsrB   = MCU_ADC_CONTROL_B_REG;
    uint8_t auxAdmux    = MCU_ADC_MUX_REG;

    // Configure mode
    clrMaskOffset(auxAdcsrB, 0x07, MCU_ADC_TRIGGER_SOURCE_BIT_POS);
    if(mode_p == Adc::Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, MCU_ADC_AUTO_TRIGGER_BIT_POS);
    } else {
        setBit(auxAdcsrA, MCU_ADC_AUTO_TRIGGER_BIT_POS);
        switch(mode_p) {
        case Adc::Mode::SINGLE_CONVERSION:                                                   break;
        case Adc::Mode::AUTO_CONTINUOUS:                                                     break;
        case Adc::Mode::AUTO_ANALOG_COMP:        setMaskOffset(auxAdcsrB, 0x01, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_INT0:               setMaskOffset(auxAdcsrB, 0x02, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER0_COMPA:       setMaskOffset(auxAdcsrB, 0x03, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER0_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x04, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_COMPB:       setMaskOffset(auxAdcsrB, 0x05, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x06, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_CAPTURE:     setMaskOffset(auxAdcsrB, 0x07, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        }
    }

    // Configure reference
    clrMaskOffset(auxAdmux, 0x03, MCU_ADC_REFERENCE_BIT_POS);
    switch(reference_p) {
    case Adc::Reference::EXTERNAL:                                                   break;
    case Adc::Reference::POWER_SUPPLY:   setMaskOffset(auxAdmux, 0x01, MCU_ADC_REFERENCE_BIT_POS);       break;
    case Adc::Reference::INTERNAL:       setMaskOffset(auxAdmux, 0x03, MCU_ADC_REFERENCE_BIT_POS);       break;
    }

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, 0x07, MCU_ADC_PRESCALER_BIT_POS);
    switch(prescaler_p) {
    case Adc::Prescaler::DISABLED:                                                   break;
    case Adc::Prescaler::PRESCALER_2:    setMaskOffset(auxAdcsrA, 0x01, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_4:    setMaskOffset(auxAdcsrA, 0x02, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_8:    setMaskOffset(auxAdcsrA, 0x03, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_16:   setMaskOffset(auxAdcsrA, 0x04, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_32:   setMaskOffset(auxAdcsrA, 0x05, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_64:   setMaskOffset(auxAdcsrA, 0x06, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_128:  setMaskOffset(auxAdcsrA, 0x07, MCU_ADC_PRESCALER_BIT_POS);      break;
    }

    // Update registers
    MCU_ADC_MUX_REG           = auxAdmux;
    MCU_ADC_CONTROL_A_REG          = auxAdcsrA;
    MCU_ADC_CONTROL_B_REG          = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;
    this->_reference        = reference_p;
    this->_prescaler        = prescaler_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setDataPresetation(const Adc::DataPresetation data_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setDataPresetation(const Adc::DataPresetation)"), Debug::CodeIndex::ADC_MODULE);

    // Configure Data Adjustment
    if(data_p == DataPresetation::RIGHT) {
        clrBit(MCU_ADC_MUX_REG, MCU_ADC_ADJUST_BIT_OFFSET);
    } else {
        setBit(MCU_ADC_MUX_REG, MCU_ADC_ADJUST_BIT_OFFSET);
    }

    // Update class members
    this->_dataAdjust       = data_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setMode(const Adc::Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setMode(const Adc::Mode)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA = MCU_ADC_CONTROL_A_REG;
    uint8_t auxAdcsrB = MCU_ADC_CONTROL_B_REG;

    // Configure mode
    clrMaskOffset(auxAdcsrB, 0x07, MCU_ADC_TRIGGER_SOURCE_BIT_POS);
    if(mode_p == Adc::Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, MCU_ADC_AUTO_TRIGGER_BIT_POS);
    } else {
        setBit(auxAdcsrA, MCU_ADC_AUTO_TRIGGER_BIT_POS);
        switch(mode_p) {
        case Adc::Mode::SINGLE_CONVERSION:                                                   break;
        case Adc::Mode::AUTO_CONTINUOUS:                                                     break;
        case Adc::Mode::AUTO_ANALOG_COMP:        setMaskOffset(auxAdcsrB, 0x01, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_INT0:               setMaskOffset(auxAdcsrB, 0x02, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER0_COMPA:       setMaskOffset(auxAdcsrB, 0x03, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER0_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x04, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_COMPB:       setMaskOffset(auxAdcsrB, 0x05, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x06, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        case Adc::Mode::AUTO_TIMER1_CAPTURE:     setMaskOffset(auxAdcsrB, 0x07, MCU_ADC_TRIGGER_SOURCE_BIT_POS);      break;
        }
    }

    // Update registers
    MCU_ADC_CONTROL_A_REG = auxAdcsrA;
    MCU_ADC_CONTROL_B_REG = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setPrescaler(const Adc::Prescaler prescaler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setPrescaler(const Adc::Prescaler)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA = MCU_ADC_CONTROL_A_REG;

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, 0x07, MCU_ADC_PRESCALER_BIT_POS);
    switch(prescaler_p) {
    case Adc::Prescaler::DISABLED:                                                   break;
    case Adc::Prescaler::PRESCALER_2:    setMaskOffset(auxAdcsrA, 0x01, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_4:    setMaskOffset(auxAdcsrA, 0x02, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_8:    setMaskOffset(auxAdcsrA, 0x03, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_16:   setMaskOffset(auxAdcsrA, 0x04, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_32:   setMaskOffset(auxAdcsrA, 0x05, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_64:   setMaskOffset(auxAdcsrA, 0x06, MCU_ADC_PRESCALER_BIT_POS);      break;
    case Adc::Prescaler::PRESCALER_128:  setMaskOffset(auxAdcsrA, 0x07, MCU_ADC_PRESCALER_BIT_POS);      break;
    }

    // Update registers
    MCU_ADC_CONTROL_A_REG = auxAdcsrA;

    // Update class members
    this->_prescaler        = prescaler_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setReference(const Adc::Reference reference_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setReference(const Adc::Reference)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdmux = MCU_ADC_MUX_REG;

    // Configure reference
    clrMaskOffset(auxAdmux, 0x03, MCU_ADC_REFERENCE_BIT_POS);
    switch(reference_p) {
    case Adc::Reference::EXTERNAL:                                                   break;
    case Adc::Reference::POWER_SUPPLY:   setMaskOffset(auxAdmux, 0x01, MCU_ADC_REFERENCE_BIT_POS);       break;
    case Adc::Reference::INTERNAL:       setMaskOffset(auxAdmux, 0x03, MCU_ADC_REFERENCE_BIT_POS);       break;
    }

    // Update registers
    MCU_ADC_MUX_REG = auxAdmux;

    // Update class members
    this->_reference        = reference_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::startConversion(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::startConversion(void)"), Debug::CodeIndex::ADC_MODULE);

    // Checks for errors
    if(!this->_isEnabled) {
        // Returns error
        this->_lastError = Error::DEVICE_DISABLED;
        debugMessage(Error::DEVICE_DISABLED, Debug::CodeIndex::ADC_MODULE);
        return false;
    }
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADC_MODULE);
        return false;
    }

    // Starts conversion
    setBit(MCU_ADC_CONTROL_A_REG, MCU_ADC_START_CONVERSION_BIT_OFFSET);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::waitUntilConversionFinish(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::waitUntilConversionFinish(void)"), Debug::CodeIndex::ADC_MODULE);

    // Checks for errors
    if(!this->_isEnabled) {
        // Returns error
        this->_lastError = Error::DEVICE_DISABLED;
        debugMessage(Error::DEVICE_DISABLED, Debug::CodeIndex::ADC_MODULE);
        return false;
    }
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::ADC_MODULE);
        return false;
    }

    // Waits until conversion finishes
    waitUntilBitIsClear(MCU_ADC_CONTROL_A_REG, MCU_ADC_START_CONVERSION_BIT_OFFSET);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

//     ////////////////////     CHANNEL CONTROL     /////////////////////     //

bool_t Adc::setChannel(const Adc::Channel channel_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setChannel(const Adc::Channel)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdmux = MCU_ADC_MUX_REG;

    // Configure channel
    clrMaskOffset(auxAdmux, 0x0F, MCU_ADC_MUX_BIT_POS);
    switch(channel_p) {
    case Adc::Channel::CHANNEL_0:                                            break;
    case Adc::Channel::CHANNEL_1:    setMaskOffset(auxAdmux, 0x01, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_2:    setMaskOffset(auxAdmux, 0x02, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_3:    setMaskOffset(auxAdmux, 0x03, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_4:    setMaskOffset(auxAdmux, 0x04, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_5:    setMaskOffset(auxAdmux, 0x05, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_6:    setMaskOffset(auxAdmux, 0x06, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::CHANNEL_7:    setMaskOffset(auxAdmux, 0x07, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::TEMPERATURE:  setMaskOffset(auxAdmux, 0x08, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::BAND_GAP:     setMaskOffset(auxAdmux, 0x0E, MCU_ADC_MUX_BIT_POS);    break;
    case Adc::Channel::GND:          setMaskOffset(auxAdmux, 0x0F, MCU_ADC_MUX_BIT_POS);    break;
    }

    // Update registers
    MCU_ADC_MUX_REG = auxAdmux;

    // Update class members
    this->_channel          = channel_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

// NONE

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

void weakened adcConversionCompleteCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! @cond
//!

ISR(ADC_vect)
{
    adcConversionCompleteCallback();
}

//!
//! @endcond
//!

// =============================================================================
// End of file (adc.cpp)
// =============================================================================
