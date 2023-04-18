//!
//! \file           hd44780.cpp
//! \brief          Hd44780 LCD controller for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-12
//! \version        23.04
//! \copyright      license
//! \details        Character LCD controller using 8- or 4-bits interface with
//!                     support to busy flag or delay-driven
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "hd44780.hpp"
#if !defined(__HD44780_HPP)
#   error "Header file is corrupted!"
#elif __HD44780_HPP != 2304
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_HD44780                   0xF4FF

#define LCD_CLEAR_DISPLAY               0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE_SET              0x04
#define LCD_DISPLAY_CONTROL             0x08
#define LCD_MOVE_CURSOR_OR_DISPLAY      0x10
#define LCD_FUNCTION_SET                0x20
#define LCD_CGRAM_ADDRESS_SET           0x40
#define LCD_DDRAM_ADDRESS_SET           0x80

#define LCD_FUNCTION_SET_8_BITS_INTERFACE       0x10
#define LCD_FUNCTION_SET_4_BITS_INTERFACE       0x00
#define LCD_FUNCTION_SET_2_LINES                0x08
#define LCD_FUNCTION_SET_1_LINE                 0x00
#define LCD_FUNCTION_SET_5x10_FONT              0x04
#define LCD_FUNCTION_SET_5x8_FONT               0x00

#define LCD_DISPLAY_CONTROL_DISPLAY_ON          0x04
#define LCD_DISPLAY_CONTROL_DISPLAY_OFF         0x00
#define LCD_DISPLAY_CONTROL_CURSOR_ON           0x02
#define LCD_DISPLAY_CONTROL_CURSOR_OFF          0x00
#define LCD_DISPLAY_CONTROL_CURSOR_BLINK_ON     0x01
#define LCD_DISPLAY_CONTROL_CURSOR_BLINK_OFF    0x00

#define LCD_ENTRY_MODE_SET_INCREMENT            0x02
#define LCD_ENTRY_MODE_SET_DECREMENT            0x00
#define LCD_ENTRY_MODE_SET_SHIFT                0x01
#define LCD_ENTRY_MODE_SET_OVERWRITE            0x00

#define LCD_MOVE_CURSOR_OR_DISPLAY_SHIFT_DISPLAY    0x80
#define LCD_MOVE_CURSOR_OR_DISPLAY_MOVE_CURSOR      0x00
#define LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT            0x40
#define LCD_MOVE_CURSOR_OR_DISPLAY_LEFT             0x00

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// Static function declarations
// =============================================================================

static int lcdWriteStd(char character, FILE *stream);

// =============================================================================
// File exclusive - Global variables
// =============================================================================

FILE lcdStream;
Hd44780 *defaultDisplay;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

// Hd44780::Hd44780()
Hd44780::Hd44780()
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::Hd44780(void)", DEBUG_HD44780);

    fdev_setup_stream(&lcdStream, lcdWriteStd, nullptr, _FDEV_SETUP_WRITE);

    // Reset data members
    this->_controlDir                   = nullptr;
    this->_controlPout                  = nullptr;
    this->_controlE                     = 0;
    this->_controlRs                    = 0;
    this->_controlRw                    = 0;
    this->_dataDir                      = nullptr;
    this->_dataPout                     = nullptr;
    this->_dataPin                      = nullptr;
    this->_dataFirst                    = 0;
    this->_use4LinesData                = false;
    this->_useBusyFlag                  = false;
    this->_columns                      = 0;
    this->_lines                        = 0;
    this->_font                         = Font::FONT_5X8;
    this->_entryIncDec                  = Step::INCREMENT;
    this->_entryShiftDisplay            = DisplayMode::OVERWRITE;
    this->_cursorBlink                  = false;
    this->_cursorColumn                 = 0;
    this->_cursorLine                   = 0;
    this->_cursorOn                     = false;
    this->_displayOn                    = false;
    this->_isBusyInitialized            = false;
    this->_isInterfaceInitialized       = false;
    this->_isControlPortSet             = false;
    this->_isDataPortSet                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return;
}

