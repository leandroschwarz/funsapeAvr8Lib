//!
//! \file           pcint2.hpp
//! \brief          External Interrupt PCINT2 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt PCINT2 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __PCINT2_HPP
#define __PCINT2_HPP                    2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __PCINT2_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __PCINT2_HPP
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
//! \brief          PCINT2 interrupt callback function
//! \details        This function is called when the PCINT2 interrupt is
//!                     treated. It is a weak function that can be overwritten
//!                     by user code.
//!
void pcint2InterruptCallback();

// =============================================================================
// Pcint2 Class
// =============================================================================

//!
//! \brief          Pcint2 class
//! \details        Pcint2 class
//!
class Pcint2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////    PCINT2 Trigger Mode     /////////////////     //
    //!
    //! \brief      Trigger Mode Pins enumeration
    //! \details    Trigger Mode Pins associated with PCINT2.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Pin : uint8_t {
        PIN_PCINT16         = (1 << 0), //!< Enables trigger by PCINT16 pin
        PIN_PCINT17         = (1 << 1), //!< Enables trigger by PCINT17 pin
        PIN_PCINT18         = (1 << 2), //!< Enables trigger by PCINT18 pin
        PIN_PCINT19         = (1 << 3), //!< Enables trigger by PCINT19 pin
        PIN_PCINT20         = (1 << 4), //!< Enables trigger by PCINT20 pin
        PIN_PCINT21         = (1 << 5), //!< Enables trigger by PCINT21 pin
        PIN_PCINT22         = (1 << 6), //!< Enables trigger by PCINT22 pin
        PIN_PCINT23         = (1 << 7), //!< Enables trigger by PCINT23 pin
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Pcint2 class constructor
    //! \details    Creates an Pcint2 object
    //!
    Pcint2(
            void
    );

    //!
    //! \brief      Pcint2 class destructor
    //! \details    Destroys an Pcint2 object
    //!
    ~Pcint2(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the PCINT2 module
    //! \details    Initializes the PCINT2 module.
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
}; // class Pcint2

// =============================================================================
// Inlined class functions
// =============================================================================

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

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Pcint2 peripheral handler object
//! \details        Pcint2 peripheral handler object
//!
extern Pcint2 pcint2;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __PCINT2_HPP

// =============================================================================
// END OF FILE
// =============================================================================
