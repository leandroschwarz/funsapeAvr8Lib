/**
 *******************************************************************************
 * @file            tm1637.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TM1637 display module interface for the  FunSAPE++ AVR8
 *                      Library.
 * @details         TM1637 display module interface for the  FunSAPE++ AVR8
 *                      Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            Implement _readByte() and readKeypadData() functions.
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

#include "tm1637.hpp"
#if !defined(__TM1637_HPP)
#    error Error 1 - Header file (tm1637.hpp) is missing or corrupted!
#elif __TM1637_HPP != 2508

#    error Error 6 - Build mismatch between header file (tm1637.hpp) and source file (tm1637.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t clockPeriod = 10;
cuint8_t segments[16] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b01110111,
    0b01111100,
    0b00111001,
    0b01011110,
    0b01111001,
    0b01110001
};

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

// NONE

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

Tm1637::Tm1637(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::Tm1637(void)"), Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_contrastLevel                = Contrast::PERCENT_62_5;
    this->_gpioClockPin                 = nullptr;
    this->_gpioDataPin                  = nullptr;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;
    this->_showDisplay                  = false;
    this->_useAutoIncrementMode         = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return;
}

Tm1637::~Tm1637(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::~Tm1637(void)"), Debug::CodeIndex::TM1637_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Tm1637::init(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::init(void)"), Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_isInitialized                = false;

    // Check for errors
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // I/O initialization (Data Bus)
    this->_gpioClockPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_gpioClockPin->set();
    this->_gpioDataPin->setMode(GpioPin::Mode::INPUT_FLOATING);

    // Updates data members
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::setPorts(GpioPin *gpioDioPin_p, GpioPin *gpioClkPin_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::setPorts(GpioPin *, GpioPin *)"), Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_gpioClockPin                 = nullptr;
    this->_gpioDataPin                  = nullptr;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;

    // Check for errors
    if(!isPointerValid(gpioDioPin_p)) {
        // Returns error
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TM1637_MODULE);
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }
    if(!isPointerValid(gpioClkPin_p)) {
        // Returns error
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TM1637_MODULE);
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Updates data members
    this->_gpioClockPin                 = gpioClkPin_p;
    this->_gpioDataPin                  = gpioDioPin_p;
    this->_isPortsSet                   = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::setAddressingMode(cbool_t useAutoIncrementMode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::setAddressingMode(cbool_t)"), Debug::CodeIndex::TM1637_MODULE);

    // Update data members
    this->_useAutoIncrementMode         = useAutoIncrementMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

//     /////////////////////    DISPLAY CONTROL     /////////////////////     //

bool_t Tm1637::setDisplayContrast(const Contrast contrastLevel_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::setDisplayContrast(const Contrast)"), Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t data = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    data = (uint8_t)Command::DISPLAY_CONTROL;
    setMaskOffset(data,
            ((uint8_t)(this->_showDisplay) & (uint8_t)(BitMask::DISPLAY_CONTROL_SHOW)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_SHOW)
    );
    setMaskOffset(data,
            ((uint8_t)(contrastLevel_p) & (uint8_t)(BitMask::DISPLAY_CONTROL_CONTRAST)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_CONTRAST)
    );

    // Send command
    this->_sendStart();
    this->_writeByte(data);
    if(!this->_readAck()) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        debugMessage(Error::COMMUNICATION_FAILED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    this->_sendStop();

    // Update data members
    this->_contrastLevel                = contrastLevel_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::showDisplay(cbool_t showDisplay_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::showDisplay(cbool_t)"), Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t data = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    data = (uint8_t)Command::DISPLAY_CONTROL;
    setMaskOffset(data,
            ((uint8_t)(showDisplay_p) & (uint8_t)(BitMask::DISPLAY_CONTROL_SHOW)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_SHOW)
    );
    setMaskOffset(data,
            ((uint8_t)(this->_contrastLevel) & (uint8_t)(BitMask::DISPLAY_CONTROL_CONTRAST)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_CONTRAST)
    );

    // Send command
    this->_sendStart();
    this->_writeByte(data);
    if(!this->_readAck()) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        debugMessage(Error::COMMUNICATION_FAILED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    this->_sendStop();

    // Update data members
    this->_showDisplay                  = showDisplay_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::writeDisplayData(cuint16_t displayValue_p, cuint8_t base_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::writeDisplayData(cuint16_t, cuint8_t)"), Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t auxSegments[4] = {0, 0, 0, 0};
    uint8_t aux8 = 0;
    uint16_t aux16 = displayValue_p;
    cuint8_t displayIndex = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    // CHECK FOR ERROR - base
    if((base_p < 2) || (base_p > 16)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Extract digits
    for(uint8_t i = 0; i < 4; i++) {
        aux8 = (aux16 % base_p);
        aux16 /= (uint16_t)base_p;
        auxSegments[i] = segments[aux8];
    }

    // Prepare command
    aux8 = (uint8_t)Command::DISPLAY_ADDRESS;
    setMaskOffset(aux8,
            ((uint8_t)(displayIndex) & (uint8_t)(BitMask::DISPLAY_ADDRESS)),
            (uint8_t)(BitPos::DISPLAY_ADDRESS)
    );

    // Writing data to display
    this->_sendStart();
    this->_writeByte(aux8);
    this->_readAck();
    for(uint8_t i = 0; i < 4; i++) {
        this->_writeByte(auxSegments[3 - i]);
        this->_readAck();
    }
    this->_sendStop();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::writeDisplayData(cuint8_t segments_p, cuint8_t index_p, cbool_t showDot_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::writeDisplayData(cuint8_t, cuint8_t, cbool_t)"), Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t aux8 = 0;
    uint8_t auxSegments = segments_p;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(this->_lastError, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    // CHECK FOR ERROR - base
    if((index_p > 4) || (index_p == 0)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    aux8 = (uint8_t)Command::DISPLAY_ADDRESS;
    setMaskOffset(aux8,
            ((uint8_t)(index_p - 1) & (uint8_t)(BitMask::DISPLAY_ADDRESS)),
            (uint8_t)(BitPos::DISPLAY_ADDRESS)
    );

    // Check dot
    if(showDot_p) {
        auxSegments |= 0x80;
    }

    // Writing data to display
    this->_sendStart();
    this->_writeByte(aux8);
    this->_readAck();
    this->_writeByte(auxSegments);
    this->_readAck();
    this->_sendStop();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

//     /////////////////////     KEYPAD CONTROL     /////////////////////     //

bool_t Tm1637::readKeypadData(uint8_t *keyPressed_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Tm1637::readKeypadData(uint8_t *)"), Debug::CodeIndex::TM1637_MODULE);

    // FIXME: Implement this function

    // Returns error
    this->_lastError = Error::NOT_IMPLEMENTED;
    debugMessage(Error::NOT_IMPLEMENTED, Debug::CodeIndex::TM1637_MODULE);
    return false;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

//     /////////////////     COMMUNICATION PROTOCOL     /////////////////     //

void Tm1637::_sendStart(void)
{
    // Pull lines up
    this->_gpioClockPin->set();
    this->_gpioDataPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    delayUs(clockPeriod);

    // Send start condition
    this->_gpioDataPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    delayUs(clockPeriod / 2);
    this->_gpioClockPin->clr();

    return;
}

void Tm1637::_sendStop(void)
{
    // Assuring the DIO line is driven LOW
    this->_gpioDataPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);

    // Send stop condition
    delayUs(clockPeriod / 2);
    this->_gpioClockPin->set();
    delayUs(clockPeriod / 2);
    this->_gpioDataPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    delayUs(clockPeriod);

    return;
}

void Tm1637::_writeByte(cuint8_t byteToWrite_p)
{
    for(uint8_t i = 0; i < 8; i++) {
        if(isBitSet(byteToWrite_p, i)) {
            this->_gpioDataPin->setMode(GpioPin::Mode::INPUT_FLOATING);
        } else {
            this->_gpioDataPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
        }
        delayUs(clockPeriod / 2);
        this->_gpioClockPin->set();
        delayUs(clockPeriod / 2);
        this->_gpioClockPin->clr();
    }

    return;
}

void Tm1637::_readByte(uint8_t *byteRead_p)
{
    // FIXME: Implement this function
    return;
}

bool_t Tm1637::_readAck(void)
{
    // Releases DIO line
    this->_gpioDataPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    // Reads ACK bit
    delayUs(clockPeriod / 2);
    this->_gpioClockPin->set();
    this->_gpioDataPin->read();
    delayUs(clockPeriod / 2);
    this->_gpioClockPin->clr();

    return true;
}

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

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

// NONE

/**
 * @endcond
*/

// =============================================================================
// End of file (tm1637.cpp)
// =============================================================================