// Hd44780::~Hd44780()
Hd44780::~Hd44780()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_HD44780);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Hd44780::init(const Size size_p, const Font font_p, cbool_t interface4Bits_p, cbool_t useBusyFlag_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::init(const Size, const Font, cbool_t, cbool_t)", DEBUG_HD44780);

    uint8_t auxCmd = 0;

    // Updates some struct variables
    this->_useBusyFlag = useBusyFlag_p;
    this->_use4LinesData = interface4Bits_p;
    this->_isBusyInitialized = false;
    this->_isInterfaceInitialized = false;
    this->_font = font_p;

    // I/O initialization
    if(interface4Bits_p) {
        clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);
        setMaskOffset(*(this->_dataDir), 0x0F, this->_dataFirst);
    } else {
        *(this->_dataPout) = 0x00;
        *(this->_dataDir) = 0xFF;
    }
    clrBit(*(this->_controlPout), this->_controlE);
    setBit(*(this->_controlDir), this->_controlE);
    clrBit(*(this->_controlPout), this->_controlRs);
    setBit(*(this->_controlDir), this->_controlRs);
    if(useBusyFlag_p) {
        clrBit(*(this->_controlPout), this->_controlRw);
        setBit(*(this->_controlDir), this->_controlRw);
    }

    // Reset the controller, must be sent 3 times
    delayMs(15);
    if(interface4Bits_p) {
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayMs(5);
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayUs(100);
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    } else {
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayMs(5);
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayUs(100);
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    }
    delayUs(100);

    // Configures the LCD to 4-bits interface
    if(interface4Bits_p) {
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_4_BITS_INTERFACE);
        delayUs(100);
    }

    // Function set
    auxCmd = LCD_FUNCTION_SET;
    auxCmd |= (interface4Bits_p) ? LCD_FUNCTION_SET_4_BITS_INTERFACE : LCD_FUNCTION_SET_8_BITS_INTERFACE;
    auxCmd |= (font_p == Font::FONT_5X8) ? LCD_FUNCTION_SET_5x8_FONT : LCD_FUNCTION_SET_5x10_FONT;
    this->_font = font_p;
    auxCmd |= (((uint8_t)size_p) < 100) ? LCD_FUNCTION_SET_1_LINE : LCD_FUNCTION_SET_2_LINES;
    this->_writeCommand(auxCmd);
    this->_isBusyInitialized = true;
    this->_writeCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_CONTROL_DISPLAY_OFF);
    this->_writeCommand(LCD_CLEAR_DISPLAY);

    auxCmd = LCD_ENTRY_MODE_SET;
    if(this->_entryIncDec == Step::INCREMENT) {
        auxCmd |= LCD_ENTRY_MODE_SET_INCREMENT;
    } else {
        auxCmd |= LCD_ENTRY_MODE_SET_DECREMENT;
    }
    if(this->_entryShiftDisplay == DisplayMode::SHIFT) {
        auxCmd |= LCD_ENTRY_MODE_SET_SHIFT;
    } else {
        auxCmd |= LCD_ENTRY_MODE_SET_OVERWRITE;
    }
    this->_writeCommand(auxCmd);

    this->_writeCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_CONTROL_DISPLAY_ON);

    // Updates the rest of the struct variables
    this->_displayOn = true;
    this->_cursorOn = false;
    this->_cursorBlink = false;
    this->_cursorLine = 0;
    this->_cursorColumn = 0;
    this->_lines = ((((uint8_t)size_p) * 2) / 100) - 1;
    this->_columns = ((((uint8_t)size_p) * 2) % 100) - 1;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

// -------------------------------------------------------------------------
// Methods -----------------------------------------------------------------

