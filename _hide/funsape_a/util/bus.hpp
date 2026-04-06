/**
 *******************************************************************************
 * @file            bus.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Bus Handler.
 * @details         This file provides support to a generic communication bus
 *                      handler for the FunSAPE++ AVR8 Library.
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

#ifndef __BUS_HPP
#define __BUS_HPP                       2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [bus.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __BUS_HPP
#   error [bus.hpp] Error 2 - Build mismatch between file (bus.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [bus.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __BUS_HPP
#   error [bus.hpp] Error 5 - Build mismatch between file (bus.hpp) and library dependency (debug.hpp)!
#endif

#include "../peripheral/gpioPin.hpp"
#if !defined(__GPIO_PIN_HPP)
#   error [bus.hpp] Error 1 - Header file (gpioPin.hpp) is missing or corrupted!
#elif __GPIO_PIN_HPP != __BUS_HPP
#   error [bus.hpp] Error 5 - Build mismatch between file (bus.hpp) and library dependency (gpioPin.hpp)!
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
// Doxygen: Start subgroup "Util/Bus"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Bus
 * @brief           Generic communication bus handler.
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
 * @brief           Bus class.
 * @details         This class is a virtual class that controls a generic
 *                      communication bus.
 * @warning         This class is pure virtual and must not be instantiated.
*/
class Bus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        BusType
     * @brief       Bus type enumeration.
     * @details     Bus type options associated with the bus.
    */
    enum class BusType {
        NONE                            = 0,    //!< Bus is not initialized
        OWI                             = 1,    //!< One Wire Interface
        PARALLEL                        = 2,    //!< Simple parallel bitbang interface
        SERIAL                          = 3,    //!< Simple serial bitbang interface
        SPI                             = 4,    //!< Serial Peripheral Interface
        TWI                             = 5,    //!< Two Wire Interface (I2C)
        UART                            = 6,    //!< Universal Sync./Async. Receiver Transmitter
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
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
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t read(
            uint8_t *buffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::read(uint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

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
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t readReg(
            cuint8_t reg_p,
            uint8_t *buffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::readReg(cuint8_t, uint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

    /**
     * @brief       Sends (exchange) data to the bus.
     * @details     This function exchanges (sends and receives) a block of data
     *                  to the bus. The data to be sent is read from the data
     *                  vector, and the data received is stored at the same
     *                  vector, overwriting its data.
     * @param[out]  buffData_p          pointer to data vector to exchange.
     * @param[in]   buffSize_p          number of data elements to exchange.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t sendData(
            uint8_t *buffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::sendData(uint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

    /**
     * @brief       Sends (exchange) data to the bus.
     * @details     This function exchanges (sends and receives) a block of data
     *                  to the bus. The data to be sent and the received data
     *                  are stored in separate data vectors.
     * @param[in]   txBuffData_p        pointer to the tx data vector.
     * @param[out]  rxBuffData_p        pointer to the rx data vector.
     * @param[in]   buffSize_p          number of data elements to exchange.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     * @par Error codes:
     *
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
     */
    virtual bool_t sendData(
            cuint8_t *txBuffData_p,
            uint8_t *rxBuffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::sendData(cuint8_t *, uint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

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
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t write(
            uint8_t *buffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::write(uint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

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
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t writeReg(
            cuint8_t reg_p,
            cuint8_t *buffData_p,
            cuint16_t buffSize_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::writeReg(cuint8_t, cuint8_t *, cuint16_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

    //     ////////////////     TWI PROTOCOL METHODS     ////////////////     //

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
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t setDevice(
            cuint16_t address_p,
            cbool_t useLongAddress_p = false
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::setDevice(cuint16_t, cbool_t)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

    //     ////////////////     SPI PROTOCOL METHODS     ////////////////     //

    /**
     * @brief       Sets the device slave select functions.
     * @details     This function sets the device slave select functions.
     * @param[in]   actFunc_p           pointer to slave select function.
     * @param[in]   deactFunc_p         pointer to slave release function.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t setDevice(
            void (* actFunc_p)(void),
            void (* deactFunc_p)(void)
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::setDevice(void *(void), void *(void))"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

    /**
     * @brief       Sets the device slave select GpioPin pin.
     * @details     This function sets the device slave select GpioPin pin.
     * @param[in]   csPin_p             pointer GpioPin slave select pin object.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                        | Meaning                              |
     * |:----------------------------------|:-------------------------------------|
     * | @ref Error::FEATURE_NOT_SUPPORTED | The virtual function is been called. |
     *
    */
    virtual bool_t setDevice(
            GpioPin *csPin_p
    ) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::setDevice(GpiPin *)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns error
        this->_lastError = Error::FEATURE_NOT_SUPPORTED;
        debugMessage(Error::FEATURE_NOT_SUPPORTED, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return false;
    };

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
    virtual Bus::BusType getBusType(void) {
        // Mark passage for debugging purpose
        debugMark(PSTR("Bus::getBusType(void)"), Debug::CodeIndex::BUS_HANDLER_MODULE);

        // Returns default handler
        this->_lastError = Error::NONE;
        debugMessage(Error::NONE, Debug::CodeIndex::BUS_HANDLER_MODULE);
        return BusType::NONE;
    }

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
    */
    virtual Error getLastError(void) {
        // Returns last error
        return this->_lastError;
    }

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    Error           _lastError;                 //!< Last error.

protected:
    // NONE

}; // class Bus

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

// NONE

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Util/Bus"
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

#endif  // __BUS_HPP

// =============================================================================
// End of file (bus.hpp)
// =============================================================================
