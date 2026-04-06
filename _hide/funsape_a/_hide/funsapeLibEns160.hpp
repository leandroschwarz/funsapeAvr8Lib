//!
//! \file           funsapeLibEns160.hpp
//! \brief          ENS160 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-13
//! \version        24.07
//! \copyright      license
//! \details        ENS160 Multi-Gas Sensor module interface
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_ENS160_HPP
#define __FUNSAPE_LIB_ENS160_HPP                        2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_ENS160_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_ENS160_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibBus.hpp"
#if !defined(__FUNSAPE_LIB_BUS_HPP)
#   error "Header file (funsapeLibBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_BUS_HPP != __FUNSAPE_LIB_ENS160_HPP
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

// Chip constants
#define ENS160_PARTID                   0x0160
#define ENS161_PARTID                   0x0161
#define ENS160_BOOTING                  10

// 7-bit I2C slave address of the ENS160
#define ENS160_I2CADDR_0                0x52    //ADDR low
#define ENS160_I2CADDR_1                0x53    //ADDR high

// ENS160 registers for version V0
#define ENS160_REG_CONFIG               0x11
#define ENS160_REG_TEMP_IN              0x13
#define ENS160_REG_RH_IN                0x15
#define ENS160_REG_DATA_STATUS          0x20
#define ENS160_REG_DATA_AQI             0x21
#define ENS160_REG_DATA_TVOC            0x22
#define ENS160_REG_DATA_ECO2            0x24
#define ENS160_REG_DATA_BL              0x28
#define ENS160_REG_DATA_T               0x30
#define ENS160_REG_DATA_RH              0x32
#define ENS160_REG_DATA_MISR            0x38

//ENS160 data register fields
#define ENS160_COMMAND_NOP              0x00
#define ENS160_COMMAND_CLRGPR           0xCC
#define ENS160_COMMAND_GET_APPVER       0x0E
#define ENS160_COMMAND_SETTH            0x02
#define ENS160_COMMAND_SETSEQ           0xC2

#define ENS160_OPMODE_RESET             0xF0
#define ENS160_OPMODE_DEP_SLEEP         0x00
#define ENS160_OPMODE_IDLE              0x01
#define ENS160_OPMODE_STD               0x02
#define ENS160_OPMODE_LP                0x03
#define ENS160_OPMODE_CUSTOM            0xC0

#define ENS160_BL_CMD_START             0x02
#define ENS160_BL_CMD_ERASE_APP         0x04
#define ENS160_BL_CMD_ERASE_BLINE       0x06
#define ENS160_BL_CMD_WRITE             0x08
#define ENS160_BL_CMD_VERIFY            0x0A
#define ENS160_BL_CMD_GET_BLVER         0x0C
#define ENS160_BL_CMD_GET_APPVER        0x0E
#define ENS160_BL_CMD_EXITBL            0x12

#define ENS160_SEQ_ACK_NOTCOMPLETE      0x80
#define ENS160_SEQ_ACK_COMPLETE         0xC0

#define IS_ENS160_SEQ_ACK_NOT_COMPLETE(x)   (ENS160_SEQ_ACK_NOTCOMPLETE == (ENS160_SEQ_ACK_NOTCOMPLETE & (x)))
#define IS_ENS160_SEQ_ACK_COMPLETE(x)       (ENS160_SEQ_ACK_COMPLETE == (ENS160_SEQ_ACK_COMPLETE & (x)))

#define ENS160_DATA_STATUS_NEWDAT       0x02
#define ENS160_DATA_STATUS_NEWGPR       0x01

#define IS_NEWDAT(x)                    (ENS160_DATA_STATUS_NEWDAT == (ENS160_DATA_STATUS_NEWDAT & (x)))
#define IS_NEWGPR(x)                    (ENS160_DATA_STATUS_NEWGPR == (ENS160_DATA_STATUS_NEWGPR & (x)))
#define IS_NEW_DATA_AVAILABLE(x)        (0 != ((ENS160_DATA_STATUS_NEWDAT | ENS160_DATA_STATUS_NEWGPR ) & (x)))

