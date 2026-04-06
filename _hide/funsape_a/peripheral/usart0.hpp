/**
 *******************************************************************************
 * @file            usart0.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           UART/USART communication peripheral control.
 * @details         This file provides control for the UART/USART 0 (USART0)
 *                      communication peripheral for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            USART and USART in SPI mode.
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

#ifndef __USART0_HPP
#define __USART0_HPP                    2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [usart0.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __USART0_HPP
#   error [usart0.hpp] Error 2 - Build mismatch between file (usart0.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [usart0.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __USART0_HPP
#   error [usart0.hpp] Error 5 - Build mismatch between file (usart0.hpp) and library dependency (debug.hpp)!
#endif

// #include "../util/bus.hpp"
// #if !defined(__BUS_HPP)
// #   error [usart0.hpp] Error 1 - Header file (bus.hpp) is missing or corrupted!
// #elif __BUS_HPP != __USART0_HPP
// #   error [usart0.hpp] Error 5 - Build mismatch between file (usart0.hpp) and library dependency (bus.hpp)!
// #endif

#include "../util/systemStatus.hpp"
#if !defined(__SYSTEM_STATUS_HPP)
#   error [usart0.hpp] Error 1 - Header file (systemStatus.hpp) is missing or corrupted!
#elif __SYSTEM_STATUS_HPP != __USART0_HPP
#   error [usart0.hpp] Error 5 - Build mismatch between file (usart0.hpp) and library dependency (systemStatus.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Peripherals
 * @brief           Microcontroller peripherals.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Usart0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Usart0
 * @brief           Universal Synchronous/Asynchronous Receiver/Transmitter 0
 *                      (USART0)controller module.
 * @{
*/

// =============================================================================
// External global variables
// =============================================================================

//!
//! \cond
//!

extern FILE usartStream;

//!
//! \endcond
//!

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

/**
 * @brief           USART0 Reception Complete interrupt callback function.
 * @details         This function is called when the USART Reception Complete
 *                      interrupt is treated. It is a weak function that can be
 *                      overwritten by user code.
*/
void usart0ReceptionCompleteCallback(void);

/**
 * @brief           USART0 Transmission Buffer Empty interrupt callback function.
 * @details         This function is called when the USART Transmission Buffer
 *                      Empty interrupt is treated. It is a weak function that
 *                      can be overwritten by user code.
*/
void usart0TransmissionBufferEmptyCallback(void);

/**
 * @brief           USART0 Transmission Complete interrupt callback function.
 * @details         This function is called when the USART Transmission Complete
 *                      interrupt is treated. It is a weak function that can be
 *                      overwritten by user code.
*/
void usart0TransmissionCompleteCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Usart0 class.
 * @details         This class manages the Universal Synchronous/Asynchronous
 *                      Receiver/Transmitter 0 (USART0) peripheral.
 * @attention       The @ref usart0 instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Usart0
