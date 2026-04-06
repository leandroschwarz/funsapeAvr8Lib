//!
//! \file           funsapeLibTwiHd44780.hpp
//! \brief          Twi Hd44780 LCD module interface for FunSAPE AVR8 Library
//! \author         Davi Feitosa
//! \date           2025-12-14
//! \version        24.07
//! \copyright      license
//! \details        Character LCD controller using 8- or 4-bits interface with
//!                     support to busy flag or delay-driven
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTwiHd44780.hpp"
#if !defined(__FUNSAPE_LIB_TWIHD44780_HPP)
#   error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TWIHD44780_HPP != 2407
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

void doWrite(uint16_t value_p);

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

// PCF8574 pins connected to LCD control lines
#define PCF8574_PIN_RS 0x01 // Register Select: P0 (Data/Command)
#define PCF8574_PIN_RW 0x02 // Read/Write: P1 (Always Write in this driver)
#define PCF8574_PIN_E 0x04 // Enable: P2 (Pulse to latch data)
#define PCF8574_PIN_P3 0x08 // Backlight control (often P3)

// Data lines (D4-D7) mapped to PCF8574 pins P4-P7
#define PCF8574_PIN_DB4 0x10
#define PCF8574_PIN_DB5 0x20
#define PCF8574_PIN_DB6 0x40
#define PCF8574_PIN_DB7 0x80

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// Static function declarations
// =============================================================================

static int twiLcdWriteStd(char character, FILE *stream);

// =============================================================================
// File exclusive - Global variables
// =============================================================================

FILE twiLcdStream                          = {0};
TwiHd44780 *defaultTwiDisplay                 = nullptr;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

TwiHd44780::TwiHd44780(uint8_t addr)
{
    fdev_setup_stream(&twiLcdStream, twiLcdWriteStd, nullptr, _FDEV_SETUP_WRITE);

    // Reset data members
    this->_deviceAddress                = addr;
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

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return;
}

