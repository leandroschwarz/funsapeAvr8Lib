//!
//! \file           int0.hpp
//! \brief          External Interrupt INT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-07
//! \version        23.04
//! \copyright      license
//! \details        External Interrupt INT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __INT0_HPP
#define __INT0_HPP                      2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __INT0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __INT0_HPP
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
//! \brief          INT0 interrupt callback function
//! \details        This function is called when the INT0 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void int0InterruptCallback();

// =============================================================================
// Int0 Class
// =============================================================================

//!
//! \brief          Int0 class
//! \details        Int0 class
//!
class Int0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////     INT0 Trigger Sense     /////////////////     //
    //!
    //! \brief      Sense Trigger enumeration
    //! \details    Sense Trigger events associated with INT0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class SenseMode : uint8_t {
        LOW_LEVEL           = 0,    //!< Trigger interrupt continuously while pin is in logic low level
        BOTH_EDGES          = 1,    //!< Trigger interrupt at both edges
        FALLING_EDGE        = 2,    //!< Trigger interrupt at falling edge
        RISING_EDGE         = 3,    //!< Trigger interrupt rising edge
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Int0 class constructor
    //! \details    Creates an Int0 object
    //!
    Int0(
            void
    );

    //!
    //! \brief      Int0 class destructor
    //! \details    Destroys an Int0 object
    //!
    ~Int0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the INT0 module
    //! \details    Initializes the INT0 module.
    //! \param      senseMode_p         Trigger sense mode
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            SenseMode senseMode_p
    );

    //!
    //! \brief      Configures the trigger sense mode
    //! \details    Configures the trigger sense mode.
    //! \param      senseMode_p         Trigger sense mode
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setSenseMode(
            SenseMode senseMode_p
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
    SenseMode       _senseMode;
    Error           _lastError;
}; // class Int0

// =============================================================================
// Inlined class functions
// =============================================================================

//     ////////////////////////    INTERRUPT     ////////////////////////     //
void inlined Int0::activateInterrupt(void)
{
    setBit(EIMSK, INT0);
    return;
}

void inlined Int0::clearInterruptRequest(void)
{
    setBit(EIFR, INTF0);
    return;
}

void inlined Int0::deactivateInterrupt(void)
{
    clrBit(EIMSK, INT0);
    return;
}

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Int0 peripheral handler object
//! \details        Int0 peripheral handler object
//!
extern Int0 int0;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __INT0_HPP

// =============================================================================
// END OF FILE
// =============================================================================
