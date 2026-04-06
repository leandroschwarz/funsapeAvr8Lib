/**
 *******************************************************************************
 * @file            tm1637.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TM1637 display module interface for the  FunSAPE++ AVR8
 *                      Library.
 * @details         TM1637 display module interface for the  FunSAPE++ AVR8
 *                      Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            Implement _readByte() and readKeypadData() functions.
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

#ifndef __TM1637_HPP
#define __TM1637_HPP                    2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [tm1637.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __TM1637_HPP
#   error [tm1637.hpp] Error 2 - Build mismatch between file (tm1637.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [tm1637.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __TM1637_HPP
#   error [tm1637.hpp] Error 5 - Build mismatch between file (tm1637.hpp) and library dependency (debug.hpp)!
#endif

#include "../peripheral/gpioPin.hpp"
#ifndef __GPIO_PIN_HPP
#   error [tm1637.hpp] Error 1 - Header file (gpioPin.hpp) is missing or corrupted!
#elif __GPIO_PIN_HPP != __TM1637_HPP
#   error [tm1637.hpp] Error 5 - Build mismatch between file (tm1637.hpp) and library dependency (gpioPin.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Devices
 * @brief           External devices.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Devices/TM1637"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      TM1637
 * @brief           TM1637 display controller module.
 * @{
*/

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

/**
 * @brief           Tm1637 class.
 * @details         This class can handle multiplexed seven segments displays,
 *                      from 2 to 8 digits based on TM1637 display controller.
*/
class Tm1637
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    enum class Contrast : uint8_t {
        PERCENT_6_25                    = 0,
        PERCENT_13                      = 1,
        PERCENT_26                      = 2,
        PERCENT_62_5                    = 3,
        PERCENT_68_75                   = 4,
        PERCENT_75                      = 5,
        PERCENT_81_25                   = 6,
        PERCENT_87_5                    = 7,
    };

private:
    //     //////////////////////     COMMANDS     //////////////////////     //
    enum class Command : uint8_t {
        DATA_SETTING                    = 0x40,
        DISPLAY_ADDRESS                 = 0xC0,
        DISPLAY_CONTROL                 = 0x80,
    };
    //     ////////////////////    BIT POSITIONS     ////////////////////     //
    enum class BitPos : uint8_t {
        // Command setting
        DATA_SETTING_MODE_READ          = 1,
        DATA_SETTING_FIXED_ADDRESS      = 2,
        DATA_SETTING_TEST_MODE          = 3,
        // Display address
        DISPLAY_ADDRESS                 = 0,
        // Display control
        DISPLAY_CONTROL_CONTRAST        = 0,
        DISPLAY_CONTROL_SHOW            = 3,
    };
    //     //////////////////////     BIT MASK     //////////////////////     //
    enum class BitMask : uint8_t {
        // Command setting
        DATA_SETTING_MODE_READ          = 0x01,
        DATA_SETTING_FIXED_ADDRESS      = 0x01,
        DATA_SETTING_TEST_MODE          = 0x01,
        // Display address
        DISPLAY_ADDRESS                 = 0x07,
        // Display control
        DISPLAY_CONTROL_CONTRAST        = 0x07,
        DISPLAY_CONTROL_SHOW            = 0x01,
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Tm1637 class constructor.
     * @details     Creates a Tm1637 object. The object still
     *                  must be initialized before use.
     * @see         init(void).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Tm1637(
            void
    );

    /**
     * @brief       Tm1637 class destructor.
     * @details     Destroys a Tm1637 object.
    */
    ~Tm1637(
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

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

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
     * @brief       Initializes a Tm1637 object.
     * @details     This function initializes the Tm1637 object.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     *
     * @par Error codes:
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t init(
            void
    );

    bool_t setAddressingMode(
            cbool_t useAutoIncrementMode_p
    );

    /**
     * @brief       Set data and control pins.
     * @details     This function sets the data and clock pins.
     * @param[out]  gpioDioPin_p        Pointer to @ref GpioPin of the data pin.
     * @param[out]  gpioClkPin_p        Pointer to @ref GpioPin of the clock
     *                                      pin.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     *
     * @par Error codes:
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setPorts(
            GpioPin *gpioDioPin_p,
            GpioPin *gpioClkPin_p
    );

    //     ///////////////////    DISPLAY CONTROL     ///////////////////     //

    bool_t setDisplayContrast(
            const Contrast contrastLevel_p
    );

    bool_t showDisplay(
            cbool_t showDisplay_p
    );

    bool_t writeDisplayData(
            cuint16_t displayValue_p,
            cuint8_t base_p = 10
    );

    bool_t writeDisplayData(
            cuint8_t segments_p,
            cuint8_t index_p,
            cbool_t showDot_p
    );

    //     ///////////////////     KEYPAD CONTROL     ///////////////////     //

    bool_t readKeypadData(
            uint8_t *keyPressed_p
    );

private:
    //     ///////////////     COMMUNICATION PROTOCOL     ///////////////     //

    bool_t _readAck(
            void
    );

    void _readByte(
            uint8_t *byteRead_p
    );

    void _sendStart(
            void
    );

    void _sendStop(
            void
    );

    void _writeByte(
            cuint8_t byteToWrite_p
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     ///////////////////    DEVICE BUS PORT     ///////////////////     //

    GpioPin                             *_gpioClockPin;
    GpioPin                             *_gpioDataPin;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t                              _isInitialized          : 1;
    bool_t                              _isPortsSet             : 1;
    Error                               _lastError;
    bool_t                              _useAutoIncrementMode   : 1;

    //     ///////////////////    DISPLAY CONTROL     ///////////////////     //
    Contrast                            _contrastLevel;
    bool_t                              _showDisplay;

protected:
    // NONE

}; // class Tm1637

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Tm1637::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Devices/TM1637"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
* @}
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
*/

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __TM1637_HPP

// =============================================================================
// End of file (tm1637.hpp)
// =============================================================================
