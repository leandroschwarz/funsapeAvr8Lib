/**
 *******************************************************************************
 * @file            adc.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Analog-to-Digital Converter peripheral control.
 * @details         This file provides peripheral control for the ADC
 *                      peripheral control for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
 * @bug             No bugs detected yet.
 *
 *******************************************************************************
 * @attention
 *
 * MIT License
 *
 * Copyright (c) 2025 Leandro Schwarz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *      of this software and associated documentation files (the "Software"), to
 *      deal in the Software without restriction, including without limitation
 *      the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *      and/or sell copies of the Software, and to permit persons to whom the
 *      Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *      all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *      THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *      OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *      ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *      OTHER DEALINGS IN THE SOFTWARE.
 *
 *******************************************************************************
*/

// =============================================================================
// System file dependencies
// =============================================================================

#include "adc.hpp"
#if !defined(__ADC_HPP)
#    error Error 1 - Header file (adc.hpp) is missing or corrupted!
#elif __ADC_HPP != 2508
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

Adc adc;

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

Adc::Adc()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::Adc(void)"), Debug::CodeIndex::ADC_MODULE);

    // Reset data members
    this->_channel                      = Channel::CHANNEL_0;
    this->_dataAdjust                   = DataPresetation::RIGHT;
    this->_isEnabled                    = false;
    this->_isInitialized                = false;
    this->_mode                         = Mode::SINGLE_CONVERSION;
    this->_prescaler                    = Prescaler::DISABLED;
    this->_reference                    = Reference::EXTERNAL;

    // Returns successfully
    this->_lastError = Error::NONE;
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

bool_t Adc::disable(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::disable(void)"), Debug::CodeIndex::ADC_MODULE);

    // Disables ADC
    clrBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::enable(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::enable(void)"), Debug::CodeIndex::ADC_MODULE);

    // Enables ADC
    setBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::init(const Mode mode_p, const Reference reference_p, const Prescaler prescaler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::init(const Mode, const Reference, const Prescaler)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;
    uint8_t auxAdmux = ADMUX;

    // Configure mode
    clrMaskOffset(auxAdcsrB, 0x07, ADTS0);
    if(mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        switch(mode_p) {
        case Mode::SINGLE_CONVERSION:                                                   break;
        case Mode::AUTO_CONTINUOUS:                                                     break;
        case Mode::AUTO_ANALOG_COMP:        setMaskOffset(auxAdcsrB, 0x01, ADTS0);      break;
        case Mode::AUTO_INT0:               setMaskOffset(auxAdcsrB, 0x02, ADTS0);      break;
        case Mode::AUTO_TIMER0_COMPA:       setMaskOffset(auxAdcsrB, 0x03, ADTS0);      break;
        case Mode::AUTO_TIMER0_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x04, ADTS0);      break;
        case Mode::AUTO_TIMER1_COMPB:       setMaskOffset(auxAdcsrB, 0x05, ADTS0);      break;
        case Mode::AUTO_TIMER1_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x06, ADTS0);      break;
        case Mode::AUTO_TIMER1_CAPTURE:     setMaskOffset(auxAdcsrB, 0x07, ADTS0);      break;
        }
    }

    // Configure reference
    clrMaskOffset(auxAdmux, 0x03, REFS0);
    switch(reference_p) {
    case Reference::EXTERNAL:                                                   break;
    case Reference::POWER_SUPPLY:   setMaskOffset(auxAdmux, 0x01, REFS0);       break;
    case Reference::INTERNAL:       setMaskOffset(auxAdmux, 0x03, REFS0);       break;
    }

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, 0x07, ADPS0);
    switch(prescaler_p) {
    case Prescaler::DISABLED:                                                   break;
    case Prescaler::PRESCALER_2:    setMaskOffset(auxAdcsrA, 0x01, ADPS0);      break;
    case Prescaler::PRESCALER_4:    setMaskOffset(auxAdcsrA, 0x02, ADPS0);      break;
    case Prescaler::PRESCALER_8:    setMaskOffset(auxAdcsrA, 0x03, ADPS0);      break;
    case Prescaler::PRESCALER_16:   setMaskOffset(auxAdcsrA, 0x04, ADPS0);      break;
    case Prescaler::PRESCALER_32:   setMaskOffset(auxAdcsrA, 0x05, ADPS0);      break;
    case Prescaler::PRESCALER_64:   setMaskOffset(auxAdcsrA, 0x06, ADPS0);      break;
    case Prescaler::PRESCALER_128:  setMaskOffset(auxAdcsrA, 0x07, ADPS0);      break;
    }

    // Update registers
    ADMUX           = auxAdmux;
    ADCSRA          = auxAdcsrA;
    ADCSRB          = auxAdcsrB;

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