// : public Bus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        Mode
     * @brief       Operation mode associated with the USART0.
     * @details     Operation mode associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Mode : uint8_t {
        ASYNCHRONOUS                            = 0,    //!< Peripheral in UART without double speed mode.
        ASYNCHRONOUS_DOUBLE_SPEED               = 1,    //!< Peripheral in UART with double speed mode.
        SYNCHRONOUS_TX_RISING_RX_FALLING        = 2,    //!< Peripheral in USART mode on falling edge.
        SYNCHRONOUS_TX_FALLING_RX_RISING        = 3,    //!< Peripheral in USART mode on rising edge.
        MASTER_SPI_MODE_0                       = 4,    //!< Peripheral in master SPI mode 0.
        MASTER_SPI_MODE_1                       = 5,    //!< Peripheral in master SPI mode 1.
        MASTER_SPI_MODE_2                       = 6,    //!< Peripheral in master SPI mode 2.
        MASTER_SPI_MODE_3                       = 7,    //!< Peripheral in master SPI mode 3.
    };

    /**
     * @enum        ReceptionError
     * @brief       USART0 Reception Error enumeration.
     * @details     Reception error associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class ReceptionError : uint8_t {
        NONE                            = 0,            //!< No reception errors occurred.
        FRAME_ERROR                     = (1 << 0),     //!< Frame format invalid.
        PARITY_ERROR                    = (1 << 1),     //!< Parity check failed.
        DATA_OVERRUN_ERROR              = (1 << 2),     //!< Data lost.
        ALL                             = (1 << 0) | (1 << 1) | (1 << 2) //!< All errors
    };

    /**
     * @enum        ParityMode
     * @brief       USART0 Parity Mode enumeration.
     * @details     Parity mode associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class ParityMode : uint8_t {
        NONE                            = 0,    //!< No parity.
        ODD                             = 1,    //!< Odd parity.
        EVEN                            = 2     //!< Even parity.
    };

    /**
     * @enum        StopBits
     * @brief       USART0 StopBits enumeration.
     * @details     Number of stop bits associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class StopBits : uint8_t {
        SINGLE                          = 0,    //!< One stop bit.
        DOUBLE                          = 1     //|< Two stop bits.
    };

    /**
     * @enum        DataSize
     * @brief       USART0 DataSize enumeration.
     * @details     Data size associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class DataSize : uint8_t {
        DATA_5_BITS                     = 0,    //!< 5 data bits.
        DATA_6_BITS                     = 1,    //!< 6 data bits.
        DATA_7_BITS                     = 2,    //!< 7 data bits.
        DATA_8_BITS                     = 3,    //!< 8 data bits.
        DATA_9_BITS                     = 4,    //!< 9 data bits.
    };

    /**
     * @enum        FrameFormat
     * @brief       USART0 FrameFormat enumeration.
     * @details     Frame format mode associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class FrameFormat : uint8_t {
        //                      = 0bDDDDPPSS
        // DDDD -> Number of data bits (5-8)
        // PP   -> Parity (NONE / ODD / EVEN)
        // SS   -> Number of stop bits (1-2)
        FRAME_FORMAT_8_N_1        = 0b10000001,    //!< 8 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_8_O_1        = 0b10000101,    //!< 8 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_8_E_1        = 0b10001001,    //!< 8 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_8_N_2        = 0b10000010,    //!< 8 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_8_O_2        = 0b10000110,    //!< 8 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_8_E_2        = 0b10001010,    //!< 8 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_9_N_1        = 0b10010001,    //!< 9 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_9_O_1        = 0b10010101,    //!< 9 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_9_E_1        = 0b10011001,    //!< 9 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_9_N_2        = 0b10010010,    //!< 9 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_9_O_2        = 0b10010110,    //!< 9 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_9_E_2        = 0b10011010,    //!< 9 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_5_N_1        = 0b01010001,    //!< 5 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_5_O_1        = 0b01010101,    //!< 5 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_5_E_1        = 0b01011001,    //!< 5 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_5_N_2        = 0b01010010,    //!< 5 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_5_O_2        = 0b01010110,    //!< 5 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_5_E_2        = 0b01011010,    //!< 5 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_6_N_1        = 0b01100001,    //!< 7 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_6_O_1        = 0b01100101,    //!< 7 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_6_E_1        = 0b01101001,    //!< 7 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_6_N_2        = 0b01100010,    //!< 7 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_6_O_2        = 0b01100110,    //!< 7 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_6_E_2        = 0b01101010,    //!< 7 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_7_N_1        = 0b01110001,    //!< 7 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_7_O_1        = 0b01110101,    //!< 7 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_7_E_1        = 0b01111001,    //!< 7 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_7_N_2        = 0b01110010,    //!< 7 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_7_O_2        = 0b01110110,    //!< 7 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_7_E_2        = 0b01111010,    //!< 7 data bits / Parity EVEN / 2 stop bit.
    };

    /**
     * @enum        BaudRate
     * @brief       USART0 Baud Rate enumeration.
     * @details     Baud rate speed associated with the USART0.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class BaudRate : uint32_t {
        BAUD_RATE_600                   = 600UL,        //!< Baud rate = 600 bps.
        BAUD_RATE_1200                  = 1200UL,       //!< Baud rate = 1,200 bps.
        BAUD_RATE_1800                  = 1800UL,       //!< Baud rate = 1,800 bps.
        BAUD_RATE_2400                  = 2400UL,       //!< Baud rate = 2,400 bps.
        BAUD_RATE_4800                  = 4800UL,       //!< Baud rate = 4,800 bps.
        BAUD_RATE_9600                  = 9600UL,       //!< Baud rate = 9,600 bps.
        BAUD_RATE_14400                 = 14400UL,      //!< Baud rate = 14,400 bps.
        BAUD_RATE_19200                 = 19200UL,      //!< Baud rate = 19,200 bps.
        BAUD_RATE_28800                 = 28800UL,      //!< Baud rate = 28,800 bps.
        BAUD_RATE_38400                 = 38400UL,      //!< Baud rate = 38,400 bps.
        BAUD_RATE_56000                 = 56000UL,      //!< Baud rate = 56,000 bps.
        BAUD_RATE_57600                 = 57600UL,      //!< Baud rate = 57,600 bps.
        BAUD_RATE_115200                = 115200UL,     //!< Baud rate = 115,200 bps.
        BAUD_RATE_128000                = 128000UL,     //!< Baud rate = 128,000 bps.
        BAUD_RATE_230400                = 230400UL,     //!< Baud rate = 230,400 bps.
        BAUD_RATE_256000                = 256000UL      //!< Baud rate = 256,000 bps.
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Usart0 class constructor.
     * @details     Creates an Usart0 object. The object is loaded with the
     *                  default register values: @ref BaudRate::BAUD_RATE_9600,
     *                  @ref Mode::ASYNCHRONOUS and
     *                  @ref FrameFormat::FRAME_FORMAT_8_N_1. The object still
     *                  must be initialized before use.
     * @param[in]   baudRate_p          Baud rate value.
     * @param[in]   mode_p              Operation mode.
     * @param[in]   format_p            Format of the frame.
     * @see         init(void).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Usart0(
            const BaudRate baudRate_p = BaudRate::BAUD_RATE_9600,
            const Mode mode_p = Mode::ASYNCHRONOUS,
            const FrameFormat format_p = FrameFormat::FRAME_FORMAT_8_N_1
    );

    /**
     * @brief       Usart0 class destructor.
     * @details     Destroys an Usart0 object.
    */
    ~Usart0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
    */
    Error getLastError(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Disables the USART receiver.
     * @details     Disables the USART receiver.
    */
    void inlined disableReceiver(
            void
    );

    /**
     * @brief       Disables the USART transmitter.
     * @details     Disables the USART transmitter.
    */
    void inlined disableTransmitter(
            void
    );

    /**
     * @brief       Enables the USART receiver.
     * @details     Enables the USART receiver.
    */
    void inlined enableReceiver(
            void
    );

    /**
     * @brief       Enables the USART transmitter.
     * @details     Enables the USART transmitter.
    */
    void inlined enableTransmitter(
            void
    );

    /**
     * @brief       Gets the errors of the last reception.
     * @details     Gets the errors of the last reception.
     * @param[out]  errorCode_p         Pointer to store the reception error
     *                                      code.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
    */
    bool_t getReceptionErrors(
            ReceptionError *errorCode_p
    );

    /**
     * @brief       Initializes the Usart0 module.
     * @details     Initializes the Usart0 module.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                           | Meaning                                                  |
     * |:-------------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                     | Success. No erros were detected.                         |
     *
    */
    bool_t init(
            void
    );

    /**
     * @brief       Verifies the reception status.
     * @details     Verifies the reception status.
     * @retval      true                There is unread data on the reception
     *                                      buffer.
     * @retval      false               There is no unread data on the
     *                                      recception buffer.
    */
    bool_t inlined isReceptionComplete(
            void
    );

    /**
     * @brief       Verifies the transmission buffer status.
     * @details     Verifies the transmission buffer status.
     * @retval      true                The transmission buffer is ready to
     *                                      receive data.
     * @retval      false               The transmission buffer is full.
    */
    bool_t inlined isTransmissionBufferEmpty(
            void
    );

    /**
     * @brief       Verifies the transmission status.
     * @details     Verifies the transmission status.
     * @retval      true                The module is not busy transmitting
     *                                      data.
     * @retval      false               The module is busy transmitting data.
    */
    bool_t inlined isTransmissionComplete(
            void
    );

    /**
     * @brief       Sets the communication baud rate.
     * @details     Sets the communication baud rate.
     * @param[in]   baudRate_p          Baud rate value.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setBaudRate(
            const BaudRate baudRate_p
    );

    /**
     * @brief       Sets frame data size.
     * @details     Sets frame data size.
     * @param[in]   dataSize_p          Frame data size.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setDataSize(
            const DataSize dataSize_p
    );

    /**
     * @brief       Sets the Frame format.
     * @details     Sets the Frame format.
     * @param[in]   frameFormat_p       Frame format.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setFrameFormat(
            const FrameFormat frameFormat_p
    );

    /**
     * @brief       Sets operation mode.
     * @details     Sets operation mode.
     * @param[in]   operationMode_p     Operation mode.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setMode(
            const Mode operationMode_p
    );

    /**
     * @brief       Sets the parity mode.
     * @details     Sets the parity mode.
     * @param[in]   parityMode_p        Parity mode.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setParityMode(
            const ParityMode parityMode_p
    );

    /**
     * @brief       Sets number of stop bits.
     * @details     Sets number of stop bits.
     * @param[in]   stopBits_p            Number of stop bits.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setStopBits(
            const StopBits stopBits_p
    );

    //     /////////////////////     INTERRUPTS    //////////////////////     //

    /**
     * @brief       Activates the Reception Complete interrupt.
     * @details     Activates the Reception Complete interrupt.
    */
    void inlined activateReceptionCompleteInterrupt(
            void
    );

    /**
     * @brief       Activates the Transmission Buffer Empty interrupt.
     * @details     Activates the Transmission Buffer Empty interrupt.
    */
    void inlined activateTransmissionBufferEmptyInterrupt(
            void
    );

    /**
     * @brief       Activates the Transmission Complete interrupt.
     * @details     Activates the Transmission Complete interrupt.
    */
    void inlined activateTransmissionCompleteInterrupt(
            void
    );

    /**
     * @brief       Deactivates the Reception Complete interrupt.
     * @details     Deactivates the Reception Complete interrupt.
    */
    void inlined deactivateReceptionCompleteInterrupt(
            void
    );

    /**
     * @brief       Deactivates the Transmission Buffer Empty interrupt.
     * @details     Deactivates the Transmission Buffer Empty interrupt.
    */
    void inlined deactivateTransmissionBufferEmptyInterrupt(
            void
    );

    /**
     * @brief       Deactivates the Transmission Complete interrupt.
     * @details     Deactivates the Transmission Complete interrupt.
    */
    void inlined deactivateTransmissionCompleteInterrupt(
            void
    );

    //     ///////////////////    DATA PROCESSING    ////////////////////     //

    /**
     * @brief       Flushes the reception buffer.
     * @details     Flushes the reception buffer.
    */
    void flushReceptionBuffer(
            void
    );

    /**
     * @brief       Gets the received data.
     * @details     Gets the received data.
     * @param[out]  data_p              Pointer to store the received data.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
    */
    bool_t receiveData(
            uint16_t *data_p
    );

    /**
     * @brief       Receives data via standard data stream.
     * @details     Receives data via standard data stream.
     * @param[out]  stream_p            Pointer to data stream.
     * @return      char                Character received.
    */
    char receiveDataStd(
            FILE *stream_p
    );

    /**
     * @brief       Sends a frame through the transmitter.
     * @details     Sends a frame through the transmitter.
     * @param[out]  data_p              Data to be transmitted.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
    */
    bool_t sendData(
            cuint16_t data_p
    );

    /**
     * @brief       Sends data via standard data stream.
     * @details     Sends data via standard data stream.
     * @param[in]   data_p              Data to be transmitted.
     * @param[out]  stream_p            Pointer to data stream.
     * @return      int16_t             Always returns 0.
    */
    int16_t sendDataStd(
            char data_p,
            FILE *stream_p
    );

    /**
     * @brief       Redirects the standard I/O streams.
     * @details     Redirects the standard I/O streams.
    */
    void inlined stdio(
            void
    );

private:
    /**
     * @cond
    */

    void _clearDataOverrunError(
            void
    );

    void _clearFrameError(
            void
    );

    void _clearParityError(
            void
    );

    char _receiveDataStd(
            FILE *stream_p
    );

    /**
     * @endcond
    */

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.
    bool_t          _isReceiverEnabled                          : 1;
    bool_t          _isReceptionCompleteInterruptEnabled        : 1;
    bool_t          _isTransmissionBufferEmptyInterruptEnabled  : 1;
    bool_t          _isTransmissionCompleteInterruptEnabled     : 1;
    bool_t          _isTransmitterEnabled                       : 1;

    //     ////////////////     RECEPTION ERROR FLAGS    ////////////////     //
    bool_t  _isDataOverrunError                         : 1;
    bool_t  _isFrameError                               : 1;
    bool_t  _isParityError                              : 1;

    //     ////////////////////     CONFIGURATION    ////////////////////     //
    DataSize        _dataSize;
    Mode            _mode;
    BaudRate        _baudRate;
    ParityMode      _parityMode;
    StopBits        _stopBits;

protected:
    // NONE

}; // class Usart0

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

