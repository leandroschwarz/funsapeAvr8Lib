//!
//! \file           keypad.cpp
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
// System file dependencies
// =============================================================================

#include "keypad.hpp"
#if !defined(__KEYPAD_HPP)
#   error "Header file is corrupted!"
#elif __KEYPAD_HPP != 2304
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_KEYPAD                    0xFFFF

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

Keypad::Keypad(void)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::Keypad(void)", DEBUG_KEYPAD);

    // Reset data members
    this->_linesDdr                     = nullptr;
    this->_linesPort                    = nullptr;
    this->_linesPin                     = nullptr;
    this->_linesFirst                   = 0;
    this->_columnsDdr                   = nullptr;
    this->_columnsPort                  = nullptr;
    this->_columnsFirst                 = 0;
    this->_type                         = Type::KEYPAD_4X4;
    this->_columnsMax                   = 0;
    this->_linesMax                     = 0;
    this->_isPortsSet                   = false;
    this->_isKeyValuesSet               = false;
    this->_isInitialized                = false;
    this->_debounceTime                 = constDefaultDebounceTime;
    this->_keyValue                     = nullptr;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
    return;
}

Keypad::~Keypad(void)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::~Keypad(void)", DEBUG_KEYPAD);

    // Deallocate memory
    if(isPointerValid(this->_keyValue)) {
        free(this->_keyValue);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t Keypad::init(cuint8_t debounceTime_p)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::init(cuint8_t)", DEBUG_KEYPAD);

    // Check for errors - PORTS NOT SET
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, DEBUG_KEYPAD);
        return false;
    }
    // Check for errors - KEY VALUES NOT SET
    if(!this->_isKeyValuesSet) {
        // Returns error
        this->_lastError = Error::KEY_VALUES_NOT_SET;
        debugMessage(Error::KEY_VALUES_NOT_SET, DEBUG_KEYPAD);
        return false;
    }
    // Checks for erros - I/O PIN INDEX INVALID
    if(!isGpioPinIndexValid(this->_columnsFirst + this->_columnsMax)) {
        // Returns error
        this->_lastError = Error::KEYPAD_LINES_PIN_INDEX_INVALID;
        debugMessage(Error::KEYPAD_LINES_PIN_INDEX_INVALID, DEBUG_KEYPAD);
        return false;
    }
    if(!isGpioPinIndexValid(this->_linesFirst + this->_linesMax)) {
        // Returns error
        this->_lastError = Error::KEYPAD_COLUMNS_PIN_INDEX_INVALID;
        debugMessage(Error::KEYPAD_COLUMNS_PIN_INDEX_INVALID, DEBUG_KEYPAD);
        return false;
    }

    // Configures GPIOs
    switch(this->_type) {
    case Type::KEYPAD_4X4:
        clrMaskOffset(*(this->_linesDdr), 0x0F, this->_linesFirst);
        setMaskOffset(*(this->_linesPort), 0x0F, this->_linesFirst);
        setMaskOffset(*(this->_columnsDdr), 0x0F, this->_columnsFirst);
        setMaskOffset(*(this->_columnsPort), 0x0F, this->_columnsFirst);
        break;
    case Type::KEYPAD_4X3:
        clrMaskOffset(*(this->_linesDdr), 0x0F, this->_linesFirst);
        setMaskOffset(*(this->_linesPort), 0x0F, this->_linesFirst);
        setMaskOffset(*(this->_columnsDdr), 0x07, this->_columnsFirst);
        setMaskOffset(*(this->_columnsPort), 0x07, this->_columnsFirst);
        break;
    case Type::KEYPAD_5X3:
        clrMaskOffset(*(this->_linesDdr), 0x1F, this->_linesFirst);
        setMaskOffset(*(this->_linesPort), 0x1F, this->_linesFirst);
        setMaskOffset(*(this->_columnsDdr), 0x07, this->_columnsFirst);
        setMaskOffset(*(this->_columnsPort), 0x07, this->_columnsFirst);
        break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        debugMessage(Error::UNKNOWN, DEBUG_KEYPAD);
        return false;
    }

    // Update data members
    this->_debounceTime = debounceTime_p;
    this->_isInitialized = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
    return true;
}

