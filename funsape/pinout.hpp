//!
//! \file           pinout.hpp
//! \brief          Microcontroller pinout
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Microcontroller support list:
//!                     - ATmegaX8Y (ATmega48, ATmega48A, ATmega48P, ATmega48PA,
//!                         ATmega88, ATmega88A, ATmega88P, ATmega88PA,
//!                         ATmega168, ATmega168A, ATmega168P, ATmega168PA,
//!                         ATmega328, ATmega328P)
//! \todo           Implement other microcontrollers
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __PINOUT_HPP
#define __PINOUT_HPP                            2304

// =============================================================================
// Dependencies
// =============================================================================

//     //////////////////     AVR STANDARD LIBRARY     //////////////////     //
#include <avr/io.h>

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
// Macrofunctions
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Inline functions declaration
// =============================================================================

// NONE

// =============================================================================
// Inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// Public functions weakly defined
// =============================================================================

// NONE

// =============================================================================
// Includes Low Level Abstraction Layer
// =============================================================================

// NONE

// =============================================================================
// Microcontroller definitions
// =============================================================================

//     ///////     ATmega48, ATmega48A, ATmega48P, ATmega48PA     ///////     //
//     ///////     ATmega88, ATmega88A, ATmega88P, ATmega88PA     ///////     //
//     /////     ATmega168, ATmega168A, ATmega168P, ATmega168PA     /////     //
//     //////////////////     ATmega328, ATmega328P    //////////////////     //
#if defined(__AVR_ATmega48__)  || defined(__AVR_ATmega48A__)  || defined(__AVR_ATmega48P__)  || defined(__AVR_ATmega48PA__)  || \
    defined(__AVR_ATmega88__)  || defined(__AVR_ATmega88A__)  || defined(__AVR_ATmega88P__)  || defined(__AVR_ATmega88PA__)  || \
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168PA__) || \
    defined(__AVR_ATmega328__) ||                                defined(__AVR_ATmega328P__)

#   define _FUNSAPE_GPIO_PORT_B_EXISTS
#   define _FUNSAPE_GPIO_PORT_C_EXISTS
#   define _FUNSAPE_GPIO_PORT_D_EXISTS
#   define IS_GPIO_ALL_INSTANCE(regAddress)    (bool_t)(        \
        ((regAddress >= &PINB) && (regAddress <= &PORTD))       \
        ? true                                                  \
        : false)
#   define IS_GPIO_ALL_PIN_NUMBER(pinNumber)    (bool_t)(       \
        (pinNumber <= 7)                                        \
        ? true                                                  \
        : false)
#   define getGpioDdrAddress(regAddress)        (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 1)
#   define getGpioPinAddress(regAddress)        (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 0)
#   define getGpioPortAddress(regAddress)       (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 2)
#endif

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __PINOUT_HPP

// =============================================================================
// END OF FILE
// =============================================================================
