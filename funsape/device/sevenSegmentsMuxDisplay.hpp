//!
//! \file           sevenSegmentsMuxDisplay.hpp
//! \brief          Seven segments multiplexed display controller
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Seven segments multiplexed display controller with support
//!                     to variable number of digits (2 to 8). The library
//!                     supports both common anode and common cathode displays,
//!                     decimal point, and the special characters defined in
//!                     sevenSegmentsDisplay.hpp.
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#define __SEVEN_SEGMENTS_MUX_DISPLAY_HPP        2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

#include "sevenSegmentsDisplay.hpp"
#if !defined(__SEVEN_SEGMENTS_DISPLAY_HPP)
#   error "Header file (sevenSegmentsDisplay.hpp) is corrupted!"
#elif __SEVEN_SEGMENTS_DISPLAY_HPP != __SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between header file and library dependency (sevenSegmentsDisplay.hpp)!"
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

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// SevenSegmentsMuxDisplay Class
// =============================================================================

//!
//! \brief          SevenSegmentsMuxDisplay class
//! \details        This class can handle multiplexed seven segments displays,
//!                     from 2 to 8 digits.
//!
class SevenSegmentsMuxDisplay
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //!
    //! \brief      Number of digits
    //! \details    Use this enumeration to configure the number of digits of
    //!                 the multiplexed display.
    //!
    enum class Digits {
        DIGITS_2                        = 2,
        DIGITS_3                        = 3,
        DIGITS_4                        = 4,
        DIGITS_5                        = 5,
        DIGITS_6                        = 6,
        DIGITS_7                        = 7,
        DIGITS_8                        = 8,
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief          SevenSegmentsMuxDisplay constructor
    //! \details        Creates a SevenSegmentsMuxDisplay object
    //!
    SevenSegmentsMuxDisplay(
            void
    );

    //!
    //! \brief          SevenSegmentsMuxDisplay destructor
    //! \details        Destroys a SevenSegmentsMuxDisplay object
    //!
    ~SevenSegmentsMuxDisplay(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Initializes a SevenSegmentsMuxDisplay object
    //! \details    This function initializes the SevenSegmentsMuxDisplay
    //!                 object, setting the display size and configuration.
    //! \param      numberOfDigits_p            Display size
    //! \param      displayType_p               Display configuration
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t init(
            Digits numberOfDigits_p,
            SevenSegmentsDisplayType displayType_p
    );

    //!
    //! \brief      Set data and control ports
    //! \details    This function sets the data and control port registers and
    //!                 pins.
    //! \param      dataRegAddress_p            Address of the data port
    //! \param      controlRegAddress_p         Address of the control port
    //! \param      controlFirstPin_p           First pin of the control port
    //! \param      displayTurnOnLevel_p        Display activation logic level
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t setPorts(
            ioRegAddress_t dataRegAddress_p,
            ioRegAddress_t controlRegAddress_p,
            ioPinIndex_t controlFirstPin_p,
            LogicLevel displayTurnOnLevel_p
    );

    //!
    //! \brief      Shows next digit of the display
    //! \details    This function turns current digit off and turns on the next
    //!             digit of the display
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t showNextDigit(
            void
    );

    //!
    //! \brief      Updates display digit values
    //! \details    This function updates the current value to be shown on the
    //!                 display.
    //! \param      digitValues_p               Array of digit values to be shown
    //! \param      digitPoints_p               Array of points to be turned on
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t updateDigitValues(
            cuint8_t *digitValues_p,
            cbool_t *digitPoints_p = nullptr
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    ioRegAddress_t                      _dataDdr;
    ioRegAddress_t                      _dataPort;
    ioRegAddress_t                      _controlDdr;
    ioRegAddress_t                      _controlPort;
    ioPinIndex_t                        _controlFirst           : 3;
    uint8_t                             _controlMask;
    uint8_t                             _digitMax               : 3;
    uint8_t                             _digitIndex             : 3;
    uint8_t                             _digitValue[8];
    bool_t                              _digitPoint[8];
    SevenSegmentsDisplayType            _displayType            : 1;
    bool_t                              _isInitialized          : 1;
    bool_t                              _isPortsSet             : 1;
    LogicLevel                          _controlActiveLevel     : 1;
    Error                               _lastError;
}; // class SevenSegmentsMuxDisplay

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

#endif  // __SEVEN_SEGMENTS_MUX_DISPLAY_HPP

// =============================================================================
// END OF FILE
// =============================================================================