void inlined Usart0::disableReceiver(void)
{
    // Updates data members
    this->_isReceiverEnabled            = false;

    // Disables receiver
    clrBit(UCSR0B, RXEN0);

    // Returns successfully
    return;
}

void inlined Usart0::disableTransmitter(void)
{
    // Updates data members
    this->_isTransmitterEnabled         = false;

    // Disables transmitter
    clrBit(UCSR0B, TXEN0);

    // Returns successfully
    return;
}

void inlined Usart0::enableReceiver(void)
{
    // Updates data members
    this->_isReceiverEnabled            = true;

    // Enables receiver
    setBit(UCSR0B, RXEN0);

    // Returns successfully
    return;
}

void inlined Usart0::enableTransmitter(void)
{
    // Updates data members
    this->_isTransmitterEnabled         = true;

    // Enables transmitter
    setBit(UCSR0B, TXEN0);

    // Returns successfully
    return;
}

bool_t inlined Usart0::isReceptionComplete(void)
{
    return isBitSet(UCSR0A, RXC0);
}

bool_t inlined Usart0::isTransmissionBufferEmpty(void)
{
    return isBitSet(UCSR0A, UDRE0);
}

bool_t inlined Usart0::isTransmissionComplete(void)
{
    return isBitSet(UCSR0A, TXC0);
}

