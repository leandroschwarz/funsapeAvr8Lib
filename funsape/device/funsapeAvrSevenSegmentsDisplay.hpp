/* =============================================================================
 * Project:         FunSAPE AVR8 Integrated Library
 * File:            funsapeAvrSevenSegmentsDisplay.hpp
 * Module:          Seven segments display controller
 * Author:          Leandro Schwarz
 * Version:         22.0
 * Last edition:    2022-11-28
 * Purpose:         Seven segments display controller with support to both
 *                      common anode and common cathode displays. The following
 *                      special characters were also implemented: dash, H, J, L
 *                      n, p, S, U, y, display off.
 * ========================================================================== */

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP
#define __FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP
#       error "Version mismatch between file header and global definitions file!"
#   endif
#else
#   error "Global definitions file is missing!"
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

enum class SevenSegmentsDisplayType : cbool_t {
    COMMON_ANODE    = false,
    COMMON_CATHODE  = true
};

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

uint8_t convertToSevenSegments(
        uint8_t numericValue_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);
uint8_t convertToSevenSegments(
        SevenSegmentsCode numericCode_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_SEVEN_SEGMENTS_DISPLAY_HPP

// =============================================================================
// END OF FILE
// =============================================================================
