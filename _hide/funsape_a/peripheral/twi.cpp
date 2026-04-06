/**
 *******************************************************************************
 * @file            twi.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TWI peripheral control.
 * @details         This file provides control for the Two Wires Interface (TWI)
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

#include "twi.hpp"
#if !defined(__TWI_HPP)
#    error Error 1 - Header file (twi.hpp) is missing or corrupted!
#elif __TWI_HPP != 2508
#    error Error 6 - Build mismatch between header file (twi.hpp) and source file (twi.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// Bit rate values
cuint32_t   constTwiBitRateMin          = 1'000;
cuint32_t   constTwiBitRateTyp          = 10'000;
cuint32_t   constTwiBitRateMax          = 400'000;

// Timeout value
cuint16_t   constTwiDefaultTimeout      = 20;

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

Twi twi;

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

Twi::Twi(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::Twi(void)"), Debug::CodeIndex::TWI_MODULE);

    // Reset data members
    this->_bufferIndex                  = 0;
    this->_bufferLength                 = 0;
    this->_devAddress                   = 0;
    this->_devAddressSet                = false;
    this->_isInitialized                = false;
    this->_lastTransOk                  = false;
    this->_state                        = State::NO_STATE;
    this->_timeout                      = constTwiDefaultTimeout;
    this->_twiError                     = 0;
    this->_useLongAddress               = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return;
}

Twi::~Twi()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::~Twi(void)"), Debug::CodeIndex::TWI_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return;
}

// =============================================================================
// Class inherited methods - Public
// =============================================================================

//     //////////////////////    DATA TRANSFER     //////////////////////     //

bool_t Twi::read(uint8_t *buffData_p, cuint8_t buffSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::read(uint8_t *, cuint8_t)"), Debug::CodeIndex::TWI_MODULE);

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::DEVICE_NOT_SELECTED;
        debugMessage(Error::DEVICE_NOT_SELECTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - NOT Initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - Message pointer
    if(!isPointerValid(buffData_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - Message size
    if(buffSize_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else if(buffSize_p > TWI_BUFFER_SIZE) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        debugMessage(Error::NOT_IMPLEMENTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else {
        // Wait last transmission ends
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
            return false;
        }

        // Read data
        this->_bufferData[0] = (this->_devAddress << 1) | (uint8_t)(Operation::READ);
        this->_bufferLength = buffSize_p + 1;
        this->_startTransmission();
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
            return false;
        }
        // Gets data from reception buffer
        if(!this->_readFromBuffer(buffData_p, buffSize_p)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
            return false;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

bool_t Twi::readReg(cuint8_t reg_p, uint8_t *buffData_p, cuint8_t buffSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::readReg(cuint8_t, uint8_t *, cuint8_t)"), Debug::CodeIndex::TWI_MODULE);

    // Local variables
    bool_t auxBool                      = false;

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::DEVICE_NOT_SELECTED;
        debugMessage(Error::DEVICE_NOT_SELECTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        debugMessage(Error::NOT_IMPLEMENTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else {
        auxBool = this->_sendData((uint8_t)this->_devAddress, Operation::READ, reg_p, buffData_p, buffSize_p);
    }

    // Error - Communication error
    if(!auxBool) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

bool_t Twi::write(uint8_t *buffData_p, cuint8_t buffSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::write(uint8_t *, cuint8_t)"), Debug::CodeIndex::TWI_MODULE);

    // Local variables
    uint8_t auxRegAddress = 0;
    uint8_t auxBuff[33];

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::DEVICE_NOT_SELECTED;
        debugMessage(Error::DEVICE_NOT_SELECTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - NOT Initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - Message pointer
    if(!isPointerValid(buffData_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TWI_MODULE);
        return false;
    }
    // Check for errors - Message size
    if(buffSize_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else if(buffSize_p > TWI_BUFFER_SIZE) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        debugMessage(Error::NOT_IMPLEMENTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else {
        // Wait last transmission ends
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
            return false;
        }
    }

    // Prepares transmission buffer
    auxRegAddress = buffData_p[0];
    for(uint8_t i = 0; i < (buffSize_p - 1); i++) {
        auxBuff[i]
            = buffData_p[i + 1];
    }

    // Write data
    if(!this->writeReg(auxRegAddress, auxBuff, buffSize_p - 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

bool_t Twi::writeReg(cuint8_t reg_p, cuint8_t *buffData_p, cuint8_t buffSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::writeReg(cuint8_t, cuint8_t *, cuint8_t)"), Debug::CodeIndex::TWI_MODULE);

    // Local variables
    bool_t auxBool                      = false;

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::DEVICE_NOT_SELECTED;
        debugMessage(Error::DEVICE_NOT_SELECTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        debugMessage(Error::NOT_IMPLEMENTED, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else {
        auxBool = this->_sendData((uint8_t)this->_devAddress, Operation::WRITE, reg_p, (uint8_t *)buffData_p, buffSize_p);
    }

    // Error - Communication error
    if(!auxBool) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

//     ////////////////////    PROTOCOL SPECIFIC     ////////////////////     //

bool_t Twi::setDevice(cuint16_t address_p, cbool_t useLongAddress_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::setDevice(cuint16_t, cbool_t)"), Debug::CodeIndex::TWI_MODULE);

    // Update data members
    this->_devAddress                   = address_p;
    this->_useLongAddress               = useLongAddress_p;
    this->_devAddressSet                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

// =============================================================================
// Class inherited methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Twi::init(cuint32_t clockSpeed_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::init(cuint32_t)"), Debug::CodeIndex::TWI_MODULE);

    // Local variables
    uint32_t aux32                      = 0;
    uint8_t aux8                        = 0;

    // Disables TWI and reset all registers
    clrBit(TWCR, TWEN);
    TWCR = 0x00;
    TWSR = 0x00;
    TWBR = 0;
    TWAR = 0;
    TWAMR = 0;

    // Check for errors - Clock speed
    if(clockSpeed_p < constTwiBitRateMin) {
        // Returns error
        this->_lastError = Error::CLOCK_SPEED_TOO_LOW;
        debugMessage(Error::CLOCK_SPEED_TOO_LOW, Debug::CodeIndex::TWI_MODULE);
        return false;
    } else if(clockSpeed_p > constTwiBitRateMax) {
        // Returns error
        this->_lastError = Error::CLOCK_SPEED_TOO_HIGH;
        debugMessage(Error::CLOCK_SPEED_TOO_HIGH, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Evaluate BIT RATE and PRESCALER
    systemStatus.getCpuClock(&aux32);
    aux32 /= 2;
    aux32 -= 8;
    if(aux32 <= 255) {                  // Prescaler 1
        aux8 = (uint8_t)
                aux32;
    } else if(aux32 <= 255 * 4) {       // Prescaler 4
        aux8 = (uint8_t)
                (aux32 / 4);
        setMaskOffset(TWSR, 0x01, TWPS0);
    } else if(aux32 <= 255 * 16) {      // Prescaler 16
        aux8 = (uint8_t)
                (aux32 / 16);
        setMaskOffset(TWSR, 0x02, TWPS0);
    } else if(aux32 <= 255 * 64) {      // Prescaler 64
        aux8 = (uint8_t)
                (aux32 / 64);
        setMaskOffset(TWSR, 0x03, TWPS0);
    }

    // Updates TWI registers
    TWBR                                = aux8;
    TWDR                                = 0xFF;         // Release SDA
    setBit(TWCR, TWEN);                 // Activate TWI interface

    // Updates data members
    this->_isInitialized                = true;
    this->_bufferIndex                  = 0;
    this->_bufferLength                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

bool_t Twi::setTimeout(cuint16_t timeout_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::setTimeout(cuint16_t)"), Debug::CodeIndex::TWI_MODULE);

    // Updates data members
    this->_timeout = timeout_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return true;
}

//     ///////////////////////     INTERRUPTS     ///////////////////////     //

void Twi::interruptHandler(void)
{
    static uint8_t twiBufferPointer;

    State twiState = (Twi::State)(TWSR & 0xFC);

    switch(twiState) {
    case Twi::State::START:             // START has been transmitted
    case Twi::State::REP_START:         // Repeated START has been transmitted
        twiBufferPointer = 0;           // Set buffer pointer to the TWI Address location
    case Twi::State::MTX_ADR_ACK:       // SLA+W has been transmitted and ACK received
    case Twi::State::MTX_DATA_ACK:      // Data byte has been transmitted and ACK received
        if(twiBufferPointer < this->_bufferLength) {
            TWDR = this->_bufferData[twiBufferPointer++];
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
        } else {                        // Send STOP after last byte
            this->_lastTransOk = true;  // Set status bits to completed successfully
            TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
        }
        break;
    case Twi::State::MRX_DATA_ACK:      // Data byte has been received and ACK transmitted
        this->_bufferData[twiBufferPointer++] = TWDR;
    case Twi::State::MRX_ADR_ACK:       // SLA+R has been transmitted and ACK received
        if(twiBufferPointer < (this->_bufferLength - 1)) {  // Detect the last byte to NACK it
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
        } else {                        // Send NACK after next reception
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
        }
        break;
    case Twi::State::MRX_DATA_NACK:     // Data byte has been received and NACK transmitted
        this->_bufferData[twiBufferPointer] = TWDR;
        this->_lastTransOk = true;      // Set status bits to completed successfully
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
        break;
    case Twi::State::ARB_LOST:          // Arbitration lost
        TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTA);
        break;
    case Twi::State::MTX_ADR_NACK:      // SLA+W has been transmitted and NACK received
    case Twi::State::MRX_ADR_NACK:      // SLA+R has been transmitted and NACK received
    case Twi::State::MTX_DATA_NACK:     // Data byte has been transmitted and NACK received
    case Twi::State::BUS_ERROR:         // Bus error due to an illegal START or STOP condition
    default:
        this->_twiError = TWSR;         // Store TWSR and automatically sets clears noErrors bit
        TWCR = (1 << TWEN);             // Reset TWI Interface
        break;
    }

    return;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

bool_t Twi::_readFromBuffer(uint8_t *msg_p, cuint8_t msgSize_p)
{
    // Check for errors
    if(!this->_lastTransOk) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        return false;
    }
    for(uint8_t i = 0; i < msgSize_p; i++) {
        msg_p[i] = this->_bufferData[i + 1];
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::_sendData(uint8_t devAddress_p, Operation readWrite_p, uint8_t reg_p, uint8_t *msg_p, uint8_t msgSize_p)
{
    // Check for errors - NOT Initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }
    // Check for errors - Message pointer
    if((msgSize_p > 0) && (msg_p == nullptr)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }
    // Check for errors - Message size
    if(msgSize_p > TWI_BUFFER_SIZE) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::TWI_MODULE);
        return false;
    }

    // Wait last transmission ends
    if(!this->_waitWhileIsBusy()) {
        // Returns error
        return false;
    }

    // Prepare to send data
    if(readWrite_p == Operation::WRITE) {       // Write operation
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::WRITE);
        this->_bufferData[1] = reg_p;
        for(uint8_t i = 0; i < msgSize_p; i++) {
            this->_bufferData[i + 2] = msg_p[i];
        }
        this->_bufferLength = msgSize_p + 2;
        this->_startTransmission();
    } else {                            // Read operation
        // Set pointer first
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::WRITE);
        this->_bufferData[1] = reg_p;
        this->_bufferLength = 2;
        this->_startTransmission();
        // Wait last transmission ends
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            return false;
        }
        // Read data
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::READ);
        this->_bufferLength = msgSize_p + 1;
        this->_startTransmission();
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            return false;
        }
        // Gets data from reception buffer
        if(!this->_readFromBuffer(msg_p, msgSize_p)) {
            // Returns error
            return false;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::_startTransmission(void)
{
    this->_lastTransOk = false;
    this->_state = State::NO_STATE;
    TWCR = 0 |
            (1 << TWEN) |
            (1 << TWIE) |
            (1 << TWINT) |
            (1 << TWSTA);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::_waitWhileIsBusy(void)
{
    // Local variables
    uint32_t stopwatchMark;
    uint32_t stopwatchDeadline;

    // Evaluates stopwatch deadline
    if(this->_timeout == 0) {
        stopwatchDeadline = 0xFFFFFFFF;
    } else {
        stopwatchDeadline = 0;
        systemStatus.getStopwatchValue(&stopwatchDeadline);
        stopwatchDeadline += this->_timeout;
    }

    // Wait until TWI is ready for next transmission
    do {
        stopwatchMark = 0;
        systemStatus.getStopwatchValue(&stopwatchMark);
        if(stopwatchMark > stopwatchDeadline) {
            // Returns error
            this->_lastError = Error::TIMED_OUT;
            return false;
        }
    } while(isBitSet(TWCR, TWIE));

    // Returns successfully
    this->_lastError = Error::NONE;
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

#ifdef STILL_NOT_IMPLEMENTED

void weakened twiInterruptCallback(void)
{
    return;
}

#endif

// =============================================================================
// Interrupt handlers
// =============================================================================

/**
 * @cond
*/

ISR(TWI_vect)
{
    twi.interruptHandler();
}

/**
 * @endcond
*/

// =============================================================================
// End of file (twi.cpp)
// =============================================================================
