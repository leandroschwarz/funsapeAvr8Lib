/**
 *******************************************************************************
 * @file            stepper.cpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Stepper motor module interface for the FunSAPE++ AVR8
 *                      Library.
 * @details         Stepper motor module interface for the FunSAPE++ AVR8
 *                      Library.
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
// System file dependencies
// =============================================================================

#include "stepper.hpp"
#if !defined(__STEPPER_HPP)
#    error Error 1 - Header file (stepper.hpp) is missing or corrupted!
#elif __STEPPER_HPP != 2508
#    error Error 6 - Build mismatch between header file (stepper.hpp) and source file (stepper.cpp)!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

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

// NONE

// =============================================================================
// Public function definitions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Stepper::Stepper(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::Stepper(void)"), Debug::CodeIndex::STEPPER_MODULE);

    // Resets data members
    this->_coilA                        = nullptr;
    this->_coilB                        = nullptr;
    this->_coilC                        = nullptr;
    this->_coilD                        = nullptr;
    this->_mode                         = Mode::FULL_STEP_DRIVE;
    this->_currentStep                  = Step::NONE;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return;
}

Stepper::~Stepper(void)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::~Stepper(void)"), Debug::CodeIndex::STEPPER_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Stepper::init(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::init(const Mode)"), Debug::CodeIndex::STEPPER_MODULE);

    // Resets data members
    this->_isInitialized                = false;

    // Checks for errors
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::STEPPER_MODULE);
        return false;
    }

    // Update data members
    switch(mode_p) {
    case Mode::FULL_STEP_DRIVE:
    case Mode::HALF_STEP_DRIVE:
    case Mode::DUAL_COIL_DRIVE:
        break;
    }

    // Updates data members
    this->_isInitialized                = true;
    this->_mode                         = mode_p;

    // Config GPIO
    this->_coilA->low();
    this->_coilB->low();
    this->_coilC->low();
    this->_coilD->low();
    this->_coilA->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilB->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilC->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilD->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->move(this->_currentRotation);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

bool_t Stepper::move(const Rotation direction_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::move(const Rotation)"), Debug::CodeIndex::STEPPER_MODULE);

    // Checks for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::STEPPER_MODULE);
        return false;
    }

    // Evaluates next step
    switch(this->_mode) {
    case Mode::HALF_STEP_DRIVE:
        if(direction_p == Rotation::CLOCKWISE) {
            this->_currentStep = (
                            (this->_currentStep == Step::D_A)
                            ? Step::A_A
                            : static_cast<Step>(static_cast<uint8_t>(this->_currentStep) + 1)
                    );
        } else {
            this->_currentStep = (
                            (this->_currentStep == Step::A_A)
                            ? Step::D_A
                            : static_cast<Step>(static_cast<uint8_t>(this->_currentStep) - 1)
                    );
        }
        break;
    case Mode::FULL_STEP_DRIVE:
        if(direction_p == Rotation::CLOCKWISE) {
            switch(this->_currentStep) {
            case Step::NONE:
            case Step::D_D:
            case Step::D_A:
                this->_currentStep = Step::A_A;
                break;
            case Step::A_A:
            case Step::A_B:
                this->_currentStep = Step::B_B;
                break;
            case Step::B_B:
            case Step::B_C:
                this->_currentStep = Step::C_C;
                break;
            case Step::C_C:
            case Step::C_D:
                this->_currentStep = Step::D_D;
                break;
            }
        } else {
            switch(this->_currentStep) {
            case Step::NONE:
            case Step::A_A:
            case Step::D_A:
                this->_currentStep = Step::D_D;
                break;
            case Step::D_D:
            case Step::C_D:
                this->_currentStep = Step::C_C;
                break;
            case Step::C_C:
            case Step::B_C:
                this->_currentStep = Step::B_B;
                break;
            case Step::B_B:
            case Step::A_B:
                this->_currentStep = Step::A_A;
                break;
            }
        }
        break;
    case Mode::DUAL_COIL_DRIVE:
        if(direction_p == Rotation::CLOCKWISE) {
            switch(this->_currentStep) {
            case Step::D_A:
            case Step::NONE:
            case Step::A_A:
                this->_currentStep = Step::A_B;
                break;
            case Step::A_B:
            case Step::B_B:
                this->_currentStep = Step::B_C;
                break;
            case Step::B_C:
            case Step::C_C:
                this->_currentStep = Step::C_D;
                break;
            case Step::C_D:
            case Step::D_D:
                this->_currentStep = Step::D_A;
                break;
            }
        } else {
            switch(this->_currentStep) {
            case Step::A_B:
            case Step::A_A:
            case Step::NONE:
                this->_currentStep = Step::D_A;
                break;
            case Step::D_A:
            case Step::D_D:
                this->_currentStep = Step::C_D;
                break;
            case Step::C_D:
            case Step::C_C:
                this->_currentStep = Step::B_C;
                break;
            case Step::B_C:
            case Step::B_B:
                this->_currentStep = Step::A_B;
                break;
            }
        }
        break;
    }

    // Moves motor
    this->_doStep();

    // Updates data members
    this->_currentRotation              = direction_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

bool_t Stepper::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::setMode(const Mode)"), Debug::CodeIndex::STEPPER_MODULE);

    // Updates data members
    this->_mode     = mode_p;

    if(this->_isInitialized) {
        this->move(this->_currentRotation);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

bool_t Stepper::setPorts(GpioPin *coilA_p, GpioPin *coilB_p, GpioPin *coilC_p, GpioPin *coilD_p)
{
    // Mark passage for debugging purpose
    debugMark(PSTR("Stepper::setPorts(GpioPin *, GpioPin *, GpioPin *, GpioPin *)"), Debug::CodeIndex::STEPPER_MODULE);

    // Resets data members
    this->_coilA                        = nullptr;
    this->_coilB                        = nullptr;
    this->_coilC                        = nullptr;
    this->_coilD                        = nullptr;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;

    // Checks for errors - Argument pointer invalid
    if(
            (!isPointerValid(coilA_p)) ||
            (!isPointerValid(coilB_p)) ||
            (!isPointerValid(coilC_p)) ||
            (!isPointerValid(coilD_p))
    ) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::STEPPER_MODULE);
        return false;
    }
    // Checks for errors - GpioPin not initialized
    if(
            (!coilA_p->isInitialized()) ||
            (!coilB_p->isInitialized()) ||
            (!coilC_p->isInitialized()) ||
            (!coilD_p->isInitialized())
    ) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Update data members
    this->_coilA        = coilA_p;
    this->_coilB        = coilB_p;
    this->_coilC        = coilC_p;
    this->_coilD        = coilD_p;
    this->_isPortsSet   = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

void Stepper::_doStep(void)
{
    // Turns off all coils
    this->_coilA->low();
    this->_coilB->low();
    this->_coilC->low();
    this->_coilD->low();

    // Turns on specific coils
    switch(this->_currentStep) {
    case Step::A_A:
        this->_coilA->high();
        break;
    case Step::A_B:
        this->_coilA->high();
        this->_coilB->high();
        break;
    case Step::B_B:
        this->_coilB->high();
        break;
    case Step::B_C:
        this->_coilB->high();
        this->_coilC->high();
        break;
    case Step::C_C:
        this->_coilC->high();
        break;
    case Step::C_D:
        this->_coilC->high();
        this->_coilD->high();
        break;
    case Step::D_D:
        this->_coilD->high();
        break;
    case Step::D_A:
        this->_coilD->high();
        this->_coilA->high();
        break;
    case Step::NONE:
        break;
    }

    return;
};

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

/**
 * @cond
*/

// NONE

/**
 * @endcond
*/

// =============================================================================
// End of file (stepper.cpp)
// =============================================================================
