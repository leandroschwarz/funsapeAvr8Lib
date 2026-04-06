//!
//! \file           funsapeLibNunchuk.hpp
//! \brief          Wii Nunchuk extension controller module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2025-10-27
//! \version        24.07
//! \copyright      license
//! \details        Wii Nunchuk extension controller module interface for the
//!                     FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_NUNCHUK_HPP
#define __FUNSAPE_LIB_NUNCHUK_HPP                        2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_NUNCHUK_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_NUNCHUK_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibBus.hpp"
#if !defined(__FUNSAPE_LIB_BUS_HPP)
#   error "Header file (funsapeLibBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_BUS_HPP != __FUNSAPE_LIB_NUNCHUK_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibBus.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

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

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

//!
//! \brief          Nunchuk class
//! \details        Nunchuk class.
//!
class Nunchuk
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Nunchuk class constructor
    //! \details    Creates a Nunchuk object.
    //!
    Nunchuk(
            void
    );

    //!
    //! \brief      Nunchuk class destructor
    //! \details    Destroys a Nunchuk object.
    //!
    ~Nunchuk(
            void
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         Error              Return info
    //!
    Error getLastError(
            void
    );

    //!
    //! \brief      Initializes the device.
    //! \details    Performs the device initialization, disabling data
    //!                     encryption.
    //! \param[in]  busHandler_p        pointer to the \ref Bus handler object
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p
    );

    //!
    //! \brief      Starts a data acquisition.
    //! \details    The function starts a data acquisition at the device. The
    //!                 data acquisition can take up to 5 ms to finish.
    //! \return true
    //! \return false
    //!
    bool_t startAcquisition(
            void
    );

    //!
    //! \brief      Reads data from device.
    //! \details    The function reads the data from device.
    //! \return true
    //! \return false
    //!
    bool_t read(
            void
    );

    //     ///////////////    DATA HANDLING FUNCTIONS     ///////////////     //

    //!
    //! \brief      Returns the acceleration value data from last acquisition.
    //! \details    Returns the acceleration value data from last acquisition.
    //! \param[out] accX_p      pointer to the variable where the value of the X
    //!                             axis of the accelerometer must be saved.
    //! \param[out] accY_p      pointer to the variable where the value of the Y
    //!                             axis of the accelerometer must be saved.
    //! \param[out] accZ_p      pointer to the variable where the value of the Z
    //!                         axis of the accelerometer must be saved.
    //! \return true
    //! \return false
    //!
    bool_t getAccData(
            uint16_t *accX_p,
            uint16_t *accY_p,
            uint16_t *accZ_p
    );

    //!
    //! \brief      Returns the joystick data from last acquisition.
    //! \details    Returns the joystick data from last acquisition.
    //! \param[out] joyX_p      pointer to the variable where the value of the X
    //!                             joystick must be saved.
    //! \param[out] joyY_p      pointer to the variable where the value of the Y
    //!                             joystick must be saved.
    //! \param[out] btnC_p      pointer to the variable where the state of the C
    //!                             button must be saved.
    //! \param[out] btnZ_p      pointer to the variable where the state of the Z
    //!                             button must be saved.
    //! \return true
    //! \return false
    //!
    bool_t getJoyData(
            uint8_t *joyX_p,
            uint8_t *joyY_p,
            bool_t *btnC_p,
            bool_t *btnZ_p
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:

    //     /////////////////     DEVICE BUS HANDLER     /////////////////     //

    Bus             *_busHandler;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isInitialized              : 1;
    Error           _lastError;

    //     /////////////////////    DEVICE DATA     /////////////////////     //

    uint8_t         _joyX;
    uint8_t         _joyY;
    uint16_t        _accX   : 10;
    uint16_t        _accY   : 10;
    uint16_t        _accZ   : 10;
    bool_t          _buttonC  : 1;
    bool_t          _buttonZ  : 1;
public:
    uint8_t         _debug;

protected:

    // NONE

}; // class Nunchuk

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_NUNCHUK_HPP

// =============================================================================
// END OF FILE - funsapeLibNunchuk.hpp
// =============================================================================
