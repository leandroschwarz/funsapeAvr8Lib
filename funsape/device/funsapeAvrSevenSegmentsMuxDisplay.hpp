/* =============================================================================
 * Project:         FunSAPE AVR8 Integrated Library
 * File:            funsapeAvrSevenSegmentsMuxDisplay.hpp
 * Module:          Seven segments multiplexed display controller
 * Author:          Leandro Schwarz
 * Version:         22.0
 * Last edition:    2022-11-28
 * Purpose:         Seven segments multiplexed display controller with support
 *                      to variable number of digits (2 to 8). The library
 *                      supports both common anode and common cathode displays,
 *                      decimal point, and the special characters defined in
 *                      funsapeAvrSevenSegments.hpp.
 * ========================================================================== */

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#define __FUNSAPE_AVR_SEVEN_SEGMENTS_MUX_DISPLAY_HPP    220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#       error "Version mismatch between file header and global definitions file!"
#   endif
#else
#   error "Global definitions file is missing!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#if __has_include("funsapeAvrSevenSegmentsDisplay.hpp")
#   include "funsapeAvrSevenSegmentsDisplay.hpp"
#   if !defined(__FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP)
#       error "Header file (funsapeAvrSevenSegmentsDisplay.hpp) is corrupted!"
#   elif __FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP != __FUNSAPE_AVR_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#       error "Version mismatch between header file and library dependency (funsapeAvrSevenSegmentsDisplay.hpp)!"
#   endif
#else
#   error "Header file (funsapeAvrSevenSegmentsDisplay.hpp) is missing!"
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

class SevenSegmentsMuxDisplay
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    SevenSegmentsMuxDisplay(
            void
    );
    ~SevenSegmentsMuxDisplay(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //
    bool_t init(
            uint8_t numberOfDigits_p,
            SevenSegmentsDisplayType displayType_p
    );
    bool_t setPorts(
            ioRegAddress_t dataRegAddress_p,
            ioRegAddress_t controlRegAddress_p,
            ioPinIndex_t controlFirstPin_p,
            LogicLevel displayOnLevel_p
    );
    bool_t showNextDigit(
            void
    );
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

#endif  // __FUNSAPE_AVR_SEVEN_SEGMENTS_MUX_DISPLAY_HPP

// =============================================================================
// END OF FILE
// =============================================================================
