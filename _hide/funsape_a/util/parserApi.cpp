/**
 *******************************************************************************
 * @file            parserApi.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           API package parser module.
 * @details         This file provides a parser for API packages for the
 * *                    FunSAPE++ AVR8 Library.
 * @date            2025-29-10
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

#include "parserApi.hpp"
#if !defined(__PARSER_API_HPP)
#    error Error 1 - Header file (parserApi.hpp) is missing or corrupted!
#elif __PARSER_API_HPP != 2508
#    error Error 6 - Build mismatch between header file (parserApi.hpp) and source file (parserApi.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

static cuint8_t constFrameEscapeMask            = 0x20;
static cuint8_t constFrameEscapeChar            = 0x7D;
static cuint8_t constFrameStartDelimiter        = 0x7E;
static cuint8_t constFrameBroadcastAddress      = 0x00;

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

ParserApi::ParserApi()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("ParserApi::ParserApi(void)"), Debug::CodeIndex::PARSER_API_MODULE);

    // Resets data members
    this->_circularBuffer               = nullptr;
    this->_frameDestinationAddress      = 0;
    this->_frameIdentifier              = 0;
    this->_framePayloadIndex            = 0;
    this->_framePayloadLength           = 0;
    this->_frameSourceAddress           = 0;
    this->_frameState                   = FrameState::GET_START_DELIMITER;
    this->_isInitialized                = false;
    this->_mustEscapeNextChar           = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
    return;
}

ParserApi::~ParserApi()
{
    // Mark passage for debugging purpose
    debugMark(PSTR("ParserApi::~ParserApi(void)"), Debug::CodeIndex::PARSER_API_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t ParserApi::init(CircularBufferBase<uint8_t> *circBuffHandler_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("ParserApi::init(CircularBufferBase<uint8_t> *)"), Debug::CodeIndex::PARSER_API_MODULE);

    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    if(!isPointerValid(circBuffHandler_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }

    // Updates data members
    this->_framePayloadIndex            = 0;
    this->_framePayloadLength           = 0;
    this->_circularBuffer               = circBuffHandler_p;
    this->_frameDestinationAddress      = 0;
    this->_frameIdentifier              = 0;
    this->_frameSourceAddress           = 0;
    this->_frameState                   = FrameState::GET_START_DELIMITER;
    this->_isInitialized                = true;
    this->_mustEscapeNextChar           = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
    return true;
}

bool_t ParserApi::processFrame(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("ParserApi::processFrame(void)"), Debug::CodeIndex::PARSER_API_MODULE);

    // Local variables
    uint8_t aux8 = 0;
    static uint8_t auxChecksum = 0;

    // Checks for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }

    // If there is already a frame awaiting at the internal buffer
    if(this->_frameState == FrameState::FRAME_READY) {
        // Returns successfully
        this->_lastError = Error::NONE;
        debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
        return true;
    }

    // Otherwise, process the data
    while((!this->_circularBuffer->isEmpty()) && (this->_frameState != FrameState::FRAME_READY)) {

        // Gets data from circular buffer
        if(!this->_circularBuffer->pop(&aux8)) {
            // Returns error
            this->_lastError = this->_circularBuffer->getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::PARSER_API_MODULE);
            return false;
        }

        //Process escape char
        if(this->_mustEscapeNextChar) {                 // Last char was a escape
            this->_mustEscapeNextChar = false;              // - resets escape flag
            aux8 ^= constFrameEscapeMask;                   // - masks data char
        } else if(aux8 == constFrameEscapeChar) {       // Next char must be escaped
            this->_mustEscapeNextChar = true;               // - set escape flag
            continue;                                       // - process next loop
        }

        // Process data
        switch(this->_frameState) {

        case FrameState::GET_START_DELIMITER:
            // If it is not a START DELIMITER
            if(aux8 != constFrameStartDelimiter) {
                // Discards data and process next loop
                continue;
            }
            // Updates states machine
            this->_frameState = FrameState::GET_FRAME_IDENTIFIER;
            break;

        case FrameState::GET_FRAME_IDENTIFIER:
            // Stores frame identifier
            this->_frameIdentifier = aux8;
            // Updates states machine
            this->_frameState = FrameState::GET_DESTINATION_ADDRESS;
            break;

        case FrameState::GET_DESTINATION_ADDRESS:
            // Stores destination address
            this->_frameDestinationAddress = aux8;
            // Updates states machine
            this->_frameState = FrameState::GET_SOURCE_ADDRESS;
            break;

        case FrameState::GET_SOURCE_ADDRESS:
            // Checks if source address is valid
            if(aux8 == constFrameBroadcastAddress) {
                // Clears state machine
                this->_frameState = FrameState::GET_START_DELIMITER;
                // Returns error
                this->_lastError = Error::PARSER_API_SOURCE_ADDRESS_INVALID;
                debugMessage(Error::PARSER_API_SOURCE_ADDRESS_INVALID, Debug::CodeIndex::PARSER_API_MODULE);
                return false;
            }
            // Stores source address
            this->_frameSourceAddress = aux8;
            // Updates states machine
            this->_frameState = FrameState::GET_PAYLOAD_LENGHT;
            break;

        case FrameState::GET_PAYLOAD_LENGHT:
            // If payload length is zero
            if(aux8 == 0) {
                // Clears state machine
                this->_frameState = FrameState::GET_START_DELIMITER;
                // Returns error
                this->_lastError = Error::PARSER_API_PAYLOAD_SIZE_ZERO;
                debugMessage(Error::PARSER_API_PAYLOAD_SIZE_ZERO, Debug::CodeIndex::PARSER_API_MODULE);
                return false;
            }
            // If payload length is larger than buffer
            if(aux8 > PARSER_API_PAYLOAD_MAX_SIZE) {
                // Clears state machine
                this->_frameState = FrameState::GET_START_DELIMITER;
                // Returns error
                this->_lastError = Error::BUFFER_NOT_ENOUGH_ELEMENTS;
                debugMessage(Error::BUFFER_NOT_ENOUGH_ELEMENTS, Debug::CodeIndex::PARSER_API_MODULE);
                return false;
            }
            // Stores payload length
            this->_framePayloadLength = aux8;
            this->_framePayloadIndex = 0;
            auxChecksum = 0;
            // Updates states machine
            this->_frameState = FrameState::GET_PAYLOAD_DATA;
            break;

        case FrameState::GET_PAYLOAD_DATA:
            // Stores payload data
            this->_framePayloadBuffer[this->_framePayloadIndex++] = aux8;
            auxChecksum += aux8;
            // If last byte of payload
            if(this->_framePayloadIndex == this->_framePayloadLength) {
                // Updates states machine
                this->_frameState = FrameState::GET_CHECKSUM;
            }
            break;

        case FrameState::GET_CHECKSUM:
            // If checksum value is incorrect
            if((aux8 + auxChecksum) != 0xFF) {
                // Clears state machine
                this->_frameState = FrameState::GET_START_DELIMITER;
                // Returns error
                this->_lastError = Error::CHECKSUM_ERROR;
                debugMessage(Error::CHECKSUM_ERROR, Debug::CodeIndex::PARSER_API_MODULE);
                return false;
            }
            // Updates states machine
            this->_frameState = FrameState::FRAME_READY;
            break;

        default:
            // Returns error
            this->_lastError = Error::UNKNOWN;
            debugMessage(Error::UNKNOWN, Debug::CodeIndex::PARSER_API_MODULE);
            return false;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
    return true;
}

bool_t ParserApi::getFrameData(uint8_t *id_p, uint8_t *sourceAddress_p, uint8_t *destAddress_p, uint8_t *payLength_p,
        uint8_t *payBuffer_p, cuint8_t payMaxSize_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("ParserApi::getFrameData(uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *, cuint8_t)"),
            Debug::CodeIndex::PARSER_API_MODULE);

    // Checks for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }
    if(this->_frameState != FrameState::FRAME_READY) {
        // Returns error
        this->_lastError = Error::NOT_READY;
        debugMessage(Error::NOT_READY, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }
    if(payMaxSize_p < this->_framePayloadLength) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_SMALL;
        debugMessage(Error::BUFFER_SIZE_TOO_SMALL, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }
    if(
            (!isPointerValid(id_p)) ||
            (!isPointerValid(sourceAddress_p)) ||
            (!isPointerValid(destAddress_p)) ||
            (!isPointerValid(payLength_p)) ||
            (!isPointerValid(payBuffer_p))
    ) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::PARSER_API_MODULE);
        return false;
    }

    // Retrieve data from buffer
    *id_p               = this->_frameIdentifier;
    *sourceAddress_p    = this->_frameSourceAddress;
    *destAddress_p      = this->_frameDestinationAddress;
    *payLength_p        = this->_framePayloadLength;
    memcpy(payBuffer_p, this->_framePayloadBuffer, this->_framePayloadLength);

    // Resets the states machine
    this->_frameState           = FrameState::GET_START_DELIMITER;
    this->_framePayloadIndex    = 0;
    this->_mustEscapeNextChar   = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::PARSER_API_MODULE);
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
// End of file (parserApi.cpp)
// =============================================================================