TwiHd44780::~TwiHd44780()
{
    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //

bool TwiHd44780::init(const Size size_p, const Font font_p)
{
    debugMark("TwiHd44780::init(const Size, const Font)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Reset the controller, must be sent 3 times
    delayMs(15);

    // Local variables
    uint8_t auxCmd                      = 0;

    // Updates some member variables
    this->_font                         = font_p;
    this->_isBusyInitialized            = false;
    this->_isInterfaceInitialized       = false;

    // Configures the LCD to 4-bits interface
    this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    delayMs(5);
    this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    delayUs(100);
    this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    delayUs(100);
    this->_functionSet4Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_4_BITS_INTERFACE);
    delayUs(100);

    // Function set
    auxCmd = (LCD_FUNCTION_SET | LCD_FUNCTION_SET_4_BITS_INTERFACE);
    auxCmd |= (font_p == Font::FONT_5X8) ? LCD_FUNCTION_SET_5x8_FONT : LCD_FUNCTION_SET_5x10_FONT;
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
    this->_displayOn                    = true;
    this->_cursorOn                     = false;
    this->_cursorBlink                  = false;
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;
    this->_lines                        = ((((uint8_t)size_p) * 2) / 100) - 1;
    this->_columns                      = ((((uint8_t)size_p) * 2) % 100) - 1;
    this->_isInterfaceInitialized       = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

//     //////////////////////    COMMANDS     ///////////////////////     //

bool_t TwiHd44780::clearScreen()
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::clearScreen(void)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Sends command
    if(!this->_writeCommand(LCD_CLEAR_DISPLAY)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool TwiHd44780::cursorGoTo(uint8_t line_p, uint8_t column_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorGoTo(cuint8_t, cuint8_t)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Local variables
    uint8_t address                     = 0xFF;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

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
        this->_cursorLine               = line_p;
        this->_cursorColumn             = column_p;
        this->_writeCommand((LCD_DDRAM_ADDRESS_SET | address));
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool TwiHd44780::cursorHome()
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorHome(void)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::cursorMove(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMove(const Direction)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Local variables
    uint8_t auxCommand = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_MOVE_CURSOR;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::cursorMoveFirstLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveFirstLine(void)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::cursorMoveNextLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveNextLine(void)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t currentLine                 = currentLine == _lines ? 0 : (this->_cursorLine + 1);

    if(!this->cursorGoTo(currentLine, 0)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::setDisplayState(const DisplayState displayState_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setDisplayState(const DisplayState)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = 0;
    bool_t auxDisplayOn                 = false;
    bool_t auxCursorOn                  = false;
    bool_t auxBlinkOn                   = false;

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
    this->_cursorBlink                  = auxBlinkOn;
    this->_cursorOn                     = auxCursorOn;
    this->_displayOn                    = auxDisplayOn;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::displayShift(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::displayShift(const Direction)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_SHIFT_DISPLAY;

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::setEntryMode(const Step incDec_p, const DisplayMode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setEntryMode(const Step, const DisplayMode)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = LCD_ENTRY_MODE_SET;

    auxCommand |= (this->_entryIncDec == Step::INCREMENT) ? LCD_ENTRY_MODE_SET_INCREMENT : LCD_ENTRY_MODE_SET_DECREMENT;
    auxCommand |= (this->_entryShiftDisplay == DisplayMode::SHIFT) ? LCD_ENTRY_MODE_SET_SHIFT :
            LCD_ENTRY_MODE_SET_OVERWRITE;
    this->_writeCommand(auxCommand);

    this->_entryIncDec                  = incDec_p;
    this->_entryShiftDisplay            = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool TwiHd44780::_writeCharacter(uint8_t character_p, bool_t ddramChar_p)
{
    if(!_writeData(character_p)) {
        return false;
    }

    // Update internal cursor position
    this->_cursorColumn++;

    // Check for line wrap
    if(this->_cursorColumn >= this->_columns) {
        this->_cursorMoveNextLine();
    }

    return true;
}

bool TwiHd44780::_cursorMoveNextLine()
{
    // Move to the next row
    this->_cursorLine++;

    // Check for display wrap (e.g., Row 1 -> Row 0)
    if(this->_cursorLine >= this->_rows) {
        this->_cursorLine = 0;
    }

    // Reset column to 0
    this->_cursorColumn = 0;

    // Update the LCD display with the new position
    return this->cursorGoTo(this->_cursorLine, this->_cursorColumn);
}

bool TwiHd44780::_cursorMove(uint8_t col_p, uint8_t row_p)
{
    if(this->cursorGoTo(row_p, col_p)) {
        this->_cursorColumn = col_p;
        this->_cursorLine = row_p;
        return true;
    }
    return false;
}

bool_t TwiHd44780::stdio()
{

    // 2. Redirect standard streams to the LCD
    stdin = stdout = stderr = &twiLcdStream;

    // 3. Set the global pointer so twiLcdWriteStd knows which object to use
    defaultTwiDisplay = this;

    // Assuming Error::NONE is defined in funsapeLibGlobalDefines.hpp
    // this->_lastError = Error::NONE;

    return true;
}

bool_t TwiHd44780::setCustomCharacter(cuint8_t charAddress_p, cuint8_t *charData_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setCustomCharacter(cuint8_t, cuint8_t *)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

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
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::print(uint8_t character_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::print(cchar_t)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    if(character_p == '\n') {
        // Pad the rest of the line with spaces
        for(uint8_t i = this->_cursorColumn; i < (this->_columns); i++) {
            this->_writeCharacter(' ', true);
        }
        this->_cursorMoveNextLine();
    } else {
        this->_writeCharacter(character_p, true);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::print(cchar_t character_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::print(cchar_t)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    if(character_p == '\n') {
        for(uint8_t i = this->_cursorColumn; i < (this->_columns); i++) {
            this->_writeCharacter(' ', true);
        }
        this->cursorMoveNextLine();
    } else {
        this->_writeCharacter(character_p, true);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

bool_t TwiHd44780::print(cchar_t *string_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::print(cchar_t *)", Debug::CodeIndex::TwiHd44780_MODULE);

    // Local variables
    uint8_t i = 0;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TwiHd44780_MODULE);
        return false;
    }

    while(string_p[i]) {
        this->print(string_p[i]);
        i++;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TwiHd44780_MODULE);
    return true;
}

static int twiLcdWriteStd(char character, FILE *stream)
{
    defaultTwiDisplay->print(character);
    return 0;
}

void TwiHd44780::_enablePulse(uint8_t data)
{
    uint8_t control = (data | PCF8574_PIN_E);
    // Send E HIGH
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, &control, 1);
    delayUs(1);

    control = (data);
    // Send E LOW
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, &control, 1);
    delayUs(1);
}

void TwiHd44780::_functionSet4Bits(uint8_t data_nibble)
{
    // RS=LOW (Command), R/W=LOW (Write), Backlight=HIGH (PCF8574_PIN_P3)
    uint8_t control = data_nibble | PCF8574_PIN_P3;

    // Send data to PCF8574 pins P4-P7 (upper nibble)
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, &control, 1);

    // Pulse E to latch the data
    _enablePulse(control);
}

// Original: HD44780_PCF8574__writeCommand
bool TwiHd44780::_writeCommand(uint8_t command_p)
{
    if(this->_useBusyFlag) {
        if(this->_isBusyInitialized) {
            this->_waitUntilReady();
        }
    }

    bool res = Send_8bits(command_p, PCF8574_PIN_P3); // PCF8574_PIN_P3 sets backlight

    if(!this->_useBusyFlag) {
        if((command_p == LCD_CLEAR_DISPLAY) || (command_p == LCD_RETURN_HOME)) {
            delayMs(2);
        } else {
            delayUs(40);
        }
    }
    return res;
}

bool_t TwiHd44780::_waitUntilReady(void)
{
    while(_isBusy()) {
        delayMs(10);
    };

    // Returns successfully
    return true;
}

bool TwiHd44780::_writeData(uint8_t data)
{
    // Data -> RS=HIGH
    return Send_8bits(data, PCF8574_PIN_RS | PCF8574_PIN_P3); // Sets RS and Backlight
}

bool TwiHd44780::_readData(const uint8_t *data)
{
    uint8_t read_byte = 0x00;

    // 1. Send E HIGH and R/W HIGH (Read mode)
    // The control byte sent here should include E=HIGH, R/W=HIGH, RS=LOW, Backlight=HIGH
    uint8_t control_high = PCF8574_PIN_E | PCF8574_PIN_RW | PCF8574_PIN_P3; // E | R/W | Backlight
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, (uint8_t *)&control_high, 1);

    // 2. Read the entire byte from the PCF8574 (P0-P7 pins)
    // The data read is the current state of the PCF8574 I/O pins, where P4-P7
    // now reflect the state of the LCD Data lines D7-D4.
    twi.sendData(_deviceAddress, Twi::Operation::READ, 0, (uint8_t *)&read_byte, 1);

    // 3. Send E LOW to latch the read data
    uint8_t control_low = PCF8574_PIN_RW | PCF8574_PIN_P3; // R/W | Backlight (E is LOW)
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, (uint8_t *)&control_low, 1);

    delayUs(1); // Small delay to ensure the pulse is registered

    // 4. Return only the data bits (P4-P7), shifted down.
    // The data is contained in bits D7-D4 of the read_byte.
    return true;
}

bool TwiHd44780::_isBusy()
{
    uint8_t data;
    if(!_readData(&data)) {
        this->_lastError = Error::COMMUNICATION_FAILED;
        debugMessage(Error::COMMUNICATION_FAILED, Debug::CodeIndex::TwiHd44780_MODULE);
        return true;
    }

    return (data & 0x80);
}

bool TwiHd44780::Send_8bits(uint8_t data, uint8_t annex)
{
    // 1. Upper Nibble
    uint8_t up_nibble = (data & 0xF0) | annex;
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, &up_nibble, 1);
    _enablePulse(up_nibble);

    // 2. Lower Nibble
    uint8_t low_nibble = (data << 4) | annex;
    twi.sendData(_deviceAddress, Twi::Operation::WRITE, 0, &low_nibble, 1);
    _enablePulse(low_nibble);

    return twi.getLastError() == Error::NONE;
}

// =============================================================================
// END OF FILE
// =============================================================================
