//!
//! \file           sevenSegmentsDisplay.hpp
//! \brief          Seven segments display controller
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Seven segments display controller with support to both
//!                     common anode and common cathode displays. The following
//!                     special characters were also implemented: dash, H, J, L
//!                     n, p, S, U, y, display off.
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __SEVEN_SEGMENTS_DISPLAY_HPP
#define __SEVEN_SEGMENTS_DISPLAY_HPP            2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __SEVEN_SEGMENTS_DISPLAY_HPP
#   error "Version mismatch between file header and global definitions file!"
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

//!
//! \brief          Seven segments code enumeration
//! \details        Enumeration to set the digit value
//!
enum class SevenSegmentsCode : uint8_t {
    HEX_0           = 0,
    HEX_1           = 1,
    HEX_2           = 2,
    HEX_3           = 3,
    HEX_4           = 4,
    HEX_5           = 5,
    HEX_6           = 6,
    HEX_7           = 7,
    HEX_8           = 8,
    HEX_9           = 9,
    HEX_A           = 10,
    HEX_B           = 11,
    HEX_C           = 12,
    HEX_D           = 13,
    HEX_E           = 14,
    HEX_F           = 15,
    LETTER_A        = 'A',
    LETTER_B        = 'B',
    LETTER_C        = 'C',
    LETTER_D        = 'D',
    LETTER_E        = 'E',
    LETTER_F        = 'F',
    LETTER_H        = 'H',
    LETTER_I        = 'i',
    LETTER_J        = 'j',
    LETTER_L        = 'L',
    LETTER_N        = 'n',
    LETTER_O        = 'O',
    LETTER_P        = 'P',
    LETTER_Q        = 'q',
    LETTER_R        = 'r',
    LETTER_S        = 'S',
    LETTER_T        = 't',
    LETTER_U        = 'U',
    LETTER_Y        = 'y',
    DASH            = '-',
    ON              = 0xFD,
    OFF             = 0xFF
};

//!
//! \brief          Display hardware configuration
//! \details        This enumeration defines anode or cathode common display
//!                     types
//!
enum class SevenSegmentsDisplayType : cbool_t {
    COMMON_ANODE    = false,            //!< Common anode displays; negative logic
    COMMON_CATHODE  = true              //!< Common cathode displays; positive logic
};

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

//!
//! \brief          Converts a value to segments code
//! \details        This function receives a numeric value and decodes it to
//!                     seven segments code, according to given display type,
//!                     with decimal point support.
//! \param          numericValue_p      Numeric value to be converted
//! \param          point_p             Decimal point status
//! \param          displayType_p       Display type, defaults to COMMON_ANODE
//! \return         uint8_t             Returns segments code in 0bPGFEDCBA order
//!
uint8_t convertToSevenSegments(
        cuint8_t numericValue_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);

//!
//! \brief          Converts a value to segments code
//! \details        This function receives a coded value and decodes it to
//!                     seven segments code, according to given display type,
//!                     with decimal point support.
//! \param          numericValue_p      Numeric value to be converted
//! \param          point_p             Decimal point status
//! \param          displayType_p       Display type, defaults to COMMON_ANODE
//! \return         uint8_t             Returns segments code in 0bPGFEDCBA order
//!
uint8_t convertToSevenSegments(
        SevenSegmentsCode numericCode_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __SEVEN_SEGMENTS_DISPLAY_HPP

// =============================================================================
// END OF FILE
// =============================================================================
