//!
//! \file           pcint1.hpp
//! \brief          External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __PCINT1_HPP
#define __PCINT1_HPP                    2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __PCINT1_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __PCINT1_HPP
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
//! \brief          PCINT1 interrupt callback function
//! \details        This function is called when the PCINT1 interrupt is
//!                     treated. It is a weak function that can be overwritten
//!                     by user code.
//!
void pcint1InterruptCallback();

// =============================================================================
// Pcint1 Class
// =============================================================================

//!
//! \brief          Pcint1 class
//! \details        Pcint1 class
//!
class Pcint1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////    PCINT1 Trigger Mode     /////////////////     //
    //!
    //! \brief      Trigger Mode Pins enumeration
    //! \details    Trigger Mode Pins associated with PCINT1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Pin : uint8_t {
        PIN_PCINT8          = (1 << 0), //!< Enables trigger by PCINT8 pin
        PIN_PCINT9          = (1 << 1), //!< Enables trigger by PCINT9 pin
        PIN_PCINT10         = (1 << 2), //!< Enables trigger by PCINT10 pin
        PIN_PCINT11         = (1 << 3), //!< Enables trigger by PCINT11 pin
        PIN_PCINT12         = (1 << 4), //!< Enables trigger by PCINT12 pin
        PIN_PCINT13         = (1 << 5), //!< Enables trigger by PCINT13 pin
        PIN_PCINT14         = (1 << 6), //!< Enables trigger by PCINT14 pin
        // PIN_PCINT15         = (1 << 7), //!< Enables trigger by PCINT15 pin
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Pcint1 class constructor
    //! \details    Creates an Pcint1 object
    //!
    Pcint1(
            void
    );

    //!
    //! \brief      Pcint1 class destructor
    //! \details    Destroys an Pcint1 object
    //!
    ~Pcint1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the PCINT1 module
    //! \details    Initializes the PCINT1 module.
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
}; // class Pcint1

// =============================================================================
// Inlined class functions
// =============================================================================

//     ////////////////////////    INTERRUPT     ////////////////////////     //
void inlined Pcint1::activateInterrupt(void)
{
    setBit(PCICR, PCINT1);
    return;
}

void inlined Pcint1::clearInterruptRequest(void)
{
    setBit(PCIFR, PCIF1);
    return;
}

void inlined Pcint1::deactivateInterrupt(void)
{
    clrBit(PCICR, PCINT1);
    return;
}

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Pcint1 peripheral handler object
//! \details        Pcint1 peripheral handler object
//!
extern Pcint1 pcint1;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __PCINT1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
