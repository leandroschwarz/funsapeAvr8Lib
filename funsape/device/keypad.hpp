//!
//! \file           keypad.hpp
//! \brief          Matrix keypad controller for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Matrix keypad controller with support to 4x3, 4x4 and 5x3
//!                     keypads and configurable debounce time.
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __KEYPAD_HPP
#define __KEYPAD_HPP                            2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __KEYPAD_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __KEYPAD_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //
#include <stdarg.h>
#include <stdlib.h>

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //
#include <avr/builtins.h>

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

cuint8_t constDefaultDebounceTime       = 1;    //!< Default debounce time

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

//!
//! \brief          Keypad class
//! \details        Keypad class with support to 4x3, 4x4 and 5x3 keypads and
//!                     configurable debounce time.
//!
class Keypad
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ////////////////////     Keypad Type     /////////////////////     //
    //!
    //! \brief      Keypad type
    //! \details    Keypad type enumeration.
    //!
    enum class Type : uint8_t {
        KEYPAD_4X4                      = 0,
        KEYPAD_4X3                      = 1,
        KEYPAD_5X3                      = 2
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Keypad class constructor
    //! \details    Creates a Keypad object.
    //!
    Keypad(
            void
    );

    //!
    //! \brief      Keypad class destructor
    //! \details    Destroys a Keypad object.
    //!
    ~Keypad(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Keypad initialization
    //! \details    Initializes a Keypad object
    //! \param      debounceTime_p      Debounce time in milliseconds
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            cuint8_t debounceTime_p     = constDefaultDebounceTime
    );

    //!
    //! \brief      Set ports
    //! \details    This function sets the keypad columns and lines registers
    //!                 and bit positions.
    //! \param      linesRegAddress_p   Port register of the Keypad lines
    //! \param      linesFirstPin_p     Position of the first Keypad line bit
    //! \param      columnsRegAddress_p Port register of the Keypad columns
    //! \param      columnsFirstPin_p   Position of the first Keypad column bit
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setPorts(
            ioRegAddress_t linesRegAddress_p,
            ioPinIndex_t linesFirstPin_p,
            ioRegAddress_t columnsRegAddress_p,
            ioPinIndex_t columnsFirstPin_p
    );

    //!
    //! \brief      Sets the keypad type and key values
    //! \details    This function sets the keypad type and keys values.
    //! \param      type_p              Keypad type
    //! \param      ...                 Array of keypad key values (uint8_t)
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setKeyValues(
            Type type_p,
            ...
    );

    //!
    //! \brief      Reads the pressed key on the keypad.
    //! \details    This function gets the keypad status and decodes the pressed
    //!                 key.
    //! \param      keyPressedValue_p   Pointer to storethe pressed key value (0xFF if no key is pressed)
    //! \return     bool_t              True on success / False on failure
    //!
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

#endif  // __KEYPAD_HPP

// =============================================================================
// END OF FILE
// =============================================================================