bool_t Adc::setDataPresetation(const DataPresetation data_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setDataPresetation(const DataPresetation)"), Debug::CodeIndex::ADC_MODULE);

    // Configure Data Adjustment
    if(data_p == DataPresetation::RIGHT) {
        clrBit(ADMUX, ADLAR);
    } else {
        setBit(ADMUX, ADLAR);
    }

    // Update class members
    this->_dataAdjust       = data_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setMode(const Mode)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;

    // Configure mode
    clrMaskOffset(auxAdcsrB, 0x07, ADTS0);
    if(mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        switch(mode_p) {
        case Mode::SINGLE_CONVERSION:                                                   break;
        case Mode::AUTO_CONTINUOUS:                                                     break;
        case Mode::AUTO_ANALOG_COMP:        setMaskOffset(auxAdcsrB, 0x01, ADTS0);      break;
        case Mode::AUTO_INT0:               setMaskOffset(auxAdcsrB, 0x02, ADTS0);      break;
        case Mode::AUTO_TIMER0_COMPA:       setMaskOffset(auxAdcsrB, 0x03, ADTS0);      break;
        case Mode::AUTO_TIMER0_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x04, ADTS0);      break;
        case Mode::AUTO_TIMER1_COMPB:       setMaskOffset(auxAdcsrB, 0x05, ADTS0);      break;
        case Mode::AUTO_TIMER1_OVERFLOW:    setMaskOffset(auxAdcsrB, 0x06, ADTS0);      break;
        case Mode::AUTO_TIMER1_CAPTURE:     setMaskOffset(auxAdcsrB, 0x07, ADTS0);      break;
        }
    }

    // Update registers
    ADCSRA = auxAdcsrA;
    ADCSRB = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setPrescaler(const Prescaler prescaler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setPrescaler(const Prescaler)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, 0x07, ADPS0);
    switch(prescaler_p) {
    case Prescaler::DISABLED:                                                   break;
    case Prescaler::PRESCALER_2:    setMaskOffset(auxAdcsrA, 0x01, ADPS0);      break;
    case Prescaler::PRESCALER_4:    setMaskOffset(auxAdcsrA, 0x02, ADPS0);      break;
    case Prescaler::PRESCALER_8:    setMaskOffset(auxAdcsrA, 0x03, ADPS0);      break;
    case Prescaler::PRESCALER_16:   setMaskOffset(auxAdcsrA, 0x04, ADPS0);      break;
    case Prescaler::PRESCALER_32:   setMaskOffset(auxAdcsrA, 0x05, ADPS0);      break;
    case Prescaler::PRESCALER_64:   setMaskOffset(auxAdcsrA, 0x06, ADPS0);      break;
    case Prescaler::PRESCALER_128:  setMaskOffset(auxAdcsrA, 0x07, ADPS0);      break;
    }

    // Update registers
    ADCSRA = auxAdcsrA;

    // Update class members
    this->_prescaler        = prescaler_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

bool_t Adc::setReference(const Reference reference_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setReference(const Reference)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure reference
    clrMaskOffset(auxAdmux, 0x03, REFS0);
    switch(reference_p) {
    case Reference::EXTERNAL:                                                   break;
    case Reference::POWER_SUPPLY:   setMaskOffset(auxAdmux, 0x01, REFS0);       break;
    case Reference::INTERNAL:       setMaskOffset(auxAdmux, 0x03, REFS0);       break;
    }

    // Update registers
    ADMUX = auxAdmux;

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
    setBit(ADCSRA, ADSC);

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
    waitUntilBitIsClear(ADCSRA, ADSC);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::ADC_MODULE);
    return true;
}

//     ////////////////////     CHANNEL CONTROL     /////////////////////     //

bool_t Adc::setChannel(const Channel channel_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Adc::setChannel(const Channel)"), Debug::CodeIndex::ADC_MODULE);

    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure channel
    clrMaskOffset(auxAdmux, 0x0F, MUX0);
    switch(channel_p) {
    case Channel::CHANNEL_0:                                            break;
    case Channel::CHANNEL_1:    setMaskOffset(auxAdmux, 0x01, MUX0);    break;
    case Channel::CHANNEL_2:    setMaskOffset(auxAdmux, 0x02, MUX0);    break;
    case Channel::CHANNEL_3:    setMaskOffset(auxAdmux, 0x03, MUX0);    break;
    case Channel::CHANNEL_4:    setMaskOffset(auxAdmux, 0x04, MUX0);    break;
    case Channel::CHANNEL_5:    setMaskOffset(auxAdmux, 0x05, MUX0);    break;
    case Channel::CHANNEL_6:    setMaskOffset(auxAdmux, 0x06, MUX0);    break;
    case Channel::CHANNEL_7:    setMaskOffset(auxAdmux, 0x07, MUX0);    break;
    case Channel::TEMPERATURE:  setMaskOffset(auxAdmux, 0x08, MUX0);    break;
    case Channel::BAND_GAP:     setMaskOffset(auxAdmux, 0x0E, MUX0);    break;
    case Channel::GND:          setMaskOffset(auxAdmux, 0x0F, MUX0);    break;
    }

    // Update registers
    ADMUX = auxAdmux;

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

/**
 * @cond
*/

ISR(ADC_vect)
{
    adcConversionCompleteCallback();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (adc.cpp)
// =============================================================================
