/**
 *******************************************************************************
 * @file            int1.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           External Interrupt INT1 peripheral control.
 * @details         This file provides peripheral control for the INT1
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

#ifndef __INT1_HPP
#define __INT1_HPP                      2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [int1.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __INT1_HPP
#   error [int1.hpp] Error 2 - Build mismatch between file (int1.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [int1.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __INT1_HPP
#   error [int1.hpp] Error 5 - Build mismatch between file (int1.hpp) and library dependency (debug.hpp)!
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
// Doxygen: Start subgroup "Peripherals/Int1"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Int1
 * @brief           External Interrupt 1 (INT1) controller module.
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
 * @brief           INT1 interrupt callback function.
 * @details         This function is called when the INT1 interrupt is treated.
 *                      It is a weak function that can be overwritten by user
 *                      code.
*/
void int1InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Int1 class.
 * @details         This class manages the External Interrupt 1 (INT1)
 *                      peripheral.
 * @attention       The @ref int1 instance of this class is already defined as
 *                      a global object. Therefore, there is not necessary,
 *                      neither recommended to create another object of this
 *                      class.
*/
class Int1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    /**
     * @enum        SenseMode
     * @brief       Sense Trigger enumeration.
     * @details     Sense Trigger events associated with INT1.
     * @warning     The value associate with the symbolic names may change
     *                  between builds and might not reflect the register/bits
     *                  real values. In order to ensure compatibility between
     *                  builds, always refer to the SYMBOLIC NAME, instead of
     *                  its VALUE.
    */
    enum class SenseMode : uint8_t {
        LOW_LEVEL           = 0,    //!< Trigger interrupt continuously while pin is in logic low level.
        BOTH_EDGES          = 1,    //!< Trigger interrupt at both edges.
        FALLING_EDGE        = 2,    //!< Trigger interrupt at falling edge.
        RISING_EDGE         = 3,    //!< Trigger interrupt at rising edge.
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
     * @brief       Int1 class constructor.
     * @details     Creates an Int1 object. The object is loaded with the
     *                  default register values: @ref SenseMode::LOW_LEVEL. The
     *                  object still must be initialized before use.
     * @see         init(const SenseMode senseMode_p).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Int1(
            void
    );

    /**
     * @brief       Int1 class destructor.
     * @details     Destroys an Int1 object.
    */
    ~Int1(
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
     * @brief       Initializes the Int1 module.
     * @details     Initializes the Int1 module. The function also configures
     *                  the sensibility mode for trigger the interrupt given by
     *                  @a senseMode_p. The default parameter is
     *                  @ref SenseMode::LOW_LEVEL.
     * @param[in]   senseMode_p         Trigger sense mode.
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
            const SenseMode senseMode_p = SenseMode::LOW_LEVEL
    );

    /**
     * @brief       Sets the @c INT1 pin operation mode.
     * @details     This function sets the @c INT1 GPIO pin operation mode to
     *                  the given @a mode_p.
     * @param[in]   mode_p              @ref Int1::PinMode operation mode.
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
            const PinMode mode_p
    );

    /**
     * @brief       Sets the trigger sense mode.
     * @details     This function sets the the sensibility mode for trigger the
     *                  interrupt given by @a senseMode_p.
     * @param[in]   senseMode_p         @ref Int1::PinMode operation mode.
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
    bool_t setSenseMode(
            const SenseMode senseMode_p
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

    SenseMode       _senseMode;                 //!< Sense mode trigger.

protected:
    // NONE

}; // class Int1

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Int1::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Int1::activateInterrupt(void)
{
    setBit(EIMSK, INT1);
    return;
}

void inlined Int1::clearInterruptRequest(void)
{
    setBit(EIFR, INTF1);
    return;
}

void inlined Int1::deactivateInterrupt(void)
{
    clrBit(EIMSK, INT1);
    return;
}

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

/**
 * @var             int1
 * @brief           Int1 peripheral handler object.
 * @details         Int1 peripheral handler object. Use this object to handle
 *                      the peripheral.
 * @warning         DO NOT create another instance of the class, since this
 *                      could lead to information mismatch between instances and
 *                      the peripheral registers.
*/
extern Int1 int1;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Int1"
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

#endif  // __INT1_HPP

// =============================================================================
// End of file (int1.hpp)
// =============================================================================
