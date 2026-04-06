//!
//! ****************************************************************************
//! @file           gpioBus.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          GPIO bus peripheral control.
//! @details        This file provides driver interface with the GPIO module to
//!                     multiple sequential pins for the FunSAPE++ AVR8
//!                     Library.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @warning        When the user calls GpioBus::clr(), GpioBus::cpl(),
//!                     GpioBus::set(), GpioBus::low(), GpioBus::high(),
//!                     GpioBus::toggle() or GpioBus::write() and the bus is in
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

#ifndef __GPIO_BUS_HPP
#define __GPIO_BUS_HPP                  2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [gpioBus.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __GPIO_BUS_HPP
#   error [gpioBus.hpp] Error 2 - Build mismatch between file (gpioBus.hpp) and global definitions file!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [gpioBus.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __GPIO_BUS_HPP
#   error [gpioBus.hpp] Error 5 - Build mismatch between file (gpioBus.hpp) and library dependency (debug.hpp)!
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
//! @brief          GpioBus class
//! @details        This class manages the General Purpose Input-Output (GPIO)
//!                     peripheral in bus mode.
//! @attention      This class is not instantiated by default. The user may
//!                     create as many instances as necessary.
//!
class GpioBus
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
    //! @brief      GpioBus class constructor.
    //! @details    Creates a GpioBus object. The object must be initialized
    //!                 before use.
    //! @see        init(ioRegAddress_t gpioPort_p, PinIndex gpioBusIndex_p,
    //!                 cuint8_t gpioBusSize_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |: ----------------|: --------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    GpioBus(
            void
    );

    //!
    //! @brief      GpioBus class destructor.
    //! @details    Destroys a GpioBus object.
    //!
    ~GpioBus(
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
    //! @brief      Initializes the GpioBus module.
    //! @details    Initializes the GpioBus module.
    //! @param[in]  gpioPortAddress_p   Register address of the GPIO port.
    //! @param[in]  gpioBusIndex_p      @ref PinIndex pin position of the first
    //!                                     pin of the bus.
    //! @param[in]  gpioBusSize_p       Bus size in bits.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                             | Meaning                                                            |
    //! |:---------------------------------------|:-------------------------------------------------------------------|
    //! | @ref Error::NONE                       | Success. No erros were detected.                                   |
    //! | @ref Error::GPIO_PORT_INVALID          | The given GPIO address is not valid.                               |
    //! | @ref Error::GPIO_BUS_SIZE_INVALID      | The bus size is greater than 8 or lower than 0.                    |
    //! | @ref Error::GPIO_PIN_OUT_OF_BOUNDARIES | The sum of the bus size and pin index must be lower of equal to 8. |
    //!
    bool_t init(
            ioRegAddress_t gpioPortAddress_p,
            const PinIndex gpioBusIndex_p,
            cuint8_t gpioBusSize_p
    );

    //     /////////////////    PIN RELATED METHODS     /////////////////     //

    //!
    //! @brief      Clears the GpioBus pins.
    //! @details    This function clears all the pins of the bus in the output
    //!                 @c PORTx register. If the bus mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin outputs
    //!                 will be set to @ref LogicLevel::LOW.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the bus mode will be changed to
    //!                 @ref PinMode::INPUT_FLOATING.
    //!
    void inlined clr(
            void
    ) const;

    //!
    //! @brief      Clears one pin of the GpioBus.
    //! @details    This function clears only one pin of the bus in the output
    //!                 @c PORTx register, given by @a bitIndex_p. The provided
    //!                 bit index @c 0 is relative to the bus first pin. If the
    //!                 bus mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 the selected pin output will be set to
    //!                 @ref LogicLevel::LOW.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the mode of the selected pin will be changed
    //!                 to @ref PinMode::INPUT_FLOATING.
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined clr(
            cuint8_t bitIndex_p
    ) const;

    //!
    //! @brief      Complements (inverts) all the GpioBus pins.
    //! @details    This function toggles all the pins in the output @c PORTx
    //!                 register. If the bus mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pins output
    //!                 will be toggled between @ref LogicLevel::LOW and
    //!                 @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the bus mode will be toggled between
    //!                 @ref PinMode::INPUT_FLOATING and
    //!                 @ref PinMode::INPUT_PULLED_UP.
    //!
    void inlined cpl(
            void
    ) const;

    //!
    //! @brief      Complements (inverts) one pin of the GpioBus pins.
    //! @details    This function toggles only one pin of the bus in the output
    //!                 @c PORTx register, given by @a bitIndex_p. The provided
    //!                 bit index @c 0 is relative to the bus first pin. If the
    //!                 bus mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 the selected pin output will be toggled between
    //!                 @ref LogicLevel::LOW and @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the mode of the selected pin will be toggled
    //!                 between @ref PinMode::INPUT_FLOATING and
    //!                 @ref PinMode::INPUT_PULLED_UP.
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined cpl(
            cuint8_t bitIndex_p
    ) const;

    //!
    //! @brief      Returns the GpioBus bus size.
    //! @details    This function returns the GpioBus bus size in bits. If the
    //!                 bus is was initialized, the function returns 0.
    //! @return     the bus size in bits, or @c 0 if the bus was not
    //!                 initialized.
    //!
    uint8_t inlined getBusSize(
            void
    ) const;

    //!
    //! @brief      Sets all the GpioBus pins.
    //! @details    This function is an alias for @ref GpioBus::set().
    //!
    void inlined high(
            void
    ) const;

    //!
    //! @brief      Sets one pin of the GpioBus pins.
    //! @details    This function is an alias of
    //!                 @ref GpioBus::set(uint8_t bitIndex_p).
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined high(
            cuint8_t bitIndex_p
    ) const;

    //!
    //! @brief      Checks if the GpioBus is initialized.
    //! @details    This function checks if the GpioBus object was successfully
    //!                 initialized.
    //! @retval     true                if the object is initialized.
    //! @retval     false               if the object is not initialized.
    //!
    bool_t inlined isInitialized(
            void
    ) const;

    //!
    //! @brief      Clears all the GpioBus pins.
    //! @details    This function is an alias for @ref GpioBus::clr().
    //!
    void inlined low(
            void
    ) const;

    //!
    //! @brief      Clears one pin of the GpioBus pins.
    //! @details    This function is an alias of
    //!                 @ref GpioBus::clr(uint8_t bitIndex_p).
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined low(
            cuint8_t bitIndex_p
    ) const;

    //!
    //! @brief       Reads the GpioBus value.
    //! @details     This function returns the logic level of all the pins of the
    //!                  bus. Since it returns the value of the input @c PINx
    //!                  register, this function can be used with any
    //!                  @ref PinMode selection.
    //! @return      the logic values in the bus pins, shiftted to bit position
    //!                  0.
    //!
    uint8_t inlined read(
            void
    ) const;

    //!
    //! @brief      Sets all the GpioBus pins.
    //! @details    This function sets all the pins of the bus in the output
    //!                 @c PORTx register. If the bus mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin outputs
    //!                 will be set to @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the bus mode will be changed to
    //!                 @ref PinMode::INPUT_PULLED_UP.
    //!
    void inlined set(
            void
    ) const;


    //!
    //! @brief      Sets one pin of the GpioBus pins.
    //! @details    This function sets only one pin of the bus in the output
    //!                 @c PORTx register, given by @a bitIndex_p. The provided
    //!                 bit index @c 0 is relative to the bus first pin. If the
    //!                 bus mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 the selected pin output will be set to
    //!                 @ref LogicLevel::HIGH.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the mode of the selected pin will be changed
    //!                 to @ref PinMode::INPUT_PULLED_UP.
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined set(
            cuint8_t bitIndex_p
    ) const;

    //!
    //! @brief      Sets the GpioBus operation mode.
    //! @details    This function sets the GPIO bus operation mode to the given
    //!                 @a mode_p.
    //! @note       When the operation mode is changed to
    //!                 @ref PinMode::INPUT_FLOATING or to
    //!                 @ref PinMode::INPUT_PULLED_UP, both output @c PORTx
    //!                 and direction @c DDRx registers are changed. However,
    //!                 when the mode is changed to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, only the direction
    //!                 @c DDRx register is changed, therefore, if a specific
    //!                 output logic level is desired on the bus pins, the user
    //!                 must call the @ref clr(), @ref set() or @ref write().
    //! @param[in]  mode_p              @ref PinMode operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                  | Meaning                          |
    //! |:----------------------------|:---------------------------------|
    //! | @ref Error::NONE            | Success. No erros were detected. |
    //! | @ref Error::NOT_INITIALIZED | The bus is not initialized.      |
    //!
    //!
    bool_t setMode(
            const PinMode mode_p
    );

    //!
    //! @brief      Complements (inverts) all the GpioBus pins.
    //! @details    This function is an alias for @ref GpioBus::cpl().
    //!
    void inlined toggle(
            void
    ) const;

    //!
    //! @brief      Complements (inverts) one pin of the GpioBus pins.
    //! @details    This function is an alias of
    //!                 @ref GpioBus::cpl(uint8_t bitIndex_p).
    //! @param[in]  bitIndex_p          position of the bit in the bus.
    //!
    void inlined toggle(
            cuint8_t bitIndex_p
    ) const;


    //!
    //! @brief      Writes data at the GpioBus pins.
    //! @details    This function writes the logic levels given by @a data_p at
    //!                 the of bus pins. The provided @a data_p must be relative
    //!                 to the bus first pin. If the bus mode is set to
    //!                 @ref PinMode::OUTPUT_PUSH_PULL, the pin outputs
    //!                 will be set to @ref LogicLevel::LOW or
    //!                 @ref LogicLevel::HIGH according to the bit value in
    //!                 @a data_p.
    //! @warning    It is recommended to use this function only when the bus
    //!                 mode is set to @ref PinMode::OUTPUT_PUSH_PULL,
    //!                 otherwise, the mode of some pins will be changed to
    //!                 @ref PinMode::INPUT_FLOATING and the some will be
    //!                 changed to @ref PinMode::INPUT_PULLED_UP.
    //! @param[in]  data_p              values to be written at the bus.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                  | Meaning                          |
    //! |:----------------------------|:---------------------------------|
    //! | @ref Error::NONE            | Success. No erros were detected. |
    //! | @ref Error::NOT_INITIALIZED | The bus is not initialized.      |
    //!
    bool_t write(
            cuint8_t data_p
    );

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
    ioPinIndex_t    _pinIndex;                  //!< Pin index.

    //     ////////////////////   CONFIGURATION     /////////////////////     //

    uint8_t         _busSize            : 4;    //!< Bus size in bits.

    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

protected:
    // NONE

}; // class GpioBus

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined GpioBus::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     /////////////////    PIN RELATED METHODS     /////////////////     //

