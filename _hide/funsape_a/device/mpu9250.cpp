
// =============================================================================
// System file dependencies
// =============================================================================

#include "mpu9250.hpp"
#if !defined(__MPU9250_HPP)
#    error Error 1 - Header file (mpu9250.hpp) is missing or corrupted!
#elif __MPU9250_HPP != 2508
#    error Error 6 - Build mismatch between header file (mpu9250.hpp) and source file (mpu9250.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

static cuint8_t constNormalSlaveAddress = 0x68;
static cuint8_t constAlternateSlaveAddress = 0x69;
static cuint8_t constDeviceId = 0x71;
static cuint8_t constResetDelay = 50;

// =============================================================================
// File exclusive - New data types
// =============================================================================

enum class Bit : uint8_t {
    PWR_MGMT_1_H_RESET              = 7,
    ACCEL_CONFIG_FS_SEL0         = 3,
    PWR_MGMT_2_DIS_XA                = 5,
    PWR_MGMT_2_DIS_YA                = 4,
    PWR_MGMT_2_DIS_ZA                = 3,
    PWR_MGMT_2_DIS_XG                = 2,
    PWR_MGMT_2_DIS_YG                = 1,
    PWR_MGMT_2_DIS_ZG                = 0,
    GYRO_CONFIG_FS_SEL0              = 2,
    GYRO_CONFIG_FCHOICE_B_0          = 0,
    ACCEL_CONFIG2_FCHOICE_B_0        = 2,
    ACCEL_CONFIG2_DLPF_CFG_0     = 0,
    CONFIG_GYRO_DLPF_CFG_0           = 0,
    GYRO_CONFIG_Z_ST_EN              = 7,
    GYRO_CONFIG_Y_ST_EN              = 6,
    GYRO_CONFIG_X_ST_EN              = 5,
    ACCEL_CONFIG_Z_ST_EN         = 7,
    ACCEL_CONFIG_Y_ST_EN         = 6,
    ACCEL_CONFIG_X_ST_EN         = 5,
    INT_PIN_LEVEL                    = 7,
    INT_PIN_DRIVER                   = 6,
    INT_PIN_LATCH                    = 5,
    INT_PIN_AUTO_RESET               = 4,
    FSYNC_LEVEL                      = 3,
    FSYNC_MODE_EN                    = 2,
    BYPASS_EN                        = 1,

    // CONFIG_FIFO_MODE             = 6,
    // CONFIG_EXT_SYNC_SET_0            = 3,
    // I2C_SLV0_EN                      = 7,
    // I2C_SLV0_BYTE_SW             = 6,
    // I2C_SLV0_REG_DIS             = 5,
    // I2C_SLV0_GRP                 = 4,
    // I2C_SLV0_LENG_0                  = 0,
    // I2C_SLV1_EN                      = 7,
    // I2C_SLV1_BYTE_SW             = 6,
    // I2C_SLV1_REG_DIS             = 5,
    // I2C_SLV1_GRP                 = 4,
    // I2C_SLV1_LENG_0                  = 0,
    // I2C_SLV2_EN                      = 7,
    // I2C_SLV2_BYTE_SW             = 6,
    // I2C_SLV2_REG_DIS             = 5,
    // I2C_SLV2_GRP                 = 4,
    // I2C_SLV2_LENG_0                  = 0,
    // I2C_SLV3_EN                      = 7,
    // I2C_SLV3_BYTE_SW             = 6,
    // I2C_SLV3_REG_DIS             = 5,
    // I2C_SLV3_GRP                 = 4,
    // I2C_SLV3_LENG_0                  = 0,
    // I2C_SLV4_EN                      = 7,
    // I2C_SLV4_INT_EN                  = 6,
    // I2C_SLV4_REG_DIS             = 5,
    // I2C_SLV4_DELAY                   = 0,
    // SIG_PAT_RST_GYRO             = 2,
    // SIG_PAT_RST_ACCEL                = 1,
    // SIG_PAT_RST_TEMP             = 0,
    // USR_CONTROLFIFO_EN               = 6,
    // USR_CONTROLI2C_MST_EN            = 5,
    // USR_CONTROLI2C_IF_DIS            = 4,
    // USR_CONTROLFIFO_RST              = 2,
    // USR_CONTROLI2C_MST_RST           = 1,
    // USR_CONTROLSIG_COND_RST          = 0,
    // PWR_MGMT_1_SLEEP             = 6,
    // PWR_MGMT_1_CYCLE             = 5,
    // PWR_MGMT_1_GYRO_STANDBY          = 4,
    // PWR_MGMT_1_PD_PTAT               = 3,
    // PWR_MGMT_1_CLKSEL_0              = 0,
    // WAKE_ON_MOTION_EN                = 6,
    // FIFO_OVERFLOW_EN             = 4,
    // FSYNC_INT_EN                 = 3,
    // RAW_DATA_READY_EN                = 0,
    // INT_STATUS_WOM                   = 6,
    // INT_STATUS_FIFO_OVERFLOW     = 4,
    // INT_STATUS_FSYNC             = 3,
    // INT_STATUS_RAW_DATA_RDY          = 0,
};

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Public function definitions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Mpu9250::Mpu9250(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Mpu9250::Mpu9250(void)"), Debug::CodeIndex::MPU9250_MODULE);

    // Resets data members

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return;
}