bool_t Hd44780::controlPortSet(ioRegAddress_t controlReg_p, const ioPinIndex_t controlE_p,
        const ioPinIndex_t controlRs_p, const ioPinIndex_t controlRw_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::controlPortSet(ioRegAddress_t, const ioPinIndex_t, const ioPinIndex_t, const ioPinIndex_t)",
            DEBUG_HD44780);

    // Check for errors
    if(!isGpioAddressValid(controlReg_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, DEBUG_HD44780);
        return false;
    }
    if(!isGpioPinIndexValid(controlE_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES, DEBUG_HD44780);
        return false;
    }
    if(!isGpioPinIndexValid(controlRs_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES, DEBUG_HD44780);
        return false;
    }
    if(!isGpioPinIndexValid(controlRw_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES, DEBUG_HD44780);
        return false;
    }

    // Updates data members
    this->_controlDir = getGpioDdrAddress(controlReg_p);
    this->_controlPout = getGpioPortAddress(controlReg_p);
    this->_controlE = controlE_p;
    this->_controlRs = controlRs_p;
    this->_controlRw = controlRw_p;
    this->_isControlPortSet = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::dataPortSet(ioRegAddress_t dataReg_p, const ioPinIndex_t dataFirst_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::dataPortSet(ioRegAddress_t, const ioPinIndex_t)", DEBUG_HD44780);

    // Check for errors
    if(!isGpioAddressValid(dataReg_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, DEBUG_HD44780);
        return false;
    }
    if(!isGpioPinIndexValid(dataFirst_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_INDEX_OUT_OF_BOUNDARIES, DEBUG_HD44780);
        return false;
    }

    // Updates data members
    this->_dataDir = getGpioDdrAddress(dataReg_p);
    this->_dataPout = getGpioPortAddress(dataReg_p);
    this->_dataPin = getGpioPinAddress(dataReg_p);
    this->_dataFirst = dataFirst_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

//     //////////////////////    COMMANDS     ///////////////////////     //

bool_t Hd44780::clearScreen(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::clearScreen(void)", DEBUG_HD44780);

    // Sends command
    if(!this->_writeCommand(LCD_CLEAR_DISPLAY)) {
        // Returns error
        debugMessage(this->_lastError, DEBUG_HD44780);
        return false;
    }
    this->_cursorLine = 0;
    this->_cursorColumn = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::cursorGoTo(cuint8_t line_p, cuint8_t column_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorGoTo(cuint8_t, cuint8_t)", DEBUG_HD44780);

    // Local variables
    uint8_t address = 0xFF;

    switch(line_p) {
    case 0:     // Go to line 0
        address = column_p;
        break;
    case 1:     // Go to line 1
        address = (this->_lines >= 1) ? (0x40 + column_p) : 0xFF;
        break;
    case 2:     // Go to line 2
        if((this->_lines == 3) && (this->_columns == 11)) {             // Display 12x4
            address = 0x0C + column_p;
        } else if((this->_lines == 3) && (this->_columns == 15)) {      // Display 16x4
            address = 0x10 + column_p;
        } else if((this->_lines == 3) && (this->_columns == 19)) {      // Display 20x4
            address = 0x14 + column_p;
        }
        break;
    case 3:     // Go to line 3
        if((this->_lines == 3) && (this->_columns == 11)) {             // Display 12x4
            address = 0x4C + column_p;
        } else if((this->_lines == 3) && (this->_columns == 15)) {      // Display 16x4
            address = 0x50 + column_p;
        } else if((this->_lines == 3) && (this->_columns == 19)) {      // Display 20x4
            address = 0x54 + column_p;
        }
        break;
    }

    if(address != 0xFF) {
        this->_cursorLine = line_p;
        this->_cursorColumn = column_p;
        this->_writeCommand((LCD_DDRAM_ADDRESS_SET | address));
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;

}

bool_t Hd44780::cursorHome(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorHome(void)", DEBUG_HD44780);

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, DEBUG_HD44780);
        return false;
    }
    this->_cursorLine = 0;
    this->_cursorColumn = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::cursorMove(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMove(const Direction)", DEBUG_HD44780);

    // Local variables
    uint8_t auxCommand = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_MOVE_CURSOR;

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::cursorMoveFirstLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveFirstLine(void)", DEBUG_HD44780);

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, DEBUG_HD44780);
        return false;
    }
    this->_cursorLine = 0;
    this->_cursorColumn = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::cursorMoveNextLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveNextLine(void)", DEBUG_HD44780);

    // Local variables
    uint8_t currentLine = (this->_cursorLine + 1);

    currentLine %= (this->_lines + 1);
    if(!this->cursorGoTo(currentLine, 0)) {
        // Returns error
        debugMessage(this->_lastError, DEBUG_HD44780);
        return false;
    }
    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::displayStateSet(const DisplayState displayState_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::displayStateSet(const DisplayState)", DEBUG_HD44780);

    // Local variables
    uint8_t auxCommand = 0;
    bool_t auxDisplayOn = false;
    bool_t auxCursorOn = false;
    bool_t auxBlinkOn = false;

    // Decodes display state
    switch(displayState_p) {
    case DisplayState::BLINK_ON:    auxDisplayOn = true;    auxCursorOn = true;     auxBlinkOn = true;  break;
    case DisplayState::CURSOR_ON:   auxDisplayOn = true;    auxCursorOn = true;     auxBlinkOn = false; break;
    case DisplayState::CURSOR_OFF:  auxDisplayOn = true;    auxCursorOn = false;    auxBlinkOn = false; break;
    case DisplayState::DISPLAY_OFF: auxDisplayOn = false;   auxCursorOn = false;    auxBlinkOn = false; break;
    }

    // Creates command
    auxCommand = LCD_DISPLAY_CONTROL;
    auxCommand |= (auxDisplayOn) ? LCD_DISPLAY_CONTROL_DISPLAY_ON : LCD_DISPLAY_CONTROL_DISPLAY_OFF;
    auxCommand |= (auxCursorOn) ? LCD_DISPLAY_CONTROL_CURSOR_ON : LCD_DISPLAY_CONTROL_CURSOR_OFF;
    auxCommand |= (auxBlinkOn) ? LCD_DISPLAY_CONTROL_CURSOR_BLINK_ON : LCD_DISPLAY_CONTROL_CURSOR_BLINK_OFF;
    this->_writeCommand(auxCommand);

    // Updates data members
    this->_cursorBlink = auxBlinkOn;
    this->_cursorOn = auxCursorOn;
    this->_displayOn = auxDisplayOn;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::displayShift(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::displayShift(const Direction)", DEBUG_HD44780);

    // Local variables
    uint8_t auxCommand = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_SHIFT_DISPLAY;

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::entryModeSet(const Step incDec_p, const DisplayMode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::entryModeSet(const Step, const DisplayMode)", DEBUG_HD44780);

    // Local variables
    uint8_t auxCommand = LCD_ENTRY_MODE_SET;

    auxCommand |= (this->_entryIncDec == Step::INCREMENT) ? LCD_ENTRY_MODE_SET_INCREMENT : LCD_ENTRY_MODE_SET_DECREMENT;
    auxCommand |= (this->_entryShiftDisplay == DisplayMode::SHIFT) ? LCD_ENTRY_MODE_SET_SHIFT :
            LCD_ENTRY_MODE_SET_OVERWRITE;
    this->_writeCommand(auxCommand);

    this->_entryIncDec = incDec_p;
    this->_entryShiftDisplay = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

bool_t Hd44780::stdio(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::init(Size, Font, bool_t, bool_t)", DEBUG_HD44780);

    stdin = stdout = stderr = &lcdStream;
    defaultDisplay = this;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;

}

bool_t Hd44780::customCharacterSet(cuint8_t charAddress_p, cuint8_t *charData_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::customCharacterSet(cuint8_t, cuint8_t *)", DEBUG_HD44780);

    if(this->_font == Font::FONT_5X8) {
        if(charAddress_p > 7) {
            return false;
        }
        this->_writeCommand(LCD_CGRAM_ADDRESS_SET | (charAddress_p * 8));
        for(uint8_t i = 0; i < 8; i++) {
            this->_writeCharacter(charData_p[i], false);
        }
    } else {
        if(charAddress_p > 3) {
            return false;
        }
        this->_writeCommand(LCD_CGRAM_ADDRESS_SET | (charAddress_p * 10));
        for(uint8_t i = 0; i < 10; i++) {
            this->_writeCharacter(charData_p[i], false);
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_HD44780);
    return true;
}

Error Hd44780::getLastError(void)
{
    // Returns error
    return this->_lastError;
}

// =============================================================================
// Class private methods
// =============================================================================

bool_t Hd44780::_functionSet8Bits(uint8_t command_p)
{
    if(this->_useBusyFlag) {
        clrBit(*(this->_controlPout), this->_controlRw);    // LCD in write mode
    }
    clrBit(*(this->_controlPout), this->_controlRs);        // LCD in command mode
    clrBit(*(this->_controlPout), this->_controlE);         // Makes sure enable is LOW
    clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);  // Writes data
    *(this->_dataPout) |= ((command_p >> 4) << this->_dataFirst);
    setBit(*(this->_controlPout), this->_controlE);         // Enable pulse start
    delayUs(1);
    clrBit(*(this->_controlPout), this->_controlE);         // Enable pulse end
    delayUs(1);
    if((!this->_useBusyFlag) || (!this->_isBusyInitialized)) {
        delayUs(40);
    }

    // Returns successfully
    return true;
}

bool_t Hd44780::_writeCommand(uint8_t command_p)
{
    if(this->_useBusyFlag) {
        if(this->_isBusyInitialized) {
            this->_waitUntilReady();
        }
        clrBit(*(this->_controlPout), this->_controlRw);    // LCD in write mode
    }
    clrBit(*(this->_controlPout), this->_controlRs);    // LCD in command mode
    clrBit(*(this->_controlPout), this->_controlE);     // Makes sure enable is LOW
    if(this->_use4LinesData) {
        clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);    // Writes data (higher nibble)
        *(this->_dataPout) |= ((command_p >> 4) << this->_dataFirst);
        setBit(*(this->_controlPout), this->_controlE);         // Enable pulse start
        delayUs(1);
        clrBit(*(this->_controlPout), this->_controlE);         // Enable pulse end
        delayUs(1);
        clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);    // Writes data (lower nibble)
        *(this->_dataPout) |= ((command_p & 0x0F) << this->_dataFirst);
    } else {
        *(this->_dataPout) = command_p;                       // Writes data
    }
    setBit(*(this->_controlPout), this->_controlE);     // Enable pulse start
    delayUs(1);
    clrBit(*(this->_controlPout), this->_controlE);     // Enable pulse end
    delayUs(1);
    if(!this->_useBusyFlag) {
        if((command_p == LCD_CLEAR_DISPLAY) || (command_p == LCD_RETURN_HOME)) {
            delayMs(2);
        } else {
            delayUs(40);
        }
    }

    // Returns successfully
    return true;
}

bool_t Hd44780::_waitUntilReady(void)
{
    uint8_t auxBusyFlag = 0;

    if(this->_use4LinesData) {
        clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);
        clrMaskOffset(*(this->_dataDir), 0x0F, this->_dataFirst);
    } else {
        *(this->_dataPout) = 0x00;
        *(this->_dataDir) = 0x00;
    }
    clrBit(*(this->_controlPout), this->_controlRs);    // LCD in command mode
    setBit(*(this->_controlPout), this->_controlRw);    // LCD in write mode
    clrBit(*(this->_controlPout), this->_controlE);     // Makes sure enable is LOW

    do {
        auxBusyFlag = 0;
        setBit(*(this->_controlPout), this->_controlE); // Enable pulse start
        delayUs(1);
        auxBusyFlag = *(this->_dataPin);
        if(this->_use4LinesData) {
            auxBusyFlag &= (0x08 << this->_dataFirst);
        } else {
            auxBusyFlag &= 0x80;
        }
        clrBit(*(this->_controlPout), this->_controlE); // Enable pulse end
        delayUs(1);
        if(this->_use4LinesData) {
            setBit(*(this->_controlPout), this->_controlE);     // Enable pulse start
            delayUs(1);
            clrBit(*(this->_controlPout), this->_controlE);     // Enable pulse end
            delayUs(1);
        }
    } while(auxBusyFlag);

    clrBit(*(this->_controlPout), this->_controlRw);    // LCD in write mode
    if(this->_use4LinesData) {
        clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);
        setMaskOffset(*(this->_dataDir), 0x0F, this->_dataFirst);
    } else {
        *(this->_dataPout) = 0x00;
        *(this->_dataDir) = 0xFF;
    }

    // Returns successfully
    return true;
}

