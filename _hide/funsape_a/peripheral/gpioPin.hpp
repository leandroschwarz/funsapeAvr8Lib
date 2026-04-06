/**
 *******************************************************************************
 * @file            gpioPin.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           GPIO single pin peripheral control.
 * @details         This file provides driver interface with the GPIO module to
 *                      single pin peripheral control for the FunSAPE++ AVR8
 *                      Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
 * @bug             When the user calls GpioPin::clr(), GpioPin::cpl(),
 *                      GpioPin::set(), GpioPin::low(), GpioPin::high() or
 *                      GpioPin::toggle() and the pin is in
 *                      GpioPin::Mode::INPUT_FLOATING mode or in
 *                      GpioPin::Mode::INPUT_PULLED_UP mode, the mode is changed
 *                      without knowledge of the class, so the GpioPin::_mode
 *                      internal member is not updated, which could lead to some
 *                      undefined behavior.
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

#ifndef __GPIO_PIN_HPP
#define __GPIO_PIN_HPP                  2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [gpioPin.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __GPIO_PIN_HPP
#   error [gpioPin.hpp] Error 2 - Build mismatch between file (gpioPin.hpp) and global definitions file (globalDefines.hpp)!
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
/**
 * @addtogroup      Peripherals
 * @brief           Microcontroller peripherals.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Gpio"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Gpio
 * @brief           General Purpose Intput/Output (GPIO) controller module.
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

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           GpioPin class.
 * @details         This class manages the General Purpose Input-Output (GPIO)
 *                      peripheral in single pin mode.
 * @attention       This class is not instantiated by default. The user may
 *                      create as many instances as necessary.
*/
class GpioPin
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        PinIndex
     * @brief       Pin number enumeration.
     * @details     Pin number enumeration.
    */
    enum class PinIndex : uint8_t {
        P0          = 0,    //!< Pin located at position 0 of the port
        P1          = 1,    //!< Pin located at position 1 of the port
        P2          = 2,    //!< Pin located at position 2 of the port
        P3          = 3,    //!< Pin located at position 3 of the port
        P4          = 4,    //!< Pin located at position 4 of the port
        P5          = 5,    //!< Pin located at position 5 of the port
        P6          = 6,    //!< Pin located at position 6 of the port
        P7          = 7     //!< Pin located at position 7 of the port
    };

    /**
     * @enum        PinMask
     * @brief       Pin mask enumeration.
     * @details     Pin mask enumeration.
    */
    enum class PinMask : uint8_t {
        P0          = 1 << 0,       //!< Bit mask of the pin located at position 0 of the port
        P1          = 1 << 1,       //!< Bit mask of the pin located at position 1 of the port
        P2          = 1 << 2,       //!< Bit mask of the pin located at position 2 of the port
        P3          = 1 << 3,       //!< Bit mask of the pin located at position 3 of the port
        P4          = 1 << 4,       //!< Bit mask of the pin located at position 4 of the port
        P5          = 1 << 5,       //!< Bit mask of the pin located at position 5 of the port
        P6          = 1 << 6,       //!< Bit mask of the pin located at position 6 of the port
        P7          = 1 << 7,       //!< Bit mask of the pin located at position 7 of the port
    };

    /**
     * @enum        Mode
     * @brief       Pin driver mode enumeration.
     * @details     Pin driver mode enumeration.
    */
    enum class Mode : uint8_t {
        INPUT_FLOATING                  = 1,    //!< Direction is INPUT without PULL resistors
        INPUT_PULLED_UP                 = 3,    //!< Direction is INPUT with PULL-UP resistors
        OUTPUT_PUSH_PULL                = 5,    //!< Direction is OUTPUT in PUSH PULL driver
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       GpioPin class constructor.
     * @details     Creates a GpioPin object. The object must be initialized
     *                  before use.
     * @see         init(ioRegAddress_t gpioPort_p, PinIndex gpioPinIndex_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    GpioPin(
            void
    );

    /**
     * @brief       GpioPin class destructor.
     * @details     Destroys a GpioPin object.
    */
    ~GpioPin(
            void
    );

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

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
    */
    Error inlined getLastError(
            void
    );

    /**
     * @brief       Initializes the GpioPin module.
     * @details     Initializes the GpioPin module.
     * @param[in]   gpioPortAddress_p   Register address of the GPIO port.
     * @param[in]   gpioPinIndex_p      @ref PinIndex pin position.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                    | Meaning                              |
     * |:------------------------------|:-------------------------------------|
     * | @ref Error::NONE              | Success. No erros were detected.     |
     * | @ref Error::GPIO_PORT_INVALID | The given GPIO address is not valid. |
     *
    */
    bool_t init(
            ioRegAddress_t gpioPortAddress_p,
            PinIndex gpioPinIndex_p
    );

    //     /////////////////    PIN RELATED METHODS     /////////////////     //

    /**
     * @brief       Clears the GpioPin pin.
     * @details     This function clears the pin bit in the output @c PORTx
     *                  register. If the pin mode is set to
     *                  @ref GpioPin::Mode::OUTPUT_PUSH_PULL, the pin output
     *                  will be set to @ref LogicLevel::LOW.
     * @warning     It is recommended to use this function only when the pin
     *                  mode is set to @ref GpioPin::Mode::OUTPUT_PUSH_PULL,
     *                  otherwise, the pin mode will be changed to
     *                  @ref GpioPin::Mode::INPUT_FLOATING.
    */
    void inlined clr(
            void
    );

    /**
     * @brief       Complements (inverts) the GpioPin pin.
     * @details     This function toggles the pin bit in the output @c PORTx
     *                  register. If the pin mode is set to
     *                  @ref GpioPin::Mode::OUTPUT_PUSH_PULL, the pin output
     *                  will be toggled between @ref LogicLevel::LOW and
     *                  @ref LogicLevel::HIGH.
     * @warning     It is recommended to use this function only when the pin
     *                  mode is set to @ref GpioPin::Mode::OUTPUT_PUSH_PULL,
     *                  otherwise, the pin mode will be toggled between
     *                  @ref GpioPin::Mode::INPUT_FLOATING and
     *                  @ref GpioPin::Mode::INPUT_PULLED_UP.
    */
    void inlined cpl(
            void
    );

    /**
     * @brief       Sets the GpioPin pin.
     * @details     This function is an alias of @ref GpioPin::set().
    */
    void inlined high(
            void
    );

    /**
     * @brief       Checks if the GpioPin is initialized.
     * @details     This function checks if the GpioPin object was successfully
     *                  initialized.
     * @retval      true                if the object is initialized.
     * @retval      false               if the object is not initialized.
    */
    bool_t inlined isInitialized(
            void
    );

    /**
     * @brief       Clears the GpioPin pin.
     * @details     This function is an alias of @ref GpioPin::clr().
    */
    void inlined low(
            void
    );

    /**
     * @brief       Reads the GpioPin value.
     * @details     This function returns the logic level of the pin. Since it
     *                  returns the value of the input @c PINx register, this
     *                  function can be used with any @ref GpioPin::Mode
     *                  selection.
     * @retval      true                if the pin is in @ref LogicLevel::HIGH.
     * @retval      false               if the pin is in @ref LogicLevel::LOW.
    */
    bool_t inlined read(
            void
    );

    /**
     * @brief       Sets the GpioPin pin.
     * @details     This function sets the pin bit in the output @c PORTx
     *                  register. If the pin mode is set to
     *                  @ref GpioPin::Mode::OUTPUT_PUSH_PULL, the pin output
     *                  will be set to @ref LogicLevel::HIGH.
     * @warning     It is recommended to use this function only when the pin
     *                  mode is set to @ref GpioPin::Mode::OUTPUT_PUSH_PULL,
     *                  otherwise, the pin mode will be changed to
     *                  @ref GpioPin::Mode::INPUT_PULLED_UP.
    */
    void inlined set(
            void
    );

    /**
     * @brief       Sets the GpioPin operation mode.
     * @details     This function sets the GPIO pin operation mode to the given
     *                  @a mode_p.
     * @note        When the operation mode is changed to
     *                  @ref GpioPin::Mode::INPUT_FLOATING or to
     *                  @ref GpioPin::Mode::INPUT_PULLED_UP, both output @c PORTx
     *                  and direction @c DDRx registers are changed. However,
     *                  when the mode is changed to
     *                  @ref GpioPin::Mode::OUTPUT_PUSH_PULL, only the direction
     *                  @c DDRx register is changed, therefore, if a specific
     *                  output logic level is desired on the pin, the user must
     *                  call the @ref clr() or @ref set().
     * @param[in]   mode_p              @ref GpioPin::Mode operation mode.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     * @par Error codes:
     *
     * | Error code                  | Meaning                          |
     * |:----------------------------|:---------------------------------|
     * | @ref Error::NONE            | Success. No erros were detected. |
     * | @ref Error::NOT_INITIALIZED | The pin is not initialized.      |
    */
    bool_t setMode(
            const Mode mode_p
    );

    /**
     * @brief       Complements (inverts) the GpioPin pin.
     * @details     This function is an alias of @ref GpioPin::cpl().
    */
    void inlined toggle(
            void
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
    PinMask         _pinMask;                   //!< Pin location.
    PinIndex        _pinIndex;                  //!< Pin mask.

    //     ////////////////////   CONFIGURATION     /////////////////////     //

    Mode            _mode;                      //!< Current operation mode.

    //     /////////////////    CONTROL AND STATUS     //////////////////     //

    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

protected:
    // NONE

}; // class GpioPin

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined GpioPin::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

//     /////////////////    PIN RELATED METHODS     /////////////////     //

void inlined GpioPin::clr(void)
{
    // Clear pin
    clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::cpl(void)
{
    // Toggle pin
    cplMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::high(void)
{
    this->set();

    return;
}

bool_t inlined GpioPin::isInitialized(void)
{
    return this->_isInitialized;
}

void inlined GpioPin::low(void)
{
    this->clr();

    return;
}

bool_t inlined GpioPin::read(void)
{
    return (bool_t)(*(this->_regIn) & (uint8_t)(this->_pinMask));
}

void inlined GpioPin::set(void)
{
    // Set pin
    setMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns
    return;
}

void inlined GpioPin::toggle(void)
{
    this->cpl();

    return;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/GpioPin"
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

#endif  // __GPIO_PIN_HPP

// =============================================================================
// End of file (gpioPin.hpp)
// =============================================================================
