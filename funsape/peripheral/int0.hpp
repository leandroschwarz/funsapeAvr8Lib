//!
//! ****************************************************************************
//! @file           int0.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          External Interrupt INT0 peripheral control.
//! @details        This file provides peripheral control for the INT0
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

#ifndef __INT0_HPP
#define __INT0_HPP                      2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [int0.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __INT0_HPP
#   error [int0.hpp] Error 2 - Build mismatch between file (int0.hpp) and global definitions file!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [int0.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __INT0_HPP
#   error [int0.hpp] Error 5 - Build mismatch between file (int0.hpp) and library dependency (debug.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// =============================================================================
// Checks peripheral existance
// =============================================================================

#if !defined(MCU_INT0_PERIPHERAL_EXISTS)
#   error [int0.hpp] Error X - Peripheral INT0 is not avalilable in selected device!
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
// Doxygen: Start subgroup "Int0" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Int0
//! @brief          External Interrupt 0 (INT0) controller module.
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
//! @brief          INT0 interrupt callback function.
//! @details        This function is called when the INT0 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void int0InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! @brief          Int0 class
//! @details        This class manages the External Interrupt 0 (INT0)
//!                     peripheral.
//! @attention      The @ref int0 instance of this class is already defined as
//!                     a singleton global object.
//!
class Int0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //!
    //! @enum       SenseMode
    //! @brief      Sense Trigger enumeration.
    //! @details    Sense Trigger events associated with INT0.
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
    //! @brief      Int0 class destructor.
    //! @details    Destroys an Int0 object.
    //!
    ~Int0(
            void
    );

private:
    //!
    //! @brief      Int0 class constructor.
    //! @details    Creates the single Int0 object. The object is loaded with
    //!                 the default register values:
    //!                 @ref Int0::SenseMode::LOW_LEVEL. The object still must
    //!                 be initialized before use.
    //! @see        init(const Int0::SenseMode senseMode_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                           |
    //! |:-----------------|:----------------------------------|
    //! | @ref Error::NONE | Success. No errors were detected. |
    //!
    Int0(
            void
    );

    //!
    //! @brief      Copy constructor (deleted).
    //! @details    Deleted to prevent cloning the Singleton instance.
    //!
    Int0(
            const Int0 &
    ) = delete;

    //!
    //! @brief      Copy assignment operator (deleted).
    //! @details    Deleted to prevent assignment of the Singleton instance.
    //!
    Int0 &operator=(
            const Int0 &
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
    //! @details    Provides global access to the single instance of the Int0
    //!                 class. This method is tightly inlined to ensure
    //!                 zero-overhead during execution.
    //! @return     Reference to the single Int0 instance.
    //!
    static inlined Int0 &getInstance(
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
    //! @brief      Initializes the Int0 module.
    //! @details    Initializes the Int0 module. The function also configures
    //!                 the sensibility mode for trigger the interrupt given by
    //!                 @a senseMode_p. The default parameter is
    //!                 @ref Int0::SenseMode::LOW_LEVEL.
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
            const Int0::SenseMode senseMode_p = Int0::SenseMode::LOW_LEVEL
    );

    //!
    //! @brief      Sets the @c INT0 pin operation mode.
    //! @details    This function sets the @c INT0 GPIO pin operation mode to
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
            const Int0::SenseMode senseMode_p
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    //!
    //! @brief      Activates interrupt.
    //! @details    Activates interrupt. If an interrupt request is pending, an
    //!                 interrupt will be triggered when activated. In most
    //!                 applications, it is recommended to ignore an old
    //!                 interrupt request prior to activate the interrupt. This
    //!                 can be done by calling
    //!                 @ref Int0::clearInterruptRequest() immediately before
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
    static Int0     _instance;                  //|< Static private instance

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //
    Int0::SenseMode _senseMode;                 //!< Sense mode trigger.

protected:
    // NONE

}; // class Int0

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////////    SINGLETON ACCESS    /////////////////////     //

Int0 inlined &Int0::getInstance(void)
{
    return Int0::_instance;
}

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Int0::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Int0::activateInterrupt(void) const
{
    setBit(MCU_INT0_ENABLE_REG, MCU_INT0_ENABLE_BIT_OFFSET);
    return;
}

void inlined Int0::clearInterruptRequest(void) const
{
    setBit(MCU_INT0_FLAG_REG, MCU_INT0_FLAG_BIT_POS);
    return;
}

void inlined Int0::deactivateInterrupt(void) const
{
    clrBit(MCU_INT0_ENABLE_REG, MCU_INT0_ENABLE_BIT_OFFSET);
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
//! @def            int0
//! @brief          Int0 peripheral handler macro.
//! @details        Macro to access the single instance of the Int0 class.
//!                     Use this macro to handle the peripheral. It replaces
//!                     the old external object instantiation to ensure
//!                     architectural safety and zero-overhead execution while
//!                     keeping the traditional lowercase syntax.
//!
#define int0 (Int0::getInstance())

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Int0" in "Peripherals"
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

#endif  // __INT0_HPP

// =============================================================================
// End of file (int0.hpp)
// =============================================================================
