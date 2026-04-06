/* =============================================================================
 * Project:         FunSAPE++ Embedded Library
 * File name:       funsapeLibMax30102.cpp
 * Module:          MAX30102 module interface for FunSAPE++ Embedded Library
 *                      project
 * Authors:         __AUTHORS_TO_REPLACE__
 * Build:           __BUILD_TO_REPLACE__
 * Last edition:    __DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Dependencies
// =============================================================================

#include "funsapeLibMax30102.hpp"
#ifndef __FUNSAPE_LIB_MAX30102_HPP
#   error   [funsapeLibMax30102.cpp] Error 1 - Header file (funsapeLibMax30102.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_MAX30102_HPP != 2407
#   error   [funsapeLibMax30102.cpp] Error 14 - Build mismatch between source (funsapeLibMax30102.cpp) and header (funsapeLibMax30102.hpp) files!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define MAX30102_DEVICE_ADDRESS         0x57
#define MAX30102_FIFO_SIZE_IN_SAMPLES   32
#define MAX30102_PART_ID                0x15
#define MAX30102_BYTES_PER_CHANNEL      3
// #define MAX30102_SERIAL_CLOCK_FREQUENCY_MAX      400'000UL
// #define MAX30102_SERIAL_CLOCK_FREQUENCY_MIN      0UL
// #define MAX30102_TEMPERATURE_CONVERSION_TIMEOUT  10

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

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

static void defaultCallbackFunction(void);

// =============================================================================
// Class constructors
// =============================================================================

/**
 * @brief       Construct a new Max30102::Max30102 object.
 * @details     The constructor also clears the class internal data. Since there
 *                  is no dynamic memory allocation procedures, the function
 *                  always sets internal the error variable to Error::NONE.
 */
Max30102::Max30102(void)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::Max30102(void)", DEBUG_CODE_MAX3010X);

    // Resets data members
    this->_clearData();
    this->_ambLightCancOverflowInterruptCallback        = defaultCallbackFunction;
    this->_dieTempReadyInterruptCallback                = defaultCallbackFunction;
    this->_fifoAlmostFullInterruptCallback              = defaultCallbackFunction;
    this->_newFifoDataReadyInterruptCallback            = defaultCallbackFunction;
    this->_powerReadyInterruptCallback                  = defaultCallbackFunction;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return;
}

/**
 * @brief       Destroy the Max30102::Max30102 object.
 * @details     Since there is no dynamic memory allocation procedures, the
 *                  function has nothing to do and just returns normally.
 */
Max30102::~Max30102(void)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::~Max30102(void)", DEBUG_CODE_MAX3010X);

    // Returns successfully
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

/**
 * @brief       Returns the code of the last error.
 * @details     Returns the FunSAPE++ Embedded Library error code of the last
 *              operation. If the operation was successfull, the return code
 *              will be \ref{Error::NONE}.
 * @return      Error   \ref{Error} error code.
 */
Error Max30102::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