bool_t Keypad::setPorts(ioRegAddress_t linesRegAddress_p, ioPinIndex_t linesFirstPin_p,
        ioRegAddress_t columnsRegAddress_p, ioPinIndex_t columnsFirstPin_p)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::setPorts(ioRegAddress_t, ioPinIndex_t, ioRegAddress_t, ioPinIndex_t)", DEBUG_KEYPAD);

    // Resets data members
    this->_linesDdr             = nullptr;
    this->_linesPort            = nullptr;
    this->_linesPin             = nullptr;
    this->_linesFirst           = 0;
    this->_columnsDdr           = nullptr;
    this->_columnsPort          = nullptr;
    this->_columnsFirst         = 0;
    this->_isPortsSet           = false;

    // Check for errors
    if(!isGpioAddressValid(linesRegAddress_p)) {
        // Returns error
        this->_lastError = Error::KEYPAD_LINES_GPIO_PORT_INVALID;
        debugMessage(Error::KEYPAD_LINES_GPIO_PORT_INVALID, DEBUG_KEYPAD);
        return false;
    }
    if(!isGpioAddressValid(columnsRegAddress_p)) {
        // Returns error
        this->_lastError = Error::KEYPAD_COLUMNS_GPIO_PORT_INVALID;
        debugMessage(Error::KEYPAD_COLUMNS_GPIO_PORT_INVALID, DEBUG_KEYPAD);
        return false;
    }

    // Updates data members
    this->_linesDdr             = getGpioDdrAddress(linesRegAddress_p);
    this->_linesPort            = getGpioPortAddress(linesRegAddress_p);
    this->_linesPin             = getGpioPinAddress(linesRegAddress_p);
    this->_linesFirst           = linesFirstPin_p;
    this->_columnsDdr           = getGpioDdrAddress(columnsRegAddress_p);
    this->_columnsPort          = getGpioPortAddress(columnsRegAddress_p);
    this->_columnsFirst         = columnsFirstPin_p;
    this->_isPortsSet           = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
    return true;
}

bool_t Keypad::setKeyValues(Type type_p, ...)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::setKeyValues(Keypad::Type, ...)", DEBUG_KEYPAD);

    // Reset data members
    this->_isKeyValuesSet = false;

    // Keypad type
    switch(type_p) {
    case Type::KEYPAD_4X4:
        this->_linesMax = 3;
        this->_columnsMax = 3;
        ;
        break;
    case Type::KEYPAD_4X3:
        this->_linesMax = 3;
        this->_columnsMax = 2;
        ;
        break;
    case Type::KEYPAD_5X3:
        this->_linesMax = 4;
        this->_columnsMax = 2;
        break;
    default:
        // Returns error
        this->_lastError = Error::KEYPAD_TYPE_UNSUPPORTED;
        debugMessage(Error::KEYPAD_TYPE_UNSUPPORTED, DEBUG_KEYPAD);
        return false;
    }
    this->_type = type_p;

    // Memory allocation
    this->_keyValue = (uint8_t *)realloc(this->_keyValue, (this->_linesMax + 1) * (this->_columnsMax + 1));
    if(!isPointerValid(this->_keyValue)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION;
        debugMessage(Error::MEMORY_ALLOCATION, DEBUG_KEYPAD);
        return false;
    }

    // Updates key values
    do {
        va_list auxArgs;
        va_start(auxArgs, type_p);
        for(uint8_t i = 0; i < (this->_linesMax + 1); i++) {
            for(uint8_t j  = 0; j < (this->_columnsMax + 1); j++) {
                this->_keyValue[((this->_linesMax + 1) *  i) + j] = (uint8_t)va_arg(auxArgs, int16_t);
            }
        }
        va_end(auxArgs);
        this->_isKeyValuesSet = true;
    } while(0);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
    return true;
}

bool_t Keypad::readKeyPressed(uint8_t *keyPressedValue_p)
{

    // Local variables
    uint8_t auxKey = 0xFF;

    // Checks for errors
    if(!this->_isInitialized) {
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, DEBUG_KEYPAD);
        return false;
    }
    if(!isPointerValid(keyPressedValue_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, DEBUG_KEYPAD);
        return false;
    }

    for(uint8_t i = 0; i <= this->_columnsMax; i++) {                   // For each column
        clrBit(*(this->_columnsPort), (i + this->_columnsFirst));       // Clear one column
        __builtin_avr_delay_cycles(5);                                  // Wait for syncronization
        uint8_t aux8 = *(this->_linesPin) >> this->_linesFirst;
        for(uint8_t j = 0; j <= this->_linesMax; j++) {                         // For each line
            if(isBitClr(aux8, j)) {                                     // Tests if the key is pressed
                auxKey = this->_keyValue[((this->_linesMax + 1) * j) + i];      // Decodes the key using the table
                for(uint8_t k = 0; k < this->_debounceTime; k++) {
                    _delay_ms(1);                                       // Debounce time
                }
            }
            // Wait until key is released
            waitUntilBitIsSet(*(this->_linesPin) >> this->_linesFirst, j);
        }
        setBit(*(this->_columnsPort), (i + this->_columnsFirst));       // Restore column value
    }

    // Update function arguments
    *keyPressedValue_p = auxKey;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_KEYPAD);
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
