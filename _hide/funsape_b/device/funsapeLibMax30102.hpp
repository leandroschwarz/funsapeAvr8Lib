/* =============================================================================
 * Project:         FunSAPE++ Embedded Library
 * File name:       funsapeLibMax30102.hpp
 * Module:          MAX30102 module interface for FunSAPE++ Embedded Library
 *                      project
 * Authors:         __AUTHORS_TO_REPLACE__
 * Build:           __BUILD_TO_REPLACE__
 * Last edition:    __DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_MAX30102_HPP
#define __FUNSAPE_LIB_MAX30102_HPP              2407

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "funsape/funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#   error   [funsapeLibMax30102.hpp] Error 9 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != 2407
#   error   [funsapeLibMax30102.hpp] Error 10 - Build mismatch between (funsapeLibMax30102.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "funsape/util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#   error   [funsapeLibMax30102.hpp] Error 11 - Required module (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_DEBUG_HPP != 2407
#   error   [funsapeLibMax30102.hpp] Error 12 - Required module (funsapeLibDebug.hpp) must be build 2407.
#endif

#include "funsape/util/funsapeLibBus.hpp"
#ifndef __FUNSAPE_LIB_BUS_HPP
#   error   [funsapeLibMax30102.hpp] Error 11 - Required module (funsapeLibBus.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_BUS_HPP != 2407
#   error   [funsapeLibMax30102.hpp] Error 12 - Required module (funsapeLibBus.hpp) must be build 2407.
#endif

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// Macro-function definitions
// *INDENT-OFF*
// =============================================================================

// NONE

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Max30102 - Class declaration
// =============================================================================

class Max30102
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //     //////////////////     SAMPLE AVERAGING     //////////////////     //
    enum class SampleAveraging {
        SAMPLE_AVERAGING_OFF            = 0,
        SAMPLE_AVERAGING_2              = 1,
        SAMPLE_AVERAGING_4              = 2,
        SAMPLE_AVERAGING_8              = 3,
        SAMPLE_AVERAGING_16             = 4,
        SAMPLE_AVERAGING_32             = 5,
    };

    //     /////////////////////     FULL SCALE     /////////////////////     //
    enum class FullScale {
        FULL_SCALE_2048_NA              = 0,
        FULL_SCALE_4096_NA              = 1,
        FULL_SCALE_8192_NA              = 2,
        FULL_SCALE_16384_NA             = 3
    };

    //     ///////////////////    INTERRUPT FLAGS     ///////////////////     //
    typedef enum InterruptFlags {
        NONE                                    = (0),
        FIFO_ALMOST_FULL_FLAG                   = (1 << 7),
        NEW_FIFO_DATA_READY_FLAG                = (1 << 6),
        AMBIENT_LIGHT_CANCELLATION_FLAG         = (1 << 5),
        INTERNAL_TEMPERATURE_READY_FLAG         = (1 << 1),
        POWER_READY_FLAG                        = (1 << 0),
        ALL_FLAGS                               = (FIFO_ALMOST_FULL_FLAG | NEW_FIFO_DATA_READY_FLAG | AMBIENT_LIGHT_CANCELLATION_FLAG | INTERNAL_TEMPERATURE_READY_FLAG | POWER_READY_FLAG)
    } InterruptFlags;

    //     /////////////////////    LED CURRENT     /////////////////////     //
    enum class LedCurrent {
        LED_OFF                         = 0,
        LED_CURRENT_200_UA              = 1,
        LED_CURRENT_400_UA              = 2,
        LED_CURRENT_800_UA              = 4,
        LED_CURRENT_1_MA                = 5,
        LED_CURRENT_2_MA                = 10,
        LED_CURRENT_3_MA                = 15,
        LED_CURRENT_4_MA                = 20,
        LED_CURRENT_5_MA                = 26,
        LED_CURRENT_6_MA                = 31,
        LED_CURRENT_7_MA                = 36,
        LED_CURRENT_8_MA                = 41,
        LED_CURRENT_9_MA                = 46,
        LED_CURRENT_10_MA               = 51,
        LED_CURRENT_11_MA               = 56,
        LED_CURRENT_12_MA               = 61,
        LED_CURRENT_13_MA               = 66,
        LED_CURRENT_14_MA               = 71,
        LED_CURRENT_15_MA               = 77,
        LED_CURRENT_16_MA               = 82,
        LED_CURRENT_17_MA               = 87,
        LED_CURRENT_18_MA               = 92,
        LED_CURRENT_19_MA               = 96,
        LED_CURRENT_20_MA               = 102,
        LED_CURRENT_21_MA               = 107,
        LED_CURRENT_22_MA               = 112,
        LED_CURRENT_23_MA               = 117,
        LED_CURRENT_24_MA               = 122,
        LED_CURRENT_25_MA               = 128,
        LED_CURRENT_26_MA               = 133,
        LED_CURRENT_27_MA               = 138,
        LED_CURRENT_28_MA               = 143,
        LED_CURRENT_29_MA               = 148,
        LED_CURRENT_30_MA               = 153,
        LED_CURRENT_31_MA               = 158,
        LED_CURRENT_32_MA               = 163,
        LED_CURRENT_33_MA               = 168,
        LED_CURRENT_34_MA               = 173,
        LED_CURRENT_35_MA               = 179,
        LED_CURRENT_36_MA               = 184,
        LED_CURRENT_37_MA               = 189,
        LED_CURRENT_38_MA               = 194,
        LED_CURRENT_39_MA               = 199,
        LED_CURRENT_40_MA               = 204,
        LED_CURRENT_41_MA               = 209,
        LED_CURRENT_42_MA               = 214,
        LED_CURRENT_43_MA               = 219,
        LED_CURRENT_44_MA               = 224,
        LED_CURRENT_45_MA               = 230,
        LED_CURRENT_46_MA               = 235,
        LED_CURRENT_47_MA               = 240,
        LED_CURRENT_48_MA               = 245,
        LED_CURRENT_49_MA               = 250,
        LED_CURRENT_50_MA               = 255
    };

    //     ////////////////////     MODE CONTROL     ////////////////////     //
    enum class ModeControl {
        NO_MODE_SELECTED                = 0,
        HEART_RATE_MODE                 = 2,
        SPO2_MODE                       = 3,
        MULTI_LED_MODE                  = 7
    };

    //     /////////////////////     RESOLUTION     /////////////////////     //
    enum class Resolution {
        RESOLUTION_15_BITS              = 0,
        RESOLUTION_16_BITS              = 1,
        RESOLUTION_17_BITS              = 2,
        RESOLUTION_18_BITS              = 3
    };

    //     /////////////////////    SAMPLE RATE     /////////////////////     //
    enum class SampleRate {
        SAMPLE_RATE_50_HZ               = 0,
        SAMPLE_RATE_100_HZ              = 1,
        SAMPLE_RATE_200_HZ              = 2,
        SAMPLE_RATE_400_HZ              = 3,
        SAMPLE_RATE_800_HZ              = 4,
        SAMPLE_RATE_1000_HZ             = 5,
        SAMPLE_RATE_1600_HZ             = 6,
        SAMPLE_RATE_3200_HZ             = 7
    };

    //     ////////////////    MULTILED SLOT CONTROL     ////////////////     //
    enum class SlotControl {
        SLOT_OFF                        = 0,
        SLOT_RED                        = 1,
        SLOT_INFRARED                   = 2
    };

private:
    //     //////////////////     REGISTER ADDRESS     //////////////////     //
    enum class Register {
        // Status registers
        INTERRUPT_STATUS_1              = 0x00,
        INTERRUPT_STATUS_2              = 0x01,
        INTERRUPT_ENABLE_1              = 0x02,
        INTERRUPT_ENABLE_2              = 0x03,

        // FIFO registers
        FIFO_WRITE_POINTER              = 0x04,
        FIFO_OVERFLOW_COUNTER           = 0x05,
        FIFO_READ_POINTER               = 0x06,
        FIFO_DATA                       = 0x07,

        // Configuration registers
        FIFO_CONFIGURATION              = 0x08,
        MODE_CONFIGURATION              = 0x09,
        SPO2_CONFIGURATION              = 0x0A,
        LED1_PULSE_AMPLITUDE            = 0x0C,
        LED2_PULSE_AMPLITUDE            = 0x0D,
        // LED3_PULSE_AMPLITUDE         = 0x0E,
        // PROXIMITY_LED_AMPLITUDE      = 0x10,
        MULTI_LED_CONTROL_1             = 0x11,
        MULTI_LED_CONTROL_2             = 0x12,

        // Die temperature registers
        DIE_TEMPERATURE_INTEGER         = 0x1F,
        DIE_TEMPERATURE_FRACTION        = 0x20,
        DIE_TEMPERATURE_CONFIG          = 0x21,

        // Proximity function registers
        // PROXIMITY_INTERRUPT_THRESHOLD    = 0x30,

        // Part ID registers
        REVISION_ID                     = 0xFE,
        PART_ID                         = 0xFF
    };

    //     ////////////////////     BIT POSITION     ////////////////////     //
    enum class Bit {
        A_FULL_INT                      = 7,    // Interrupt Status 1
        PPG_RDY_INT                     = 6,
        ALC_OVF_INT                     = 5,
        PWR_RDY_INT                     = 0,
        DIE_TEMP_RDY_INT                = 1,    // Interrupt Status 2
        A_FULL_EN                       = 7,    // Interrupt Enable 1
        PPG_RDY_EN                      = 6,
        ALC_OVF_EN                      = 5,
        DIE_TEMP_RDY_EN                 = 1,    // Interrupt Enable 2
        FIFO_WR_PTR                     = 0,    // FIFO Write Pointer
        FIFO_OVF_COUNTER                = 0,    // FIFO Overflow Counter
        FIFO_RD_PTR                     = 0,    // FIFO Read Pointer
        FIFO_DATA                       = 0,    // FIFO Data Register
        FIFO_SMP_AVE                    = 5,    // FIFO Configuration
        FIFO_ROLLOVER_EN                = 4,
        FIFO_A_FULL                     = 0,
        SHDN                            = 7,    // Mode Configuration
        RESET                           = 6,
        MODE                            = 0,
        SPO2_ADC_RGE                    = 5,    // SPO2 Configuration
        SPO2_SR                         = 2,
        LED_PW                          = 0,
        LED1_PA                         = 0,    // LED Pulse Amplitude 1
        LED2_PA                         = 0,    // LED Pulse Amplitude 2
        // PILOT_PA                     = 0,    // Proximity Mode LED Pulse Amplitude
        SLOT2                           = 4,    // Multi-LED Mode Control Register 1
        SLOT1                           = 0,
        SLOT4                           = 4,    // Multi-LED Mode Control Register 2
        SLOT3                           = 0,
        // Temperature Data
        TINT                            = 0,    // Die Temperature Integer
        TFRAC                           = 0,    // Die Temperature Fraction
        TEMP_EN                         = 0,    // Die Temperature Config
        // Proximity Function
        // PROX_INT_THRESH                  = 0,    // Proximity Interrupt Threshold
    };

protected:
    //     /////////////////////     RESOLUTION     /////////////////////     //

    // -------------------------------------------------------------------------
    // Operators overloading ---------------------------------------------------

public:
    // NONE

private:
    inlined friend uint8_t operator<<(uint8_t a, Max30102::Bit b);
    inlined friend uint8_t operator>>(uint8_t a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::FullScale a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::FullScale a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::LedCurrent a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::LedCurrent a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::ModeControl a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::ModeControl a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::Resolution a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::Resolution a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::SampleAveraging a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::SampleAveraging a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::SampleRate a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::SampleRate a, Max30102::Bit b);

    inlined friend uint8_t operator<<(Max30102::SlotControl a, Max30102::Bit b);
    inlined friend uint8_t operator>>(Max30102::SlotControl a, Max30102::Bit b);

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    Max30102(
            void
    );
    ~Max30102(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Error getLastError(
            void
    );
    bool init(
            Bus *busHandler_p
    );
    bool reset(
            void
    );
    bool shutDown(
            void
    );
    bool wakeUp(
            void
    );

    //     ////////////////     DEVICE CONFIGURATION     ////////////////     //
    bool setFullScale(
            FullScale fullScale_p
    );
    bool setHeartRateMode(
            LedCurrent redLedCurrent_p = LedCurrent::LED_CURRENT_1_MA
    );
    bool setInfraredLedCurrent(
            LedCurrent infraredLedCurrent_p = LedCurrent::LED_CURRENT_1_MA
    );
    bool setMultiLedMode(               // FIXIT: Implement MultiLed mode
            SlotControl slot1_p,
            SlotControl slot2_p = SlotControl::SLOT_OFF,
            SlotControl slot3_p = SlotControl::SLOT_OFF,
            SlotControl slot4_p = SlotControl::SLOT_OFF
    );
    bool setRedLedCurrent(
            LedCurrent redLedCurrent_p = LedCurrent::LED_CURRENT_1_MA
    );
    bool setResolution(
            Resolution resolution_p
    );
    bool setSampleRate(
            SampleRate sampleRate_p
    );
    bool setSpo2Mode(
            LedCurrent redLedCurrent_p = LedCurrent::LED_CURRENT_1_MA,
            LedCurrent infraredLedCurrent_p  = LedCurrent::LED_CURRENT_1_MA
    );

    //     ///////////////    FIFO CONTROL AND STATUS     ///////////////     //
    bool configFifo(
            SampleAveraging sampleAveraging_p,
            bool rolloverOnFull_p,
            uint8_t fifoAlmostFullValue_p
    );
    bool flushFifo(
            void
    );
    bool getFifoOccupation(
            uint8_t *samplesWaiting_p,
            uint8_t *samplesLost_p = nullptr
    );

    //     ///////////////////    DATA MANAGEMENT     ///////////////////     //
    bool getFifoData(
            uint8_t samplesCount_p,
            uint16_t *redLedBuffer_p,
            uint16_t *infraredLedBuffer_p = nullptr
    );
    bool getFifoData(
            uint8_t samplesCount_p,
            uint32_t *redLedBuffer_p,
            uint32_t *infraredLedBuffer_p = nullptr
    );
    bool getFifoNewestSample(
            uint16_t *redValue_p,
            uint16_t *infraredValue_p = nullptr
    );
    bool getFifoNewestSample(
            uint32_t *redValue_p,
            uint32_t *infraredValue_p = nullptr
    );
    bool getFifoOldestSample(
            uint16_t *redValue_p,
            uint16_t *infraredValue_p = nullptr
    );
    bool getFifoOldestSample(
            uint32_t *redValue_p,
            uint32_t *infraredValue_p = nullptr
    );
    bool getTemperature(
            float *tempValue_p,
            ThermometricScale tempScale_p = ThermometricScale::CELSIUS
    );
    bool getTemperature(
            int8_t *tempInteger_p,
            uint8_t *tempFrac_p
    );
    bool startTemperatureRead(
            void
    );
    // TODO: Implement a function to return the temperature in fixed point notation

    //     ////////////     INTERRUPT CONTROL AND STATUS     ////////////     //
    bool disableInterrupts(
            InterruptFlags deactivationMask_p
    );
    bool enableInterrupts(
            InterruptFlags activationMask_p
    );
    bool generalIrqHandler(
            void
    );
    bool getInterruptStatus(
            InterruptFlags *interruptStatus_p = nullptr
    );

    //     /////////////////    INTERRUPT CALLBACKS     /////////////////     //
    bool setAmbLightCancOverflowInterruptCallback(
            void (* callbackFunction_p)(void)
    );
    bool setDieTempReadyInterruptCallback(
            void (* callbackFunction_p)(void)
    );
    bool setFifoAlmostFullInterruptCallback(
            void (* callbackFunction_p)(void)
    );
    bool setNewFifoDataReadyInterruptCallback(
            void (* callbackFunction_p)(void)
    );
    bool setPowerReadyInterruptCallback(
            void (* callbackFunction_p)(void)
    );

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    void _clearData(
            void
    );
    bool _isInitialized(
            void
    );

    //     ////////////////    REGISTER MANIPULATION     ////////////////     //
    bool _read(
            Register regAddr_p,
            uint8_t *dataBuffer_p,
            uint16_t bytesToRead_p
    );
    bool _write(
            Register regAddr_p,
            uint8_t *dataBuffer_p,
            uint16_t bytesToWrite_p
    );

    //     ///////////////    FIFO CONTROL AND STATUS     ///////////////     //
    bool _getFifoInfo(
            void
    );
    bool _getFifoReadPointer(
            uint8_t *pointer_p
    );
    bool _getFifoWritePointer(
            uint8_t *pointer_p
    );
    bool _readFifoData(
            uint8_t samples_p,
            void *redLedBuffer_p,
            void *infraredLedBuffer_p,
            uint8_t varSize_p
    );
    bool _setFifoReadPointer(
            uint8_t pointer_p
    );
    bool _setFifoWritePointer(
            uint8_t pointer_p
    );

    //     /////////////     TEMPORARY - USED FOR DEBUG     /////////////     //
    void readAllRegs(
            uint8_t *regs_p
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
    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    Bus         *_busHandler;

    //     ////////////     INTERRUPT CONTROL AND STATUS     ////////////     //
    bool            _ambLightCancOverflowInterruptEnable        : 1;
    bool            _ambLightCancOverflowInterruptFlag          : 1;
    bool            _dieTempReadyInterruptEnable                : 1;
    bool            _dieTempReadyInterruptFlag                  : 1;
    bool            _fifoAlmostFullInterruptEnable              : 1;
    bool            _fifoAlmostFullInterruptFlag                : 1;
    bool            _newFifoDataReadyInterruptEnable            : 1;
    bool            _newFifoDataReadyInterruptFlag              : 1;
    bool            _powerReadyInterruptFlag                    : 1;

    //     ////////////////////    DEVICE STATUS     ////////////////////     //
    bool            _initialized                                : 1;
    Error           _lastError;
    uint8_t         _partId;
    uint8_t         _partRevision;
    bool            _shuttedDown                                : 1;

    //     ////////////////     DEVICE CONFIGURATION     ////////////////     //
    uint8_t         _activeLedsCounter                          : 3;
    FullScale       _fullScale;
    LedCurrent      _infraredLedCurrent;
    ModeControl     _modeControl;
    LedCurrent      _redLedCurrent;
    Resolution      _resolution;
    SampleRate      _sampleRate;

    //     ///////////////    FIFO CONTROL AND STATUS     ///////////////     //
    uint8_t         _fifoAlmostFullValue                        : 4;
    uint8_t         _fifoData;
    uint8_t         _fifoOverflowCounter                        ; //: 5;
    uint8_t         _fifoOverflowCounterOld                     ; //: 5;
    uint8_t         _fifoOverflowCounterNew                     ; //: 5;
    uint8_t         _fifoReadPointer                            ; //: 5;
    uint8_t         _fifoReadPointerOld                         ; //: 5;
    uint8_t         _fifoReadPointerNew                         ; //: 5;
    bool            _fifoRolloverOnFull                         : 1;
    uint8_t         _fifoWritePointer                           ; //: 5;
    uint8_t         _fifoWritePointerOld                        ; //: 5;
    uint8_t         _fifoWritePointerNew                        ; //: 5;
    SampleAveraging _sampleAveraging;

    //     //////////////////     TEMPERATURE DATA     //////////////////     //
    bool            _dieTempEnable                              : 1;
    uint8_t         _dieTempFraction                            : 4;
    uint8_t         _dieTempInteger;
    bool            _dieTempReady                               : 1;

    //     ////////////////    MULTILED SLOT CONTROL     ////////////////     //
    SlotControl     _multiLedSlot1Control;
    SlotControl     _multiLedSlot2Control;
    SlotControl     _multiLedSlot3Control;
    SlotControl     _multiLedSlot4Control;
    uint8_t         _slotsEnabledCounter                        : 3;

    //     /////////////////    INTERRUPT CALLBACKS     /////////////////     //
    void (*_ambLightCancOverflowInterruptCallback)(void);
    void (*_dieTempReadyInterruptCallback)(void);
    void (*_fifoAlmostFullInterruptCallback)(void);
    void (*_newFifoDataReadyInterruptCallback)(void);
    void (*_powerReadyInterruptCallback)(void);

protected:
    // NONE

}; // class Max30102

// =============================================================================
// Max30102 - Class overloading operators
// =============================================================================


// -------------------------------------------------------------------------
// Bit position operator overloading
// -------------------------------------------------------------------------

inlined uint8_t operator<<(uint8_t a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(uint8_t a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::FullScale a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::FullScale a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::LedCurrent a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::LedCurrent a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::ModeControl a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::ModeControl a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::Resolution a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::Resolution a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::SampleAveraging a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::SampleAveraging a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::SampleRate a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::SampleRate a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined uint8_t operator<<(Max30102::SlotControl a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) << static_cast<uint8_t>(b));
}

inlined uint8_t operator>>(Max30102::SlotControl a, Max30102::Bit b)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(a) >> static_cast<uint8_t>(b));
}

inlined Max30102::InterruptFlags operator|(Max30102::InterruptFlags a, Max30102::InterruptFlags b)
{
    return static_cast<Max30102::InterruptFlags>(static_cast<int>(a) | static_cast<int>(b));
}

inlined Max30102::InterruptFlags &operator|=(Max30102::InterruptFlags &a, Max30102::InterruptFlags b)
{
    return a = static_cast<Max30102::InterruptFlags>(static_cast<int>(a) | static_cast<int>(b));
}



// -------------------------------------------------------------------------
// Interrupt flags operator overloading
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
// Fifo averaging operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::SampleAveraging a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// -------------------------------------------------------------------------
// Slot control operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::SlotControl a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// -------------------------------------------------------------------------
// Full scale operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::FullScale a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// -------------------------------------------------------------------------
// Mode control operator overloading
// -------------------------------------------------------------------------


// -------------------------------------------------------------------------
// Resolution operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::Resolution a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// -------------------------------------------------------------------------
// Sample rate operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::SampleRate a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// -------------------------------------------------------------------------
// Led current operator overloading
// -------------------------------------------------------------------------

// inlined uint8_t operator<<(Max30102::LedCurrent a, uint8_t b)
// {
//  return static_cast<uint8_t>(static_cast<uint8_t>(a) << b);
// }

// =============================================================================
// Global variables
// =============================================================================

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// =============================================================================
// Max30102 - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

#endif // __FUNSAPE_LIB_MAX30102_HPP

// =============================================================================
// END OF FILE
// =============================================================================