/**
 * @brief       Initializes the device.
 * @details     Initializes the handler and communicates with the device to
 *              check it's part ID.
 * @param[in]   handler_p   \ref{Twi} class handler associated with the device
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::init(Bus *busHandler_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Mark passage for debugging purpose
    debugMark("Max30102::init(Bus *)", DEBUG_CODE_MAX3010X);

    // Resets data members
    this->_clearData();
    this->_ambLightCancOverflowInterruptCallback        = defaultCallbackFunction;
    this->_dieTempReadyInterruptCallback                = defaultCallbackFunction;
    this->_fifoAlmostFullInterruptCallback              = defaultCallbackFunction;
    this->_newFifoDataReadyInterruptCallback            = defaultCallbackFunction;
    this->_powerReadyInterruptCallback                  = defaultCallbackFunction;

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    } else if(busHandler_p->getBusType() != Bus::BusType::TWI) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
        debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_busHandler = busHandler_p;
    this->_initialized = true;

    // Retrieve device's part and revision IDs
    if(!this->_read(Register::REVISION_ID, auxBuff, 2)) {
        // Returns error
        this->_initialized = false;
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check device ID
    if(auxBuff[1] != MAX30102_PART_ID) {
        // Returns error
        this->_initialized = false;
        this->_lastError = Error::COMMUNICATION_DEVICE_ID_MATCH_FAILED;
        debugMessage(Error::COMMUNICATION_DEVICE_ID_MATCH_FAILED, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reset device
    delayMs(100);
    if(!this->reset()) {
        // Returns error
        this->_initialized = false;
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    delayMs(100);

    // Update data members
    this->_initialized                  = true;
    this->_partId                       = auxBuff[1];
    this->_partRevision                 = auxBuff[0];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Resets the device.
 * @details     Sends a reset signal to device and clears internal class data members.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::reset(void)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::reset(void)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Sends reset signal to device
    auxBuff = (1 << Bit::RESET);
    if(!this->_write(Register::MODE_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Clears data members
    this->_clearData();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Makes the device to enter in power-save mode.
 * @details     Makes the device to enter in power-save mode. While power-save
 *              mode, the LEDs, the ADC sensor, and all interrupts are tuned
 *              off, but all device registers retain their values (allowing
 *              quick wake-up). Also, write/read operations function as normal.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::shutDown(void)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::shutDown(void)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (1 << Bit::SHDN) |
                    (this->_modeControl << Bit::MODE)
            );
    if(!this->_write(Register::MODE_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_shuttedDown = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Wakes up the device when in power-save mode.
 * @details     Wakes up the device when in power-save mode. Since all device
 *              registers retain their values during power-save mode, all
 *              previous device configuration are active and the device responds
 *              accordingly imediately (quick wake-up).
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::wakeUp(void)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::wakeUp(void)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (0 << Bit::SHDN) |
                    (this->_modeControl << Bit::MODE)
            );
    if(!this->_write(Register::MODE_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_shuttedDown = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     //////////////////     DEVICE CONFIGURATION     //////////////////     //

/**
 * @brief       Configures the full scale of the SpO2 ADC.
 * @details     Configures the full scale of the SpO2 ADC. The SpO2 ADC has
 *              programmable full-scale ranges from 2 µA to 16 µA.
 * @param[in]   fullScale_p     ADC's full scale value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setFullScale(FullScale fullScale_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::setFullScale(FullScale)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (fullScale_p << Bit::SPO2_ADC_RGE) |
                    (this->_sampleRate << Bit::SPO2_SR) |
                    (this->_resolution << Bit::LED_PW)
            );
    if(!this->_write(Register::SPO2_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fullScale = fullScale_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the device in Heart Rate mode.
 * @details     Configures the device in Heart Rate mode. In this mode, each
 *              sample consist of 3-byte output into the FIFO. By default, only
 *              the red LED is used to capture optical data and determine the
 *              user’s heart rate and/or photoplethysmogram (PPG). The function
 *              also configures the red LED amplitude of the device and turns
 *              the infrared LED channel off. The LED current can be programmed
 *              from 0 to 50 mA with proper supply voltage.
 * @note        Actual measured LED's current amplitude for each part can vary widely due to
 *              the trimming methodology.
 * @note        The user can select either the red LED or the infrared LED
 *              channel for heart rate measurements. If the infrared channel is
 *              desired, the user must turn the red LED OFF, by calling the
 *              setRedLedCurrent() with the parameter LedCurrent::LED_OFF, and
 *              call the setInfraredLedCurrent() to configure its amplitide.
 * @attention   Heart Rate mode using the infrared LED was not tested and its
 *              not clear if it really works. Further tests must be executed.
 * @param[in]   redLedCurrent_p     LED's current amplitude value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setHeartRateMode(LedCurrent redLedCurrent_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Mark passage for debugging purpose
    debugMark("Max30102::setHeartRateMode(LedCurrent)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff[0] = (
                    (this->_shuttedDown << Bit::SHDN) |
                    (ModeControl::HEART_RATE_MODE << Bit::MODE)
            );
    if(!this->_write(Register::MODE_CONFIGURATION, auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    auxBuff[0] = (redLedCurrent_p << Bit::LED1_PA);
    auxBuff[1] = (LedCurrent::LED_OFF << Bit::LED2_PA);
    if(!this->_write(Register::LED1_PULSE_AMPLITUDE, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_activeLedsCounter = 1;
    this->_infraredLedCurrent = LedCurrent::LED_OFF;
    this->_modeControl = ModeControl::HEART_RATE_MODE;
    this->_redLedCurrent = redLedCurrent_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the infrared LED's amplitude.
 * @details     Configures the infrared LED's amplitude of the device.
 *              The LED's current amplitude can be programmed from 0 to 50 mA with proper
 *              supply voltage.
 * @note        Actual measured LED's current amplitude for each part can vary widely due to
 *              the trimming methodology.
 * @param[in]   infraredLedCurrent_p        LED's current amplitude value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setInfraredLedCurrent(LedCurrent infraredLedCurrent_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::setInfraredLedCurrent(LedCurrent)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (infraredLedCurrent_p << Bit::LED2_PA);
    if(!this->_write(Register::LED2_PULSE_AMPLITUDE, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_infraredLedCurrent = infraredLedCurrent_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the device in Multi-LED mode.
 * @details     Configures the device in Multi-LED mode. In this mode, each
 *              sample is split into up to four time slots, SLOT1 through
 *              SLOT4. It is possible to set which LED is active in each time
 *              slot, making for a very flexible configuration.
 *              Each slot generates a 3-byte output into the FIFO. One sample
 *              comprises all active slots, for example if SLOT1 and SLOT2 are
 *              non-zero, then one sample is 2 x 3 = 6 bytes.
 *              The slots should be enabled in order (i.e., SLOT1 should not be
 *              disabled if SLOT2 is enabled).
 * @note        The currents of the LEDs remain unchanged. User must call the
 *              setRedLedCurrent() and setInfraredLedCurrent() functions in
 *              order to proper configure the device.
 * @param[in]   slot1_p     Determine the active LED in that time slot.
 * @param[in]   slot2_p     Determine the active LED in that time slot.
 * @param[in]   slot3_p     Determine the active LED in that time slot.
 * @param[in]   slot4_p     Determine the active LED in that time slot.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setMultiLedMode(SlotControl slot1_p, SlotControl slot2_p, SlotControl slot3_p, SlotControl slot4_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Mark passage for debugging purpose
    debugMark("Max30102::setMultiLedMode(SlotControl, SlotControl, SlotControl, SlotControl)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(slot1_p == SlotControl::SLOT_OFF) {              // Then, slots 2, 3, and 4 MUST be OFF
        if((slot2_p != SlotControl::SLOT_OFF) || (slot3_p != SlotControl::SLOT_OFF) || (slot4_p != SlotControl::SLOT_OFF)) {
            // Returns error
            this->_lastError = Error::ARGUMENTS_MISMATCH;
            debugMessage(Error::ARGUMENTS_MISMATCH, Debug::CodeIndex::MAX30102_MODULE);
            return false;
        }
        this->_activeLedsCounter = 0;
    } else if(slot2_p == SlotControl::SLOT_OFF) {       // Then, slots 3, and 4 MUST be OFF
        if((slot3_p != SlotControl::SLOT_OFF) || (slot4_p != SlotControl::SLOT_OFF)) {
            // Returns error
            this->_lastError = Error::ARGUMENTS_MISMATCH;
            debugMessage(Error::ARGUMENTS_MISMATCH, Debug::CodeIndex::MAX30102_MODULE);
            return false;
        }
        this->_activeLedsCounter = 1;
    } else if(slot3_p == SlotControl::SLOT_OFF) {       // Then, slot 4 MUST be OFF
        if(slot4_p != SlotControl::SLOT_OFF) {
            // Returns error
            this->_lastError = Error::ARGUMENTS_MISMATCH;
            debugMessage(Error::ARGUMENTS_MISMATCH, Debug::CodeIndex::MAX30102_MODULE);
            return false;
        }
        this->_activeLedsCounter = 2;
    } else if(slot4_p == SlotControl::SLOT_OFF) {       // Ok, just set active LEDs to 3
        this->_activeLedsCounter = 3;
    } else {                                            // Ok, just set active LEDs to 4
        this->_activeLedsCounter = 4;
    }

    // Configure device
    auxBuff[0] = (
                    (slot2_p << Bit::SLOT2) |
                    (slot1_p << Bit::SLOT1)
            );
    auxBuff[1] = (
                    (slot4_p << Bit::SLOT4) |
                    (slot3_p << Bit::SLOT3)
            );
    if(!this->_write(Register::MULTI_LED_CONTROL_1, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    auxBuff[0] = (
                    (this->_shuttedDown << Bit::SHDN) |
                    (ModeControl::MULTI_LED_MODE << Bit::MODE)
            );
    if(!this->_write(Register::MODE_CONFIGURATION, auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_modeControl = ModeControl::MULTI_LED_MODE;
    this->_multiLedSlot1Control = slot1_p;
    this->_multiLedSlot2Control = slot2_p;
    this->_multiLedSlot3Control = slot3_p;
    this->_multiLedSlot4Control = slot4_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the red LED's amplitude.
 * @details     Configures the red LED's amplitude of the device. The
 *              LED's current amplitude can be programmed from 0 to 50 mA with proper
 *              supply voltage.
 * @note        Actual measured LED's current amplitude for each part can vary widely due to
 *              the trimming methodology.
 * @param[in]   redLedCurrent_p     LED's current amplitude value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setRedLedCurrent(LedCurrent redLedCurrent_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::setRedLedCurrent(LedCurrent)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (redLedCurrent_p << Bit::LED1_PA);
    if(!this->_write(Register::LED1_PULSE_AMPLITUDE, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_redLedCurrent = redLedCurrent_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the channel's output resolution.
 * @details     Configures the channel's output resolution of the ADC sensor.
 *              The output resolution of the ADC sensor is directly related to
 *              LED pulse width (the IR and Red have the same pulse width), and
 *              therefore, indirectly sets the integration time of the ADC in
 *              each sample.
 * @param[in]   resolution_p        SpO2 ADC sensor full scale.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setResolution(Resolution resolution_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::setResolution(Resolution)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (this->_fullScale << Bit::SPO2_ADC_RGE) |
                    (this->_sampleRate << Bit::SPO2_SR) |
                    (resolution_p << Bit::LED_PW)
            );
    if(!this->_write(Register::SPO2_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_resolution = resolution_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the ADC's output sample rate.
 * @details     Configures the ADC's output sample rate. The ADC output data
 *              rate can be programmed from 50 sps to 3200 sps. The maximum
 *              sample rate for the ADC depends on the selected pulse width,
 *              which in turn, determines the ADC resolution. For instance, if
 *              the ADCresolution is set to 15 bits (pulse width = 69 µs), then
 *              all sample rates are selectable. However, if the ADC resolution
 *              is set to 18 bits (pulse width = 411 µs), then the samples rates
 *              are limited in accordance to the selected operation mode.
 * @note        The actual FIFO ouput rate is a combination of the ADC's output
 *              sample rate and the FIFO averaging. (PUT EQUATION HERE!!!)
 * @attention   If the user selects a sample rate that is too high for the
 *              selected resolution, the highest possible sample rate is
 *              programmed instead into the register.
 * @param[in]   resolution_p        SpO2 ADC sensor full scale.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setSampleRate(SampleRate sampleRate_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::setSampleRate(SampleRate)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (this->_fullScale << Bit::SPO2_ADC_RGE) |
                    (sampleRate_p << Bit::SPO2_SR) |
                    (this->_resolution << Bit::LED_PW)
            );
    if(!this->_write(Register::SPO2_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_sampleRate = sampleRate_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Configures the device in SpO2 mode.
 * @details     Configures the device in SpO2 mode. In this mode, each sample
 *              consist of 6-byte (2 x 3 bytes) output into the FIFO. Both red
 *              and infrared LEDs are active. In the FIFO, the red channel is
 *              stored first, followed by the infrared channel. The function
 *              also configures the LEDs' amplitudes of the device. The LED
 *              current can be programmed from 0 to 50 mA with proper supply
 *              voltage.
 * @note        Actual measured LED's current amplitude for each part can vary widely due to
 *              the trimming methodology.
 * @note        In SpO2 mode, the user must use the internal temperature sensor
 *              information to calibrate the temperature dependence of the SpO2
 *              sub-system. The device output data is relatively insensitive to
 *              the wavelength of the IR LED, where the Red LED's wavelength is
 *              critical to correct interpretation of the data. An SpO2
 *              algorithm used with the MAX30102 output signal can compensate
 *              for the associated SpO2 error with ambient temperature changes.
 * @param[in]   redLedCurrent_p         LED's current amplitude value.
 * @param[in]   infraredLedCurrent_p    LED's current amplitude value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::setSpo2Mode(LedCurrent redLedCurrent_p, LedCurrent infraredLedCurrent_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Mark passage for debugging purpose
    debugMark("Max30102::setSpo2Mode(LedCurrent, LedCurrent)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff[0] = (
                    (this->_shuttedDown << Bit::SHDN) |
                    (ModeControl::SPO2_MODE << Bit::MODE))
            ;
    if(!this->_write(Register::MODE_CONFIGURATION, auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    auxBuff[0] = (redLedCurrent_p << Bit::LED1_PA);
    auxBuff[1] = (infraredLedCurrent_p << Bit::LED2_PA);
    if(!this->_write(Register::LED1_PULSE_AMPLITUDE, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_modeControl = ModeControl::SPO2_MODE;
    this->_redLedCurrent = redLedCurrent_p;
    this->_infraredLedCurrent = infraredLedCurrent_p;
    this->_activeLedsCounter = 2;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     /////////////////    FIFO CONTROL AND STATUS     /////////////////     //

/**
 * @brief       Configures the FIFO.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[in]   averages_p                  number of ADC samples to be averaged
 *                                          to each sample in FIFO.
 * @param[in]   overflowEnable_p            if true, new samples will replace
 *                                          old ones in FIFO when FIFO is full.
 * @param[in]   remainingSpaceInterrupt_p   controls the number of samples
 *                                          spaces are remaining in FIFO when
 *                                          a FIFO almost full interruption is
 *                                          generated.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::configFifo(SampleAveraging averages_p, bool overflowEnable_p, uint8_t remainingSpaceInterrupt_p)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::configFifo(SampleAveraging, bool, uint8_t)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff = (
                    (averages_p << Bit::FIFO_SMP_AVE) |
                    (overflowEnable_p << Bit::FIFO_ROLLOVER_EN) |
                    (remainingSpaceInterrupt_p << Bit::FIFO_A_FULL)
            );
    if(!this->_write(Register::FIFO_CONFIGURATION, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoAlmostFullValue = remainingSpaceInterrupt_p;
    this->_fifoRolloverOnFull = overflowEnable_p;
    this->_sampleAveraging = averages_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Flushes data from the FIFO.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::flushFifo(void)
{
    // Local variables
    uint8_t auxBuff[3];

    // Mark passage for debugging purpose
    debugMark("Max30102::flushFifo(void)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Configure device
    auxBuff[0] = 0;
    auxBuff[1] = 0;
    auxBuff[2] = 0;
    if(!this->_write(Register::FIFO_WRITE_POINTER, auxBuff, 3)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoOverflowCounter = 0;
    this->_fifoReadPointer = 0;
    this->_fifoWritePointer = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Gets the occupation of the FIFO.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[out]  samplesWaiting_p    number of samples available in the FIFO.
 * @param[out]  samplesLost_p       number of samples that where lost in the
 *                                  FIFO.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoOccupation(uint8_t *samplesWaiting_p, uint8_t *samplesLost_p)
{
    // Local variables
    uint8_t samples;

    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoOccupation(uint8_t *, uint8_t *)", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(samplesWaiting_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Gets FIFO information
    if(!this->_getFifoInfo()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Calculate number of available samples
    if(this->_fifoWritePointer >= this->_fifoReadPointer) {
        samples = this->_fifoWritePointer;
        samples -= this->_fifoReadPointer;
    } else {
        samples = MAX30102_FIFO_SIZE_IN_SAMPLES;
        samples -= this->_fifoReadPointer;
        samples += this->_fifoWritePointer;
    }
    *samplesWaiting_p = samples;
    if(isPointerValid(samplesLost_p)) {
        *samplesLost_p = this->_fifoOverflowCounter;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     /////////////////////    DATA MANAGEMENT     /////////////////////     //

/**
 * @brief       Reads FIFO data, converting it to a 2-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[in]   samplesCount_p          number of samples to be read from the
 *                                      FIFO.
 * @param[out]  redLedBuffer_p          pointer to the buffer that will hold the
 *                                      red LED channel values.
 * @param[out]  infraredLedBuffer_p     pointer to the buffer that will hold the
 *                                      infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoData(uint8_t samplesCount_p, uint16_t *redLedBuffer_p, uint16_t *infraredLedBuffer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoData(uint8_t, uint16_t *, uint16_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(samplesCount_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    if(!(isPointerValid(redLedBuffer_p) || isPointerValid(infraredLedBuffer_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads data from FIFO
    if(!this->_readFifoData(samplesCount_p, redLedBuffer_p, infraredLedBuffer_p, sizeof(uint16_t))) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads FIFO data, converting it to a 4-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[in]   samplesCount_p          number of samples to be read from the
 *                                      FIFO.
 * @param[out]  redLedBuffer_p          pointer to the buffer that will hold the
 *                                      red LED channel values.
 * @param[out]  infraredLedBuffer_p     pointer to the buffer that will hold the
 *                                      infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoData(uint8_t samplesCount_p, uint32_t *redLedBuffer_p, uint32_t *infraredLedBuffer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoData(uint8_t, uint32_t *, uint32_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(samplesCount_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    if(!(isPointerValid(redLedBuffer_p) || isPointerValid(infraredLedBuffer_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads data from FIFO
    if(!this->_readFifoData(samplesCount_p, redLedBuffer_p, infraredLedBuffer_p, sizeof(uint32_t))) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads FIFO data, getting the newest sample and converting it to a 2-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[out]  redValue_p          pointer to the buffer that will hold the
 *                                  red LED channel values.
 * @param[out]  infraredValue_p     pointer to the buffer that will hold the
 *                                  infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoNewestSample(uint16_t *redValue_p, uint16_t *infraredValue_p)
{
    // Local variables
    uint8_t auxBuff[6];
    uint32_t auxInfrared = 0;
    uint32_t auxRed = 0;
    uint8_t readPointer = 0;
    uint8_t resolutionFix = 0;
    uint8_t writePointer = 0;

    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoNewestSample(uint16_t *, uint16_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(!(isPointerValid(redValue_p) || isPointerValid(infraredValue_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Move FIFO pointers to read only the newest sample
    if(!this->_getFifoWritePointer(&writePointer)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    readPointer = (writePointer == 0) ? (MAX30102_FIFO_SIZE_IN_SAMPLES - 1) : (writePointer - 1);
    if(!this->_setFifoReadPointer(readPointer)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads a sample from the FIFO
    if(!this->_read(Register::FIFO_DATA, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Evaluates the number of shifts to fix the value due to resolution
    switch(this->_resolution) {
    case Resolution::RESOLUTION_15_BITS:
        resolutionFix = 3;
        break;
    case Resolution::RESOLUTION_16_BITS:
        resolutionFix = 2;
        break;
    case Resolution::RESOLUTION_17_BITS:
        resolutionFix = 1;
        break;
    case Resolution::RESOLUTION_18_BITS:
        resolutionFix = 0;
        break;
    }

    // Calculates the LED channel values
    if(isPointerValid(redValue_p)) {
        auxRed = (uint32_t)auxBuff[0];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[1];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[2];
        auxRed >>= resolutionFix;
    }
    if(isPointerValid(infraredValue_p)) {
        auxInfrared = (uint32_t)auxBuff[3];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[4];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[5];
        auxInfrared >>= resolutionFix;
    }

    // Truncates the sample size to 16 bits
    if(resolutionFix < 2) {
        resolutionFix = 2 - resolutionFix;
        auxRed >>= resolutionFix;
        auxInfrared >>= resolutionFix;
    }

    // Update values of the function arguments
    if(isPointerValid(redValue_p)) {
        *redValue_p = (uint16_t)auxRed;
    }
    if(isPointerValid(infraredValue_p)) {
        *infraredValue_p = (uint16_t)auxInfrared;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads FIFO data, getting the newest sample and converting it to a 4-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[out]  redValue_p          pointer to the buffer that will hold the
 *                                  red LED channel values.
 * @param[out]  infraredValue_p     pointer to the buffer that will hold the
 *                                  infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoNewestSample(uint32_t *redValue_p, uint32_t *infraredValue_p)
{
    // Local variables
    uint8_t auxBuff[6];
    uint32_t auxInfrared = 0;
    uint32_t auxRed = 0;
    uint8_t readPointer = 0;
    uint8_t resolutionFix = 0;
    uint8_t writePointer = 0;

    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoNewestSample(uint32_t *, uint32_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(!(isPointerValid(redValue_p) || isPointerValid(infraredValue_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // DEBUG: START TEST
    // this->_read(Register::FIFO_WRITE_POINTER, auxBuff, 3);
    // this->_fifoWritePointerOld = auxBuff[0];
    // this->_fifoOverflowCounterOld = auxBuff[1];
    // this->_fifoReadPointerOld = auxBuff[2];
    // DEBUG: END TEST

    // Move FIFO pointers to read only the newest sample
    if(!this->_getFifoWritePointer(&writePointer)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }
    readPointer = (writePointer == 0) ? (MAX30102_FIFO_SIZE_IN_SAMPLES - 1) : (writePointer - 1);
    if(!this->_setFifoReadPointer(readPointer)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads a sample from the FIFO
    if(!this->_read(Register::FIFO_DATA, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // DEBUG: START TEST
    // this->_read(Register::FIFO_WRITE_POINTER, auxBuff, 3);
    // this->_fifoWritePointerNew = auxBuff[0];
    // this->_fifoOverflowCounterNew = auxBuff[1];
    // this->_fifoReadPointerNew = auxBuff[2];
    // DEBUG: END TEST

    // Evaluates the number of shifts to fix the value due to resolution
    switch(this->_resolution) {
    case Resolution::RESOLUTION_15_BITS:
        resolutionFix = 3;
        break;
    case Resolution::RESOLUTION_16_BITS:
        resolutionFix = 2;
        break;
    case Resolution::RESOLUTION_17_BITS:
        resolutionFix = 1;
        break;
    case Resolution::RESOLUTION_18_BITS:
        resolutionFix = 0;
        break;
    }

    // Calculates the LED channel values
    if(isPointerValid(redValue_p)) {
        auxRed = (uint32_t)auxBuff[0];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[1];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[2];
        auxRed >>= resolutionFix;
    }
    if(isPointerValid(infraredValue_p)) {
        auxInfrared = (uint32_t)auxBuff[3];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[4];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[5];
        auxInfrared >>= resolutionFix;
    }

    // Update values of the function arguments
    if(isPointerValid(redValue_p)) {
        *redValue_p = (uint32_t)auxRed;
    }
    if(isPointerValid(infraredValue_p)) {
        *infraredValue_p = (uint32_t)auxInfrared;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads FIFO data, getting the oldest sample and converting it to a 2-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[out]  redValue_p          pointer to the buffer that will hold the
 *                                  red LED channel values.
 * @param[out]  infraredValue_p     pointer to the buffer that will hold the
 *                                  infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoOldestSample(uint16_t *redValue_p, uint16_t *infraredValue_p)
{
    // Local variables
    uint8_t auxBuff[6];
    uint32_t auxInfrared = 0;
    uint32_t auxRed = 0;
    uint8_t resolutionFix = 0;

    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoOldestSample(uint16_t *, uint16_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(!(isPointerValid(redValue_p) || isPointerValid(infraredValue_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads a sample from the FIFO
    if(!this->_read(Register::FIFO_DATA, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Evaluates the number of shifts to fix the value due to resolution
    switch(this->_resolution) {
    case Resolution::RESOLUTION_15_BITS:
        resolutionFix = 3;
        break;
    case Resolution::RESOLUTION_16_BITS:
        resolutionFix = 2;
        break;
    case Resolution::RESOLUTION_17_BITS:
        resolutionFix = 1;
        break;
    case Resolution::RESOLUTION_18_BITS:
        resolutionFix = 0;
        break;
    }

    // Calculates the LED channel values
    if(isPointerValid(redValue_p)) {
        auxRed = (uint32_t)auxBuff[0];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[1];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[2];
        auxRed >>= resolutionFix;
    }
    if(isPointerValid(infraredValue_p)) {
        auxInfrared = (uint32_t)auxBuff[3];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[4];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[5];
        auxInfrared >>= resolutionFix;
    }

    // Update values of the function arguments
    if(isPointerValid(redValue_p)) {
        *redValue_p = (uint16_t)auxRed;
    }
    if(isPointerValid(infraredValue_p)) {
        *infraredValue_p = (uint16_t)auxInfrared;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads FIFO data, getting the oldest sample and converting it to a 4-bytes per channel.
 * @details     // TODO: Detailed explanation of the FIFO operation
 * @param[out]  redValue_p          pointer to the buffer that will hold the
 *                                  red LED channel values.
 * @param[out]  infraredValue_p     pointer to the buffer that will hold the
 *                                  infrared LED channel values.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getFifoOldestSample(uint32_t *redValue_p, uint32_t *infraredValue_p)
{
    // Local variables
    uint8_t auxBuff[6];
    uint32_t auxInfrared = 0;
    uint32_t auxRed = 0;
    uint8_t resolutionFix = 0;

    // Mark passage for debugging purpose
    debugMark("Max30102::getFifoOldestSample(uint32_t *, uint32_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(!(isPointerValid(redValue_p) || isPointerValid(infraredValue_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads a sample from the FIFO
    if(!this->_read(Register::FIFO_DATA, auxBuff, 6)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Evaluates the number of shifts to fix the value due to resolution
    switch(this->_resolution) {
    case Resolution::RESOLUTION_15_BITS:
        resolutionFix = 3;
        break;
    case Resolution::RESOLUTION_16_BITS:
        resolutionFix = 2;
        break;
    case Resolution::RESOLUTION_17_BITS:
        resolutionFix = 1;
        break;
    case Resolution::RESOLUTION_18_BITS:
        resolutionFix = 0;
        break;
    }

    // Calculates the LED channel values
    if(isPointerValid(redValue_p)) {
        auxRed = (uint32_t)auxBuff[0];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[1];
        auxRed <<= 8;
        auxRed |= (uint32_t)auxBuff[2];
        auxRed >>= resolutionFix;
    }
    if(isPointerValid(infraredValue_p)) {
        auxInfrared = (uint32_t)auxBuff[3];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[4];
        auxInfrared <<= 8;
        auxInfrared |= (uint32_t)auxBuff[5];
        auxInfrared >>= resolutionFix;
    }

    // Update values of the function arguments
    if(isPointerValid(redValue_p)) {
        *redValue_p = (uint32_t)auxRed;
    }
    if(isPointerValid(infraredValue_p)) {
        *infraredValue_p = (uint32_t)auxInfrared;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads internal sensor internal temperature.
 * @details     // TODO: Detailed explanation of the sensor internal temperature
 * @param[out]  tempValue_p     pointer to the temperature value variable.
 * @param[in]   tempScale_p     to which thermometric scale the value must be
 *                              converted.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getTemperature(float *tempValue_p, ThermometricScale tempScale_p)
{
    // Local variables
    uint8_t auxBuff[2];
    float auxFloat = 0.0;

    // Mark passage for debugging purpose
    debugMark("Max30102::getTemperature(float *, ThermometricScale)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if(!isPointerValid(tempValue_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads die temperature register
    if(!this->_read(Register::DIE_TEMPERATURE_INTEGER, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Calculates temperature
    // FIXME: Implement a better algorithm using the fact that (1/16 = 0.0625 = 1 >> 4)
    auxFloat = (float)auxBuff[0] + ((float)auxBuff[1] / 16);

    switch(tempScale_p) {
    case ThermometricScale::CELSIUS:
        *tempValue_p = auxFloat;
        break;
    case ThermometricScale::DELISLE:
    case ThermometricScale::FAHRENHEIT:
    case ThermometricScale::KELVIN:
    case ThermometricScale::NEWTON:
    case ThermometricScale::RANKINE:
    case ThermometricScale::REAUMUR:
    case ThermometricScale::ROMER:
        // TODO: Implement the conversion between thermometric scales
        // Returns error
        this->_lastError = Error::UNDER_DEVELOPMENT;
        debugMessage(Error::UNDER_DEVELOPMENT, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads internal sensor internal temperature.
 * @details     // TODO: Detailed explanation of the sensor internal temperature
 * @param[out]  tempInteger_p
 * @param[out]  tempFrac_p
 *                              converted.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getTemperature(int8_t *tempInteger_p, uint8_t *tempFrac_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Mark passage for debugging purpose
    debugMark("Max30102::getTemperature(int8_t *, uint8_t *)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Check function arguments for errors
    if((!isPointerValid(tempInteger_p)) || (!isPointerValid(tempFrac_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads die temperature register
    if(!this->_read(Register::DIE_TEMPERATURE_INTEGER, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns temperature
    *tempInteger_p = (int8_t)auxBuff[0];
    *tempFrac_p = (uint8_t)auxBuff[1];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @return true
 * @return false
 */