bool_t Hd44780::_writeCharacter(uint8_t character_p, bool_t ddramChar_p)
{
    if((this->_cursorColumn < 40) || (!ddramChar_p)) {
        if(this->_useBusyFlag) {
            this->_waitUntilReady();
            clrBit(*(this->_controlPout), this->_controlRw);    // LCD in write mode
        }
        setBit(*(this->_controlPout), this->_controlRs);    // LCD in command mode
        clrBit(*(this->_controlPout), this->_controlE);     // Makes sure enable is LOW
        if(this->_use4LinesData) {
            clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);    // Writes data (higher nibble)
            *(this->_dataPout) |= ((character_p >> 4) << this->_dataFirst);
            setBit(*(this->_controlPout), this->_controlE);         // Enable pulse start
            delayUs(1);
            clrBit(*(this->_controlPout), this->_controlE);         // Enable pulse end
            delayUs(1);
            clrMaskOffset(*(this->_dataPout), 0x0F, this->_dataFirst);    // Writes data (lower nibble)
            *(this->_dataPout) |= ((character_p & 0x0F) << this->_dataFirst);
        } else {
            *(this->_dataPout) = character_p;                   // Writes data
        }
        setBit(*(this->_controlPout), this->_controlE);     // Enable pulse start
        delayUs(1);
        clrBit(*(this->_controlPout), this->_controlE);     // Enable pulse end
        if(!this->_useBusyFlag) {
            delayUs(40);
        }
        if(ddramChar_p) {
            this->_cursorColumn++;
        }
    }

    // Returns successfully
    return true;
}

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

static int lcdWriteStd(char character, FILE *stream)
{
    uint8_t columns = defaultDisplay->_columns + 1;
    uint8_t i = 0;

    if(character == '\n') {
        for(i = defaultDisplay->_cursorColumn; i < columns; i++) {
            defaultDisplay->_writeCharacter(' ', true);
        }
        defaultDisplay->cursorMoveNextLine();
    } else {
        defaultDisplay->_writeCharacter(character, true);
    }

    return 0;
}

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interruption handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
