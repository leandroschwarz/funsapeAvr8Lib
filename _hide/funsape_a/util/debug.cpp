/**
 *******************************************************************************
 * @file            debug.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Debug support.
 * @details         This file provides extended debug support to all modules of
 *                       the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            This file is just a stub. Must implement the full file.
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

#include "debug.hpp"
#if !defined(__DEBUG_HPP)
#    error Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != 2508
#    error Error 6 - Build mismatch between header file (debug.hpp) and source file (debug.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint16_t           constDebugTimeOutDefault    = 30;

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

Debug debug;

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

Debug::Debug(void)
{
    // Resets data members
    // this->_busHandler       = nullptr;
    this->_isInitialized    = false;
    this->_showMarks        = false;
    this->_showSuccess      = false;
    this->_stopOnError      = true;
    this->_timeOut          = constDebugTimeOutDefault;

    for(uint8_t i = 0; i < DEBUG_CODE_INDEX_LAST; i++) {
        this->_list[i] = false;
    }

    this->_lastError        = Error::NONE;
}

Debug::~Debug(void)
{
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

// bool_t Debug::init(Bus *busHandler_p, cbool_t stopOnError_p)
bool_t Debug::init(cbool_t stopOnError_p)
{
    // Checks for errors
    // if(!isPointerValid(busHandler_p)) {
    //     this->_lastError = Error::ARGUMENT_POINTER_NULL;
    //     return false;
    // }

    // Update data members
    // this->_busHandler                   = busHandler_p;
    this->_isInitialized                = true;
    this->_stopOnError                  = stopOnError_p;

    usart0.enableTransmitter();
    usart0.init();

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     ////////////////////    MESSAGE FUNCTIONS     ////////////////////     //

void Debug::logMark(cuint8_t *file_p, cuint16_t line_p, cuint8_t *identifier_p, const CodeIndex module_p)
{
    // Local variables
    char auxMessage[100];

    // Just exits if user doesn't want to log marks
    if(!this->_showMarks) {
        return;
    }

    // Just exits if debug is disabled for the module
    if(!(this->_list[(uint8_t)module_p])) {
        return;
    }

    // Sends message
    sprintf_P(auxMessage, PSTR("-> %s : %d @ %s\r"), (char *)file_p, (uint16_t)line_p, (char *)identifier_p);
    printf(auxMessage);
    // this->_busHandler->sendData((uint8_t *)auxMessage, strlen(auxMessage));

    // Returns
    return;
}

void Debug::logMessage(const Error errorCode_p, cuint8_t *file_p, cuint16_t line_p)
{
    char auxMessage[100];

    // Just exits if user doesn't want to log success messages
    if((!this->_showSuccess) && (errorCode_p == Error::NONE)) {
        return;
    }

    // Sends message
    sprintf_P(auxMessage, PSTR("%s:%d - 0x%04X\r"), file_p, (uint16_t)line_p, (uint16_t)errorCode_p);
    printf(auxMessage);
    // this->_busHandler->sendData((uint8_t *)auxMessage, strlen(auxMessage));

    // If must stop on first error
    if((this->_stopOnError) && (errorCode_p != Error::NONE)) {
        systemHalt();
    }

    // Returns
    return;
}

void Debug::logMessage(const Error errorCode_p, cuint8_t *file_p, cuint16_t line_p, const CodeIndex module_p)
{
    char auxMessage[100];

    // Just exits if user doesn't want to log success messages
    if((!this->_showSuccess) && (errorCode_p == Error::NONE)) {
        return;
    }

    // Just exits if debug is disabled for the module
    if(!(this->_list[(uint8_t)module_p])) {
        return;
    }

    // Logs message
    sprintf_P(auxMessage, PSTR("%s:%d - 0x%04X\r"), file_p, (uint16_t)line_p, (uint16_t)errorCode_p);
    printf(auxMessage);
    // this->_busHandler->sendData((uint8_t *)auxMessage, strlen(auxMessage));

    // If must stop on first error
    if((this->_stopOnError) && (errorCode_p != Error::NONE)) {
        systemHalt();
    }

    // Returns
    return;
}

bool_t Debug::printMessage(cchar_t *message_p)
{
    // Sends message
    printf(message_p);
    // this->_busHandler->sendData((uint8_t *)message_p, strlen(message_p));

    // Return successfully
    this->_lastError = Error::NONE;
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
// End of file (debug.cpp)
// =============================================================================
