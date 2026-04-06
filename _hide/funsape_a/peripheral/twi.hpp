/**
 *******************************************************************************
 * @file            twi.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           TWI peripheral control.
 * @details         This file provides control for the Two Wires Interface (TWI)
 *                      peripheral control for the FunSAPE++ AVR8 Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
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

#ifndef __TWI_HPP
#define __TWI_HPP                       2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [twi.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __TWI_HPP
#   error [twi.hpp] Error 2 - Build mismatch between file (twi.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [twi.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __TWI_HPP
#   error [twi.hpp] Error 5 - Build mismatch between file (twi.hpp) and library dependency (debug.hpp)!
#endif

#include "../util/bus.hpp"
#if !defined(__BUS_HPP)
#   error [twi.hpp] Error 1 - Header file (bus.hpp) is missing or corrupted!
#elif __BUS_HPP != __TWI_HPP
#   error [twi.hpp] Error 5 - Build mismatch between file (twi.hpp) and library dependency (bus.hpp)!
#endif

#include "../util/systemStatus.hpp"
#if !defined(__SYSTEM_STATUS_HPP)
#   error [twi.hpp] Error 1 - Header file (systemStatus.hpp) is missing or corrupted!
#elif __SYSTEM_STATUS_HPP != __TWI_HPP
#   error [twi.hpp] Error 5 - Build mismatch between file (twi.hpp) and library dependency (systemStatus.hpp)!
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
// Doxygen: Start subgroup "Peripherals/Twi"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Twi
 * @brief           Twi Wires Interface (TWI) controller module.
 * @{
 */

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

#define TWI_BUFFER_SIZE                 32

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

#ifdef STILL_NOT_IMPLEMENTED

/**
 * @brief           TWI interrupt callback function.
 * @details         This function is called when the TWI interrupt is treated.
 *                      It is a weak function that can be overwritten by user
 *                      code.
 */
void twiInterruptCallback(void);

#endif

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Twi class.
 * @details         This class manages the Two Wires Interface (TWI) peripheral.
 * @attention       The @ref twi instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
 */
class Twi
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        Operation
     * @brief       TWI operation mode.
     * @details     Operation modes associated with TWI.
     */
    enum class Operation : bool_t {
        WRITE       = false,
        READ        = true
    };

