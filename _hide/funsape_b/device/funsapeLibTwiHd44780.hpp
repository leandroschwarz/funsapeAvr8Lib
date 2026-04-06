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
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_TWIHD44780_HPP
#define __FUNSAPE_LIB_TWIHD44780_HPP                       2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_TWIHD44780_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../peripheral/funsapeLibTwi.hpp"
#if !defined(__FUNSAPE_LIB_TWI_HPP)
#   error "Header file (funsapeLibTwi.hpp) is corrupted!"
#elif __FUNSAPE_LIB_TWI_HPP != __FUNSAPE_LIB_TWIHD44780_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibTwi.hpp)!"
#endif

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_TWIHD44780_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

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

//!
//! \brief          Hd44780 class
//! \details        Hd44780 class.
//!
class TwiHd44780
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     //////////////////////     LCD SIZE     //////////////////////     //

    //!
    //! \brief      Display size
    //! \details    Display size enumeration.
    //!
    enum class Size : uint8_t {
        LCD_SIZE_UNDEFINED = 0,
        LCD_8X1     = 54,
        LCD_8X2     = 104,
        LCD_10x2    = 105,
        LCD_12X2    = 106,
        LCD_12X4    = 206,
        LCD_16X1    = 58,
        LCD_16X2    = 108,
        LCD_16X4    = 208,
        LCD_20X1    = 60,
        LCD_20X2    = 110,
        LCD_20X4    = 210,
        LCD_24X1    = 62,
        LCD_24X2    = 112,
        LCD_30X2    = 115,
        LCD_32X2    = 116,
        LCD_40X1    = 70,
        LCD_40X2    = 120
    };

    //     ////////////////////    LCD FONT SIZE     ////////////////////     //

    //!
    //! \brief      Font size
    //! \details    Font size enumeration.
    //!
    enum class Font : bool_t {
        FONT_5X8    = false,
        FONT_5X10   = true
    };

    //     /////////////////     DISPLAY ENTRY MODE     /////////////////     //

    //!
    //! \brief      Display mode
    //! \details    Display mode enumeration.
    //!
    enum class DisplayMode : bool_t {
        OVERWRITE   = false,
        SHIFT       = true,
    };

    //     /////////////////     DISPLAY ENTRY STEP     /////////////////     //

    //!
    //! \brief      Step
    //! \details    Step enumeration.
    //!
    enum class Step : bool_t {
        DECREMENT   = false,
        INCREMENT   = true,
    };

    //     ////////////////////    DISPLAY STATE     ////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //!
    enum class DisplayState {
        DISPLAY_OFF                     = 0,
        CURSOR_OFF                      = 1,
        CURSOR_ON                       = 2,
        BLINK_ON                        = 3
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    // Constructor: Takes the I2C slave address.
    TwiHd44780(uint8_t addr);

    //!
    //! \brief      Hd44780 class destructor
    //! \details    Destroys a Hd44780 object.
    //!
    ~TwiHd44780(
            void
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:

    //     ////////////////////    CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      size_p                  Param description
    //! \param      font_p                  Param description
    //! \return     bool_t                  Return info
    //!
    bool_t init(
            const Size size_p,
            const Font font_p           = Font::FONT_5X8
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t              Return info
    //!
    bool_t clearScreen();
    //!
    //! \brief Sets the cursor to the home position (0, 0) without clearing.
    //! \return True on success.
    //!
    bool_t cursorHome();
    //!
    //! \brief Sets the cursor position (column, row).
    //! \param col_p Column address (0 to NUM_COLS - 1).
    //! \param row_p Row address (0 to NUM_ROWS - 1).
    //! \return True on success.
    //!
    bool_t cursorGoTo(uint8_t col_p, uint8_t row_p);

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      direction_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMove(
            const Direction direction_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMoveFirstLine(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMoveNextLine(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      displayState_p      Param description
    //! \return     bool_t              Return info
    //!
    bool_t setDisplayState(
            const DisplayState displayState_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      direction_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t displayShift(
            const Direction direction_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      incDec_p                Param description
    //! \param      mode_p                  Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setEntryMode(
            const Step incDec_p,
            const DisplayMode mode_p
    );

    //!
    //! \brief Redirects standard I/O streams (stdout, stdin, stderr) to the LCD.
    //! \details After calling this, printf() will write to the LCD.
    //! \return True on success.
    //!
    bool_t stdio();

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      charAddress_p           Param description
    //! \param      charData_p              Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setCustomCharacter(
            cuint8_t charAddress_p,
            cuint8_t *charData_p
    );

    //!
    //! \brief Writes a single character to the LCD. Alias for SendData.
    //! \param character The character to display.
    //! \return True on success.
    //!
    bool_t print(uint8_t character);

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      character_p             Param description
    //! \return     bool_t              Return info
    //!
    bool_t print(
            cchar_t character_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      string_p         Param description
    //! \return     bool_t              Return info
    //!
    bool_t print(
            cchar_t *string_p
    );

private:
    //!
    //! \brief Sends an instruction command (RS=LOW) to the LCD.
    //! \param instruction The 8-bit instruction command.
    //! \return True on successful transmission.
    //!
    bool_t _writeCommand(uint8_t instruction);

    //!
    //! \brief Sends a data byte (character, RS=HIGH) to the LCD.
    //! \param data The 8-bit character data to display.
    //! \return True on successful transmission.
    //!
    bool_t _writeData(uint8_t data);

    //!
    //! \brief Reads a data byte (character, RS=HIGH) to the LCD.
    //! \param data The 8-bit character data of the display.
    //! \return True on successful transmission.
    //!
    bool_t _readData(const uint8_t *data);

    //! \brief Generates the Enable (E) pulse to latch data.
    void _enablePulse(uint8_t data);

    //!
    //! \brief Reads busy flag from display
    //! \return True if busy.
    //!
    bool_t _isBusy();

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t              Return info
    //!
    bool_t _waitUntilReady(
            void
    );

public:

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      character_p             Param description
    //! \param      ddramChar_p             Param description
    //! \return     bool_t              Return info
    //!
    bool_t _writeCharacter(
            uint8_t character_p,
            bool_t ddramChar_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isBusyInitialized          : 1;    // 0 off, 1 on
    bool_t          _isInterfaceInitialized     : 1;    // 0 off, 1 on
    Error           _lastError;

    //     ///////////////     HARDWARE CONFIGURATION     ///////////////     //

    uint8_t         _deviceAddress              : 8;
    bool_t          _useBusyFlag                : 1;
    uint8_t         _lines                      : 2;
    Font            _font                       : 1;

    //     ////////////////     CHARACTER ENTRY MODE     ////////////////     //

    Step            _entryIncDec                : 1;
    DisplayMode     _entryShiftDisplay          : 1;

    //     //////////////     DISPLAY AND CURSOR STATE     //////////////     //

    bool_t          _cursorBlink                : 1;    // 0 off, 1 on
    uint8_t         _cursorLine                 : 2;    // 0 to 3
    bool_t          _cursorOn                   : 1;    // 0 off, 1 on
    bool_t          _displayOn                  : 1;    // 0 off, 1 on

protected:

    // NONE

public:
    uint8_t         _columns                    : 6;
    uint8_t         _cursorColumn               : 6;    // 0 to 39

private:
    uint8_t i2c_addr;

    uint8_t _rows = 2; // Assuming 2 rows
    uint8_t _cursorRow = 0;

    //! \brief Sends a single 4-bit nibble, used only during the 4-bit initialization sequence.
    void _functionSet4Bits(uint8_t data_nibble);

    //! \brief Sends a full 8-bit command/data in two 4-bit transfers.
    bool Send_8bits(uint8_t data, uint8_t annex);

    bool _writeCharacter(uint8_t character_p);
    bool _cursorMoveNextLine();
    bool _cursorMove(uint8_t col_p, uint8_t row_p); // To update the internal state and LCD

}; // class Hd44780

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


#endif // __FUNSAPE_LIB_TWIHD44780_HPP

// =============================================================================
// END OF FILE - funsapeLibTwiHd44780.hpp
// =============================================================================