#define CONVERT_RS_RAW2OHMS_I(x)        (1 << ((x) >> 11))
#define CONVERT_RS_RAW2OHMS_F(x)        (pow (2, (float)(x) / 2048))

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
//! \brief          Ens160 class
//! \details        Ens160 class.
//!
class Ens160
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class Mode : uint8_t {
        DEEP_SLEEP                      = 0x00,
        IDLE                            = 0x01,
        STANDARD                        = 0x02,
        RESET                           = 0xF0,
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Ens160 class constructor
    //! \details    Creates an Ens160 object.
    //!
    Ens160(
            void
    );

    //!
    //! \brief      Ens160 class destructor
    //! \details    Destroys an Ens160 object.
    //!
    ~Ens160(
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
    //!                 address is responding. Since the ENS160 has an internal
    //!                 register to store it's device (or part) ID, this
    //!                 register is also checked to ensure the device is
    //!                 actually an ENS160 device. The busOption_p flag value
    //!                 depends on the communication interface that is used. If
    //!                 an TWI Bus is used, it selects which slave address will
    //!                 be used (true => 0x53, false => 0x52). It has no use in
    //!                 SPI communication.
    //! \param[in]  busHandler_p        pointer to the \ref Bus handler object
    //! \param[in]  busOption_p         see function details
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p,
            cbool_t busOption_p = false
    );

    bool_t setMode(
            const Mode mode_p
    );




    // Report availability of sensor
    bool available() {
        return this->_available;
    }

    // Report version of sensor (0: ENS160, 1: ENS161)
    uint8_t revENS16x() {
        return this->_revENS16x;
    }



    // Initialize definition of custom mode with <n> steps
    bool initCustomMode(
            uint16_t stepNum
    );

    // Add a step to custom measurement profile with definition of duration, enabled data acquisition and temperature for each hotplate
    bool addCustomStep(
            uint16_t time,
            bool measureHP0,
            bool measureHP1,
            bool measureHP2,
            bool measureHP3,
            uint16_t tempHP0,
            uint16_t tempHP1,
            uint16_t tempHP2,
            uint16_t tempHP3
    );

    // Perform measurement and stores result in internal variables
    bool measure(
            bool waitForNew = true
    );

    // Perform raw measurement and stores result in internal variables
    bool measureRaw(
            bool waitForNew = true
    );

    // Writes t (degC) and h (%rh) to ENV_DATA. Returns "0" if I2C transmission is successful
    bool set_envdata(
            float t,
            float h
    );

    // Writes t and h (in ENS210 format) to ENV_DATA. Returns "0" if I2C transmission is successful
    bool set_envdata210(
            uint16_t t,
            uint16_t h
    );

    // Get major revision number of used firmware
    uint8_t getMajorRev() {
        return this->_fw_ver_major;
    }

    // Get minor revision number of used firmware
    uint8_t getMinorRev() {
        return this->_fw_ver_minor;
    }

    // Get build revision number of used firmware
    uint8_t getBuild() {
        return this->_fw_ver_build;
    }

    // Get AQI value of last measurement
    uint8_t getAQI() {
        return this->_data_aqi;
    }

    // Get TVOC value of last measurement
    uint16_t getTVOC() {
        return this->_data_tvoc;
    }

    // Get eCO2 value of last measurement
    uint16_t geteCO2() {
        return this->_data_eco2;
    }

    // Get AQI500 value of last measurement
    uint16_t getAQI500() {
        return this->_data_aqi500;
    }

    // Get resistance of HP0 of last measurement
    uint32_t getHP0() {
        return this->_hp0_rs;
    }

    // Get resistance of HP1 of last measurement
    uint32_t getHP1() {
        return this->_hp1_rs;
    }

    // Get resistance of HP2 of last measurement
    uint32_t getHP2() {
        return this->_hp2_rs;
    }

    // Get resistance of HP3 of last measurement
    uint32_t getHP3() {
        return this->_hp3_rs;
    }

    // Get baseline resistance of HP0 of last measurement
    uint32_t getHP0BL() {
        return this->_hp0_bl;
    }

    // Get baseline resistance of HP1 of last measurement
    uint32_t getHP1BL() {
        return this->_hp1_bl;
    }

    // Get baseline resistance of HP2 of last measurement
    uint32_t getHP2BL() {
        return this->_hp2_bl;
    }

    // Get baseline resistance of HP3 of last measurement
    uint32_t getHP3BL() {
        return this->_hp3_bl;
    }

    // Return status code of sensor
    uint8_t getMISR() {
        return this->_misr;
    }

private:

    bool_t _getWhoAmI(
            void
    );

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
    uint8_t         _deviceAddress;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isInitialized              : 1;
    // bool_t          _newDataReady               : 1;
    Error           _lastError;
    Mode            _mode;
    uint8_t         _firmwareVersionMajor;
    uint8_t         _firmwareVersionMinor;
    uint8_t         _firmwareVersionBuild;

    uint8_t         _nINT;
    uint8_t         _nCS;
    uint8_t         _sdaPin = 0;
    uint8_t         _sclPin = 0;

    bool            debugENS160 = false;
    bool            _available = false;                     // ENS160 available
    uint8_t         _revENS16x = 0;                         // ENS160 or ENS161 connected? (FW >7)
    uint8_t         _fw_ver_major;
    uint8_t         _fw_ver_minor;
    uint8_t         _fw_ver_build;
    uint16_t        _stepCount;                         // Counter for custom sequence

    uint8_t         _data_aqi;
    uint16_t        _data_tvoc;
    uint16_t        _data_eco2;
    uint16_t        _data_aqi500;
    uint32_t        _hp0_rs;
    uint32_t        _hp0_bl;
    uint32_t        _hp1_rs;
    uint32_t        _hp1_bl;
    uint32_t        _hp2_rs;
    uint32_t        _hp2_bl;
    uint32_t        _hp3_rs;
    uint32_t        _hp3_bl;
    uint16_t        _temp;
    int             _slaveaddr;                         // Slave address of the ENS160
    uint8_t         _misr;

    // Sends a reset to the ENS160. Returns false on I2C problems.
    bool _reset();
    // Reads the part ID and confirms valid sensor
    bool _checkPartID();
    // Initialize idle mode and confirms
    bool _clearCommand();
    // Read firmware revisions
    bool _getFirmware();

    void _i2c_init();

    uint8_t _read8(uint8_t addr, uint8_t reg);
    uint8_t _read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t num);
    uint8_t _write8(uint8_t addr, uint8_t reg, uint8_t value);
    uint8_t _write(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t num);

    //Isotherm, HP0 252°C / HP1 350°C / HP2 250°C / HP3 324°C / measure every 1008ms
    uint8_t _seq_steps[1][8] = {{ 0x7C, 0x0A, 0x7E, 0xAF, 0xAF, 0xA2, 0x00, 0x80 },};

protected:

    // NONE

}; // class Ens160

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

#endif  // __FUNSAPE_LIB_ENS160_HPP

// =============================================================================
// END OF FILE - funsapeLibEns160.hpp
// =============================================================================
