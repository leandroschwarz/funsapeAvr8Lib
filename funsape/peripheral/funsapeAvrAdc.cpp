//!
//! \file           funsapeAvrAdc.cpp
//! \brief          Analog-to-Digital Converter peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// System file dependencies
// =============================================================================

#if __has_include("funsapeAvrAdc.hpp")
#   include "funsapeAvrAdc.hpp"
#   if !defined(__FUNSAPE_AVR_ADC_HPP)
#       error "Header file is corrupted!"
#   elif __FUNSAPE_AVR_ADC_HPP != 220
#       error "Version mismatch between source and header files!"
#   endif
#else
#   error "Header file is missing!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constChannelOffset             = MUX0;
cuint8_t constChannelMask               = 0x0F;
cuint8_t constReferenceOffset           = REFS0;
cuint8_t constReferenceMask             = 0x03;
cuint8_t constPrescalerOffset           = ADPS0;
cuint8_t constPrescalerMask             = 0x07;
cuint8_t constTriggerSourceOffset       = ADTS0;
cuint8_t constTriggerSourceMask         = 0x07;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Adc adc;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Adc::Adc()
{
    // Reset data members
    this->_channel                      = Channel::CHANNEL_0;
    this->_dataAdjust                   = DataAdjust::RIGHT;
    this->_isEnabled                    = false;
    this->_isInitialized                = false;
    this->_isInterruptEnabled           = false;
    this->_mode                         = Mode::SINGLE_CONVERSION;
    this->_prescaler                    = Prescaler::DISABLED;
    this->_reference                    = Reference::EXTERNAL;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

Adc::~Adc()
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Adc::init(Mode mode_p, Reference reference_p, Prescaler prescale_p)
{
    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;
    uint8_t auxAdmux = ADMUX;

    // Configure mode
    clrMaskOffset(auxAdcsrB, constTriggerSourceMask, constTriggerSourceOffset);
    if (mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        setMaskOffset(auxAdcsrB, (uint8_t)mode_p, constTriggerSourceOffset);
    }
    // Configure reference
    clrMaskOffset(auxAdmux, constReferenceMask, constReferenceOffset);
    setMaskOffset(auxAdmux, (uint8_t)reference_p, constReferenceOffset);
    // Configure prescaler
    clrMaskOffset(auxAdcsrA, constPrescalerMask, constPrescalerOffset);
    setMaskOffset(auxAdcsrA, (uint8_t)prescale_p, constPrescalerOffset);

    // Update registers
    ADMUX = auxAdmux;
    ADCSRA = auxAdcsrA;
    ADCSRB = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;
    this->_reference        = reference_p;
    this->_prescaler        = prescale_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::setDataAdjust(DataAdjust datap)
{
    // Configure Data Adjustment
    if (datap == DataAdjust::RIGHT) {
        clrBit(ADMUX, ADLAR);
    } else {
        setBit(ADMUX, ADLAR);
    }

    // Update class members
    this->_dataAdjust       = datap;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::setMode(Mode mode_p)
{
    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;

    // Configure mode
    clrMaskOffset(auxAdcsrB, constTriggerSourceMask, constTriggerSourceOffset);
    if (mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        setMaskOffset(auxAdcsrB, (uint8_t)mode_p, constTriggerSourceOffset);
    }

    // Update registers
    ADCSRA = auxAdcsrA;
    ADCSRB = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::setPrescaler(Prescaler prescale_p)
{
    // Local variables
    uint8_t auxAdcsrA = ADCSRA;

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, constPrescalerMask, constPrescalerOffset);
    setMaskOffset(auxAdcsrA, (uint8_t)prescale_p, constPrescalerOffset);

    // Update registers
    ADCSRA = auxAdcsrA;

    // Update class members
    this->_prescaler        = prescale_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::setReference(Reference reference_p)
{
    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure reference
    clrMaskOffset(auxAdmux, constReferenceMask, constReferenceOffset);
    setMaskOffset(auxAdmux, (uint8_t)reference_p, constReferenceOffset);

    // Update registers
    ADMUX = auxAdmux;

    // Update class members
    this->_reference        = reference_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     //////////////////     CHANNEL CONTROL     ///////////////////     //
bool_t Adc::disableDigitalInput(DigitalInput flagInputs_p)
{
    // TODO: Implement function
    this->_lastError = Error::NOT_IMPLEMENTED;
    return false;
}

bool_t Adc::enableDigitalInput(DigitalInput flagInputs_p)
{
    // TODO: Implement function
    this->_lastError = Error::NOT_IMPLEMENTED;
    return false;
}

bool_t Adc::setChannel(Channel channel_p)
{
    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure reference
    clrMaskOffset(auxAdmux, constChannelMask, constChannelOffset);
    setMaskOffset(auxAdmux, (uint8_t)channel_p, constChannelOffset);

    // Update registers
    ADMUX = auxAdmux;

    // Update class members
    this->_channel          = channel_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     /////////////////     INTERRUPT CONTROL     //////////////////     //
bool_t Adc::activateInterrupt(void)
{
    // Configure Interrupt
    setBit(ADCSRA, ADIE);

    // Update class members
    this->_isInterruptEnabled           = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::clearInterruptRequest(void)
{
    // Configure Interrupt
    setBit(ADCSRA, ADIF);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::deactivateInterrupt(void)
{
    // Configure Interrupt
    clrBit(ADCSRA, ADIE);

    // Update class members
    this->_isInterruptEnabled           = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
bool_t Adc::enable(void)
{
    // Enables ADC
    setBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::disable(void)
{
    // Disables ADC
    clrBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

Error Adc::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Adc::isBusy(void)
{
    return isBitSet(ADCSRA, ADSC);
}

bool_t Adc::startConversion(void)
{
    // Starts conversion
    setBit(ADCSRA, ADSC);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Adc::waitUntilConversionFinish(void)
{
    waitUntilBitIsClear(ADCSRA, ADSC);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

weakened void adcConversionCompleteCallback(void)
{
    return;
}

// =============================================================================
// Interruption handlers
// =============================================================================

ISR(ADC_vect)
{
    adcConversionCompleteCallback();
}

// =============================================================================
// END OF FILE
// =============================================================================
