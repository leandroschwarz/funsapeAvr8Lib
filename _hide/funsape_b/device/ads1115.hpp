//!
//! \file           funsapeLibAds1115.hpp
//! \brief          ADS1115 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2025-12-10
//! \version        24.07
//! \copyright      license
//! \details        ADS1115 ADC module interface
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_ADS1115_HPP
#define __FUNSAPE_LIB_ADS1115_HPP                       2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_ADS1115_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_ADS1115_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibBus.hpp"
#if !defined(__FUNSAPE_LIB_BUS_HPP)
#   error "Header file (funsapeLibBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_BUS_HPP != __FUNSAPE_LIB_ADS1115_HPP
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
//! \brief          Ads1115 class
//! \details        Ads1115 class.
//!
class Ads1115
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class DeviceAddress : uint8_t {
        ADDR_GND    = 0x48,
        ADDR_VDD    = 0x49,
        ADDR_SDA    = 0x4A,
        ADDR_SCL    = 0x4B
    };

    enum class Channel : uint8_t {
        AIN0_TO_AIN1    = 0,
        AIN0_TO_AIN3    = 1,
        AIN1_TO_AIN3    = 2,
        AIN2_TO_AIN3    = 3,
        AIN0_TO_GND     = 4,
        AIN1_TO_GND     = 5,
        AIN2_TO_GND     = 6,
        AIN3_TO_GND     = 7
    };

    enum class Reference : uint8_t {
        REF_6_144_V     = 0,
        REF_4_096_V     = 1,
        REF_2_048_V     = 2,
        REF_1_024_V     = 3,
        REF_0_512_V     = 4,
        REF_0_256_V     = 5,
    };

    enum class Mode : uint8_t {
        CONTINUOUS_8_SPS    = 0,
        CONTINUOUS_16_SPS   = 1,
        CONTINUOUS_32_SPS   = 2,
        CONTINUOUS_64_SPS   = 3,
        CONTINUOUS_128_SPS  = 4,
        CONTINUOUS_250_SPS  = 5,
        CONTINUOUS_475_SPS  = 6,
        CONTINUOUS_860_SPS  = 7,
        SINGLE_SHOT         = 8
    };

    enum class ComparatorMode : uint8_t {
        DISABLED                        = 0,
        TRADITIONAL_AFTER_1_CONVERSION  = 1,
        TRADITIONAL_AFTER_2_CONVERSIONS = 2,
        TRADITIONAL_AFTER_4_CONVERSIONS = 3,
        WINDOW_AFTER_1_CONVERSION       = 4,
        WINDOW_AFTER_2_CONVERSIONS      = 5,
        WINDOW_AFTER_4_CONVERSIONS      = 6
    };

private:

    enum class Register : uint8_t {
        CONVERSION      = 0,
        CONFIG          = 1,
        THRESHOLD_LOW   = 2,
        THRESHOLD_HIGH  = 3,
    };

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Ads1115 class constructor
    //! \details    Creates an Ads1115 object.
    //!
    Ads1115(
            void
    );

    //!
    //! \brief      Ads1115 class destructor
    //! \details    Destroys an Ads1115 object.
    //!
    ~Ads1115(
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
    //!                 address is responding. Since the Ads1115 has no internal
    //!                 register to store it's device (or part) ID, there is no
    //!                 way to be sure if the device responding is actually a
    //!                 Ads1115 device.
    //! \param[in]  busHandler_p        pointer to the \ref Bus handler object
    //! \param[in]  deviceAddress_p     7 bit address of the device
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p,
            const DeviceAddress deviceAddress_p = DeviceAddress::ADDR_GND
    );

    // Conversion
    bool_t getConversionValue(
            int16_t *conversionValue_p
    );

    // Config
    bool_t selectInput(
            const Channel channel_p,
            const Reference fullScalReference_p
    );

    bool_t setMode(
            const Mode mode_p
    );

    bool_t setComparatorMode(
            const ComparatorMode comparatorMode_p,
            const LogicLevel activeLevel_p      = LogicLevel::LOW,
            cbool_t isLatched_p                 = false
    );

    bool_t getStatus(
            bool_t *isBusy_p
    );

    bool_t startSingleConversion(void);

    // Lo_thresh
    bool_t getComparatorLowThreshold(
            int16_t *lowThresholdValue_p
    );

    bool_t setComparatorLowThreshold(
            cint16_t lowThresholdValue_p
    );

    // Hi_thresh
    bool_t getComparatorHighThreshold(
            int16_t *highThresholdValue_p
    );

    bool_t setComparatorHighThreshold(
            cint16_t highThresholdValue_p
    );

private:

    bool_t _configDevice(void);

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

    Error           _lastError;
    uint8_t         _deviceAddress      : 7;
    Channel         _channel;
    Reference       _fullScaleReference;
    Mode            _mode;
    ComparatorMode  _comparatorMode;
    LogicLevel      _readyPinActiveLevel;
    bool_t          _readyPinIsLatched  : 1;
    bool_t          _isInitialized      : 1;
    bool_t          _triggerConversion  : 1;

protected:

    // NONE

}; // class Ads1115

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

#endif  // __FUNSAPE_LIB_ADS1115_HPP

// =============================================================================
// END OF FILE - funsapeLibAds1115.hpp
// =============================================================================
