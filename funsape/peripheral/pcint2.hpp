//!
//! ****************************************************************************
//! @file           pcint2.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Pin Change Interrupt 2 PCINT2 peripheral control.
//! @details        This file provides peripheral control for the PCINT2
//!                     peripheral control for the FunSAPE++ AVR8 Library.
//! @date           2026-04-03
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

#ifndef __PCINT2_HPP
#define __PCINT2_HPP                    2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [pcint2.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __PCINT2_HPP
#   error [pcint2.hpp] Error 2 - Build mismatch between file (pcint2.hpp) and global definitions file!
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

// =============================================================================
// Checks peripheral existance
// =============================================================================

#if !defined(MCU_PCINT2_PERIPHERAL_EXISTS)
#   error [pcint2.hpp] Error X - Peripheral PCINT2 is not avalilable in selected device!
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
// Doxygen: Start subgroup "Pcint2" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Pcint2
//! @brief          Pin Change Interrupt 2 (PCINT2) controller module.
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
//! @brief          PCINT2 interrupt callback function.
//! @details        This function is called when the PCINT2 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void pcint2InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! @brief          Pcint2 class
//! @details        This class manages the Pin Change Interrupt 2 (PCINT2)
//!                     peripheral.
//! @attention      The @ref pcint2 instance of this class is already defined as
//!                     a singleton global object.
//!
class Pcint2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //!
    //! @enum       Pin
    //! @brief      Trigger Mode Pins enumeration.
    //! @details    Trigger Mode Pins associated with PCINT2.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class Pin : uint8_t {
#if defined(MCU_PCINT2_PIN_16_EXISTS)
        PIN_PCINT16         = (1 << 0), //!< Enables trigger by PCINT16 pin.
#endif
#if defined(MCU_PCINT2_PIN_17_EXISTS)
        PIN_PCINT17         = (1 << 1), //!< Enables trigger by PCINT17 pin.
#endif
#if defined(MCU_PCINT2_PIN_18_EXISTS)
        PIN_PCINT18         = (1 << 2), //!< Enables trigger by PCINT18 pin.
#endif
#if defined(MCU_PCINT2_PIN_19_EXISTS)
        PIN_PCINT19         = (1 << 3), //!< Enables trigger by PCINT19 pin.
#endif
#if defined(MCU_PCINT2_PIN_20_EXISTS)
        PIN_PCINT20         = (1 << 4), //!< Enables trigger by PCINT20 pin.
#endif
#if defined(MCU_PCINT2_PIN_21_EXISTS)
        PIN_PCINT21         = (1 << 5), //!< Enables trigger by PCINT21 pin.
#endif
#if defined(MCU_PCINT2_PIN_22_EXISTS)
        PIN_PCINT22         = (1 << 6), //!< Enables trigger by PCINT22 pin.
#endif
#if defined(MCU_PCINT2_PIN_23_EXISTS)
        PIN_PCINT23         = (1 << 7), //!< Enables trigger by PCINT23 pin.
#endif
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    //!
    //! @brief      Pcint2 class destructor.
    //! @details    Destroys a Pcint2 object.
    //!
    ~Pcint2(
            void
    );

