/**
 *******************************************************************************
 * @file            pcint2.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt PCINT2 peripheral control.
 * @details         This file provides peripheral control for the PCINT2
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

#ifndef __PCINT2_HPP
#define __PCINT2_HPP                    2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [pcint2.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __PCINT2_HPP
#   error [pcint2.hpp] Error 2 - Build mismatch between file (pcint2.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [pcint2.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __PCINT2_HPP
#   error [pcint2.hpp] Error 5 - Build mismatch between file (pcint2.hpp) and library dependency (debug.hpp)!
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
// Doxygen: Start subgroup "Peripherals/Pcint2"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Pcint2
 * @brief           Pin Change Interrupt 2 (PCINT2) controller module.
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
 * @brief           PCINT2 interrupt callback function.
 * @details         This function is called when the PCINT2 interrupt is
 *                      treated. It is a weak function that can be overwritten
 *                      by user code.
*/
void pcint2InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Pcint2 class.
 * @details         This class manages the Pin Change Interrupt 2 (PCINT2)
 *                      peripheral.
 * @attention       The @ref pcint2 instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Pcint2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        Pin
     * @brief       Trigger Mode Pins enumeration.
     * @details     Trigger Mode Pins associated with PCINT2.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class Pin : uint8_t {
        PIN_PCINT16         = (1 << 0), //!< Enables trigger by PCINT16 pin.
        PIN_PCINT17         = (1 << 1), //!< Enables trigger by PCINT17 pin.
        PIN_PCINT18         = (1 << 2), //!< Enables trigger by PCINT18 pin.
        PIN_PCINT19         = (1 << 3), //!< Enables trigger by PCINT19 pin.
        PIN_PCINT20         = (1 << 4), //!< Enables trigger by PCINT20 pin.
        PIN_PCINT21         = (1 << 5), //!< Enables trigger by PCINT21 pin.
        PIN_PCINT22         = (1 << 6), //!< Enables trigger by PCINT22 pin.
        PIN_PCINT23         = (1 << 7), //!< Enables trigger by PCINT23 pin.
    };

    /**
     * @enum        PinMode
     * @brief       Pin driver mode enumeration.
     * @details     Pin driver mode enumeration.
    */
    enum class PinMode : uint8_t {
        INPUT_FLOATING                  = 1,
        INPUT_PULLED_UP                 = 3,
        OUTPUT_PUSH_PULL                = 5,
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Pcint2 class constructor.
     * @details     Creates a Pcint2 object. The object is loaded with the
     *                  default register values (no pins enabled). The object
     *                  still must be initialized before use.
     * @see         init(const Pin enablePins_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Pcint2(
            void
    );

    /**
     * @brief       Pcint2 class destructor.
     * @details     Destroys a Pcint2 object.
    */
    ~Pcint2(
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
     * @brief       Disables edge detection on pins.
     * @details     Disables edge detection on pins to trigger the interrupt
     *                  when a logical change event is detected.
     * @param[in]   disablePins_p       Disable interrupt pins. Multiple pins
     *                                      can be disabled at the same time by
     *                                      using bitwise-OR operations.
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
    bool_t disablePins(
            const Pin disablePins_p
    );

    /**
     * @brief       Enables edge detection on pins.
     * @details     Configure pins that trigger the interrupt when a logical
     *                  change event is detected.
     * @param[in]   enablePins_p        Enable interrupt pins. Multiple pins can
     *                                      be enabled at the same time by using
     *                                      bitwise-OR operations.
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
    bool_t enablePins(
            const Pin enablePins_p
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
     * @brief       Initializes the Pcint2 module.
     * @details     Initializes the PCINT2 module. The function also enables the
     *                  pins that trigger the interrupt. The default parameter
     *                  has no pins enabled.
     * @param[in]   enablePins_p        Enable interrupt pins. Multiples pins
     *                                      can be enabled at the same time by
     *                                      using bitwise-OR operations.
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
            const Pin enablePins_p = (Pcint2::Pin)0
    );

    /**
     * @brief       Sets the @c PCINT2 pin operation mode.
     * @details     This function sets the @c PCINT2 GPIO pin operation mode to
     *                  the given @a mode_p.
     * @param[in]   pinList_p           List of pins to be configured. Multiple
     *                                      pins can be configured at the same
     *                                      time by using bitwise-OR operations.
     * @param[in]   pinMode_p           @ref Pcint2::PinMode operation mode.
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
    bool_t setPinMode(
            const Pin pinList_p,
            const PinMode pinMode_p
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

    //     ////////////////////   CONFIGURATION     /////////////////////     //

    Pin             _enabledPins;               //!< List of enabled pins.

protected:
    // NONE

}; // class Pcint2

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Pcint2::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Pcint2::activateInterrupt(void)
{
    setBit(PCICR, PCINT2);
    return;
}

void inlined Pcint2::clearInterruptRequest(void)
{
    setBit(PCIFR, PCIF2);
    return;
}

void inlined Pcint2::deactivateInterrupt(void)
{
    clrBit(PCICR, PCINT2);
    return;
}

//     //////////////////     OPERATOR OVERLOADING     //////////////////     //

Pcint2::Pin inlined operator|(Pcint2::Pin a, Pcint2::Pin b)
{
    return static_cast<Pcint2::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Pcint2::Pin inlined &operator|=(Pcint2::Pin &a, Pcint2::Pin b)
{
    return a = static_cast<Pcint2::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Pcint2::Pin inlined operator&(Pcint2::Pin a, Pcint2::Pin b)
{
    return static_cast<Pcint2::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

Pcint2::Pin inlined &operator&=(Pcint2::Pin &a, Pcint2::Pin b)
{
    return a = static_cast<Pcint2::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             pcint2
 * @brief           Pcint2 peripheral handler object.
 * @details         Pcint2 peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern Pcint2 pcint2;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Pcint2"
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

#endif  // __PCINT2_HPP

// =============================================================================
// End of file (pcint2.hpp)
// =============================================================================
