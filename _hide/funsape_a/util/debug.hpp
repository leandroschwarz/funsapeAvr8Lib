/**
 *******************************************************************************
 * @file            debug.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __DEBUG_HPP
#define __DEBUG_HPP                     2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [debug.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __DEBUG_HPP
#   error [debug.hpp] Error 2 - Build mismatch between file (debug.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

// #include "bus.hpp"
// #if !defined(__BUS_HPP)
// #   error [debug.hpp] Error 1 - Header file (bus.hpp) is missing or corrupted!
// #elif __BUS_HPP != __DEBUG_HPP
// #   error [debug.hpp] Error 5 - Build mismatch between file (debug.hpp) and library dependency (bus.hpp)!
// #endif

#include "usart0.hpp"
#if !defined(__USART0_HPP)
#   error [debug.hpp] Error 1 - Header file (usart0.hpp) is missing or corrupted!
#elif __USART0_HPP != __DEBUG_HPP
#   error [debug.hpp] Error 5 - Build mismatch between file (debug.hpp) and library dependency (usart0.hpp)!
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
// Doxygen: Start subgroup "Util/Debug"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Debug
 * @brief           Debug module.
 * @{
*/

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

#define debugMark(identifier_p, module_p)       do{usart0.stdio();debug.logMark((uint8_t *)__FILE__, __LINE__, (uint8_t *)identifier_p, (Debug::CodeIndex)module_p);}while (0)
#define debugMessage(errorCode_p, module_p)     do{usart0.stdio();debug.logMessage(errorCode_p, (uint8_t *)__FILE__, __LINE__, module_p);}while(0)

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
 * @brief           Debug class.
 * @details         This class handle calendar and clock data.
 * @attention       The @ref debug instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Debug
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        Month
     * @brief       Month enumerations.
     * @details     Month enumerations.
    */
    enum class CodeIndex : uint8_t {
        ADC_MODULE                              = 0,
        BUS_HANDLER_MODULE                      = 1,
        CIRCULAR_BUFFER_MODULE                  = 2,
        DATE_TIME_MODULE                        = 3,
        GPIO_BUS_MODULE                         = 4,
        GPIO_PIN_MODULE                         = 5,
        INT0_MODULE                             = 6,
        INT1_MODULE                             = 7,
        PCINT0_MODULE                           = 8,
        PCINT1_MODULE                           = 9,
        PCINT2_MODULE                           = 10,
        TIMER0_MODULE                           = 11,
        TIMER1_MODULE                           = 12,
        TIMER2_MODULE                           = 13,
        TWI_MODULE                              = 14,
        NOKIA5110_MODULE                        = 15,

        AHT21_MODULE                            = 16,
        BH1750_MODULE                           = 17,
        BME280_MODULE                           = 18,
        BMP280_MODULE                           = 19,
        DS1307_MODULE                           = 20,
        ENS160_MODULE                           = 21,
        Hd44780_MODULE                          = 22,
        KEYPAD_MODULE                           = 23,
        NMEA_PARSER_MODULE                      = 24,
        PARSER_API_MODULE                       = 25,
        SEVEN_SEGMENTS_MUX_DISPLAY_MODULE       = 26,
        SN74595_MODULE                          = 27,
        STEPPER_MODULE                          = 28,
        TM1637_MODULE                           = 29,
        MPU9250_MODULE                          = 30,
    };

private:
#define     DEBUG_CODE_INDEX_LAST       30

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Debug class constructor.
     * @details     Creates a Debug object. The object still must be
     *                   feed with data before use.
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Debug(
            void
    );

    /**
     * @brief       Debug class destructor.
     * @details     Destroys a Debug object.
    */
    ~Debug(
            void
    );

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
    void inlined hideMarks(
            void
    );
    void inlined hideSuccess(
            void
    );
    bool_t init(
            // Bus *busHandler_p,
            cbool_t stopOnError_p = true
    );
    void inlined setStopOnError(
            cbool_t stopOnError_p
    );
    void inlined setTimeOut(
            cuint16_t timeOut_p
    );
    void inlined showMarks(
            void
    );
    void inlined showSuccess(
            void
    );

    //     //////////////////    MESSAGE FUNCTIONS     //////////////////     //

    void logMark(
            cuint8_t *file_p,
            cuint16_t line_p,
            cuint8_t *identifier_p,
            const CodeIndex module_p
    );
    void logMessage(
            const Error errorCode_p,
            cuint8_t *file_p,
            cuint16_t line_p
    );
    void logMessage(
            const Error errorCode_p,
            cuint8_t *file_p,
            cuint16_t line_p,
            const CodeIndex module_p
    );
    bool_t printMessage(
            cchar_t *message_p
    );

    //     ///////////////////    MODULES CONTROL     ///////////////////     //

    void inlined debugAdc(
            cbool_t enable_p
    );
    void inlined debugAht21(
            cbool_t enable_p
    );
    void inlined debugBh1750(
            cbool_t enable_p
    );
    void inlined debugBme280(
            cbool_t enable_p
    );
    void inlined debugBmp280(
            cbool_t enable_p
    );
    void inlined debugBus(
            cbool_t enable_p
    );
    void inlined debugCircularBuffer(
            cbool_t enable_p
    );
    void inlined debugDateTime(
            cbool_t enable_p
    );
    void inlined debugDs1307(
            cbool_t enable_p
    );
    void inlined debugEns160(
            cbool_t enable_p
    );
    void inlined debugGpioBus(
            cbool_t enable_p
    );
    void inlined debugGpioPin(
            cbool_t enable_p
    );
    void inlined debugHd44780(
            cbool_t enable_p
    );
    void inlined debugInt0(
            cbool_t enable_p
    );
    void inlined debugInt1(
            cbool_t enable_p
    );
    void inlined debugKeypad(
            cbool_t enable_p
    );
    void inlined debugNmeaParser(
            cbool_t enable_p
    );
    void inlined debugPcint0(
            cbool_t enable_p
    );
    void inlined debugPcint1(
            cbool_t enable_p
    );
    void inlined debugPcint2(
            cbool_t enable_p
    );
    void inlined debugSevenSegmentsMuxDisplay(
            cbool_t enable_p
    );
    void inlined debugSn74595(
            cbool_t enable_p
    );
    void inlined debugStepper(
            cbool_t enable_p
    );
    void inlined debugTimer0(
            cbool_t enable_p
    );
    void inlined debugTimer1(
            cbool_t enable_p
    );
    void inlined debugTimer2(
            cbool_t enable_p
    );
    void inlined debugTm1637(
            cbool_t enable_p
    );
    void inlined debugTwi(
            cbool_t enable_p
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    // Bus              *_busHandler;
    bool_t          _isInitialized      : 1;
    Error           _lastError;
    bool_t          _list[DEBUG_CODE_INDEX_LAST];
    bool_t          _showMarks          : 1;
    bool_t          _showSuccess        : 1;
    bool_t          _stopOnError        : 1;
    uint16_t        _timeOut;

protected:
    // NONE

}; // class Debug

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Debug::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