private:
    /**
     * @cond
     */

    enum class State {
        START                           = 0x08, //!< START has been transmitted
        REP_START                       = 0x10, //!< Repeated START has been transmitted
        ARB_LOST                        = 0x38, //!< Arbitration lost
        MTX_ADR_ACK                     = 0x18, //!< SLA+W has been transmitted and ACK received
        MTX_ADR_NACK                    = 0x20, //!< SLA+W has been transmitted and NACK received
        MTX_DATA_ACK                    = 0x28, //!< Data byte has been transmitted and ACK received
        MTX_DATA_NACK                   = 0x30, //!< Data byte has been transmitted and NACK received
        MRX_ADR_ACK                     = 0x40, //!< SLA+R has been transmitted and ACK received
        MRX_ADR_NACK                    = 0x48, //!< SLA+R has been transmitted and NACK received
        MRX_DATA_ACK                    = 0x50, //!< Data byte has been received and ACK transmitted
        MRX_DATA_NACK                   = 0x58, //!< Data byte has been received and NACK transmitted
        STX_ADR_ACK                     = 0xA8, //!< Own SLA+R has been received; ACK has been returned
        STX_ADR_ACK_M_ARB_LOST          = 0xB0, //!< Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
        STX_DATA_ACK                    = 0xB8, //!< Data byte in TWDR has been transmitted; ACK has been received
        STX_DATA_NACK                   = 0xC0, //!< Data byte in TWDR has been transmitted; NOT ACK has been received
        STX_DATA_ACK_LAST_BYTE          = 0xC8, //!< Last data byte in TWDR has been transmitted (TWEA = 0); ACK has been received
        SRX_ADR_ACK                     = 0x60, //!< Own SLA+W has been received ACK has been returned
        SRX_ADR_ACK_M_ARB_LOST          = 0x68, //!< Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
        SRX_GEN_ACK                     = 0x70, //!< General call address has been received; ACK has been returned
        SRX_GEN_ACK_M_ARB_LOST          = 0x78, //!< Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
        SRX_ADR_DATA_ACK                = 0x80, //!< Previously addressed with own SLA+W; data has been received; ACK has been returned
        SRX_ADR_DATA_NACK               = 0x88, //!< Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
        SRX_GEN_DATA_ACK                = 0x90, //!< Previously addressed with general call; data has been received; ACK has been returned
        SRX_GEN_DATA_NACK               = 0x98, //!< Previously addressed with general call; data has been received; NOT ACK has been returned
        SRX_STOP_RESTART                = 0xA0, //!< A STOP condition or repeated START condition has been received while still addressed as Slave
        NO_STATE                        = 0xF8, //!< No relevant state information available; TWINT = 0
        BUS_ERROR                       = 0x00  //!< Bus error due to an illegal START or STOP condition
    };

    /**
     * @endcond
     */

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Twi class constructor.
     * @details     Creates a Twi object. The object is loaded with the default
     *                  register values The object still must be initialized
     *                  before use.
     * @see         init(cuint32_t clockSpeed_p, cuint8_t bufferSize_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
     */
    Twi(
            void
    );

    /**
     * @brief       Twi class destructor.
     * @details     Destroys a Twi object.
     */
    ~Twi(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    //     ////////////////////    DATA TRANSFER     ////////////////////     //

    /**
     * @brief       Reads data.
     * @details     This function reads a block of data pointed by current
     *                  register address.
     * @param[out]  buffData_p          pointer to data vector.
     * @param[in]   buffSize_p          number of data elements to read.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                          | Meaning                                                  |
     * |:------------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                    | Success. No erros were detected.                         |
     * | @ref Error::DEVICE_NOT_SELECTED     | The communication device was not selected.               |
     * | @ref Error::NOT_INITIALIZED         | The TWI object was not initialized.                      |
     * | @ref Error::ARGUMENT_POINTER_NULL   | @a buffData_p cannot be a null pointer.                  |
     * | @ref Error::ARGUMENT_CANNOT_BE_ZERO | @a buffSize_p cannot be zero.                            |
     * | @ref Error::BUFFER_SIZE_TOO_LARGE   | |
     * | @ref Error::NOT_IMPLEMENTED         | 10-bit addressing mode is currently not implemented yet. |
     * | @ref Error::TIMED_OUT               | The operation has timed out.                             |
     * | @ref Error::COMMUNICATION_FAILED    | An error occurred during the communication procedure.    |
     *
     */
    bool_t read(
            uint8_t     *buffData_p,
            cuint8_t    buffSize_p      = 1
    );

    /**
     * @brief       Reads data from an address.
     * @details     This function reads a block of data from the given
     *                  register address.
     * @param[in]   reg_p               register address.
     * @param[out]  buffData_p          pointer to data vector.
     * @param[in]   buffSize_p          number of data elements to read.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                        | Meaning                                                  |
     * |:----------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                  | Success. No erros were detected.                         |
     * | @ref Error::DEVICE_NOT_SELECTED   | The communication device was not selected.               |
     * | @ref Error::NOT_IMPLEMENTED       | 10-bit addressing mode is currently not implemented yet. |
     * | @ref Error::NOT_INITIALIZED       | The TWI object was not initialized.                      |
     * | @ref Error::ARGUMENT_POINTER_NULL | @a buffData_p cannot be a null pointer.                  |
     * | @ref Error::BUFFER_SIZE_TOO_LARGE | |
     * | @ref Error::TIMED_OUT             | The operation has timed out.                             |
     * | @ref Error::COMMUNICATION_FAILED  | An error occurred during the communication procedure.    |
     *
     */
    bool_t readReg(
            cuint8_t    reg_p,
            uint8_t     *buffData_p,
            cuint8_t    buffSize_p      = 1
    );

    /**
     * @brief       Writes data.
     * @details     This function writes a block of data.
     * @param[out]  buffData_p          pointer to data vector.
     * @param[in]   buffSize_p          number of data elements to write.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                          | Meaning                                                  |
     * |:------------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                    | Success. No erros were detected.                         |
     * | @ref Error::DEVICE_NOT_SELECTED     | The communication device was not selected.               |
     * | @ref Error::NOT_INITIALIZED         | The TWI object was not initialized.                      |
     * | @ref Error::ARGUMENT_POINTER_NULL   | @a buffData_p cannot be a null pointer.                  |
     * | @ref Error::ARGUMENT_CANNOT_BE_ZERO | @a buffSize_p cannot be zero.                            |
     * | @ref Error::BUFFER_SIZE_TOO_LARGE   | |
     * | @ref Error::NOT_IMPLEMENTED         | 10-bit addressing mode is currently not implemented yet. |
     * | @ref Error::TIMED_OUT               | The operation has timed out.                             |
     * | @ref Error::COMMUNICATION_FAILED    | An error occurred during the communication procedure.    |
     *
     */
    bool_t write(
            uint8_t     *buffData_p,
            cuint8_t    buffSize_p      = 1
    );

    /**
     * @brief       Writes data at an address.
     * @details     This function writes a block of data at the given register
     *                  address.
     * @param[in]   reg_p               register address.
     * @param[out]  buffData_p          pointer to data vector.
     * @param[in]   buffSize_p          number of data elements to write.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                        | Meaning                                                  |
     * |:----------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                  | Success. No erros were detected.                         |
     * | @ref Error::DEVICE_NOT_SELECTED   | The communication device was not selected.               |
     * | @ref Error::NOT_INITIALIZED       | The TWI object was not initialized.                      |
     * | @ref Error::ARGUMENT_POINTER_NULL | @a buffData_p cannot be a null pointer.                  |
     * | @ref Error::BUFFER_SIZE_TOO_LARGE | |
     * | @ref Error::NOT_IMPLEMENTED       | 10-bit addressing mode is currently not implemented yet. |
     * | @ref Error::TIMED_OUT             | The operation has timed out.                             |
     * | @ref Error::COMMUNICATION_FAILED  | An error occurred during the communication procedure.    |
     *
     */
    bool_t writeReg(
            cuint8_t    reg_p,
            cuint8_t    *buffData_p,
            cuint8_t    buffSize_p      = 1
    );

    //     //////////////////    PROTOCOL SPECIFIC     //////////////////     //

    /**
     * @brief       Sets the device slave address.
     * @details     This function sets the device slave address.
     * @param[in]   address_p           slave address.
     * @param[in]   useLongAddress_p    use 10-bits slave address.
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
    bool_t setDevice(
            cuint16_t address_p,
            cbool_t useLongAddress_p = false
    );

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Retuns the bus type.
     * @details     This function returns the bus type interface.
     * @return      the bus type @ref Bus::BusType.
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
     */
    Bus::BusType inlined getBusType(
            void
    );

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
     */
    Error inlined getLastError(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Initializes the Twi module.
     * @details     Initializes the Twi module. The function also configures the
     *                  the bit rate with the value given by @a clockSpeed_p and
     *                  the internal transfer buffer with the value of
     *                  @a bufferSize_p.
     * @param[in]   clockSpeed_p        Bit rate value to adjust clock speed.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                           | Meaning                                                  |
     * |:-------------------------------------|:---------------------------------------------------------|
     * | @ref Error::NONE                     | Success. No erros were detected.                         |
     * | @ref Error::CLOCK_SPEED_TOO_LOW      | The clock speed is too low.                              |
     * | @ref Error::CLOCK_SPEED_TOO_HIGH     | The clock speed is too high.                             |
     *
     */
    bool_t init(
            cuint32_t   clockSpeed_p    = 10'000
    );

    /**
     * @brief       Sets the operation timeout.
     * @details     Configures the operation timeout.
     * @param[in]   timeout_p           Timeout value in miliseconds.
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
    bool_t setTimeout(
            cuint16_t   timeout_p
    );

    //     /////////////////////     INTERRUPTS     /////////////////////     //

    /**
     * @brief       Internal interrupt handler function.
     * @details     Internal interrupt handler function.
     * @warning     Do not call this function.
     */
    void interruptHandler(
            void
    );

private:
    /**
     * @cond
     */

    bool_t _readFromBuffer(
            uint8_t     *msg_p,
            cuint8_t    msgSize_p
    );

    bool_t _sendData(
            uint8_t     devAddress_p,
            Operation   readWrite_p,
            uint8_t     reg_p,
            uint8_t     *msg_p,
            uint8_t     msgSize_p
    );

    bool_t _startTransmission(
            void
    );

    bool_t _waitWhileIsBusy(
            void
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
    bool_t          _devAddressSet      : 1;    //!< Device address set flag.
    bool_t          _lastTransOk        : 1;    //!< Last transmission ok flag.
    uint8_t         _twiError;                  //!< Twi error.
    State           _state;                     //!< Twi state.
    uint16_t        _timeout;                   //!< Operation timeout delay.

    //     /////////////////     DEVICE ADDRESSING      /////////////////     //
    uint16_t        _devAddress         : 10;   //!< Device address value.
    bool_t          _useLongAddress     : 1;    //!< Use 10-bits device address.

    //     ////////////////////    DATA BUFFERS      ////////////////////     //
    uint8_t         _bufferLength       : 7;    //!< Current length of the internal buffer.
    uint8_t         _bufferData[TWI_BUFFER_SIZE + 2];   //!< Internal buffer data.
    uint8_t         _bufferIndex        : 7;    //!< Current index of the internal buffer.

protected:
    // NONE

}; // class Twi

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
 */

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Bus::BusType inlined Twi::getBusType(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Twi::getBusType(void)"), Debug::CodeIndex::TWI_MODULE);

    // Returns bus type
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TWI_MODULE);
    return Bus::BusType::TWI;
}

Error inlined Twi::getLastError(void)
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

/**
 * @var             twi
 * @brief           Twi peripheral handler object.
 * @details         Twi peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
 */
extern Twi twi;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Twi"
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

#endif  // __TWI_HPP

// =============================================================================
// End of file (twi.hpp)
// =============================================================================