bool Max30102::startTemperatureRead(void)
{
    // Local variables
    uint8_t auxBuff;

    // Mark passage for debugging purpose
    debugMark("Max30102::startTemperatureRead(void)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Starts a temperature acquisiton
    auxBuff = (1 << Bit::TEMP_EN);
    if(!this->_write(Register::DIE_TEMPERATURE_CONFIG, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update class data members
    this->_dieTempReady = false;
    this->_dieTempEnable = true;
    this->_dieTempInteger = 0;
    this->_dieTempFraction = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     //////////////     INTERRUPT CONTROL AND STATUS     //////////////     //

/**
 * @brief       Disables the interrupt pin to relay an internal interrupt.
 * @details     Disables the interrupt pin to relay an internal interrupt.
 *              // TODO: Explain the operation of the deactivation mask
 * @note        Since its not possible to turn on or off the power on interrupt,
 *              the function just ignores it from the interrupt mask.
 * @param[in]   deactivationMask_p  interrupts to be disabled.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::disableInterrupts(InterruptFlags deactivationMask_p)
{
    // Local variables
    uint8_t auxBuff[2];
    bool intAmbient                     = false;
    bool intAlmostFull                  = false;
    bool intTempReady                   = false;
    bool intNewDataReady                = false;

    // Mark passage for debugging purpose
    debugMark("Max30102::disableInterrupts(InterruptFlags)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Populate the variables with the class members values
    intAmbient = this->_ambLightCancOverflowInterruptEnable;
    intAlmostFull = this->_fifoAlmostFullInterruptEnable;
    intTempReady = this->_dieTempReadyInterruptEnable;
    intNewDataReady = this->_newFifoDataReadyInterruptEnable;

    // Process the deactivation mask
    if(deactivationMask_p & InterruptFlags::FIFO_ALMOST_FULL_FLAG) {
        intAlmostFull = false;
    }
    if(deactivationMask_p & InterruptFlags::NEW_FIFO_DATA_READY_FLAG) {
        intNewDataReady = false;
    }
    if(deactivationMask_p & InterruptFlags::AMBIENT_LIGHT_CANCELLATION_FLAG) {
        intAmbient = false;
    }
    if(deactivationMask_p & InterruptFlags::INTERNAL_TEMPERATURE_READY_FLAG) {
        intTempReady  = false;
    }

    // Configure device
    auxBuff[0] = (
                    (intAlmostFull << Bit::A_FULL_EN) |
                    (intNewDataReady << Bit::PPG_RDY_EN) |
                    (intAmbient << Bit::ALC_OVF_EN)
            );
    auxBuff[1] = (intTempReady << Bit::DIE_TEMP_RDY_EN);
    if(!this->_write(Register::INTERRUPT_ENABLE_1, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update class data members
    this->_ambLightCancOverflowInterruptEnable = intAmbient;
    this->_fifoAlmostFullInterruptEnable = intAlmostFull;
    this->_dieTempReadyInterruptEnable = intTempReady;
    this->_newFifoDataReadyInterruptEnable = intNewDataReady;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Enables the interrupt pin to relay an internal interrupt.
 * @details     Enables the interrupt pin to relay an internal interrupt.
 *              // TODO: Explain the operation of the activation mask
 * @note        Since its not possible to turn on or off the power on interrupt,
 *              the function just ignores it from the interrupt mask.
 * @param[in]   activationMask_p    interrupts to be enabled.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::enableInterrupts(InterruptFlags activationMask_p)
{
    // Local variables
    uint8_t auxBuff[2];
    bool intAmbient                     = false;
    bool intAlmostFull                  = false;
    bool intTempReady                   = false;
    bool intNewDataReady                = false;

    // Mark passage for debugging purpose
    debugMark("Max30102::enableInterrupts(InterruptFlags)", DEBUG_CODE_MAX3010X);

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Populate the variables with the class members values
    intAmbient = this->_ambLightCancOverflowInterruptEnable;
    intAlmostFull = this->_fifoAlmostFullInterruptEnable;
    intTempReady = this->_dieTempReadyInterruptEnable;
    intNewDataReady = this->_newFifoDataReadyInterruptEnable;

    // Process the deactivation mask
    if(activationMask_p & InterruptFlags::FIFO_ALMOST_FULL_FLAG) {
        intAlmostFull = true;
    }
    if(activationMask_p & InterruptFlags::NEW_FIFO_DATA_READY_FLAG) {
        intNewDataReady = true;
    }
    if(activationMask_p & InterruptFlags::AMBIENT_LIGHT_CANCELLATION_FLAG) {
        intAmbient = true;
    }
    if(activationMask_p & InterruptFlags::INTERNAL_TEMPERATURE_READY_FLAG) {
        intTempReady  = true;
    }

    // Configure device
    auxBuff[0] = (
                    (intAlmostFull << Bit::A_FULL_EN) |
                    (intNewDataReady << Bit::PPG_RDY_EN) |
                    (intAmbient << Bit::ALC_OVF_EN)
            );
    auxBuff[1] = (intTempReady << Bit::DIE_TEMP_RDY_EN);
    if(!this->_write(Register::INTERRUPT_ENABLE_1, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update class data members
    this->_ambLightCancOverflowInterruptEnable = intAmbient;
    this->_fifoAlmostFullInterruptEnable = intAlmostFull;
    this->_dieTempReadyInterruptEnable = intTempReady;
    this->_newFifoDataReadyInterruptEnable = intNewDataReady;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @return true
 * @return false
 */
bool Max30102::generalIrqHandler(void)
{
    // Local variables
    //  InterruptFlags auxFlags;

    // Note: Since this function is called asynchroneusly, no debug mark passage
    // was placed for caution. The same happens with the getInterruptStatus()
    // function that is called inside this function.
    // debugMark("generalIrqHandler(void)");

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Read the interrupt status registers
    if(!this->getInterruptStatus()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Call callback functions
    if(this->_ambLightCancOverflowInterruptFlag) {
        this->_ambLightCancOverflowInterruptCallback();
    }
    if(this->_dieTempReadyInterruptFlag) {
        this->_dieTempReadyInterruptCallback();
    }
    if(this->_fifoAlmostFullInterruptFlag) {
        this->_fifoAlmostFullInterruptCallback();
    }
    if(this->_newFifoDataReadyInterruptFlag) {
        this->_newFifoDataReadyInterruptCallback();
    }
    if(this->_powerReadyInterruptFlag) {
        this->_powerReadyInterruptCallback();
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads the sensor interrupt status.
 * @details     Reads the sensor interrupt status.
 *              // TODO: Explain the operation of the interrupt
 * @param[out]  interruptStatus_p   status of sensor interrupts.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::getInterruptStatus(InterruptFlags *interruptStatus_p)
{
    // Local variables
    uint8_t auxBuff[2];

    // Note: This function is also called by the generalIrqHandler() function.
    // Since the generalIrqHandler() function is called asynchroneusly,
    // triggered by interrupts, no debug mark passage was placed for caution.
    // debugMark("getInterruptStatus(InterruptFlags *)");

    // Check device's initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Read the interrupt status registers
    if(!this->_read(Register::INTERRUPT_STATUS_1, auxBuff, 2)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update class data members
    this->_fifoAlmostFullInterruptFlag = (bool)(auxBuff[0] & (1 << Bit::A_FULL_INT));
    this->_newFifoDataReadyInterruptFlag = (bool)(auxBuff[0] & (1 << Bit::PPG_RDY_INT));
    this->_ambLightCancOverflowInterruptFlag = (bool)(auxBuff[0] & (1 << Bit::ALC_OVF_INT));
    this->_powerReadyInterruptFlag = (bool)(auxBuff[0] & (1 << Bit::PWR_RDY_INT));
    this->_dieTempReadyInterruptFlag = (bool)(auxBuff[1] & (1 << Bit::DIE_TEMP_RDY_INT));

    // Retrieve interrupt status
    if(isPointerValid(interruptStatus_p)) {
        *interruptStatus_p = InterruptFlags::NONE;
        if(this->_fifoAlmostFullInterruptFlag) {
            *interruptStatus_p |= InterruptFlags::FIFO_ALMOST_FULL_FLAG;
        }
        if(this->_newFifoDataReadyInterruptFlag) {
            *interruptStatus_p |= InterruptFlags::NEW_FIFO_DATA_READY_FLAG;
        }
        if(this->_ambLightCancOverflowInterruptFlag) {
            *interruptStatus_p |= InterruptFlags::AMBIENT_LIGHT_CANCELLATION_FLAG;
        }
        if(this->_dieTempReadyInterruptFlag) {
            *interruptStatus_p |= InterruptFlags::INTERNAL_TEMPERATURE_READY_FLAG;
        }
        if(this->_powerReadyInterruptFlag) {
            *interruptStatus_p |= InterruptFlags::POWER_READY_FLAG;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     ///////////////////    INTERRUPT CALLBACKS     ///////////////////     //

/**
 * @brief
 * // TODO: document this function
 * @param callbackFunction_p
 * @return true
 * @return false
 */
bool Max30102::setAmbLightCancOverflowInterruptCallback(void (* callbackFunction_p)(void))
{
    // Mark passage for debugging purpose
    debugMark("Max30102::setAmbLightCancOverflowInterruptCallback(void (*)(void))", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(callbackFunction_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_ambLightCancOverflowInterruptCallback = callbackFunction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @param callbackFunction_p
 * @return true
 * @return false
 */
bool Max30102::setDieTempReadyInterruptCallback(void (* callbackFunction_p)(void))
{
    // Mark passage for debugging purpose
    debugMark("Max30102::setDieTempReadyInterruptCallback(void (*)(void))", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(callbackFunction_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_dieTempReadyInterruptCallback = callbackFunction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @param callbackFunction_p
 * @return true
 * @return false
 */
bool Max30102::setFifoAlmostFullInterruptCallback(void (* callbackFunction_p)(void))
{
    // Mark passage for debugging purpose
    debugMark("Max30102::setFifoAlmostFullInterruptCallback(void (*)(void))", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(callbackFunction_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoAlmostFullInterruptCallback = callbackFunction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @param callbackFunction_p
 * @return true
 * @return false
 */
bool Max30102::setNewFifoDataReadyInterruptCallback(void (* callbackFunction_p)(void))
{
    // Mark passage for debugging purpose
    debugMark("Max30102::setNewFifoDataReadyInterruptCallback(void (*)(void))", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(callbackFunction_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_newFifoDataReadyInterruptCallback = callbackFunction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief
 * // TODO: document this function
 * @param callbackFunction_p
 * @return true
 * @return false
 */
bool Max30102::setPowerReadyInterruptCallback(void (* callbackFunction_p)(void))
{
    // Mark passage for debugging purpose
    debugMark("Max30102::setPowerReadyInterruptCallback(void (*)(void))", DEBUG_CODE_MAX3010X);

    // Check function arguments for errors
    if(!isPointerValid(callbackFunction_p)) {
        // Returns error
        this->_lastError = Error::FUNCTION_POINTER_NULL;
        debugMessage(Error::FUNCTION_POINTER_NULL, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_powerReadyInterruptCallback = callbackFunction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}



// =============================================================================
// Class own methods - Private
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

/**
 * @brief
 * @details
 */
void Max30102::_clearData(void)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_clearData(void)", DEBUG_CODE_MAX3010X);

    //     ////////////     INTERRUPT CONTROL AND STATUS     ////////////     //
    this->_ambLightCancOverflowInterruptEnable          = false;
    this->_ambLightCancOverflowInterruptFlag            = false;
    this->_dieTempReadyInterruptEnable                  = false;
    this->_dieTempReadyInterruptFlag                    = false;
    this->_fifoAlmostFullInterruptEnable                = false;
    this->_fifoAlmostFullInterruptFlag                  = false;
    this->_newFifoDataReadyInterruptEnable              = false;
    this->_newFifoDataReadyInterruptFlag                = false;
    this->_powerReadyInterruptFlag                      = false;
    //     ////////////////////    DEVICE STATUS     ////////////////////     //
    this->_initialized                                  = false;
    this->_partId                                       = 0;
    this->_partRevision                                 = 0;
    this->_shuttedDown                                  = false;
    //     ////////////////     DEVICE CONFIGURATION     ////////////////     //
    this->_activeLedsCounter                            = 0;
    this->_fullScale                                    = FullScale::FULL_SCALE_2048_NA;
    this->_infraredLedCurrent                           = LedCurrent::LED_OFF;
    this->_modeControl                                  = ModeControl::NO_MODE_SELECTED;
    this->_redLedCurrent                                = LedCurrent::LED_OFF;
    this->_resolution                                   = Resolution::RESOLUTION_15_BITS;
    this->_sampleRate                                   = SampleRate::SAMPLE_RATE_50_HZ;
    //     ///////////////    FIFO CONTROL AND STATUS     ///////////////     //
    this->_fifoAlmostFullValue                          = 0;
    this->_fifoData                                     = 0;
    this->_fifoOverflowCounter                          = 0;
    // this->_fifoOverflowCounterNew                        = 0;
    // this->_fifoOverflowCounterOld                        = 0;
    this->_fifoReadPointer                              = 0;
    // this->_fifoReadPointerNew                            = 0;
    // this->_fifoReadPointerOld                            = 0;
    this->_fifoRolloverOnFull                           = false;
    this->_fifoWritePointer                             = 0;
    // this->_fifoWritePointerNew                           = 0;
    // this->_fifoWritePointerOld                           = 0;
    this->_sampleAveraging                              = SampleAveraging::SAMPLE_AVERAGING_OFF;
    //     //////////////////     TEMPERATURE DATA     //////////////////     //
    this->_dieTempEnable                                = false;
    this->_dieTempFraction                              = 0;
    this->_dieTempInteger                               = 0;
    this->_dieTempReady                                 = false;
    //     ////////////////    MULTILED SLOT CONTROL     ////////////////     //
    this->_multiLedSlot1Control                         = SlotControl::SLOT_OFF;
    this->_multiLedSlot2Control                         = SlotControl::SLOT_OFF;
    this->_multiLedSlot3Control                         = SlotControl::SLOT_OFF;
    this->_multiLedSlot4Control                         = SlotControl::SLOT_OFF;
    this->_slotsEnabledCounter                          = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return;
}

/**
 * @brief       Checks if the device was initialized.
 * @details     Checks if the device was initialized.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @attention   This function only verifies the device initialization, it does
 *              not verifies if the device is configured properly.
 * @return      true        Device is initialized.
 * @return      false       Device is not initialized.
 */
bool Max30102::_isInitialized(void)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_isInitialized(void)", DEBUG_CODE_MAX3010X);

    // Checks if device is initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     //////////////////    REGISTER MANIPULATION     //////////////////     //

/**
 * @brief       Reads registers from the device.
 * @details     Reads registers from the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[in]   regAddr_p       device's register addess.
 * @param[out]  dataBuffer_p    pointer to buffer.
 * @param[in]   bytesToRead_p   number of bytes to read from the device.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_read(Register regAddr_p, uint8_t *dataBuffer_p, uint16_t bytesToRead_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_read(Register, uint8_t *, uint16_t)", DEBUG_CODE_MAX3010X);

    // Selects device
    if(!this->_busHandler->setDevice(MAX30102_DEVICE_ADDRESS)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Read data from device
    if(!this->_busHandler->readReg((uint8_t)regAddr_p, dataBuffer_p, bytesToRead_p)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Writes registers at the device.
 * @details     Writes registers at the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[in]   regAddr_p       device's register addess.
 * @param[out]  dataBuffer_p    pointer to buffer.
 * @param[in]   bytesToWrite_p  number of bytes to write at the device.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_write(Register regAddr_p, uint8_t *dataBuffer_p, uint16_t bytesToWrite_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_write(Register, uint8_t *, uint16_t)", DEBUG_CODE_MAX3010X);

    // Selects device
    if(!this->_busHandler->setDevice(MAX30102_DEVICE_ADDRESS)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Read data from device
    if(!this->_busHandler->writeReg((uint8_t)regAddr_p, dataBuffer_p, bytesToWrite_p)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     /////////////////    FIFO CONTROL AND STATUS     /////////////////     //

/**
 * @brief       Gets FIFO status registers from the device.
 * @details     Gets FIFO status registers from the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_getFifoInfo(void)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_getFifoInfo(void)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t auxBuff[3];

    // Reads from device
    if(!this->_read(Register::FIFO_WRITE_POINTER, auxBuff, 3)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoWritePointer = auxBuff[0];
    this->_fifoOverflowCounter = auxBuff[1];
    this->_fifoReadPointer = auxBuff[2];

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Gets the FIFO's read pointer from the device.
 * @details     Gets the FIFO's read pointer from the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[out]  pointer_p       pointer to variable to store the value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_getFifoReadPointer(uint8_t *pointer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_getFifoReadPointer(uint8_t *)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t auxBuff;

    // Reads from device
    if(!this->_read(Register::FIFO_READ_POINTER, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoReadPointer = auxBuff;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Gets the FIFO's write pointer from the device.
 * @details     Gets the FIFO's write pointer from the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[out]  pointer_p       pointer to variable to store the value.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_getFifoWritePointer(uint8_t *pointer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_getFifoWritePointer(uint8_t *)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t auxBuff;

    // Reads from device
    if(!this->_read(Register::FIFO_WRITE_POINTER, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoWritePointer = auxBuff;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Reads data from device's FIFO.
 * @details     Reads data from device's FIFO.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[in]   samples_p   number of samples to be read from FIFO.
 * @param[out]  buff1       buffer to red LED values.
 * @param[out]  buff2       buffer to infrared LED values.
 * @param[in]   varSize     size of the variable to be stored.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_readFifoData(uint8_t samples_p, void *redLedBuffer_p, void *infraredLedBuffer_p, uint8_t varSize_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_readFifoData(uint8_t, void *, void*, uint8_t)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t *auxBuff = nullptr;
    uint8_t resolutionFix = 0;
    uint16_t aux16 = 0;
    int32_t aux32 = 0;
    uint16_t *buff16ptr1 = (uint16_t *)redLedBuffer_p;
    uint16_t *buff16ptr2 = (uint16_t *)infraredLedBuffer_p;
    uint32_t *buff32ptr1 = (uint32_t *)redLedBuffer_p;
    uint32_t *buff32ptr2 = (uint32_t *)infraredLedBuffer_p;

    // Evaluate buffer size
    switch(this->_modeControl) {
    case ModeControl::HEART_RATE_MODE:
        aux16 = MAX30102_BYTES_PER_CHANNEL * samples_p * 1;
        break;
    case ModeControl::SPO2_MODE:
        aux16 = MAX30102_BYTES_PER_CHANNEL * samples_p * 2;
        break;
    case ModeControl::MULTI_LED_MODE:
        aux16 = MAX30102_BYTES_PER_CHANNEL * samples_p * this->_activeLedsCounter;
        break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        debugMessage(Error::UNKNOWN, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Memory allocation
    auxBuff = (uint8_t *)calloc(aux16, sizeof(uint8_t));
    if(!isPointerValid(auxBuff)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION;
        debugMessage(Error::MEMORY_ALLOCATION, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Reads from device
    if(!this->_read(Register::FIFO_DATA, auxBuff, aux16)) {
        // Returns error
        free(auxBuff);
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Evaluates the number of shifts to fix the value due to resolution
    switch(this->_resolution) {
    case Resolution::RESOLUTION_15_BITS:
        resolutionFix = 3;
        break;
    case Resolution::RESOLUTION_16_BITS:
        resolutionFix = 2;
        break;
    case Resolution::RESOLUTION_17_BITS:
        resolutionFix = 1;
        break;
    case Resolution::RESOLUTION_18_BITS:
        resolutionFix = 0;
        break;
    }

    // Decode data
    aux16 = 0;
    for(uint8_t i = 0; i < samples_p; i++) {
        switch(this->_modeControl) {
        case ModeControl::HEART_RATE_MODE:
            // Process red LED value
            aux32 = (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 >>= resolutionFix;
            // Truncates the sample size to 16 bits
            if((resolutionFix < 2) && (varSize_p == 2)) {
                aux32 >>= (2 - resolutionFix);
            }
            // Update function arguments
            if(isPointerValid(redLedBuffer_p)) {
                if(varSize_p == 2) {
                    *buff16ptr1++ = (uint16_t)(aux32);
                } else {
                    *buff32ptr1++ = (uint32_t)(aux32);
                }
            }
            break;

        case ModeControl::SPO2_MODE:
            // Process red LED value
            aux32 = (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 >>= resolutionFix;
            // Truncates the sample size to 16 bits
            if((resolutionFix < 2) && (varSize_p == 2)) {
                aux32 >>= (2 - resolutionFix);
            }
            // Update function arguments
            if(isPointerValid(redLedBuffer_p)) {
                if(varSize_p == 2) {
                    *buff16ptr1++ = (uint16_t)(aux32);
                } else {
                    *buff32ptr1++ = (uint32_t)(aux32);
                }
            }
            // Process infrared LED value
            aux32 = (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 <<= 8;
            aux32 |= (uint32_t)(auxBuff[aux16++]);
            aux32 >>= resolutionFix;
            // Truncates the sample size to 16 bits
            if((resolutionFix < 2) && (varSize_p == 2)) {
                aux32 >>= (2 - resolutionFix);
            }
            // Update function arguments
            if(isPointerValid(infraredLedBuffer_p)) {
                if(varSize_p == 2) {
                    *buff16ptr2++ = (uint16_t)(aux32);
                } else {
                    *buff32ptr2++ = (uint32_t)(aux32);
                }
            }
            break;

        case ModeControl::MULTI_LED_MODE:
            // TODO: Implement this mode
            // Returns error
            this->_lastError = Error::UNDER_DEVELOPMENT;
            debugMessage(Error::UNDER_DEVELOPMENT, Debug::CodeIndex::MAX30102_MODULE);
            return false;
        }
    }
    free(auxBuff);

    // Update data members
    if(!this->_getFifoInfo()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Sets the FIFO's read pointer at the device.
 * @details     Sets the FIFO's read pointer at the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[in]   pointer_p       value to be stored into the register.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_setFifoReadPointer(uint8_t pointer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_setFifoReadPointer(uint8_t)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t auxBuff;

    // Writes at device
    auxBuff = (pointer_p << Bit::FIFO_RD_PTR);
    if(!this->_write(Register::FIFO_READ_POINTER, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoReadPointer = auxBuff;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

/**
 * @brief       Sets the FIFO's write pointer at the device.
 * @details     Sets the FIFO's write pointer at the device.
 * @note        This function is private, so before calling it, the
 *              programmer must ensure that all parameters are checked.
 * @param[in]   pointer_p       value to be stored into the register.
 * @return      true        Operation successfull.
 * @return      false       Operation failed. Retrieve error calling
 *                          getLastError() function.
 */
bool Max30102::_setFifoWritePointer(uint8_t pointer_p)
{
    // Mark passage for debugging purpose
    debugMark("Max30102::_setFifoWritePointer(uint8_t)", DEBUG_CODE_MAX3010X);

    // Local variables
    uint8_t auxBuff;

    // Writes at device
    auxBuff = (pointer_p << Bit::FIFO_WR_PTR);
    if(!this->_write(Register::FIFO_WRITE_POINTER, &auxBuff, 1)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::MAX30102_MODULE);
        return false;
    }

    // Update data members
    this->_fifoWritePointer = auxBuff;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::MAX30102_MODULE);
    return true;
}

//     /////////////     TEMPORARY - USED FOR DEBUG     /////////////     //

void Max30102::readAllRegs(uint8_t *regs_p)
{
    uint8_t auxBuff[11];

    debugMark("Max30102::readAllRegs(uint8_t *)", DEBUG_CODE_MAX3010X);

    this->_read(Register::INTERRUPT_STATUS_1, auxBuff, 7);
    regs_p[0]       = auxBuff[0];       // Int status 1
    regs_p[1]       = auxBuff[1];       // Int status 2
    regs_p[2]       = auxBuff[2];       // Int enable 1
    regs_p[3]       = auxBuff[3];       // Int enable 2
    regs_p[4]       = auxBuff[4];       // Fifo write
    regs_p[5]       = auxBuff[5];       // Fifo overflow
    regs_p[6]       = auxBuff[6];       // Fifo read

    this->_read(Register::FIFO_CONFIGURATION, auxBuff, 11);
    regs_p[7]       = auxBuff[0];       // Fifo configuration
    regs_p[8]       = auxBuff[1];       // Mode configuration
    regs_p[9]       = auxBuff[2];       // SpO2 configuration
    regs_p[10]      = auxBuff[4];       // Pulse amplitude LED 1
    regs_p[11]      = auxBuff[5];       // Pulse amplitude LED 2
    regs_p[12]      = auxBuff[9];       // Multi-slot 1
    regs_p[13]      = auxBuff[10];      // Multi-slot 2

    this->_read(Register::DIE_TEMPERATURE_INTEGER, auxBuff, 3);
    regs_p[14]      = auxBuff[0];       // Temperature integer
    regs_p[15]      = auxBuff[1];       // Temperature fraction
    regs_p[16]      = auxBuff[2];       // Temperature config

    this->_read(Register::REVISION_ID, auxBuff, 2);
    regs_p[17]      = auxBuff[0];       // Temperature integer
    regs_p[18]      = auxBuff[1];       // Temperature fraction

    return;
}

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

/**
 * @brief
 * // TODO: document this function
 */
static void defaultCallbackFunction(void)
{
    return;
}

// =============================================================================
// END OF FILE
// =============================================================================