Mpu9250::~Mpu9250(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Mpu9250::~Mpu9250(void)"), Debug::CodeIndex::MPU9250_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

bool_t Mpu9250::init(Bus *twiHandler_p, cbool_t useAlternateAddress_p)
{
    // Local variables
    uint8_t auxBuff;

    // Reset data members
    this->_isInitialized    = false;
    this->_busHandler       = nullptr;
    this->_activateDevice   = nullptr;
    this->_deactivateDevice = nullptr;
    this->_useSpi           = false;
    this->_i2cAddress       = 0;

    // Check for errors
    if(!isPointerValid(twiHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    } else {
        switch(twiHandler_p->getBusType()) {
        case Bus::BusType::TWI:
            break;
        case Bus::BusType::SPI:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_INVALID;
            debugMessage(Error::BUS_HANDLER_INVALID, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        default:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
    }

    // Update data members
    this->_busHandler = twiHandler_p;
    this->_i2cAddress = (useAlternateAddress_p) ? constAlternateSlaveAddress : constNormalSlaveAddress;
    this->_useSpi = false;

    // Initialize device
    if(!this->_initialize()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::init(Bus *spiHandler_p, void (*actDevFuncCallback_p)(void), void (*deactDevFuncCallback_p)(void))
{
    // Local variables
    uint8_t auxBuff;

    // Reset data members
    this->_isInitialized = false;
    this->_busHandler = nullptr;
    this->_activateDevice = nullptr;
    this->_deactivateDevice = nullptr;
    this->_useSpi = false;
    this->_i2cAddress = 0;

    // Check for errors
    if(!isPointerValid(actDevFuncCallback_p) || !isPointerValid(deactDevFuncCallback_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(spiHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    } else {
        switch(spiHandler_p->getBusType()) {
        case Bus::BusType::TWI:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_INVALID;
            debugMessage(Error::BUS_HANDLER_INVALID, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        case Bus::BusType::SPI:
            break;
        default:
            // Returns error
            this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
            debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
    }

    // Update data members
    this->_busHandler = spiHandler_p;
    this->_activateDevice = actDevFuncCallback_p;
    this->_deactivateDevice = deactDevFuncCallback_p;
    this->_useSpi = true;

    // Initialize device
    if(!this->_initialize()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::restart(void)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Send reset signal
    auxBuff = (1 << (uint8_t)Bit::PWR_MGMT_1_H_RESET);
    if(!this->_write(Register::PWR_MGMT_1, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Wait until reset takes
    delayMs(constResetDelay);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::setAccelFullScale(AccelFullScale scale_p)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process arguments
    auxBuff = (uint8_t)scale_p << (uint8_t)Bit::ACCEL_CONFIG_FS_SEL0;

    // Writes configuration
    if(!this->_write(Register::ACCEL_CONFIG_1, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates data members
    this->_accelFullScale = scale_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::getAccelData(int16_t *accelBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[6] = {0, 0, 0, 0, 0, 0};
    int16_t auxInt16 = 0;
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(accelBuff_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::ACCEL_XOUT_H, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    if((axis_p & Axis::X) == Axis::X) {
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        accelBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        accelBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        accelBuff_p[index++] = auxInt16;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::getAccelOffset(int16_t *accelBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[6] = {0, 0, 0, 0, 0, 0};
    int16_t auxInt16 = 0;
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(accelBuff_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::XA_OFFSET_H, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    if((axis_p & Axis::X) == Axis::X) {
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        accelBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        accelBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        accelBuff_p[index++] = auxInt16;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::setAccelOffset(int16_t *accelBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[2] = {0, 0};
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(accelBuff_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Writes configuration
    if((axis_p & Axis::X) == Axis::X) {
        auxBuff[1] = (uint8_t)(accelBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(accelBuff_p[index] & 0xFF);
        if(!this->_write(Register::XA_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
        index++;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxBuff[1] = (uint8_t)(accelBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(accelBuff_p[index] & 0xFF);
        if(!this->_write(Register::YA_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
        index++;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxBuff[1] = (uint8_t)(accelBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(accelBuff_p[index] & 0xFF);
        if(!this->_write(Register::ZA_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
    }

    // Returns error
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return false;
}

bool_t Mpu9250::setAccelEnabledAxis(Axis enabledAxis_p)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process arguments
    if(((enabledAxis_p & Axis::X) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_XA);
    }
    if(((enabledAxis_p & Axis::Y) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_YA);
    }
    if(((enabledAxis_p & Axis::Z) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_ZA);
    }
    if(this->_gyroDisableX) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_XG);
    }
    if(this->_gyroDisableY) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_YG);
    }
    if(this->_gyroDisableZ) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_ZG);
    }

    // Writes configuration
    if(!this->_write(Register::PWR_MGMT_2, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates data members
    this->_accelDisableX = ((enabledAxis_p & Axis::X) == Axis::NONE) ? true : false;
    this->_accelDisableY = ((enabledAxis_p & Axis::Y) == Axis::NONE) ? true : false;
    this->_accelDisableZ = ((enabledAxis_p & Axis::Z) == Axis::NONE) ? true : false;

    // Returns error
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return false;
}

bool_t Mpu9250::setGyroFullScale(GyroFullScale scale_p)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process arguments
    setMaskOffset(auxBuff, this->_gyroFChoiceB, (uint8_t)Bit::GYRO_CONFIG_FCHOICE_B_0);
    setMaskOffset(auxBuff, (uint8_t)scale_p, (uint8_t)Bit::GYRO_CONFIG_FS_SEL0);

    // Writes configuration
    if(!this->_write(Register::GYRO_CONFIG, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates data members
    this->_gyroFullScale = scale_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::getGyroData(int16_t *gyroBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[6] = {0, 0, 0, 0, 0, 0};
    int16_t auxInt16 = 0;
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(gyroBuff_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::GYRO_XOUT_H, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    if((axis_p & Axis::X) == Axis::X) {
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        gyroBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        gyroBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        gyroBuff_p[index++] = auxInt16;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::getGyroOffset(int16_t *gyroBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[6] = {0, 0, 0, 0, 0, 0};
    int16_t auxInt16 = 0;
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(gyroBuff_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::XG_OFFSET_H, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    if((axis_p & Axis::X) == Axis::X) {
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        gyroBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        gyroBuff_p[index++] = auxInt16;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        gyroBuff_p[index++] = auxInt16;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::setGyroOffset(int16_t *gyroBuff_p, Axis axis_p)
{
    // Local variables
    uint8_t auxBuff[2] = {0, 0};
    uint8_t index = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(axis_p == Axis::NONE) {
        // Returns error
        this->_lastError = Error::AXIS_INVALID;
        debugMessage(Error::AXIS_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(gyroBuff_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Writes configuration
    if((axis_p & Axis::X) == Axis::X) {
        auxBuff[1] = (uint8_t)(gyroBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(gyroBuff_p[index] & 0xFF);
        if(!this->_write(Register::XG_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
        index++;
    }
    if((axis_p & Axis::Y) == Axis::Y) {
        auxBuff[1] = (uint8_t)(gyroBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(gyroBuff_p[index] & 0xFF);
        if(!this->_write(Register::YG_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
        index++;
    }
    if((axis_p & Axis::Z) == Axis::Z) {
        auxBuff[1] = (uint8_t)(gyroBuff_p[index] >> 8);
        auxBuff[0] = (uint8_t)(gyroBuff_p[index] & 0xFF);
        if(!this->_write(Register::ZG_OFFSET_H, auxBuff, 2)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }
    }

    // Returns error
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return false;
}

bool_t Mpu9250::setGyroEnabledAxis(Axis enabledAxis_p)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process arguments
    if(this->_accelDisableX) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_XA);
    }
    if(this->_accelDisableY) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_YA);
    }
    if(this->_accelDisableZ) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_ZA);
    }
    if(((enabledAxis_p & Axis::X) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_XG);
    }
    if(((enabledAxis_p & Axis::Y) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_YG);
    }
    if(((enabledAxis_p & Axis::Z) == Axis::NONE)) {
        setBit(auxBuff, (uint8_t)Bit::PWR_MGMT_2_DIS_ZG);
    }

    // Writes configuration
    if(!this->_write(Register::PWR_MGMT_2, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates data members
    this->_gyroDisableX = ((enabledAxis_p & Axis::X) == Axis::NONE) ? true : false;
    this->_gyroDisableY = ((enabledAxis_p & Axis::Y) == Axis::NONE) ? true : false;
    this->_gyroDisableZ = ((enabledAxis_p & Axis::Z) == Axis::NONE) ? true : false;

    // Returns error
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return false;
}

bool_t Mpu9250::getTempData(int16_t *tempValue_p)
{
    // Local variables
    uint8_t auxBuff[2] = {0, 0};
    int16_t auxInt16 = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(tempValue_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::TEMP_OUT_H, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    *tempValue_p = (int16_t)auxBuff[0];
    *tempValue_p <<= 8;
    *tempValue_p |= (int16_t)auxBuff[1];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::performSelfTest(bool_t *isSuccess_p)
{
    // Local variables
    uint8_t auxBuff[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t auxRegConfig = 0;
    uint8_t auxRegGyroConfig = 0;
    uint8_t auxRegAccelConfig = 0;
    uint8_t auxRegAccelConfig2 = 0;
    int16_t auxInt16 = 0;
    int32_t auxAverages[6] = {0, 0, 0, 0, 0, 0};
    int16_t avgSelfTestOff[6] = {0, 0, 0, 0, 0, 0};
    int16_t avgSelfTestOn[6] = {0, 0, 0, 0, 0, 0};
    int16_t selfTestResponse[6] = {0, 0, 0, 0, 0, 0};
    int8_t factorySelfTestValues[6] = {0, 0, 0, 0, 0, 0};

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(isSuccess_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates arguments
    *isSuccess_p = false;

    // Read registers
    if(!this->_read(Register::CONFIG, auxBuff, 4)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Stores current configuration
    auxRegConfig = auxBuff[0];
    auxRegGyroConfig = auxBuff[1];
    auxRegAccelConfig = auxBuff[2];
    auxRegAccelConfig2 = auxBuff[3];

    // Initial configuration
    auxBuff[0] = (uint8_t)GyroConfig::FREQ_1_KHZ_FILTER_FREQ_92_HZ << (uint8_t)Bit::CONFIG_GYRO_DLPF_CFG_0;
    auxBuff[1] = (uint8_t)GyroFullScale::FULL_SCALE_250_DPS << (uint8_t)Bit::GYRO_CONFIG_FS_SEL0;
    auxBuff[2] = (uint8_t)AccelFullScale::FULL_SCALE_2_G << (uint8_t)Bit::ACCEL_CONFIG_FS_SEL0;
    auxBuff[3] = (uint8_t)AccelConfig::FREQ_1_KHZ_FILTER_FREQ_99_HZ << (uint8_t)Bit::ACCEL_CONFIG2_DLPF_CFG_0;

    // Writes configuration
    if(!this->_write(Register::CONFIG, auxBuff, 4)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Takes 200 samples
    auxAverages[0] = 0;
    auxAverages[1] = 0;
    auxAverages[2] = 0;
    auxAverages[3] = 0;
    auxAverages[4] = 0;
    auxAverages[5] = 0;
    for(uint8_t i = 0; i < 200; i++) {
        delayMs(1);
        // Read registers
        if(!this->_read(Register::ACCEL_XOUT_H, auxBuff, 14)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }

        // Process data
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        auxAverages[0] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        auxAverages[1] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        auxAverages[2] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[8];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[9];
        auxAverages[3] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[10];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[11];
        auxAverages[4] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[12];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[13];
        auxAverages[5] += (int32_t)auxInt16;
    }
    auxAverages[0] /= 200;
    auxAverages[1] /= 200;
    auxAverages[2] /= 200;
    auxAverages[3] /= 200;
    auxAverages[4] /= 200;
    auxAverages[5] /= 200;
    avgSelfTestOff[0] = (int16_t)auxAverages[0];
    avgSelfTestOff[1] = (int16_t)auxAverages[1];
    avgSelfTestOff[2] = (int16_t)auxAverages[2];
    avgSelfTestOff[3] = (int16_t)auxAverages[3];
    avgSelfTestOff[4] = (int16_t)auxAverages[4];
    avgSelfTestOff[5] = (int16_t)auxAverages[5];

    // Configures self-test
    auxBuff[0] = (uint8_t)GyroFullScale::FULL_SCALE_250_DPS << (uint8_t)Bit::GYRO_CONFIG_FS_SEL0;
    setBit(auxBuff[0], (uint8_t)Bit::GYRO_CONFIG_X_ST_EN);
    setBit(auxBuff[0], (uint8_t)Bit::GYRO_CONFIG_Y_ST_EN);
    setBit(auxBuff[0], (uint8_t)Bit::GYRO_CONFIG_Z_ST_EN);
    auxBuff[1] = (uint8_t)AccelFullScale::FULL_SCALE_2_G << (uint8_t)Bit::ACCEL_CONFIG_FS_SEL0;
    setBit(auxBuff[1], (uint8_t)Bit::ACCEL_CONFIG_X_ST_EN);
    setBit(auxBuff[1], (uint8_t)Bit::ACCEL_CONFIG_Y_ST_EN);
    setBit(auxBuff[1], (uint8_t)Bit::ACCEL_CONFIG_Z_ST_EN);

    // Writes configuration
    if(!this->_write(Register::GYRO_CONFIG, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    delayMs(20);

    // Takes 200 samples
    auxAverages[0] = 0;
    auxAverages[1] = 0;
    auxAverages[2] = 0;
    auxAverages[3] = 0;
    auxAverages[4] = 0;
    auxAverages[5] = 0;
    for(uint8_t i = 0; i < 200; i++) {
        delayMs(1);
        // Read registers
        if(!this->_read(Register::ACCEL_XOUT_H, auxBuff, 14)) {
            // Returns error
            debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
            return false;
        }

        // Process data
        auxInt16 = (int16_t)auxBuff[0];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[1];
        auxAverages[0] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[2];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[3];
        auxAverages[1] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[4];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[5];
        auxAverages[2] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[8];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[9];
        auxAverages[3] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[10];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[11];
        auxAverages[4] += (int32_t)auxInt16;
        auxInt16 = (int16_t)auxBuff[12];
        auxInt16 <<= 8;
        auxInt16 |= (int16_t)auxBuff[13];
        auxAverages[5] += (int32_t)auxInt16;
    }
    auxAverages[0] /= 200;
    auxAverages[1] /= 200;
    auxAverages[2] /= 200;
    auxAverages[3] /= 200;
    auxAverages[4] /= 200;
    auxAverages[5] /= 200;
    avgSelfTestOn[0] = (int16_t)auxAverages[0];
    avgSelfTestOn[1] = (int16_t)auxAverages[1];
    avgSelfTestOn[2] = (int16_t)auxAverages[2];
    avgSelfTestOn[3] = (int16_t)auxAverages[3];
    avgSelfTestOn[4] = (int16_t)auxAverages[4];
    avgSelfTestOn[5] = (int16_t)auxAverages[5];

    // Calculates the response
    selfTestResponse[0] = avgSelfTestOn[0] - avgSelfTestOff[0];
    selfTestResponse[1] = avgSelfTestOn[1] - avgSelfTestOff[1];
    selfTestResponse[2] = avgSelfTestOn[2] - avgSelfTestOff[2];
    selfTestResponse[3] = avgSelfTestOn[3] - avgSelfTestOff[3];
    selfTestResponse[4] = avgSelfTestOn[4] - avgSelfTestOff[4];
    selfTestResponse[5] = avgSelfTestOn[5] - avgSelfTestOff[5];

    // Disables self-test
    auxBuff[0] = (uint8_t)GyroFullScale::FULL_SCALE_250_DPS << (uint8_t)Bit::GYRO_CONFIG_FS_SEL0;
    auxBuff[1] = (uint8_t)AccelFullScale::FULL_SCALE_2_G << (uint8_t)Bit::ACCEL_CONFIG_FS_SEL0;

    // Writes configuration
    if(!this->_write(Register::GYRO_CONFIG, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    delayMs(20);

    // Restores configuration
    auxBuff[0] = auxRegConfig;
    auxBuff[1] = auxRegGyroConfig;
    auxBuff[2] = auxRegAccelConfig;
    auxBuff[3] = auxRegAccelConfig2;

    // Writes configuration
    if(!this->_write(Register::CONFIG, auxBuff, 4)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    if(!this->_read(Register::SELF_TEST_X_ACCEL, auxBuff, 3)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    factorySelfTestValues[0] = auxBuff[0];
    factorySelfTestValues[1] = auxBuff[1];
    factorySelfTestValues[2] = auxBuff[2];
    if(!this->_read(Register::SELF_TEST_X_GYRO, auxBuff, 3)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    factorySelfTestValues[3] = auxBuff[0];
    factorySelfTestValues[4] = auxBuff[1];
    factorySelfTestValues[5] = auxBuff[2];

    // 12) Calculate factory Self-Test value (ST_OTP) based on the following equation:
    // 13) Determine passing or failing Self-Test

    // Updates arguments
    *isSuccess_p = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::getExtSensData(uint8_t *buffData_p, cuint8_t firstSensor_p, cuint8_t totalSensors_p)
{
    // Local variables
    uint8_t auxBuff[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t auxRegister = (uint8_t)Register::EXT_SENS_DATA_00;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if(!isPointerValid(buffData_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    if((firstSensor_p > 23) || ((firstSensor_p + totalSensors_p) > 24)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Read registers
    auxRegister += firstSensor_p;
    if(!this->_read((Register)auxRegister, auxBuff, totalSensors_p)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process data
    for(uint8_t i = 0; i < totalSensors_p; i++) {
        buffData_p[i] = auxBuff[i];
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::setIntPinMode(const LogicLevel activeLevel_p, const DriverMode driverMode_p,
        const CleanMode cleanMode_p)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Check for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Process arguments
    auxBuff |= (activeLevel_p == LogicLevel::LOW) ? (1 << (uint8_t)Bit::INT_PIN_LEVEL) : 0;
    auxBuff |= (driverMode_p == DriverMode::OPEN_DRAIN) ? (1 << (uint8_t)Bit::INT_PIN_DRIVER) : 0;
    switch(cleanMode_p) {
    case CleanMode::PULSED:
        clrBit(auxBuff, (uint8_t)Bit::INT_PIN_LATCH);
        clrBit(auxBuff, (uint8_t)Bit::INT_PIN_AUTO_RESET);
        break;
    case CleanMode::LATCHED_STATUS_READ:
        setBit(auxBuff, (uint8_t)Bit::INT_PIN_LATCH);
        clrBit(auxBuff, (uint8_t)Bit::INT_PIN_AUTO_RESET);
        break;
    case CleanMode::LATCHED_ANY_READ:
        setBit(auxBuff, (uint8_t)Bit::INT_PIN_LATCH);
        setBit(auxBuff, (uint8_t)Bit::INT_PIN_AUTO_RESET);
        break;
    }
    auxBuff |= (this->_fsyncPinActiveLevel == LogicLevel::LOW) ? (1 << (uint8_t)Bit::FSYNC_LEVEL) : 0;
    auxBuff |= (this->_fsyncPinIntModeEnable) ? (1 << (uint8_t)Bit::FSYNC_MODE_EN) : 0;
    auxBuff |= (this->_i2cBypassModeEnabled) ? (1 << (uint8_t)Bit::BYPASS_EN) : 0;

    // Writes configuration
    if(!this->_write(Register::INT_PIN_CFG, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Updates data members
    this->_intPinActiveLevel = activeLevel_p;
    this->_intPinCleanMode = cleanMode_p;
    this->_intPinDriverMode = driverMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

bool_t Mpu9250::enableIntPin(const LogicLevel activeLevel_p, const DriverMode driverMode_p,
        const CleanMode cleanMode_p)
{

}




// bool_t Mpu9250::configAccel(AccelConfig config_p, AccelFullScale scale_p, Axis axis_p)
// {
// 	// Local variables
// 	uint8_t auxBuff[2];
// 	uint8_t auxFChoiceB = 0;
// 	uint8_t auxDlpfCfg = 0;
// 	uint8_t auxFullScale = 0;

// 	// Mark passage for debug
// 	debugMark();

// 	// Check for errors
// 	if(!this->_initialized) {
// 		// Returns error
// 		this->_lastError = Error::NOT_INITIALIZED;
// 		debugMessage(Error::NOT_INITIALIZED);
// 		return false;
// 	}
// 	if(axis_p == Axis::NONE) {
// 		// Returns error
// 		this->_lastError = Error::INVALID_AXIS;
// 		debugMessage(Error::INVALID_AXIS);
// 		return false;
// 	}

// 	// Process arguments
// 	auxFullScale = ((uint8_t)scale_p & 0x03) << MPU9250_BIT_ACCEL_CONFIG_FS_SEL0;
// 	auxFChoiceB = isBitSet((uint8_t)config_p, 4) << MPU9250_BIT_ACCEL_CONFIG2_FCHOICE_B_0;
// 	auxDlpfCfg = ((uint8_t)config_p & 0x07) << MPU9250_BIT_ACCEL_CONFIG2_DLPF_CFG_0;
// 	this->_accelDisableX = isBitClr((uint8_t)axis_p, 0);
// 	this->_accelDisableY = isBitClr((uint8_t)axis_p, 1);
// 	this->_accelDisableZ = isBitClr((uint8_t)axis_p, 2);

// 	// Manipulate registers ACCEL_CONFIG and ACCEL_CONFIG2
// 	if(!this->_read(MPU9250_REG_ACCEL_CONFIG_1, auxBuff, 2)) {
// 		// Returns error
// 		debugMessage(this->_lastError);
// 		return false;
// 	}
// 	clrMask(auxBuff[0], 0x03, MPU9250_BIT_ACCEL_CONFIG_FS_SEL0);
// 	clrBit(auxBuff[1], MPU9250_BIT_ACCEL_CONFIG2_FCHOICE_B_0);
// 	clrMask(auxBuff[1], 0x07, MPU9250_BIT_ACCEL_CONFIG2_DLPF_CFG_0);
// 	auxBuff[0] |= auxFullScale;
// 	auxBuff[1] |= auxFChoiceB | auxDlpfCfg;
// 	if(!this->_write(MPU9250_REG_ACCEL_CONFIG_1, auxBuff, 2)) {
// 		// Returns error
// 		debugMessage(this->_lastError);
// 		return false;
// 	}

// 	// Manipulate registers PWR_MGMT_2
// 	if(!this->_read(MPU9250_REG_PWR_MGMT_2, auxBuff, 1)) {
// 		// Returns error
// 		debugMessage(this->_lastError);
// 		return false;
// 	}
// 	clrBit(auxBuff[0], MPU9250_BIT_PWR_MGMT_2_DIS_XA);
// 	clrBit(auxBuff[0], MPU9250_BIT_PWR_MGMT_2_DIS_YA);
// 	clrBit(auxBuff[0], MPU9250_BIT_PWR_MGMT_2_DIS_ZA);
// 	auxBuff[0] |= (
// 					(this->_accelDisableX << MPU9250_BIT_PWR_MGMT_2_DIS_XA) |
// 					(this->_accelDisableY << MPU9250_BIT_PWR_MGMT_2_DIS_YA) |
// 					(this->_accelDisableX << MPU9250_BIT_PWR_MGMT_2_DIS_ZA));
// 	if(!this->_write(MPU9250_REG_PWR_MGMT_2, auxBuff, 1)) {
// 		// Returns error
// 		debugMessage(this->_lastError);
// 		return false;
// 	}

// 	// Returns successfully
// 	this->_lastError = Error::NONE;
// 	debugMessage(Error::NONE);
// 	return true;
// }

// =============================================================================
// Class own methods - Private
// =============================================================================

bool_t Mpu9250::_initialize(void)
{
    // Local variables
    uint8_t auxBuff = 0;

    // Get device ID
    if(!this->_read(Register::WHO_AM_I, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }
    // Check device ID
    if(auxBuff != constDeviceId) {
        // Returns error
        this->_lastError = Error::DEVICE_ID_MATCH_FAILED;
        debugMessage(Error::DEVICE_ID_MATCH_FAILED, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Restart device
    if(!this->restart()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MPU9250_MODULE);
        return false;
    }

    // Update data members
    this->_isInitialized = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MPU9250_MODULE);
    return true;
}

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// End of file (mpu9250.cpp)
// =============================================================================
