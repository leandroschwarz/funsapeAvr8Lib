/**
 *******************************************************************************
 * @file            adc.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Analog-to-Digital Converter peripheral control.
 * @details         This file provides peripheral control for the ADC
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

#ifndef __ADC_HPP
#define __ADC_HPP                       2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [adc.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __ADC_HPP
#   error [adc.hpp] Error 2 - Build mismatch between file (adc.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [adc.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __ADC_HPP
#   error [adc.hpp] Error 5 - Build mismatch between file (adc.hpp) and library dependency (debug.hpp)!
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
// Doxygen: Start subgroup "Peripherals/Adc"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Adc
 * @brief           Analog to Digital Converter (ADC) controller module.
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

/**
 * @brief           ADC conversion complete interrupt callback function.
 * @details         This function is called when the ADC interrupt is treated.
 *                      It is a weak function that can be overwritten by user
 *                      code.
*/
void adcConversionCompleteCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Adc class.
 * @details         This class manages the Analog to Digital Converter (ADC)
 *                      peripheral.
 * @attention       The @ref adc instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Adc
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        Prescaler
     * @brief       Clock prescaler enumeration.
     * @details     Clock prescaler options associated with ADC.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Prescaler : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, Adc is off.
        PRESCALER_2                     = 1,    //!< Adc clock frequency will be CPU clock divided by 2.
        PRESCALER_4                     = 2,    //!< Adc clock frequency will be CPU clock divided by 4.
        PRESCALER_8                     = 3,    //!< Adc clock frequency will be CPU clock divided by 8.
        PRESCALER_16                    = 4,    //!< Adc clock frequency will be CPU clock divided by 16.
        PRESCALER_32                    = 5,    //!< Adc clock frequency will be CPU clock divided by 32.
        PRESCALER_64                    = 6,    //!< Adc clock frequency will be CPU clock divided by 64.
        PRESCALER_128                   = 7,    //!< Adc clock frequency will be CPU clock divided by 128.
    };

    /**
     * @enum        Reference
     * @brief       Reference enumeration.
     * @details     Full scale reference source associated with ADC.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Reference : uint8_t {
        EXTERNAL                        = 0,    //!< Adc full scale reference is the voltage at the AVREF pin.
        POWER_SUPPLY                    = 1,    //!< Adc full scale reference is the voltage of the analog power supply.
        INTERNAL                        = 2,    //!< Adc full scale reference is the internal 1.1 V bandgap generator.
    };

    /**
     * @enum        Channel
     * @brief       Channel enumeration.
     * @details     Channel source selection.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
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
        BAND_GAP                        = 9,    //!< Select the internal bandgap generator.
        GND                             = 10,   //!< Select the GND.
    };

    /**
     * @enum        Mode
     * @brief       Operation mode enumeration.
     * @details     Operation mode associated with the ADC.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Mode {
        AUTO_CONTINUOUS                 = 0,    //!< ADC in automatic mode, triggered automatically at the end of the conversion.
        AUTO_ANALOG_COMP                = 1,    //!< ADC in automatic mode, triggered by Analog Comparator.
        AUTO_INT0                       = 2,    //!< ADC in automatic mode, triggered by External Interrupt INT0.
        AUTO_TIMER0_COMPA               = 3,    //!< ADC in automatic mode, triggered by Timer0 Compare A Match.
        AUTO_TIMER0_OVERFLOW            = 4,    //!< ADC in automatic mode, triggered by Timer0 Counter Overflow.
        AUTO_TIMER1_COMPB               = 5,    //!< ADC in automatic mode, triggered by Timer1 Compare B Match.
        AUTO_TIMER1_OVERFLOW            = 6,    //!< ADC in automatic mode, triggered by Timer1 Counter Overflow.
        AUTO_TIMER1_CAPTURE             = 7,    //!< ADC in automatic mode, triggered by Timer1 Input Capture Match.
        SINGLE_CONVERSION               = 8,    //!< ADC in sigle mode, triggered by software.
    };

    /**
     * @enum        DataPresetation
     * @brief       Presentation mode of the ADC result.
     * @details     Presentation mode of the ADC result.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class DataPresetation : cbool_t {
        RIGHT                           = 0,    //!< Adjust right. Significant bits are ADC[9...0].
        LEFT                            = 1     //!< Adjust left. Significant bits are ADC[15...6].
    };

    /**
     * @enum        DigitalInput
     * @brief       Digital input enumeration.
     * @details     Digital inputs to be enabled/disabled. The values can be
     *                  'ORed' (|) to select multiple inputs.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class DigitalInput : uint8_t {
        INPUT_0                         = (1 << 0),     //!< Digital input 0.
        INPUT_1                         = (1 << 1),     //!< Digital input 1.
        INPUT_2                         = (1 << 2),     //!< Digital input 2.
        INPUT_3                         = (1 << 3),     //!< Digital input 3.
        INPUT_4                         = (1 << 4),     //!< Digital input 4.
        INPUT_5                         = (1 << 5),     //!< Digital input 5.
        INPUT_6                         = (1 << 6),     //!< Digital input 6.
        INPUT_7                         = (1 << 7),     //!< Digital input 7.
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Adc class constructor.
     * @details     Creates an Adc object. The object is loaded with the
     *                  default register values: @ref Channel::CHANNEL_0,
     *                  @ref DataPresetation::RIGHT,
     *                  @ref Mode::SINGLE_CONVERSION, @ref Prescaler::DISABLED
     *                  and @ref Reference::EXTERNAL. The object still must be
     *                  initialized before use.
     * @see         init(const Mode mode_p, const Reference reference_p, const Prescaler prescaler_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Adc(
            void
    );

    /**
     * @brief       Adc class destructor.
     * @details     Destroys an Adc object.
    */
    ~Adc(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Turns the ADC module off.
     * @details     Turns the ADC module off.
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
    bool_t disable(
            void
    );

    /**
     * @brief       Turns the ADC module on.
     * @details     Turns the ADC module on.
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
    bool_t enable(
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

    /**
     * @brief       Returns the conversion value.
     * @details     Returns the conversion value at @c ADC register.
     * @return      the value of the conversion value, i.e. the value of @c ADC
     *                  register.
    */
    uint16_t inlined getValue(
            void
    );

    /**
     * @brief       Initializes the ADC module.
     * @details     Initializes the ADC module, according to tyhe given
     *                  @a mode_p operation mode, @a reference_p reference
     *                  source and @a prescaler_p clock prescaler.
     * @param[in]   mode_p              Operation mode.
     * @param[in]   reference_p         Reference source.
     * @param[in]   prescaler_p         Clock prescaler value.
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
    bool_t init(
            const Mode mode_p,
            const Reference reference_p,
            const Prescaler prescaler_p
    );

    /**
     * @brief       Checks if ADC module is busy.
     * @details     Checks if ADC module is busy.
     * @retval      true                if the module is busy.
     * @retval      false               if the module is not busy.
    */
    bool_t inlined isBusy(
            void
    );

    /**
     * @brief       Sets data presentation result.
     * @details     Sets data presentation result, according to tyhe given
     *                  @a dataPresentation_p mode.
     * @param[in]   dataPresentation_p  Data presentation mode.
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
    bool_t setDataPresetation(
            const DataPresetation dataPresentation_p
    );

    /**
     * @brief       Sets the operation mode.
     * @details     Sets the operation mode, according to tyhe given @a mode_p
     *                  mode.
     * @param[in]   mode_p              Operation mode.
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
    bool_t setMode(
            const Mode mode_p
    );

    /**
     * @brief       Sets the clock prescaler.
     * @details     Sets the clock prescaler, according to tyhe given
     *                  @a prescaler_p clock prescaler.
     * @param[in]   prescaler_p         Clock prescaler.
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
    bool_t setPrescaler(
            const Prescaler prescaler_p
    );

    /**
     * @brief       Sets the reference source.
     * @details     Sets the reference source, according to tyhe given
     *                  @a reference_p reference source.
     * @param[in]   reference_p         Reference source.
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
    bool_t setReference(
            const Reference reference_p
    );

    /**
     * @brief       Triggers a new conversion.
     * @details     Triggers a new conversion.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                  | Meaning                          |
     * |:----------------------------|:---------------------------------|
     * | @ref Error::NONE            | Success. No erros were detected. |
     * | @ref Error::DEVICE_DISABLED | ADC module is disabled.          |
     * | @ref Error::NOT_INITIALIZED | ADC module is not initialized.   |
     *
    */
    bool_t startConversion(
            void
    );

    /**
     * @brief       Waits the end of current conversion.
     * @details     This function continually pools for the ADC conversion
     *                  status.
     * @attention   The system will be halted while the conversion is in
     *                  process.
     * @retval      true                if when the current conversion ends.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                  | Meaning                          |
     * |:----------------------------|:---------------------------------|
     * | @ref Error::NONE            | Success. No erros were detected. |
     * | @ref Error::DEVICE_DISABLED | ADC module is disabled.          |
     * | @ref Error::NOT_INITIALIZED | ADC module is not initialized.   |
     *
    */
    bool_t waitUntilConversionFinish(
            void
    );

    //     //////////////////     CHANNEL CONTROL     ///////////////////     //

    /**
     * @brief       Disables digital inputs.
     * @details     Disables digital inputs to save power.
     * @param[in]   flagInputs_p        Input flags mask to de disabled.
    */
    void inlined disableDigitalInput(
            const DigitalInput flagInputs_p
    );

    /**
     * @brief       Enables digital inputs.
     * @details     Enables digital inputs.
     * @param[in]   flagInputs_p        Input flags mask to de enabled.
    */
    void inlined enableDigitalInput(
            const DigitalInput flagInputs_p
    );

    /**
     * @brief       Selects the channel.
     * @details     Selects the channel to be converted.
     * @param[in]   channel_p           Channel to be converted.
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
    bool_t setChannel(
            Channel channel_p
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    /**
     * @brief       Activates interrupt.
     * @details     Activates interrupt. If an interrupt request is pending, an
     *                  interrupt will be triggered when activated. In most
     *                  applications, it is recommended to ignore an old
     *                  interrupt request prior to activate the interrupt. This
     *                  can be done by calling @ref clearInterruptRequest()
     *                  imediatelly before activating the interrupt.
    */
    void inlined activateInterrupt(
            void
    );

    /**
     * @brief       Clears interrupt flag.
     * @details     Clears interrupt flag, dismissing any pending interrupt
     *                  request.
    */
    void inlined clearInterruptRequest(
            void
    );

    /**
     * @brief       Deactivates interrupt.
     * @details     Deactivates interrupt. This function does not clears any
     *                  pending interrupt request.
    */
    void inlined deactivateInterrupt(
            void
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.
    bool_t          _isEnabled          : 1;    //!< Enabled flag.

    //     ////////////////////   CONFIGURATION     /////////////////////     //

    Prescaler       _prescaler;                 //!< Clock prescaler.
    Reference       _reference;                 //!< Reference source.
    Channel         _channel;                   //!< Channel selection.
    Mode            _mode;                      //!< Operation mode.
    DataPresetation _dataAdjust         : 1;    //!< Data presentation.

}; // class Adc

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Adc::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

uint16_t inlined Adc::getValue(void)
{
    return ADC;
}

bool_t inlined Adc::isBusy(void)
{
    return isBitSet(ADCSRA, ADSC);
}

//     ////////////////////     CHANNEL CONTROL     /////////////////////     //

void inlined Adc::disableDigitalInput(const DigitalInput flagInputs_p)
{
    // Local variables
    uint8_t auxMask = 0;

    // Decodes input pins
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_0)) {
        auxMask |= 1 << 0;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_1)) {
        auxMask |= 1 << 1;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_2)) {
        auxMask |= 1 << 2;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_3)) {
        auxMask |= 1 << 3;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_4)) {
        auxMask |= 1 << 4;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_5)) {
        auxMask |= 1 << 5;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_6)) {
        auxMask |= 1 << 6;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_7)) {
        auxMask |= 1 << 7;
    }

    // Disable pins
    setMask(DIDR0, auxMask);

    // Returns successfully
    return;
}

