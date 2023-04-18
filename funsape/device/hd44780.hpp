//!
//! \file           hd44780.hpp
//! \brief          HD44780 LCD controller for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-12
//! \version        23.04
//! \copyright      license
//! \details        Character LCD controller using 8- or 4-bits interface with
//!                     support to busy flag or delay-driven
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __HD44780_HPP
#define __HD44780_HPP                           2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __HD44780_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __HD44780_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
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
// Hd44780 Class
// =============================================================================

//!
//! \brief          Hd44780 class
//! \details        Hd44780 class.
//!
class Hd44780
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     //////////////////////    LCD Type     ///////////////////////     //
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

    //     ////////////////////    LCD font size    /////////////////////     //
    //!
    //! \brief      Font size
    //! \details    Font size enumeration.
    //!
    enum class Font : bool_t {
        FONT_5X8    = false,
        FONT_5X10   = true
    };

    //     ////////////////////    Display mode     /////////////////////     //
    //!
    //! \brief      Display mode
    //! \details    Display mode enumeration.
    //!
    enum class DisplayMode : bool_t {
        OVERWRITE   = false,
        SHIFT       = true,
    };

    //     ////////////////////////     Step    /////////////////////////     //
    //!
    //! \brief      Step
    //! \details    Step enumeration.
    //!
    enum class Step : bool_t {
        DECREMENT   = false,
        INCREMENT   = true,
    };

    //     ////////////////////    Display State    /////////////////////     //
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

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Hd44780 class constructor
    //! \details    Creates a Hd44780 object.
    //!
    Hd44780(
            void
    );

    //!
    //! \brief      Hd44780 class destructor
    //! \details    Destroys a Hd44780 object.
    //!
    ~Hd44780(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      size_p                  Param description
    //! \param      font_p                  Param description
    //! \param      interface4Bits_p        Param description
    //! \param      useBusyFlag_p           Param description
    //! \return     bool_t                  Return info
    //!
    bool_t init(
            const Size size_p,
            const Font font_p,
            cbool_t interface4Bits_p,
            cbool_t useBusyFlag_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      controlReg_p            Param description
    //! \param      controlE_p              Param description
    //! \param      controlRs_p             Param description
    //! \param      controlRw_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t controlPortSet(
            ioRegAddress_t controlReg_p,
            const ioPinIndex_t controlE_p,
            const ioPinIndex_t controlRs_p,
            const ioPinIndex_t controlRw_p      = 0
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      dataReg_p               Param description
    //! \param      dataFirst_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t dataPortSet(
            ioRegAddress_t dataReg_p,
            const ioPinIndex_t dataFirst_p
    );

    //     //////////////////////    COMMANDS     ///////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t              Return info
    //!
    bool_t clearScreen(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      line_p                  Param description
    //! \param      column_p                Param description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorGoTo(
            cuint8_t line_p,
            cuint8_t column_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorHome(
            void
    );

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
    bool_t displayStateSet(
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
    bool_t entryModeSet(
            const Step incDec_p,
            const DisplayMode mode_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t stdio(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      charAddress_p           Param description
    //! \param      charData_p              Param description
    //! \return     bool_t                  Return info
    //!
    bool_t customCharacterSet(
            cuint8_t charAddress_p,
            cuint8_t *charData_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     Error               Return info
    //!
    Error getLastError(
            void
    );

private:
    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      command_p           Param description
    //! \return     bool_t              Return info
    //!
    bool_t _functionSet8Bits(
            uint8_t command_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      command             Param description
    //! \return     bool_t              Return info
    //!
    bool_t _writeCommand(
            uint8_t command_p
    );

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
    // Control I/O port
    ioRegAddress_t  _controlDir;
    ioRegAddress_t  _controlPout;
    ioPinIndex_t    _controlE                   : 3;
    ioPinIndex_t    _controlRs                  : 3;
    ioPinIndex_t    _controlRw                  : 3;
    // Data I/O port
    ioRegAddress_t  _dataDir;
    ioRegAddress_t  _dataPout;
    ioRegAddress_t  _dataPin;
    ioPinIndex_t    _dataFirst                  : 3;
    // Hardware layout
    bool_t          _use4LinesData              : 1;
    bool_t          _useBusyFlag                : 1;
    uint8_t         _columns                    : 6;
    uint8_t         _lines                      : 2;
    Font            _font                       : 1;
    // Entry mode
    Step            _entryIncDec                : 1;
    DisplayMode     _entryShiftDisplay          : 1;
    // Display and cursor
    bool_t          _cursorBlink                : 1;    // 0 off, 1 on
    uint8_t         _cursorColumn               : 6;    // 0 to 39
    uint8_t         _cursorLine                 : 2;    // 0 to 3
    bool_t          _cursorOn                   : 1;    // 0 off, 1 on
    bool_t          _displayOn                  : 1;    // 0 off, 1 on
    // General status
    bool_t          _isBusyInitialized          : 1;    // 0 off, 1 on
    bool_t          _isInterfaceInitialized     : 1;    // 0 off, 1 on
    bool_t          _isControlPortSet           : 1;    // 0 off, 1 on
    bool_t          _isDataPortSet              : 1;    // 0 off, 1 on
    Error           _lastError;
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

#endif  // __HD44780_HPP

// =============================================================================
// END OF FILE
// =============================================================================