void inlined Debug::hideMarks(void)
{
    this->_showMarks = false;
}

void inlined Debug::hideSuccess(void)
{
    this->_showSuccess = false;
}

void inlined Debug::setStopOnError(cbool_t stopOnError_p)
{
    this->_stopOnError = stopOnError_p;
}

void inlined Debug::setTimeOut(cuint16_t timeOut_p)
{
    this->_timeOut = timeOut_p;
}

void inlined Debug::showMarks(void)
{
    this->_showMarks = true;
}

void inlined Debug::showSuccess(void)
{
    this->_showSuccess = true;
}

//     ///////////////////    MODULES CONTROL     ///////////////////     //

void inlined Debug::debugAdc(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::ADC_MODULE] = enable_p;
}

void inlined Debug::debugAht21(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::AHT21_MODULE] = enable_p;
}

void inlined Debug::debugBh1750(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::BH1750_MODULE] = enable_p;
}

void inlined Debug::debugBme280(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::BME280_MODULE] = enable_p;
}

void inlined Debug::debugBmp280(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::BMP280_MODULE] = enable_p;
}

void inlined Debug::debugBus(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::BUS_HANDLER_MODULE] = enable_p;
}

void inlined Debug::debugCircularBuffer(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::CIRCULAR_BUFFER_MODULE] = enable_p;
}

void inlined Debug::debugDateTime(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::DATE_TIME_MODULE] = enable_p;
}

void inlined Debug::debugDs1307(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::DS1307_MODULE] = enable_p;
}

void inlined Debug::debugEns160(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::ENS160_MODULE] = enable_p;
}

void inlined Debug::debugGpioBus(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::GPIO_BUS_MODULE] = enable_p;
}

void inlined Debug::debugGpioPin(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::GPIO_PIN_MODULE] = enable_p;
}

void inlined Debug::debugHd44780(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::Hd44780_MODULE] = enable_p;
}

void inlined Debug::debugInt0(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::INT0_MODULE] = enable_p;
}

void inlined Debug::debugInt1(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::INT1_MODULE] = enable_p;
}

void inlined Debug::debugKeypad(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::KEYPAD_MODULE] = enable_p;
}

void inlined Debug::debugNmeaParser(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::NMEA_PARSER_MODULE] = enable_p;
}

void inlined Debug::debugPcint0(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::PCINT0_MODULE] = enable_p;
}

void inlined Debug::debugPcint1(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::PCINT1_MODULE] = enable_p;
}

void inlined Debug::debugPcint2(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::PCINT2_MODULE] = enable_p;
}

void inlined Debug::debugSevenSegmentsMuxDisplay(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE] = enable_p;
}

void inlined Debug::debugSn74595(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::SN74595_MODULE] = enable_p;
}

void inlined Debug::debugStepper(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::STEPPER_MODULE] = enable_p;
}

void inlined Debug::debugTimer0(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::TIMER0_MODULE] = enable_p;
}

void inlined Debug::debugTimer1(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::TIMER1_MODULE] = enable_p;
}

void inlined Debug::debugTimer2(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::TIMER2_MODULE] = enable_p;
}

void inlined Debug::debugTm1637(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::TM1637_MODULE] = enable_p;
}

void inlined Debug::debugTwi(cbool_t enable_p)
{
    this->_list[(uint8_t)Debug::CodeIndex::TWI_MODULE] = enable_p;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             debug
 * @brief           Debug module handler object.
 * @details         Debug module handler object. Use this object to handle the
 *                      debug module.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances.
*/
extern Debug debug;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Util/Debug"
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

#endif  // __DEBUG_HPP

// =============================================================================
// End of file (debug.hpp)
// =============================================================================
