//!
//! ****************************************************************************
//! @file           gpioPin.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          GPIO single pin peripheral control.
//! @details        This file provides driver interface with the GPIO module to
//!                     single pin peripheral control for the FunSAPE++ AVR8
//!                     Library.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @warning        When the user calls GpioPin::clr(), GpioPin::cpl(),
//!                     GpioPin::set(), GpioPin::low(), GpioPin::high() or
//!                     GpioPin::toggle() and the pin is in
//!                     PinMode::INPUT_FLOATING mode or in
//!                     PinMode::INPUT_PULLED_UP mode, the mode is changed which
//!                     could lead to some undefined behavior.
//! ****************************************************************************
//! @attention
//!
//! MIT License
//!
//! Copyright (c) 2026 Leandro Schwarz
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//!     of this software and associated documentation files (the "Software"), to
//!     deal in the Software without restriction, including without limitation
//!     the rights to use, copy, modify, merge, publish, distribute, sublicense,
//!     and/or sell copies of the Software, and to permit persons to whom the
//!     Software is furnished to do so, subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in
//!     all copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//!     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//!     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//!     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//!     OTHER DEALINGS IN THE SOFTWARE.
//!
//! ****************************************************************************
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __GPIO_PIN_HPP
#define __GPIO_PIN_HPP                  2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [gpioPin.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __GPIO_PIN_HPP
#   error [gpioPin.hpp] Error 2 - Build mismatch between file (gpioPin.hpp) and global definitions file!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [gpioPin.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __GPIO_PIN_HPP
#   error [gpioPin.hpp] Error 5 - Build mismatch between file (gpioPin.hpp) and library dependency (debug.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Peripherals
//! @brief          Microcontroller peripherals.
//! @{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Gpio" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Gpio
//! @brief          General Purpose Input/Output (GPIO) controller module.
//! @{
//!

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
// Interrupt callback functions declarations
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
//! @brief          GpioPin class
//! @details        This class manages the General Purpose Input-Output (GPIO)
//!                     peripheral in single pin mode.
//! @attention      This class is not instantiated by default. The user may
//!                     create as many instances as necessary.
//!
class GpioPin
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    // NONE

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Constructors ------------------------------------------------------------