//     ///////////////////////     INTERRUPTS    ////////////////////////     //

void inlined Usart0::activateReceptionCompleteInterrupt(void)
{
    // Updates data members
    this->_isReceptionCompleteInterruptEnabled          = true;

    // Activates interrupt
    setBit(UCSR0B, RXCIE0);

    // Returns successfully
    return;
}

void inlined Usart0::activateTransmissionBufferEmptyInterrupt(void)
{
    // Updates data members
    this->_isTransmissionBufferEmptyInterruptEnabled    = true;

    // Activates interrupt
    setBit(UCSR0B, UDRIE0);

    // Returns successfully
    return;
}

void inlined Usart0::activateTransmissionCompleteInterrupt(void)
{
    // Updates data members
    this->_isTransmissionCompleteInterruptEnabled       = true;

    // Activates interrupt
    setBit(UCSR0B, TXCIE0);

    // Returns successfully
    return;
}

void inlined Usart0::deactivateReceptionCompleteInterrupt(void)
{
    // Updates data members
    this->_isReceptionCompleteInterruptEnabled          = false;

    // Deactivates interrupt
    clrBit(UCSR0B, RXCIE0);

    // Returns successfully
    return;
}

void inlined Usart0::deactivateTransmissionBufferEmptyInterrupt(void)
{
    // Updates data members
    this->_isTransmissionBufferEmptyInterruptEnabled    = false;

    // Deactivates interrupt
    clrBit(UCSR0B, UDRIE0);

    // Returns successfully
    return;
}

void inlined Usart0::deactivateTransmissionCompleteInterrupt(void)
{
    // Updates data members
    this->_isTransmissionCompleteInterruptEnabled       = false;

    // Deactivates interrupt
    clrBit(UCSR0B, TXCIE0);

    // Returns successfully
    return;
}

//     /////////////////////    DATA PROCESSING    //////////////////////     //

void inlined Usart0::stdio(void)
{
    // Redirects streams
    stdin = stdout = stderr = &usartStream;

    // Returns successfully
    return;
}

//     //////////////////     OPERATOR OVERLOADING    ///////////////////     //

Usart0::ReceptionError inlined operator|(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator|=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator&(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator&=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator~(Usart0::ReceptionError a)
{
    return static_cast<Usart0::ReceptionError>(static_cast<int>(Usart0::ReceptionError::ALL) ^ static_cast<int>(a));
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             usart0
 * @brief           Usart0 peripheral handler object.
 * @details         Usart0 peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern Usart0 usart0;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Usart0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
* @}
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
*/

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __USART0_HPP

// =============================================================================
// End of file (usart0.hpp)
// =============================================================================
