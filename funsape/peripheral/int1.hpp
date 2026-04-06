//!
//! ****************************************************************************
//! @file           int1.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          External Interrupt INT1 peripheral control.
//! @details        This file provides peripheral control for the INT1
//!                     peripheral control for the FunSAPE++ AVR8 Library.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @bug            No bugs detected yet.
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

#ifndef __INT1_HPP
#define __INT1_HPP                      2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [int1.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __INT1_HPP
#   error [int1.hpp] Error 2 - Build mismatch between file (int1.hpp) and global definitions file!
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

// =============================================================================
// Checks peripheral existance
// =============================================================================

#if !defined(MCU_INT1_PERIPHERAL_EXISTS)
#   error [int1.hpp] Error X - Peripheral INT1 is not avalilable in selected device!
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Peripherals
//! @brief          Microcontroller peripherals.
//! @{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Int1" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Int1
//! @brief          External Interrupt 1 (INT1) controller module.
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

//!
//! @brief          INT1 interrupt callback function.
//! @details        This function is called when the INT1 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void int1InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! @brief          Int1 class
//! @details        This class manages the External Interrupt 1 (INT1)
//!                     peripheral.
//! @attention      The @ref int1 instance of this class is already defined as
//!                     a singleton global object.
//!
class Int1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //!
    //! @enum       SenseMode
    //! @brief      Sense Trigger enumeration.
    //! @details    Sense Trigger events associated with INT1.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class SenseMode : uint8_t {
        LOW_LEVEL           = 0,    //!< Trigger interrupt continuously while pin is in logic low level.
        BOTH_EDGES          = 1,    //!< Trigger interrupt at both edges.
        FALLING_EDGE        = 2,    //!< Trigger interrupt at falling edge.
        RISING_EDGE         = 3,    //!< Trigger interrupt at rising edge.
    };

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Constructors ------------------------------------------------------------

public:
    //!
    //! @brief      Int1 class destructor.
    //! @details    Destroys an Int1 object.
    //!
    ~Int1(
            void
    );

private:
    //!
    //! @brief      Int1 class constructor.
    //! @details    Creates the single Int1 object. The object is loaded with
    //!                 the default register values:
    //!                 @ref Int1::SenseMode::LOW_LEVEL. The object still must
    //!                 be initialized before use.
    //! @see        init(const Int1::SenseMode senseMode_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                           |
    //! |:-----------------|:----------------------------------|
    //! | @ref Error::NONE | Success. No errors were detected. |
    //!
    Int1(
            void
    );

    //!
    //! @brief      Copy constructor (deleted).
    //! @details    Deleted to prevent cloning the Singleton instance.
    //!
    Int1(
            const Int1 &
    ) = delete;

    //!
    //! @brief      Copy assignment operator (deleted).
    //! @details    Deleted to prevent assignment of the Singleton instance.
    //!
    Int1 &operator=(
            const Int1 &
    ) = delete;

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
    //     ///////////////////    SINGLETON ACCESS    ///////////////////     //

    //!
    //! @brief      Returns the Singleton instance.
    //! @details    Provides global access to the single instance of the Int1
    //!                 class. This method is tightly inlined to ensure
    //!                 zero-overhead during execution.
    //! @return     Reference to the single Int1 instance.
    //!
    static inlined Int1 &getInstance(
            void
    );

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
    //! @brief      Initializes the Int1 module.
    //! @details    Initializes the Int1 module. The function also configures
    //!                 the sensibility mode for trigger the interrupt given by
    //!                 @a senseMode_p. The default parameter is
    //!                 @ref Int1::SenseMode::LOW_LEVEL.
    //! @param[in]  senseMode_p         Trigger sense mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code                    | Meaning                              |
    //! |:------------------------------|:-------------------------------------|
    //! | @ref Error::NONE              | Success. No erros were detected.     |
    //!
    bool_t init(
            const Int1::SenseMode senseMode_p = Int1::SenseMode::LOW_LEVEL
    );

    //!
    //! @brief      Sets the @c INT1 pin operation mode.
    //! @details    This function sets the @c INT1 GPIO pin operation mode to
    //!                 the given @a mode_p.
    //! @param[in]  mode_p              @ref PinMode operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setPinMode(
            const PinMode mode_p
    );

    //!
    //! @brief      Sets the trigger sense mode.
    //! @details    This function sets the the sensibility mode for trigger the
    //!                 interrupt given by @a senseMode_p.
    //! @param[in]  senseMode_p         Trigger sense mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling @ref getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setSenseMode(
            const Int1::SenseMode senseMode_p
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    //!
    //! @brief      Activates interrupt.
    //! @details    Activates interrupt. If an interrupt request is pending, an
    //!                 interrupt will be triggered when activated. In most
    //!                 applications, it is recommended to ignore an old
    //!                 interrupt request prior to activate the interrupt. This
    //!                 can be done by calling
    //!                 @ref Int1::clearInterruptRequest() immediately before
    //!                 activating the interrupt.
    //!
    void inlined activateInterrupt(
            void
    ) const;

    //!
    //! @brief      Clears interrupt flag.
    //! @details    Clears interrupt flag, dismissing any pending interrupt
    //!                 request.
    //!
    void inlined clearInterruptRequest(
            void
    ) const;

    //!
    //! @brief      Deactivates interrupt.
    //! @details    Deactivates interrupt. This function does not clears any
    //!                 pending interrupt request.
    //!
    void inlined deactivateInterrupt(
            void
    ) const;

private:
    // NONE

protected:
    // NONE

// -------------------------------------------------------------------------
// Properties --------------------------------------------------------------

private:
    //     /////////////////    SINGLETON INSTANCE     //////////////////     //
    static Int1     _instance;                  //|< Static private instance

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //
    Int1::SenseMode _senseMode;                 //!< Sense mode trigger.

protected:
    // NONE

}; // class Int1

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////////    SINGLETON ACCESS    /////////////////////     //

Int1 inlined &Int1::getInstance(void)
{
    return Int1::_instance;
}

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined Int1::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //


void inlined Int1::activateInterrupt(void) const
{
    setBit(MCU_INT1_ENABLE_REG, MCU_INT1_ENABLE_BIT_OFFSET);
    return;
}

void inlined Int1::clearInterruptRequest(void) const
{
    setBit(MCU_INT1_FLAG_REG, MCU_INT1_FLAG_BIT_POS);
    return;
}

void inlined Int1::deactivateInterrupt(void) const
{
    clrBit(MCU_INT1_ENABLE_REG, MCU_INT1_ENABLE_BIT_OFFSET);
    return;
}

//!
//! @endcond
//!

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Singleton Access Macro
// =============================================================================

//!
//! @def            int1
//! @brief          Int1 peripheral handler macro.
//! @details        Macro to access the single instance of the Int1 class.
//!                     Use this macro to handle the peripheral. It replaces
//!                     the old external object instantiation to ensure
//!                     architectural safety and zero-overhead execution while
//!                     keeping the traditional lowercase syntax.
//!
#define int1 (Int1::getInstance())

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Int1" in "Peripherals"
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

#endif  // __INT1_HPP

// =============================================================================
// End of file (int1.hpp)
// =============================================================================