public:
    //!
    //! @brief      GpioPin class constructor.
    //! @details    Creates a GpioPin object. The object must be initialized
    //!                 before use.
    //! @see        init(ioRegAddress_t gpioPort_p, PinIndex gpioPinIndex_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |: ----------------|: --------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    GpioPin(
            void
    );

    //!
    //! @brief      GpioPin class destructor.
    //! @details    Destroys a GpioPin object.
    //!
    ~GpioPin(
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
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    //!
    //! @brief      Returns the last error.
    //! @details    Returns the last error.
    //! @return     @ref Error          Error status of the last operation.
    //!
    Error inlined getLastError(
            void
    ) const;

    //!
    //! @brief      Initializes the GpioPin module.
    //! @details    Initializes the GpioPin module.
    //! @param[in]  gpioPortAddress_p   Register address of the GPIO port.
    //! @param[in]  gpioPinIndex_p      @ref PinIndex pin position.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                    | Meaning                              |
    //! |:------------------------------|:-------------------------------------|
    //! | @ref Error::NONE              | Success. No erros were detected.     |
    //! | @ref Error::GPIO_PORT_INVALID | The given GPIO address is not valid. |
    //!
    bool_t init(
            ioRegAddress_t gpioPortAddress_p,
            const PinIndex gpioPinIndex_p
    );

    //     /////////////////    PIN RELATED METHODS     /////////////////     //

    //!
    //! @brief      Clears the GpioPin pin.
    //! @details    This function clears the pin bit in the output @c PORTx
    //!                 register. If the pin mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin output
    //!                 will be set to @ref LogicLevel::LOW.
    //! @warning    It is recommended to use this function only when the pin
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the pin mode will be changed to
    //!                 @ref PinMode::INPUT_FLOATING.
    //!
    void inlined clr(
            void
    ) const;

    //!
    //! @brief      Complements (inverts) the GpioPin pin.
    //! @details    This function toggles the pin bit in the output @c PORTx
    //!                 register. If the pin mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin output
    //!                 will be toggled between @ref LogicLevel::LOW and
    //!                 @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the pin
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the pin mode will be toggled between
    //!                 @ref PinMode::INPUT_FLOATING and
    //!                 @ref PinMode::INPUT_PULLED_UP.
    //!
    void inlined cpl(
            void
    ) const;

    //!
    //! @brief      Sets the GpioPin pin.
    //! @details    This function is an alias for @ref GpioPin::set().
    //!
    void inlined high(
            void
    ) const;

    //!
    //! @brief      Checks if the GpioPin is initialized.
    //! @details    This function checks if the GpioPin object was successfully
    //!                 initialized.
    //! @retval     true                if the object is initialized.
    //! @retval     false               if the object is not initialized.
    //!
    bool_t inlined isInitialized(
            void
    ) const;

    //!
    //! @brief      Clears the GpioPin pin.
    //! @details    This function is an alias for @ref GpioPin::clr().
    //!
    void inlined low(
            void
    ) const;

    //!
    //! @brief      Reads the pin level.
    //! @details    This function returns the logic level of the pin. Since it
    //!                 returns the value of the input @c PINx register, this
    //!                 function can be used with any @ref PinMode
    //!                 selection.
    //! @retval     true                if the pin is in @ref LogicLevel::HIGH.
    //! @retval     false               if the pin is in @ref LogicLevel::LOW.
    //!
    bool_t inlined read(
            void
    ) const;

    //!
    //! @brief      Sets the GpioPin pin.
    //! @details    This function sets the pin bit in the output @c PORTx
    //!                 register. If the pin mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin output
    //!                 will be set to @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the pin
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the pin mode will be changed to
    //!                 @ref PinMode::INPUT_PULLED_UP.
    //!
    void inlined set(
            void
    ) const;

    //!
    //! @brief      Sets the GpioPin operation mode.
    //! @details    This function sets the GPIO pin operation mode to the given
    //!                 @a mode_p.
    //! @note       When the operation mode is changed to
    //!                 @ref PinMode::INPUT_FLOATING or to
    //!                 @ref PinMode::INPUT_PULLED_UP, both output @c PORTx
    //!                 and direction @c DDRx registers are changed. However,
    //!                 when the mode is changed to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, only the direction
    //!                 @c DDRx register is changed, therefore, if a specific
    //!                 output logic level is desired on the pin, the user must
    //!                 call the @ref clr() or @ref set().
    //! @param[in]  mode_p              @ref PinMode operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                  | Meaning                          |
    //! |:----------------------------|:---------------------------------|
    //! | @ref Error::NONE            | Success. No erros were detected. |
    //! | @ref Error::NOT_INITIALIZED | The pin is not initialized.      |
    //!
    bool_t setMode(
            const PinMode mode_p
    );

    //!
    //! @brief      Complements (inverts) the GpioPin pin.
    //! @details    This function is an alias for @ref GpioPin::cpl().
    //!
    void inlined toggle(
            void
    ) const;

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Properties --------------------------------------------------------------

private:
    //     //////////////////    HARDWARE LINKAGE     ///////////////////     //

    ioRegAddress_t  _regDir;                    //!< Address to the direction @c DDRx register.
    ioRegAddress_t  _regOut;                    //!< Address to the output @c PORTx register.
    ioRegAddress_t  _regIn;                     //!< Address to the input @c PINx register.
    ioPinMask_t     _pinMask;                   //!< Pin mask.

    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

protected:
    // NONE

}; // class GpioPin

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined GpioPin::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     /////////////////    PIN RELATED METHODS     /////////////////     //

void inlined GpioPin::clr(void) const
{
    // Clear pin
    clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::cpl(void) const
{
    // Toggle pin
    cplMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::high(void) const
{
    this->set();

    return;
}

bool_t inlined GpioPin::isInitialized(void) const
{
    return this->_isInitialized;
}

void inlined GpioPin::low(void) const
{
    this->clr();

    return;
}

bool_t inlined GpioPin::read(void) const
{
    return (bool_t)(*(this->_regIn) & (uint8_t)(this->_pinMask));
}

void inlined GpioPin::set(void) const
{
    // Set pin
    setMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::toggle(void) const
{
    this->cpl();

    return;
}

//!
//! @endcond
//!

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Gpio" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __GPIO_PIN_HPP

// =============================================================================
// End of file (gpioPin.hpp)
// =============================================================================
