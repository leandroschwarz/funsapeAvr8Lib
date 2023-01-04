/* =============================================================================
 * Project:         FunSAPE AVR8 Integrated Library
 * File:            funsapeAvrKeypad.hpp
 * Module:          Matrix keypad controller
 * Author:          Leandro Schwarz
 * Version:         22.0
 * Last edition:    2022-11-30
 * Purpose:         Matrix keypad controller with support to 4x3, 4x4 and 5x3
 *                      keypads and configurable debounce time.
 * ========================================================================== */

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_KEYPAD_HPP
#define __FUNSAPE_AVR_KEYPAD_HPP                        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_KEYPAD_HPP
#       error "Version mismatch between file header and global definitions file!"
#   endif
#else
#   error "Global definitions file is missing!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //
#include <stdarg.h>
#include <stdlib.h>

#include <avr/builtins.h>

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

cuint8_t constDefaultDebounceTime           = 1;

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
// Keypad Class
// =============================================================================

class Keypad
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    enum class Type : uint8_t {
        KEYPAD_4X4          = 0,
        KEYPAD_4X3          = 1,
        KEYPAD_5X3          = 2
    };


    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Keypad(
            void
    );
    ~Keypad(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //
    bool_t init(
            uint8_t debounceTime_p   = constDefaultDebounceTime
    );
    bool_t setPorts(
            ioRegAddress_t linesRegAddress_p,
            ioPinIndex_t linesFirstPin_p,
            ioRegAddress_t columnsRegAddress_p,
            ioPinIndex_t columnsFirstPin_p
    );
    bool_t setKeyValues(
            Type type_p,
            ...
    );
    bool_t readKeyPressed(
            uint8_t *keyPressedValue_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    ioRegAddress_t                      _linesDdr;
    ioRegAddress_t                      _linesPort;
    ioRegAddress_t                      _linesPin;
    ioPinIndex_t                        _linesFirst     : 3;
    ioRegAddress_t                      _columnsDdr;
    ioRegAddress_t                      _columnsPort;
    ioPinIndex_t                        _columnsFirst   : 3;
    Type                                _type;
    uint8_t                             _columnsMax     : 3;
    uint8_t                             _linesMax       : 3;
    bool_t                              _isPortsSet     : 1;
    bool_t                              _isKeyValuesSet : 1;
    bool_t                              _isInitialized  : 1;
    bool_t                              _debounceTime   : 7;
    uint8_t                             *_keyValue;
    Error                               _lastError;
}; // class Keypad

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_KEYPAD_HPP

// =============================================================================
// END OF FILE
// =============================================================================
