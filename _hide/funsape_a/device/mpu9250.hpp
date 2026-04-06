// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __MPU9250_HPP
#define __MPU9250_HPP                   2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [mpu9250.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __MPU9250_HPP
#   error [mpu9250.hpp] Error 2 - Build mismatch between file (mpu9250.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/bus.hpp"
#if !defined(__BUS_HPP)
#   error [mpu9250.hpp] Error 1 - Header file (bus.hpp) is missing or corrupted!
#elif __BUS_HPP != __MPU9250_HPP
#   error [mpu9250.hpp] Error 5 - Build mismatch between file (mpu9250.hpp) and library dependency (bus.hpp)!
#endif

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [mpu9250.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __MPU9250_HPP
#   error [mpu9250.hpp] Error 5 - Build mismatch between file (mpu9250.hpp) and library dependency (debug.hpp)!
#endif

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

class Mpu9250
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    enum class AccelFullScale {
        FULL_SCALE_2_G      = 0,
        FULL_SCALE_4_G      = 1,
        FULL_SCALE_8_G      = 2,
        FULL_SCALE_16_G     = 3,
    };

    enum class GyroFullScale {
        FULL_SCALE_250_DPS      = 0,
        FULL_SCALE_500_DPS      = 1,
        FULL_SCALE_1000_DPS     = 2,
        FULL_SCALE_2000_DPS     = 3,
    };

    enum class GyroConfig {
        FREQ_32_KHZ_FILTER_FREQ_8800_HZ     = 0b11'000,
        FREQ_32_KHZ_FILTER_FREQ_3600_HZ     = 0b10'000,
        FREQ_8_KHZ_FILTER_FREQ_250_HZ       = 0b00'000,
        FREQ_1_KHZ_FILTER_FREQ_184_HZ       = 0b00'001,
        FREQ_1_KHZ_FILTER_FREQ_92_HZ        = 0b00'010,
        FREQ_1_KHZ_FILTER_FREQ_41_HZ        = 0b00'011,
        FREQ_1_KHZ_FILTER_FREQ_20_HZ        = 0b00'100,
        FREQ_1_KHZ_FILTER_FREQ_10_HZ        = 0b00'101,
        FREQ_1_KHZ_FILTER_FREQ_5_HZ         = 0b00'110,
        FREQ_8_KHZ_FILTER_FREQ_3600_HZ      = 0b00'111,
    };

    enum class AccelConfig {
        FREQ_4_KHZ_FILTER_FREQ_1046_HZ  = 0b1'000,
        FREQ_1_KHZ_FILTER_FREQ_218_HZ   = 0b0'000,
        FREQ_1_KHZ_FILTER_FREQ_99_HZ    = 0b0'010,
        FREQ_1_KHZ_FILTER_FREQ_45_HZ    = 0b0'011,
        FREQ_1_KHZ_FILTER_FREQ_21_HZ    = 0b0'100,
        FREQ_1_KHZ_FILTER_FREQ_10_HZ    = 0b0'101,
        FREQ_1_KHZ_FILTER_FREQ_5_HZ     = 0b0'110,
        FREQ_1_KHZ_FILTER_FREQ_420_HZ   = 0b0'111,
        // SAMPLE_RATE_4_KHZ       = 256,
        // SAMPLE_RATE_1_KHZ       = 0,
        // SAMPLE_RATE_500_HZ      = 1,
        // SAMPLE_RATE_250_HZ      = 3,
        // SAMPLE_RATE_200_HZ      = 4,
        // SAMPLE_RATE_125_HZ      = 7,
        // SAMPLE_RATE_100_HZ      = 9,
        // SAMPLE_RATE_50_HZ       = 19,
        // SAMPLE_RATE_40_HZ       = 24,
        // SAMPLE_RATE_25_HZ       = 39,
        // SAMPLE_RATE_20_HZ       = 49,
        // SAMPLE_RATE_12P5_HZ     = 79,
        // SAMPLE_RATE_10_HZ       = 99,
        // SAMPLE_RATE_8_HZ        = 124,
        // SAMPLE_RATE_5_HZ        = 199,
        // SAMPLE_RATE_4_HZ        = 249,
        // SAMPLE_RATE_3P9_HZ      = 255,
    };

    enum class CleanMode {
        PULSED              = 0,
        LATCHED_STATUS_READ = 1,
        LATCHED_ANY_READ    = 2,
    };

private:
    enum class Register {
        SELF_TEST_X_GYRO    = 0x00,
        SELF_TEST_Y_GYRO    = 0x01,
        SELF_TEST_Z_GYRO    = 0x02,
        SELF_TEST_X_ACCEL   = 0x0D,
        SELF_TEST_Y_ACCEL   = 0x0E,
        SELF_TEST_Z_ACCEL   = 0x0F,
        XG_OFFSET_H         = 0x13,
        XG_OFFSET_L         = 0x14,
        YG_OFFSET_H         = 0x15,
        YG_OFFSET_L         = 0x16,
        ZG_OFFSET_H         = 0x17,
        ZG_OFFSET_L         = 0x18,
        SMPLRT_DIV          = 0x19,
        CONFIG              = 0x1A,
        GYRO_CONFIG         = 0x1B,
        ACCEL_CONFIG_1      = 0x1C,
        ACCEL_CONFIG_2      = 0x1D,
        LP_ACCEL_ODR        = 0x1E,
        WOM_THR             = 0x1F,
        FIFO_EN             = 0x23,
        I2C_MST_CTRL        = 0x24,
        I2C_SLV0_ADDR       = 0x25,
        I2C_SLV0_REG        = 0x26,
        I2C_SLV0_CTRL       = 0x27,
        I2C_SLV1_ADDR       = 0x28,
        I2C_SLV1_REG        = 0x29,
        I2C_SLV1_CTRL       = 0x2A,
        I2C_SLV2_ADDR       = 0x2B,
        I2C_SLV2_REG        = 0x2C,
        I2C_SLV2_CTRL       = 0x2D,
        I2C_SLV3_ADDR       = 0x2E,
        I2C_SLV3_REG        = 0x2F,
        I2C_SLV3_CTRL       = 0x30,
        I2C_SLV4_ADDR       = 0x31,
        I2C_SLV4_REG        = 0x32,
        I2C_SLV4_DO         = 0x33,
        I2C_SLV4_CTRL       = 0x34,
        I2C_SLV4_DI         = 0x35,
        I2C_MST_STATUS      = 0x36,
        INT_PIN_CFG         = 0x37,
        INT_ENABLE          = 0x38,
        INT_STATUS          = 0x3A,
        ACCEL_XOUT_H        = 0x3B,
        ACCEL_XOUT_L        = 0x3C,
        ACCEL_YOUT_H        = 0x3D,
        ACCEL_YOUT_L        = 0x3E,
        ACCEL_ZOUT_H        = 0x3F,
        ACCEL_ZOUT_L        = 0x40,
        TEMP_OUT_H          = 0x41,
        TEMP_OUT_L          = 0x42,
        GYRO_XOUT_H         = 0x43,
        GYRO_XOUT_L         = 0x44,
        GYRO_YOUT_H         = 0x45,
        GYRO_YOUT_L         = 0x46,
        GYRO_ZOUT_H         = 0x47,
        GYRO_ZOUT_L         = 0x48,
        EXT_SENS_DATA_00    = 0x49,
        EXT_SENS_DATA_01    = 0x4A,
        EXT_SENS_DATA_02    = 0x4B,
        EXT_SENS_DATA_03    = 0x4C,
        EXT_SENS_DATA_04    = 0x4D,
        EXT_SENS_DATA_05    = 0x4E,
        EXT_SENS_DATA_06    = 0x4F,
        EXT_SENS_DATA_07    = 0x50,
        EXT_SENS_DATA_08    = 0x51,
        EXT_SENS_DATA_09    = 0x52,
        EXT_SENS_DATA_10    = 0x53,
        EXT_SENS_DATA_11    = 0x54,
        EXT_SENS_DATA_12    = 0x55,
        EXT_SENS_DATA_13    = 0x56,
        EXT_SENS_DATA_14    = 0x57,
        EXT_SENS_DATA_15    = 0x58,
        EXT_SENS_DATA_16    = 0x59,
        EXT_SENS_DATA_17    = 0x5A,
        EXT_SENS_DATA_18    = 0x5B,
        EXT_SENS_DATA_19    = 0x5C,
        EXT_SENS_DATA_20    = 0x5D,
        EXT_SENS_DATA_21    = 0x5E,
        EXT_SENS_DATA_22    = 0x5F,
        EXT_SENS_DATA_23    = 0x60,
        I2C_SLV0_DO         = 0x63,
        I2C_SLV1_DO         = 0x64,
        I2C_SLV2_DO         = 0x65,
        I2C_SLV3_DO         = 0x66,
        I2C_MST_DELAY_CTRL  = 0x67,
        SIGNAL_PATH_RESET   = 0x68,
        MOT_DETECT_CTRL     = 0x69,
        USER_CTRL           = 0x6A,
        PWR_MGMT_1          = 0x6B,
        PWR_MGMT_2          = 0x6C,
        FIFO_COUNTH         = 0x72,
        FIFO_COUNTL         = 0x73,
        FIFO_R_W            = 0x74,
        WHO_AM_I            = 0x75,
        XA_OFFSET_H         = 0x77,
        XA_OFFSET_L         = 0x78,
        YA_OFFSET_H         = 0x7A,
        YA_OFFSET_L         = 0x7B,
        ZA_OFFSET_H         = 0x7D,
        ZA_OFFSET_L         = 0x7E,
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    Mpu9250(
            void
    );

    ~Mpu9250(
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
    bool_t init(
            Bus *twiHandler_p,
            cbool_t useAlternateAddress_p = false
    );
    bool_t init(
            Bus *spiHandler_p,
            void (*actDevFuncCallback_p)(void),
            void (*deactDevFuncCallback_p)(void)
    );
    bool_t restart(
            void
    );
    inlined Error getLastError(void);

    bool_t getAccelData(int16_t *accelBuff_p, Axis axis_p = Axis::ALL);
    bool_t getAccelOffset(int16_t *accelBuff_p, Axis axis_p = Axis::ALL);
    bool_t setAccelFullScale(AccelFullScale scale_p);
    bool_t setAccelOffset(int16_t *accelBuff_p, Axis axis_p = Axis::ALL);
    bool_t setAccelEnabledAxis(Axis enabledAxis_p);

    bool_t getGyroData(int16_t *gyroBuff_p, Axis axis_p = Axis::ALL);
    bool_t getGyroOffset(int16_t *gyroBuff_p, Axis axis_p = Axis::ALL);
    bool_t setGyroFullScale(GyroFullScale scale_p);
    bool_t setGyroOffset(int16_t *gyroBuff_p, Axis axis_p = Axis::ALL);
    bool_t setGyroEnabledAxis(Axis enabledAxis_p);

    bool_t getTempData(int16_t *tempValue_p);

    // bool_t configAccel(AccelConfig config_p,, Axis axis_p = Axis::ALL);

    bool_t performSelfTest(bool_t *isSuccess_p);

    bool_t setIntPinMode(
            const LogicLevel activeLevel_p,
            const DriverMode driverMode_p       = DriverMode::OPEN_DRAIN,
            const CleanMode cleanMode_p         = CleanMode::LATCHED_STATUS_READ
    );

    bool_t getExtSensData(uint8_t *buffData_p, cuint8_t firstSensor_p = 0, cuint8_t totalSensors_p = 24);


//     /////////////////     CONTROL AND STATUS     /////////////////     //

private:
    bool_t _read(const Register regAddress_p, uint8_t *buffData_p, cuint8_t bytesToRead_p);
    bool_t _write(const Register regAddress_p, cuint8_t *buffData_p, cuint8_t bytesToWrite_p);
    bool_t _initialize(void);

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    Error _lastError;
    bool_t _isInitialized : 1;
    bool_t _useSpi : 1;
    Bus *_busHandler;
    uint8_t _i2cAddress : 7;
    void (* _activateDevice)(void);
    void (* _deactivateDevice)(void);
    AccelFullScale _accelFullScale      : 2;
    bool_t _accelDisableX : 1;
    bool_t _accelDisableY : 1;
    bool_t _accelDisableZ : 1;
    bool_t _gyroDisableX : 1;
    bool_t _gyroDisableY : 1;
    bool_t _gyroDisableZ : 1;
    uint8_t _gyroFChoiceB : 2;
    GyroFullScale _gyroFullScale;

    CleanMode _intPinCleanMode;
    bool_t _i2cBypassModeEnabled : 1;
    bool_t _fsyncPinIntModeEnable : 1;
    LogicLevel _fsyncPinActiveLevel;
    LogicLevel _intPinActiveLevel;
    DriverMode _intPinDriverMode;

    // bool_t _intFsyncFlag : 1;
    // bool_t _intPinActiveLevel : 1;
    // bool_t _intPinAutoClear : 1;
    // bool_t _intPinLatchEnable : 1;
    // bool_t _intPinOpenDrain : 1;
    // bool_t _intRawDataReadyEnable : 1;
    // bool_t _intWakeOnMotionEnabled : 1;
    // bool_t _intWakeOnMotionFlag : 1;
    // bool_t _intFifoOverflowEnabled : 1;
    // bool_t _intFifoOverflowFlag : 1;



    // AccelConfig _accelConfig;
    // AccelLowPowerSampleRate _accelLowPowerSampleRate;
    // bool_t _accelFChoiceB : 1;
    // bool_t _accelSignalPathReset : 1;
    // GyroConfig _gyroConfig;
    // bool_t _gyroSignalPathReset : 1;
    // bool_t _gyroStandby : 1;
    // bool_t _wakeOnMotionEnable : 1;
    // bool_t _wakeOnMotionMode : 1;
    // uint8_t _clockSelection : 3;
    // uint8_t _extSyncSet : 3;
    // uint8_t _lowPowerOscClock : 4;
    // uint8_t _sampleRateDivider;
    // uint8_t _wakeOnMotionThreshold;
    // bool_t _cycleEnable : 1;
    // bool_t _powerDownMode : 1;
    // bool_t _ptatDisable : 1;
    // bool_t _resetDevice : 1;
    // bool_t _resetSignal : 1;
    // bool_t _resetTemp : 1;
    // bool_t _signalPathResetStrobe : 1;
    // bool_t _sleepEnable : 1;
    // bool_t _tempSignalPathReset : 1;
    // bool_t _resetI2c : 1;
    // bool_t _i2cExtSensorShadowDelayEnable : 1;
    // bool_t _i2cWaitForExtSensor : 1;
    // bool_t _i2cDataReadyIntWaitExternalSensors : 1;
    // bool_t _intI2cDataReadyEnabled : 1;
    // bool_t _i2cStopBetweenTransmissions : 1;
    // bool_t _i2cStatusArbitrationLost : 1;
    // bool_t _i2cStatusPassThroughFlag : 1;
    // bool_t _magI2cBypass : 1;
    // bool_t _i2cMasterClock : 4;
    // bool_t _i2cMasterEnable : 1;
    // bool_t _i2cMultiMasterEnabled : 1;
    // bool_t _i2cMasterResetStrobe : 1;
    // bool_t _i2cSlave0DelayEnable : 1;
    // bool_t _i2cSlave0Enable : 1;
    // bool_t _i2cSlave0GroupingSkipFirst : 1;
    // bool_t _i2cSlave0ReadWrite : 1;
    // bool_t _i2cSlave0DoNotSendRegister : 1;
    // bool_t _i2cSlave0GroupEndingEven : 1;
    // bool_t _i2cSlave0ReadMode : 1;
    // bool_t _i2cSlave0WordBytesSwap : 1;
    // bool_t _i2cStatusSlave0NackReceivedFlag : 1;
    // uint8_t _i2cSlave0Address : 7;
    // uint8_t _i2cSlave0DataLength : 4;
    // uint8_t _i2cSlave0DataOut;
    // uint8_t _i2cSlave0Register;
    // bool_t _i2cSlave1DelayEnable : 1;
    // bool_t _i2cSlave1Enable : 1;
    // bool_t _i2cSlave1GroupingSkipFirst : 1;
    // bool_t _i2cSlave1ReadWrite : 1;
    // bool_t _i2cSlave1DoNotSendRegister : 1;
    // bool_t _i2cSlave1GroupEndingEven : 1;
    // bool_t _i2cSlave1WordBytesSwap : 1;
    // bool_t _i2cStatusSlave1NackReceivedFlag : 1;
    // uint8_t _i2cSlave1Address : 7;
    // uint8_t _i2cSlave1DataLength : 4;
    // uint8_t _i2cSlave1DataOut;
    // uint8_t _i2cSlave1Register;
    // bool_t _i2cSlave2DelayEnable : 1;
    // bool_t _i2cSlave2Enable : 1;
    // bool_t _i2cSlave2GroupingSkipFirst : 1;
    // bool_t _i2cSlave2ReadWrite : 1;
    // bool_t _i2cSlave2DoNotSendRegister : 1;
    // bool_t _i2cSlave2GroupEndingEven : 1;
    // bool_t _i2cSlave2WordBytesSwap : 1;
    // bool_t _i2cStatusSlave2NackReceivedFlag : 1;
    // uint8_t _i2cSlave2Address : 7;
    // uint8_t _i2cSlave2DataLength : 4;
    // uint8_t _i2cSlave2DataOut;
    // uint8_t _i2cSlave2Register;
    // bool_t _i2cSlave3DelayEnable : 1;
    // bool_t _i2cSlave3Enable : 1;
    // bool_t _i2cSlave3GroupingSkipFirst : 1;
    // bool_t _i2cSlave3ReadWrite : 1;
    // bool_t _i2cSlave3DoNotSendRegister : 1;
    // bool_t _i2cSlave3GroupEndingEven : 1;
    // bool_t _i2cSlave3WordBytesSwap : 1;
    // bool_t _i2cStatusSlave3NackReceivedFlag : 1;
    // uint8_t _i2cSlave3Address : 7;
    // uint8_t _i2cSlave3DataLength : 4;
    // uint8_t _i2cSlave3DataOut;
    // uint8_t _i2cSlave3Register;
    // bool_t _i2cSlave4DelayEnable : 1;
    // bool_t _i2cSlave4Enable : 1;
    // bool_t _i2cSlave4ReadWrite : 1;
    // bool_t _i2cSlave4DoNotSendRegister : 1;
    // bool_t _i2cSlave4IntTransferReadyEnabled : 1;
    // bool_t _i2cSlave4SingleTransferEnable : 1;
    // bool_t _i2cStatusSlave4NackReceivedFlag : 1;
    // bool_t _i2cStatusSlave4TransferDoneFlag : 1;
    // uint8_t _i2cSlave4Address : 7;
    // uint8_t _i2cSlave4DataOut;
    // uint8_t _i2cSlave4Delay : 5;
    // uint8_t _i2cSlave4Register;
    // uint8_t _i2cSlave4DataIn;
    // uint8_t _i2cSlave4MasterDelay : 5;
    // bool_t _resetFifo : 1;
    // bool_t _fifoEnabled : 1;
    // bool_t _fifoMode : 1;
    // bool_t _fifoResetStrobe : 1;
    // bool_t _fifoSlave0Store : 1;
    // bool_t _fifoSlave1Store : 1;
    // bool_t _fifoSlave2Store : 1;
    // bool_t _fifoSlave3Store : 1;
    // bool_t _fifoStopWhenFull : 1;
    // bool_t _fifoTempStore : 1;
    // uint16_t _fifoCount : 13;
    // uint16_t _fifoLenght;
    // uint8_t _fifoData;
    // bool_t _fifoGyroXStore : 1;
    // bool_t _fifoGyroYStore : 1;
    // bool_t _fifoGyroZStore : 1;
    // bool_t _fifoAccelStore : 1;
    // int16_t magSensibility_[3];

protected:
    // NONE

}; // class Mpu9250

// =============================================================================
// Inlined class functions
// =============================================================================

inlined Error Mpu9250::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __MPU9250_HPP

// =============================================================================
// End of file (mpu9250.hpp)
// =============================================================================