private:
    //!
    //! @brief      Pcint2 class constructor.
    //! @details    Creates a Pcint2 object. The object is loaded with the
    //!                 default register values (no pins enabled). The object
    //!                 still must be initialized before use
    //! @see        init(const Pcint2::Pin enablePins_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                           |
    //! |: ----------------|: ---------------------------------|
    //! | @ref Error::NONE | Success. No errors were detected. |
    //!
    Pcint2(
            void
    );

    //!
    //! @brief      Copy constructor (deleted).
    //! @details    Deleted to prevent cloning the Singleton instance.
    //!
    Pcint2(
            const Pcint2 &
    ) = delete;

    //!
    //! @brief      Copy assignment operator (deleted).
    //! @details    Deleted to prevent assignment of the Singleton instance.
    //!
    Pcint2 &operator=(
            const Pcint2 &
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
    //! @details    Provides global access to the single instance of the Pcint2
    //!                 class. This method is tightly inlined to ensure
    //!                 zero-overhead during execution.
    //! @return     Reference to the single Pcint2 instance.
    //!
    static inlined Pcint2 &getInstance(
            void
    );

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    //!
    //! @brief      Disables edge detection on pins.
    //! @details    Disables edge detection on pins to trigger the interrupt
    //!                 when a logical change event is detected.
    //! @param[in]  disablePins_p       Disable interrupt pins. Multiple pins
    //!                                     can be disabled at the same time by
    //!                                     using bitwise-OR (|) operations.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                 @ref Pcint2::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t disablePins(
            const Pcint2::Pin disablePins_p
    );

    //!
    //! @brief      Enables edge detection on pins.
    //! @details    Configure pins that trigger the interrupt when a logical
    //!                 change event is detected.
    //! @param[in]  enablePins_p        Enable interrupt pins. Multiple pins can
    //!                                     be enabled at the same time by using
    //!                                     bitwise-OR (|) operations.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Pcint2::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t enablePins(
            const Pcint2::Pin enablePins_p
    );

    //!
    //! @brief      Returns the last error.
    //! @details    Returns the last error.
    //! @return     @ref Error          Error status of the last operation.
    //!
    Error inlined getLastError(
            void
    ) const;

    //!
    //! @brief      Initializes the Pcint2 module.
    //! @details    Initializes the PCINT2 module. The function also enables the
    //!                 pins that trigger the interrupt. The default parameter
    //!                 has no pins enabled.
    //! @param[in]  enablePins_p        Enable interrupt pins. Multiples pins
    //!                                     can be enabled at the same time by
    //!                                     using bitwise-OR (|) operations.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Pcint2::getLastError().
    //! @par Error codes:
    //!
    //! | Error code                    | Meaning                              |
    //! |:------------------------------|:-------------------------------------|
    //! | @ref Error::NONE              | Success. No erros were detected.     |
    //!
    bool_t init(
            const Pcint2::Pin enablePins_p = (Pcint2::Pin)0
    );

    //!
    //! @brief      Sets the @c PCINT2 pin operation mode.
    //! @details    This function sets the @c PCINT2 GPIO pin operation mode to
    //!                 the given @a mode_p.
    //! @param[in]  pinList_p           List of pins to be configured. Multiple
    //!                                     pins can be configured at the same
    //!                                     time by using bitwise-OR operations.
    //! @param[in]  mode_p              @ref Pcint2::PinMode operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Pcint2::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setPinMode(
            const Pcint2::Pin pinList_p,
            const PinMode mode_p
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    //!
    //! @brief      Activates interrupt.
    //! @details    Activates interrupt. If an interrupt request is pending, an
    //!                 interrupt will be triggered when activated. In most
    //!                 applications, it is recommended to ignore an old
    //!                 interrupt request prior to activate the interrupt. This
    //!                 can be done by calling
    //!                 @ref Pcint2::clearInterruptRequest() immediately before
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
    static Pcint2   _instance;                  //|< Static private instance

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //
    Pcint2::Pin     _enabledPins;               //!< Sense mode trigger.

protected:
    // NONE

}; // class Pcint2

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////////    SINGLETON ACCESS    /////////////////////     //

Pcint2 inlined &Pcint2::getInstance(void)
{
    return Pcint2::_instance;
}

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined Pcint2::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Pcint2::activateInterrupt(void) const
{
    setBit(MCU_PCINT2_ENABLE_REG, MCU_PCINT2_ENABLE_BIT_POS);
    return;
}

void inlined Pcint2::clearInterruptRequest(void) const
{
    setBit(MCU_PCINT2_FLAG_REG, MCU_PCINT2_FLAG_BIT);
    return;
}

void inlined Pcint2::deactivateInterrupt(void) const
{
    clrBit(MCU_PCINT2_ENABLE_REG, MCU_PCINT2_ENABLE_BIT_POS);
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
//! @def            pcint2
//! @brief          Pcint2 peripheral handler macro.
//! @details        Macro to access the single instance of the Pcint2 class.
//!                     Use this macro to handle the peripheral. It replaces
//!                     the old external object instantiation to ensure
//!                     architectural safety and zero-overhead execution while
//!                     keeping the traditional lowercase syntax.
//!
#define pcint2 (Pcint2::getInstance())

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Pcint2" in "Peripherals"
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

#endif  // __PCINT2_HPP

// =============================================================================
// End of file (pcint2.hpp)
// =============================================================================
