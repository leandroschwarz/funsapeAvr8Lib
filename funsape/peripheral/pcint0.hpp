//!
//! \file           pcint0.hpp
//! \brief          External Interrupt PCINT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt PCINT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __PCINT0_HPP
#define __PCINT0_HPP                    2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __PCINT0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __PCINT0_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

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

//!
//! \brief          PCINT0 interrupt callback function
//! \details        This function is called when the PCINT0 interrupt is
//!                     treated. It is a weak function that can be overwritten
//!                     by user code.
//!
void pcint0InterruptCallback();

// =============================================================================
// Pcint0 Class
// =============================================================================

//!
//! \brief          Pcint0 class
//! \details        Pcint0 class
//!
class Pcint0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////    PCINT0 Trigger Mode     /////////////////     //
    //!
    //! \brief      Trigger Mode Pins enumeration
    //! \details    Trigger Mode Pins associated with PCINT0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Pin : uint8_t {
        PIN_PCINT0          = (1 << 0), //!< Enables trigger by PCINT0 pin
        PIN_PCINT1          = (1 << 1), //!< Enables trigger by PCINT1 pin
        PIN_PCINT2          = (1 << 2), //!< Enables trigger by PCINT2 pin
        PIN_PCINT3          = (1 << 3), //!< Enables trigger by PCINT3 pin
        PIN_PCINT4          = (1 << 4), //!< Enables trigger by PCINT4 pin
        PIN_PCINT5          = (1 << 5), //!< Enables trigger by PCINT5 pin
        PIN_PCINT6          = (1 << 6), //!< Enables trigger by PCINT6 pin
        PIN_PCINT7          = (1 << 7), //!< Enables trigger by PCINT7 pin
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Pcint0 class constructor
    //! \details    Creates an Pcint0 object
    //!
    Pcint0(
            void
    );

    //!
    //! \brief      Pcint0 class destructor
    //! \details    Destroys an Pcint0 object
    //!
    ~Pcint0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the PCINT0 module
    //! \details    Initializes the PCINT0 module.
    //! \param      enablePins_p        Enable interrupt pins
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            Pin enablePins_p
    );

    //!
    //! \brief      Enables interrupt pins
    //! \details    Configures the trigger sense mode.
    //! \param      enablePins_p        Enable interrupt pins
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t enablePins(
            Pin enablePins_p
    );

    //!
    //! \brief      Disables interrupt pins
    //! \details    Configures the trigger sense mode.
    //! \param      disablePins_p       Disable interrupt pins
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t disablePins(
            Pin disablePins_p
    );
    //     /////////////////     CONTROL AND STATUS    //////////////////     //

    //!
    //! \brief      Returns the last error
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation
    //!
    Error           getLastError(
            void
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    //!
    //! \brief      Activates interrupt
    //! \details    Activates interrupt.
    //!
    void inlined activateInterrupt(
            void
    );

    //!
    //! \brief      Clears interrupt flag
    //! \details    Clears interrupt flag.
    //!
    void inlined clearInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates interrupt
    //! \details    Deactivates interrupt.
    //!
    void inlined deactivateInterrupt(
            void
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    Pin             _enabledPins;
    Error           _lastError;
}; // class Pcint0

// =============================================================================
// Inlined class functions
// =============================================================================

//     ////////////////////////    INTERRUPT     ////////////////////////     //
void inlined Pcint0::activateInterrupt(void)
{
    setBit(PCICR, PCINT0);
    return;
}

void inlined Pcint0::clearInterruptRequest(void)
{
    setBit(PCIFR, PCIF0);
    return;
}

void inlined Pcint0::deactivateInterrupt(void)
{
    clrBit(PCICR, PCINT0);
    return;
}

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Pcint0 peripheral handler object
//! \details        Pcint0 peripheral handler object
//!
extern Pcint0 pcint0;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __PCINT0_HPP

// =============================================================================
// END OF FILE
// =============================================================================
