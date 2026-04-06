//!
//! \file           funsapeLibAht21.hpp
//! \brief          AHT21 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-11
//! \version        24.07
//! \copyright      license
//! \details        AHT21 Humidity and Temperature Sensor module interface
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_AHT21_HPP
#define __FUNSAPE_LIB_AHT21_HPP                         2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_AHT21_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_AHT21_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibBus.hpp"
#if !defined(__FUNSAPE_LIB_BUS_HPP)
#   error "Header file (funsapeLibBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_BUS_HPP != __FUNSAPE_LIB_AHT21_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibBus.hpp)!"
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
//! \brief          Aht21 class
//! \details        Aht21 class.
//!
class Aht21
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Aht21 class constructor
    //! \details    Creates a Aht21 object.
    //!
    Aht21(
            void
    );

    //!
    //! \brief      Aht21 class destructor
    //! \details    Destroys a Aht21 object.
    //!
    ~Aht21(
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

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         Error              Return info
    //!
    Error getLastError(
            void
    );

    //!
    //! \brief      Initializes the device.
    //! \details    Performs the device initialization, checking if the device
    //!                 address is responding. Since the AHT21 has no internal
    //!                 register to store it's device (or part) ID, there is no
    //!                 way to be sure if the device responding is actually a
    //!                 AHT21 device.
    //! \param[in]  busHandler_p        pointer to the \ref Bus handler object
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p
    );

    //!
    //! \brief      Checks the status of the device.
    //! \details    Reads all data from device and stores into the class data
    //!                 members. Must be called before the isCalibrated(),
    //!                 isReady() or getData() functions to synchronize the
    //!                 class data with the device data.
    //! \return true
    //! \return false
    //!
    bool_t checkStatus(
            void
    );

    //!
    //! \brief      Triggers a measurement procedure.
    //! \details    Sends the command to start an acquisition. The measurement
    //!                 procedure can takes up to 80 ms to finish. After calling
    //!                 startMeasurement(), the user must call checkStatus() to
    //!                 synchronize the device status and call isReady() to
    //!                 check if new data is available.
    //! \return true
    //! \return false
    //!
    bool_t startMeasurement(
            void
    );

    //!
    //! \brief      Checks if there is unread data into the class data members.
    //! \details    Checks if there is unread data into the class data members.
    //!                 The user must call checkStatus() to synchronize the
    //!                 device status before calling isReady().
    //! \return true
    //! \return false
    //!
    inlined bool_t isReady(
            void
    ) {
        return this->_newDataReady;
    }

    //!
    //! \brief      Checks if the device is calibrated.
    //! \details    Checks if the device is calibrated. The user must call
    //!                 checkStatus() to synchronize the device status before
    //!                 calling isCalibrated().
    //! \return true
    //! \return false
    //!
    inlined bool_t isCalibrated(
            void
    ) {
        return this->_isCalibrated;
    }

    //!
    //! \brief      Gets data from class members.
    //! \details    Gets the data from the class data members. The user must
    //!                 synchronize the status of the device (by calling
    //!                 checkStatus()) and checks if there is new data awaiting
    //!                 (by calling isReady()), before calling getData(). After
    //!                 retrieval, data is marked as "not new", so, subsequent
    //!                 calls of getData() without data syncronization
    //!                 (checkStatus()) will fail.
    //! \param[in]  temp_p              pointer to the variable to receive the temperature value
    //! \param[in]  humi_p              pointer to the variable to receive the humidity value
    //! \return true
    //! \return false
    //!
    bool_t getData(
            uint16_t *temp_p,
            uint16_t *humi_p
    );

    //!
    //! \brief      Performs the device reset.
    //! \details    Performs the device reset.
    //! \return true
    //! \return false
    //!
    bool_t reset(
            void
    );

    //!
    //! \brief      Performs calibration procedure.
    //! \details    Performs calibration procedure.
    //! \return true
    //! \return false
    //!
    bool_t calibrate(
            void
    );

private:

    bool_t _resetRegister(
            uint8_t register_p
    );

    uint8_t _evaluateCrc(
            uint8_t *data_p
    );

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:

    //     /////////////////     DEVICE BUS HANDLER     /////////////////     //

    Bus             *_busHandler;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isInitialized              : 1;
    bool_t          _isCalibrated               : 1;
    bool_t          _newDataReady               : 1;
    bool_t          _isDataValid                : 1;
    uint16_t        _humidity;
    uint16_t        _temperature;
    Error           _lastError;

protected:

    // NONE

}; // class Aht21

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

#endif  // __FUNSAPE_LIB_AHT21_HPP

// =============================================================================
// END OF FILE - funsapeLibAht21.hpp
// =============================================================================
