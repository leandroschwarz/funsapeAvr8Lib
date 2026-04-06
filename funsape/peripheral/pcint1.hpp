//!
//! ****************************************************************************
//! @file           pcint1.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Pin Change Interrupt 1 PCINT1 peripheral control.
//! @details        This file provides peripheral control for the PCINT1
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

#ifndef __PCINT1_HPP
#define __PCINT1_HPP                    2604

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [pcint1.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __PCINT1_HPP
#   error [pcint1.hpp] Error 2 - Build mismatch between file (pcint1.hpp) and global definitions file!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [pcint1.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __PCINT1_HPP
#   error [pcint1.hpp] Error 5 - Build mismatch between file (pcint1.hpp) and library dependency (debug.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// =============================================================================
// Checks peripheral existance
// =============================================================================

#if !defined(MCU_PCINT1_PERIPHERAL_EXISTS)
#   error [pcint1.hpp] Error X - Peripheral PCINT1 is not avalilable in selected device!
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
// Doxygen: Start subgroup "Pcint1" in "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Pcint1
//! @brief          Pin Change Interrupt 1 (PCINT1) controller module.
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
//! @brief          PCINT1 interrupt callback function.
//! @details        This function is called when the PCINT1 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void pcint1InterruptCallback(void);

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! @brief          Pcint1 class
//! @details        This class manages the Pin Change Interrupt 1 (PCINT1)
//!                     peripheral.
//! @attention      The @ref pcint1 instance of this class is already defined as
//!                     a singleton global object.
//!
class Pcint1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    //!
    //! @enum       Pin
    //! @brief      Trigger Mode Pins enumeration.
    //! @details    Trigger Mode Pins associated with PCINT1.
    //! @warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 its VALUE.
    //!
    enum class Pin : uint8_t {
#if defined(MCU_PCINT1_PIN_8_EXISTS)
        PIN_PCINT8          = (1 << 0), //!< Enables trigger by PCINT8 pin.
#endif
#if defined(MCU_PCINT1_PIN_9_EXISTS)
        PIN_PCINT9          = (1 << 1), //!< Enables trigger by PCINT9 pin.
#endif
#if defined(MCU_PCINT1_PIN_10_EXISTS)
        PIN_PCINT10         = (1 << 2), //!< Enables trigger by PCINT10 pin.
#endif
#if defined(MCU_PCINT1_PIN_11_EXISTS)
        PIN_PCINT11         = (1 << 3), //!< Enables trigger by PCINT11 pin.
#endif
#if defined(MCU_PCINT1_PIN_12_EXISTS)
        PIN_PCINT12         = (1 << 4), //!< Enables trigger by PCINT12 pin.
#endif
#if defined(MCU_PCINT1_PIN_13_EXISTS)
        PIN_PCINT13         = (1 << 5), //!< Enables trigger by PCINT13 pin.
#endif
#if defined(MCU_PCINT1_PIN_14_EXISTS)
        PIN_PCINT14         = (1 << 6), //!< Enables trigger by PCINT14 pin.
#endif
#if defined(MCU_PCINT1_PIN_15_EXISTS)
        PIN_PCINT15         = (1 << 7), //!< Enables trigger by PCINT15 pin.
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
    //! @brief      Pcint1 class destructor.
    //! @details    Destroys a Pcint1 object.
    //!
    ~Pcint1(
            void
    );

private:
    //!
    //! @brief      Pcint1 class constructor.
    //! @details    Creates a Pcint1 object. The object is loaded with the
    //!                 default register values (no pins enabled). The object
    //!                 still must be initialized before use
    //! @see        init(const Pcint1::Pin enablePins_p).
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                           |
    //! |: ----------------|: ---------------------------------|
    //! | @ref Error::NONE | Success. No errors were detected. |
    //!
    Pcint1(
            void
    );

    //!
    //! @brief      Copy constructor (deleted).
    //! @details    Deleted to prevent cloning the Singleton instance.
    //!
    Pcint1(
            const Pcint1 &
    ) = delete;

    //!
    //! @brief      Copy assignment operator (deleted).
    //! @details    Deleted to prevent assignment of the Singleton instance.
    //!
    Pcint1 &operator=(
            const Pcint1 &
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
    //! @details    Provides global access to the single instance of the Pcint1
    //!                 class. This method is tightly inlined to ensure
    //!                 zero-overhead during execution.
    //! @return     Reference to the single Pcint1 instance.
    //!
    static inlined Pcint1 &getInstance(
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
    //!                                 @ref Pcint1::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t disablePins(
            const Pcint1::Pin disablePins_p
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
    //!                                     @ref Pcint1::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t enablePins(
            const Pcint1::Pin enablePins_p
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
    //! @brief      Initializes the Pcint1 module.
    //! @details    Initializes the PCINT1 module. The function also enables the
    //!                 pins that trigger the interrupt. The default parameter
    //!                 has no pins enabled.
    //! @param[in]  enablePins_p        Enable interrupt pins. Multiples pins
    //!                                     can be enabled at the same time by
    //!                                     using bitwise-OR (|) operations.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Pcint1::getLastError().
    //! @par Error codes:
    //!
    //! | Error code                    | Meaning                              |
    //! |:------------------------------|:-------------------------------------|
    //! | @ref Error::NONE              | Success. No erros were detected.     |
    //!
    bool_t init(
            const Pcint1::Pin enablePins_p = (Pcint1::Pin)0
    );

    //!
    //! @brief      Sets the @c PCINT1 pin operation mode.
    //! @details    This function sets the @c PCINT1 GPIO pin operation mode to
    //!                 the given @a mode_p.
    //! @param[in]  pinList_p           List of pins to be configured. Multiple
    //!                                     pins can be configured at the same
    //!                                     time by using bitwise-OR operations.
    //! @param[in]  mode_p              @ref Pcint1::PinMode operation mode.
    //! @retval     true                if success.
    //! @retval     false               if an error occurred. Retrieve the error
    //!                                     by calling
    //!                                     @ref Pcint1::getLastError().
    //! @par Error codes:
    //!
    //! | Error code       | Meaning                          |
    //! |:-----------------|:---------------------------------|
    //! | @ref Error::NONE | Success. No erros were detected. |
    //!
    bool_t setPinMode(
            const Pcint1::Pin pinList_p,
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
    //!                 @ref Pcint1::clearInterruptRequest() immediately before
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
    static Pcint1   _instance;                  //|< Static private instance

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isInitialized      : 1;    //!< Initialization flag.
    Error           _lastError;                 //!< Last error.

    //     ////////////////////   CONFIGURATION     /////////////////////     //
    Pcint1::Pin     _enabledPins;               //!< Sense mode trigger.

protected:
    // NONE

}; // class Pcint1

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! @cond
//!

//     /////////////////////    SINGLETON ACCESS    /////////////////////     //

Pcint1 inlined &Pcint1::getInstance(void)
{
    return Pcint1::_instance;
}

//     /////////////////     CONTROL AND STATUS     /////////////////     //

Error inlined Pcint1::getLastError(void) const
{
    // Returns last error
    return this->_lastError;
}

//     ////////////////////////    INTERRUPT     ////////////////////////     //

void inlined Pcint1::activateInterrupt(void) const
{
    setBit(MCU_PCINT1_ENABLE_REG, MCU_PCINT1_ENABLE_BIT_POS);
    return;
}

void inlined Pcint1::clearInterruptRequest(void) const
{
    setBit(MCU_PCINT1_FLAG_REG, MCU_PCINT1_FLAG_BIT);
    return;
}

void inlined Pcint1::deactivateInterrupt(void) const
{
    clrBit(MCU_PCINT1_ENABLE_REG, MCU_PCINT1_ENABLE_BIT_POS);
    return;
}

//     //////////////////     OPERATOR OVERLOADING     //////////////////     //

Pcint1::Pin inlined operator|(Pcint1::Pin a, Pcint1::Pin b)
{
    return static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Pcint1::Pin inlined &operator|=(Pcint1::Pin &a, Pcint1::Pin b)
{
    return a = static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Pcint1::Pin inlined operator&(Pcint1::Pin a, Pcint1::Pin b)
{
    return static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

Pcint1::Pin inlined &operator&=(Pcint1::Pin &a, Pcint1::Pin b)
{
    return a = static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
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
//! @def            pcint1
//! @brief          Pcint1 peripheral handler macro.
//! @details        Macro to access the single instance of the Pcint1 class.
//!                     Use this macro to handle the peripheral. It replaces
//!                     the old external object instantiation to ensure
//!                     architectural safety and zero-overhead execution while
//!                     keeping the traditional lowercase syntax.
//!
#define pcint1 (Pcint1::getInstance())

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Pcint1" in "Peripherals"
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

#endif  // __PCINT1_HPP

// =============================================================================
// End of file (pcint1.hpp)
// =============================================================================