void inlined GpioBus::clr(void) const
{
    // Clear pin
    clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioBus::clr(cuint8_t bitIndex_p) const
{
    // Clear pin
    clrBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

    // Returns
    return;
}

void inlined GpioBus::cpl(void) const
{
    // Toggle pin
    cplMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioBus::cpl(cuint8_t bitIndex_p) const
{
    // Clear pin
    cplBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

    // Returns
    return;
}

uint8_t inlined GpioBus::getBusSize(void) const
{
    // Returns value
    return ((this->_isInitialized) ? (this->_busSize) : (0));
}

void inlined GpioBus::high(void) const
{
    this->set();

    return;
}

void inlined GpioBus::high(cuint8_t bitIndex_p) const
{
    this->set(bitIndex_p);

    return;
}

bool_t inlined GpioBus::isInitialized(void) const
{
    return this->_isInitialized;
}

void inlined GpioBus::low(void) const
{
    this->clr();

    return;
}

void inlined GpioBus::low(cuint8_t bitIndex_p) const
{
    this->clr(bitIndex_p);

    return;
}

uint8_t inlined GpioBus::read(void) const
{
    return (uint8_t)((*(this->_regIn) & (uint8_t)this->_pinMask) >> (uint8_t)this->_pinIndex);
}

void inlined GpioBus::set(void) const
{
    // Set pin
    setMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioBus::set(cuint8_t bitIndex_p) const
{
    // Clear pin
    setBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

    // Returns
    return;
}

void inlined GpioBus::toggle(void) const
{
    this->cpl();

    return;
}

void inlined GpioBus::toggle(cuint8_t bitIndex_p) const
{
    this->cpl(bitIndex_p);

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

#endif  // __GPIO_BUS_HPP

// =============================================================================
// End of file (gpioBus.hpp)
// =============================================================================
