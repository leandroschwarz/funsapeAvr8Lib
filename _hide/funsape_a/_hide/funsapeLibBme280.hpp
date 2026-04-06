//!
//! \file           funsapeLibBme280.hpp
//! \brief          BME280 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-11
//! \version        24.07
//! \copyright      license
//! \details        BME280 Barometric Pressure, Humidity and Temperature Sensor
//!                     module interface
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_BME280_HPP
#define __FUNSAPE_LIB_BME280_HPP                        2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_BME280_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_BME280_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibBus.hpp"
#if !defined(__FUNSAPE_LIB_BUS_HPP)
#   error "Header file (funsapeLibBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_BUS_HPP != __FUNSAPE_LIB_BME280_HPP
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
//! \brief          Bme280 class
//! \details        Bme280 class.
//!
class Bme280
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class Resolution : uint8_t {
        DISABLE_MEASUREMENT             = 0,
        RESOLUTION_16_BITS              = 1,
        RESOLUTION_17_BITS              = 2,
        RESOLUTION_18_BITS              = 3,
        RESOLUTION_19_BITS              = 4,
        RESOLUTION_20_BITS              = 5,
    };

    enum class FilterCoeff : uint8_t {
        FILTER_OFF                      = 0,    // ?
        COEFF_2                         = 1,    // ?
        COEFF_4                         = 2,    // ?
        COEFF_8                         = 3,    // ?
        COEFF_16                        = 4,    // ?
    };

    enum class OversamplingMode : uint8_t {
        DISABLE                         = 0,    // P = 0x, T = 0x
        ULTRA_LOW_POWER                 = 1,    // P = 1x, T = 1x
        LOW_POWER                       = 2,    // P = 2x, T = 1x
        STANDARD                        = 3,    // P = 4x, T = 1x
        HIGH_RESOLUTION                 = 4,    // P = 8x, T = 1x
        ULTRA_HIGH_RESOLUTION           = 5,    // P = 16x, T = 2x
    };

    enum class Mode : uint8_t {
        SLEEP                           = 0,    // No measurement is performed
        FORCED                          = 1,    // Performs a measurement then returns to sleep mode
        NORMAL                          = 3,    // Automatically cycles between measurement and standby
    };

    enum class StandbyTime : uint8_t {
        STANDBY_500_US                  = 0,    // 500 us between measurements
        STANDBY_62_5_MS                 = 1,    // 62.5 ms between measurements
        STANDBY_125_MS                  = 2,    // 125 ms between measurements
        STANDBY_250_MS                  = 3,    // 250 ms between measurements
        STANDBY_500_MS                  = 4,    // 500 ms between measurements
        STANDBY_1_S                     = 5,    // 1 s between measurements
        STANDBY_10_MS                   = 6,    // 10 ms between measurements
        STANDBY_20_MS                   = 7,    // 20 ms between measurements
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Bme280 class constructor
    //! \details    Creates a Bme280 object.
    //!
    Bme280(
            void
    );

    //!
    //! \brief      Bme280 class destructor
    //! \details    Destroys a Bme280 object.
    //!
    ~Bme280(
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
    //!                 address is responding. Since the BME280 has an internal
    //!                 register to store it's device (or part) ID, this
    //!                 register is also checked to ensure the device is
    //!                 actually a BME280 device. The busOption_p flag value
    //!                 depends on the communication interface that is used. If
    //!                 an TWI Bus is used, it selects which slave address will
    //!                 be used (true => 0x77, false => 0x76). If SPI Bus is
    //!                 used, it selects the communication lines interface
    //!                 (true => 3-wires SPI, false => 4-wires SPI).
    //! \param[in]  busHandler_p        pointer to the \ref Bus handler object
    //! \param[in]  busOption_p         see function details
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p,
            cbool_t busOption_p = false
    );

    //!
    //! \brief      Sets the device resolution.
    //! \details    Sets the device resolution for pressure and temperature
    //!                 measurements.
    //! \param[in]  pressureRes_p       resolution of pressure measurement
    //! \param[in]  temperatureRes_p    resolution of temperature measurement
    //! \param[in]  munidityRes_p       resolution of humidity measurement
    //! \return true
    //! \return false
    //!
    bool_t setResolution(
            const Resolution pressureRes_p = Resolution::RESOLUTION_18_BITS,
            const Resolution temperatureRes_p = Resolution::RESOLUTION_16_BITS,
            const Resolution humidityRes_p = Resolution::RESOLUTION_16_BITS
    );

    //!
    //! \brief      Triggers a measurement procedure.
    //! \details    Sends the command to start an acquisition in forced mode.
    //!                 After the measurement, the device is automatically put
    //!                 in sleep mode. Do not use this function in normal mode
    //!                 operation. The measurement duration depends on the
    //!                 resolution, and can takes up to 45 ms to finish. In
    //!                 forced mode, after calling startMeasurement(), the user
    //!                 must call checkStatus() to synchronize the device status
    //!                 and call isReady() to check if new data is available.
    //! \return true
    //! \return false
    //!
    bool_t startMeasurement(
            void
    );

    //!
    //! \brief      Checks the status of the device.
    //! \details    Reads the device status and stores into the class data
    //!                 members. In forced mode, must be called before the
    //!                 isReady() or getData() functions to synchronize the
    //!                 class data with the device data. In normal mode, this
    //!                 function has no use.
    //! \return true
    //! \return false
    //!
    bool_t checkStatus(
            void
    );

    //!
    //! \brief      Checks if the measurement is finished.
    //! \details    Checks if the measurement is finished. In forced mode, the
    //!                 user must call checkStatus() to synchronize the device
    //!                 status before calling isReady(). In normal mode, this
    //!                 function has no use.
    //! \return true
    //! \return false
    //!
    inlined bool_t isReady(
            void
    ) {
        return this->_newDataReady;
    }

    //!
    //! \brief      Sets the standby time.
    //! \details    Sets the standby time between measurements in normal mode
    //!                 operation.
    //! \param[in]  standbyTime_p       time between measurements
    //! \return true
    //! \return false
    //!
    bool_t setStandbyTime(
            const StandbyTime standbyTime_p
    );

    //!
    //! \brief      Puts the device in sleep mode.
    //! \details    Puts the device in sleep mode.
    //! \return true
    //! \return false
    //!
    bool_t setSleepMode(
            void
    );

    //!
    //! \brief      Puts the device in normal operation mode.
    //! \details    Puts the device in normal operation mode.
    //! \return true
    //! \return false
    //!
    bool_t setNormalMode(
            void
    );

    //!
    //! \brief      Sets the filter coefficients.
    //! \details    Sets the filter coefficients.
    //! \param[in]  filterCoeff_p       filter coefficients
    //! \return true
    //! \return false
    //!
    bool_t setFilterCoefficients(
            const FilterCoeff filterCoeff_p
    );

    //!
    //! \brief      Performs the device reset.
    //! \details    Performs the device reset. The reset operation also changes
    //!                 the device parameters (Resolution, Mode, Filter, etc.)
    //!                 to the default setting.
    //! \return true
    //! \return false
    //!
    bool_t reset(
            void
    );

    //!
    //! \brief      Gets data from device.
    //! \details    Gets the data from the class data members. The user must
    //!                 synchronize the status of the device (by calling
    //!                 checkStatus()) and checks if there is new data awaiting
    //!                 (by calling isReady()), before calling getData(). After
    //!                 retrieval, data is marked as "not new", so, subsequent
    //!                 calls of getData() without data syncronization
    //!                 (checkStatus()) will fail.
    //! \param[in]  pres_p              pointer to the variable to receive the pressure value
    //! \param[in]  temp_p              pointer to the variable to receive the temperature value
    //! \param[in]  humi_p              pointer to the variable to receive the humidity value
    //! \return true
    //! \return false
    //!
    bool_t getData(
            uint32_t *pres_p,
            int16_t *temp_p,
            uint16_t *humi_p
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:
    //     /////////////////     DEVICE BUS HANDLER     /////////////////     //

    Bus             *_busHandler;
    bool_t          _useSpiInterface            : 1;
    bool_t          _useSpiInterface3Wire       : 1;
    uint8_t         _deviceAddress;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isInitialized              : 1;
    bool_t          _newDataReady               : 1;
    Resolution      _temperatureResolution;
    Resolution      _pressureResolution;
    Resolution      _humidityResolution;
    FilterCoeff     _filterCoefficient;
    Mode            _operationMode;
    StandbyTime     _standbyTime;
    Error           _lastError;

    //     ///////////////     CALIBRATION PARAMETERS     ///////////////     //

    uint16_t        _calibDigP1;
    int16_t         _calibDigP2;
    int16_t         _calibDigP3;
    int16_t         _calibDigP4;
    int16_t         _calibDigP5;
    int16_t         _calibDigP6;
    int16_t         _calibDigP7;
    int16_t         _calibDigP8;
    int16_t         _calibDigP9;
    uint16_t        _calibDigT1;
    int16_t         _calibDigT2;
    int16_t         _calibDigT3;
    int16_t         _calibDigT4;
    uint8_t         _calibDigH1;
    int16_t         _calibDigH2;
    uint8_t         _calibDigH3;
    int16_t         _calibDigH4;
    int16_t         _calibDigH5;
    int8_t          _calibDigH6;

protected:

    // NONE

}; // class Bme280

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

#endif  // __FUNSAPE_LIB_BME280_HPP

// =============================================================================
// END OF FILE - funsapeLibBme280.hpp
// =============================================================================