void inlined Adc::enableDigitalInput(const DigitalInput flagInputs_p)
{
    // Local variables
    uint8_t auxMask = 0;

    // Decodes input pins
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_0)) {
        auxMask |= 1 << 0;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_1)) {
        auxMask |= 1 << 1;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_2)) {
        auxMask |= 1 << 2;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_3)) {
        auxMask |= 1 << 3;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_4)) {
        auxMask |= 1 << 4;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_5)) {
        auxMask |= 1 << 5;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_6)) {
        auxMask |= 1 << 6;
    }
    if((uint8_t)(flagInputs_p) & (uint8_t)(DigitalInput::INPUT_7)) {
        auxMask |= 1 << 7;
    }

    // Enable pins
    clrMask(DIDR0, auxMask);

    // Returns successfully
    return;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Adc::activateInterrupt(void)
{
    setBit(ADCSRA, ADIE);
    return;
}

void inlined Adc::clearInterruptRequest(void)
{
    setBit(ADCSRA, ADIF);
    return;
}

void inlined Adc::deactivateInterrupt(void)
{
    clrBit(ADCSRA, ADIE);
    return;
}

//     //////////////////     OPERATOR OVERLOADING     //////////////////     //

Adc::DigitalInput inlined operator|(Adc::DigitalInput a, Adc::DigitalInput b)
{
    return static_cast<Adc::DigitalInput>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

Adc::DigitalInput inlined &operator|=(Adc::DigitalInput &a, Adc::DigitalInput b)
{
    return a = static_cast<Adc::DigitalInput>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             adc
 * @brief           Adc peripheral handler object.
 * @details         Adc peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern Adc adc;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Adc"
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

#endif  // __ADC_HPP

// =============================================================================
// End of file (adc.hpp)
// =============================================================================
