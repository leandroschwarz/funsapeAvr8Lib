//!
//! \file           funsapeAvrAdc.hpp
//! \brief          Analog-to-Digital Converter peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_ADC_HPP
#define __FUNSAPE_AVR_ADC_HPP                           220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_ADC_HPP
#       error "Version mismatch between file header and global definitions file!"
#   endif
#else
#   error "Global definitions file is missing!"
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
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

void adcConversionCompleteCallback(void);

// =============================================================================
// Adc Class
// =============================================================================

class Adc
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     //////////////////     ADC Clock Source    ///////////////////     //
    //!
    //! \enum           ClockSource
    //!     \details    Clock prescaler options associated with ADC.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Prescaler : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, Adc is off
        PRESCALER_2                     = 1,    //!< Adc clock frequency will be CPU clock divided by 2
        PRESCALER_4                     = 2,    //!< Adc clock frequency will be CPU clock divided by 4
        PRESCALER_8                     = 3,    //!< Adc clock frequency will be CPU clock divided by 8
        PRESCALER_16                    = 4,    //!< Adc clock frequency will be CPU clock divided by 16
        PRESCALER_32                    = 5,    //!< Adc clock frequency will be CPU clock divided by 32
        PRESCALER_64                    = 6,    //!< Adc clock frequency will be CPU clock divided by 64
        PRESCALER_128                   = 7     //!< Adc clock frequency will be CPU clock divided by 128
    };
    //     //////////////     ADC Full Scale Reference    ///////////////     //
    //!
    //! \enum           Reference
    //!     \details    Full scale reference source.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Reference : uint8_t {
        EXTERNAL                        = 0,    //!< Adc full scale reference is the voltage at the AVREF pin.
        POWER_SUPPLY                    = 1,    //!< Adc full scale reference is teh voltage of the analog power supply.
        // RESERVED                     = 2,
        INTERNAL                        = 3     //!< Adc full scale reference is the internal 1.1 V bandgap generator.
    };
    //     ///////////////     ADC Channel Selection     ////////////////     //
    //!
    //! \enum           Channel
    //!     \details    Channel source selection.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Channel : uint8_t {
        CHANNEL_0                       = 0,    //!< Select the ADC channel 0.
        CHANNEL_1                       = 1,    //!< Select the ADC channel 1.
        CHANNEL_2                       = 2,    //!< Select the ADC channel 2.
        CHANNEL_3                       = 3,    //!< Select the ADC channel 3.
        CHANNEL_4                       = 4,    //!< Select the ADC channel 4.
        CHANNEL_5                       = 5,    //!< Select the ADC channel 5.
        CHANNEL_6                       = 6,    //!< Select the ADC channel 6 (not available on the DIP package).
        CHANNEL_7                       = 7,    //!< Select the ADC channel 7 (not available on the DIP package).
        TEMPERATURE                     = 8,    //!< Select the internal temperature sensor.
        // RESERVED                     = 9,
        // RESERVED                     = 10,
        // RESERVED                     = 11,
        // RESERVED                     = 12,
        // RESERVED                     = 13,
        BAND_GAP                        = 14,   //!< Select the internal bandgap generator.
        GND                             = 15    //!< Select the GND.
    };
    //     /////////////////     ADC Operation Mode    //////////////////     //
    //!
    //! \enum           Mode
    //!     \details    Operation mode associated with the ADC.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Mode {
        AUTO_CONTINUOUS                 = 0,    //!< ADC in automatic mode, triggered automatically at the end of the conversion.
        AUTO_ANALOG_COMP                = 1,    //!< ADC in automatic mode, triggered by Analog Comparator.
        AUTO_INT0                       = 2,    //!< ADC in automatic mode, triggered by External Interrupt INT0.
        AUTO_TIMER0_COMPA               = 3,    //!< ADC in automatic mode, triggered by Timer0 Compare A Match.
        AUTO_TIMER0_OVERFLOW            = 4,    //!< ADC in automatic mode, triggered by Timer0 Counter Overflow.
        AUTO_TIMER1_COMPB               = 5,    //!< ADC in automatic mode, triggered by Timer1 Compare B Match.
        AUTO_TIMER1_OVERFLOW            = 6,    //!< ADC in automatic mode, triggered by Timer1 Counter Overflow.
        AUTO_TIMER1_CAPTURE             = 7,    //!< ADC in automatic mode, triggered by Timer1 Input Capture Match.
        SINGLE_CONVERSION               = 15    //!< ADC in sigle mode, triggered by software.
    };
    //     //////////////     ADC Result Presentation     ///////////////     //
    //!
    //! \enum           DataAdjust
    //!     \details    Presentation mode of the ADC result.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class DataAdjust : cbool_t {
        RIGHT                           = 0,    //!< Adjust right. Significant bits are ADC[9...0]
        LEFT                            = 1     //!< Adjust left. Significant bits are ADC[15...6]
    };
    //     ///////////////////     Digital Input     ////////////////////     //
    //!
    //! \enum           DigitalInput
    //!     \details    Digital inputs to be enabled/disabled. The values can be ORed (|) to mark multiple inputs.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class DigitalInput : uint8_t {
        INPUT_0                         = (1 << 0),     //!< Digital input 0
        INPUT_1                         = (1 << 1),     //!< Digital input 1
        INPUT_2                         = (1 << 2),     //!< Digital input 2
        INPUT_3                         = (1 << 3),     //!< Digital input 3
        INPUT_4                         = (1 << 4),     //!< Digital input 4
        INPUT_5                         = (1 << 5),     //!< Digital input 5
        INPUT_6                         = (1 << 6),     //!< Digital input 6
        INPUT_7                         = (1 << 7)      //!< Digital input 7
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Adc(
            void
    );
    ~Adc(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //
    bool_t init(
            Mode mode_p,
            Reference reference_p,
            Prescaler prescale_p
    );
    bool_t setDataAdjust(
            DataAdjust dataAdjust_p
    );
    bool_t setMode(
            Mode mode_p
    );
    bool_t setPrescaler(
            Prescaler prescale_p
    );
    bool_t setReference(
            Reference reference_p
    );

    //     //////////////////     CHANNEL CONTROL     ///////////////////     //
    bool_t disableDigitalInput(
            DigitalInput flagInputs_p
    );
    bool_t enableDigitalInput(
            DigitalInput flagInputs_p
    );
    bool_t setChannel(
            Channel channel_p
    );

    //     /////////////////     INTERRUPT CONTROL     //////////////////     //
    bool_t activateInterrupt(
            void
    );
    bool_t clearInterruptRequest(
            void
    );
    bool_t deactivateInterrupt(
            void
    );

    //     /////////////     MASTER CONTROL AND STATUS     //////////////     //
    bool_t enable(
            void
    );
    bool_t disable(
            void
    );
    Error getLastError(
            void
    );
    bool_t isBusy(
            void
    );
    bool_t startConversion(
            void
    );
    bool_t waitUntilConversionFinish(
            void
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isEnabled          : 1;
    bool_t          _isInitialized      : 1;
    bool_t          _isInterruptEnabled : 1;
    Error           _lastError;
    Prescaler       _prescaler          : 3;
    Reference       _reference          : 2;
    Channel         _channel            : 4;
    Mode            _mode               : 4;
    DataAdjust      _dataAdjust         : 1;
}; // class Adc

// =============================================================================
// Inlined class functions
// =============================================================================

inlined Adc::DigitalInput operator|(Adc::DigitalInput a, Adc::DigitalInput b)
{
    return static_cast<Adc::DigitalInput>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

inlined Adc::DigitalInput &operator|=(Adc::DigitalInput &a, Adc::DigitalInput b)
{
    return a = static_cast<Adc::DigitalInput>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

// =============================================================================
// External global variables
// =============================================================================

extern Adc adc;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_ADC_HPP

// =============================================================================
// END OF FILE
// =============================================================================
