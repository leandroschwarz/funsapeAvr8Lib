/**
 *******************************************************************************
 * @file            parserApi.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __PARSER_API_HPP
#define __PARSER_API_HPP                2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [parserApi.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __PARSER_API_HPP
#   error [parserApi.hpp] Error 2 - Build mismatch between file (parserApi.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [parserApi.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __PARSER_API_HPP
#   error [parserApi.hpp] Error 5 - Build mismatch between file (parserApi.hpp) and library dependency (debug.hpp)!
#endif

#include "../util/circularBuffer.hpp"
#if !defined(__CIRCULAR_BUFFER_HPP)
#   error [parserApi.hpp] Error 1 - Header file (circularBuffer.hpp) is missing or corrupted!
#elif __CIRCULAR_BUFFER_HPP != __PARSER_API_HPP
#   error [parserApi.hpp] Error 5 - Build mismatch between file (parserApi.hpp) and library dependency (circularBuffer.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Util"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Util
 * @brief           Utilities.
 * @{
 */

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Util/Parser_API"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Parser_API
 * @brief           API package parser module.
 * @{
 */

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

#define PARSER_API_PAYLOAD_MAX_SIZE     32

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           ParserApi class.
 * @details         This class implements a parser for API packages.
 */
class ParserApi
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    // NONE

private:
    enum class FrameState : uint8_t {
        GET_START_DELIMITER             = 0,
        GET_FRAME_IDENTIFIER            = 1,
        GET_DESTINATION_ADDRESS         = 2,
        GET_SOURCE_ADDRESS              = 3,
        GET_PAYLOAD_LENGHT              = 4,
        GET_PAYLOAD_DATA                = 5,
        GET_CHECKSUM                    = 6,
        FRAME_READY                     = 7,
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       ParserApi class constructor.
     * @details     Creates a ParserApi object. The object still must be
     *                  initialized before use.
     * @see         init(CircularBuffer<uint8_t> *circBuffHandler_p, cuint8_t payloadMaxSize_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
     */
    ParserApi(
            void
    );

    /**
     * @brief       ParserApi class destructor.
     * @details     Destroys a ParserApi object.
     */
    ~ParserApi(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
     */
    Error inlined getLastError(
            void
    );

    /**
     * @brief       Returns if there is a new frame awaiting.
     * @details     Returns if there is a new frame awaiting.
     * @retval      true                if there is a new frame awaiting.
     * @retval      false               if there is a no frame awaiting.
     */
    bool_t inlined isFrameReady(
            void
    );

    /**
     * @brief       Initializes the ParserApi module.
     * @details     Initializes the ParserApi, according to the given
     *                  @a circBuffHandler_p Circular Buffer handler pointer and
     *                  @a payloadMaxSize_p size of the internal payload buffer.
     * @param[in]   circBuffHandler_p   Circular Buffer handler pointer.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                           | Meaning                                        |
     * |:-------------------------------------|:-----------------------------------------------|
     * | @ref Error::NONE                     | Success. No erros were detected.               |
     * | @ref Error::ARGUMENT_POINTER_NULL    | @a circBuffHandler_p cannot be a null pointer. |
     * | @ref Error::BUFFER_SIZE_TOO_SMALL    | @a payloadMaxSize_p must be at least 2.        |
     * | @ref Error::MEMORY_ALLOCATION_FAILED | Memory allocation procedure failed.            |
     *
     */
    bool_t init(
            CircularBufferBase<uint8_t>     *circBuffHandler_p
    );

    /**
     * @brief       Process the frame.
     * @details     Reads and decodes the data from the Circular Buffer if there
     *                  is no frame data awaiting to be read.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                                    | Meaning                                                      |
     * |:----------------------------------------------|:-------------------------------------------------------------|
     * | @ref Error::NONE                              | Success. No erros were detected.                             |
     * | @ref Error::NOT_INITIALIZED                   | The object was not initialized.                              |
     * | @ref Error::LOCKED                            | The circular buffer is locked.                               |
     * | @ref Error::READ_PROTECTED                    | The circular buffer is protected against read operations.    |
     * | @ref Error::BUFFER_EMPTY                      | The circular buffer is empty. There is no elements to read.  |
     * | @ref Error::PARSER_API_SOURCE_ADDRESS_INVALID | The source address cannot be a broadcast address.            |
     * | @ref Error::PARSER_API_PAYLOAD_SIZE_ZERO      | The payload size cannot be zero.                             |
     * | @ref Error::BUFFER_NOT_ENOUGH_ELEMENTS        | The internal buffer is too small to handle the payload data. |
     * | @ref Error::CHECKSUM_ERROR                    | The checksum failed.                                         |
     * | @ref Error::UNKNOWN                           | Opps...                                                      |
     *
     */
    bool_t processFrame(
            void
    );

    /**
     * @brief       Gets frame data.
     * @details     Retrieves frame data from internal buffer.
     * @param[in]   id_p                Pointer to store the frame
     *                                      identification.
     * @param[in]   sourceAddress_p     Pointer to store the frame source
     *                                      address.
     * @param[in]   destAddress_p       Pointer to store the frame destination
     *                                      address.
     * @param[in]   payLength_p         Pointer to store the frame payload
     *                                      length.
     * @param[in]   payBuffer_p         Pointer to the buffer to store the frame
     *                                      data.
     * @param[in]   payMaxSize_p        Max size of the buffer to store the
     *                                      frame data.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                                    | Meaning                                                   |
     * |:----------------------------------------------|:----------------------------------------------------------|
     * | @ref Error::NONE                              | Success. No erros were detected.                          |
     * | @ref Error::NOT_INITIALIZED                   | The object was not initialized.                           |
     * | @ref Error::NOT_READY                         | There is no new frame awaiting at the internal buffer.    |
     * | @ref Error::BUFFER_SIZE_TOO_SMALL             | The payload data length is greater than the given buffer. |
     * | @ref Error::ARGUMENT_POINTER_NULL             | One or more arguments is a null pointer.                  |
     *
     */
    bool_t getFrameData(
            uint8_t *id_p,
            uint8_t *sourceAddress_p,
            uint8_t *destAddress_p,
            uint8_t *payLength_p,
            uint8_t *payBuffer_p,
            cuint8_t payMaxSize_p
    );

    void inlined printDebug(
            void
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    Error                   _lastError;
    bool_t                  _isInitialized      : 1;
    FrameState              _frameState;

    //     ///////////////////    CIRCULAR BUFFER     ///////////////////     //
    CircularBufferBase<uint8_t> *_circularBuffer;

    //     /////////////////////     FRAME DATA     /////////////////////     //
    uint8_t                 _frameIdentifier;
    uint8_t                 _frameDestinationAddress;
    uint8_t                 _frameSourceAddress;
    uint8_t                 _framePayloadBuffer[PARSER_API_PAYLOAD_MAX_SIZE];
    uint8_t                 _framePayloadLength;
    uint8_t                 _framePayloadIndex;
    bool_t                  _mustEscapeNextChar : 1;

}; // class ParserApi

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
 */

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined ParserApi::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t inlined ParserApi::isFrameReady(void)
{
    // Returns if there is a new frame ready
    return (this->_frameState == FrameState::FRAME_READY) ? true : false;
}

void inlined ParserApi::printDebug(void)
{
    // printf("Last Error:   %04X\r", (uint16_t)this->_lastError);
    // printf("Frame State:  %u\r", (uint8_t)this->_frameState);
    // printf("Buff. Occup.: %u\r", this->_circularBuffer->getOccupation());
    // printf("Frame Id:     %02X\r", this->_frameIdentifier);
    // printf("Dest. Add.:   %02X\r", this->_frameDestinationAddress);
    // printf("Sour. Add.:   %02X\r", this->_frameSourceAddress);
    // printf("Must Escape:  %u\r", this->_mustEscapeNextChar);
    // printf("Pay. Index:   %02X\r", this->_framePayloadIndex);
    // printf("Pay. Length:  %02X\r", this->_framePayloadLength);
    // printf("Payload Data: ");
    // for(uint8_t i = 0; i < this->_framePayloadLength; i++) {
    //     printf("%02X ", this->_framePayloadBuffer[i]);
    // }
    // printf("\r\r");
};

/**
 * @endcond
 */

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Util/Parser_API"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
 */

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Util"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
 */

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __PARSER_API_HPP

// =============================================================================
// End of file (parserApi.hpp)
// =============================================================================
