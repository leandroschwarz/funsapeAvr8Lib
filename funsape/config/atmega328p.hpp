//!
//! ****************************************************************************
//! @file           atmega328p.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          MCU description file.
//! @details        This file list the traits of the ATmega328P microcontroller.
//! @date           2026-04-01
//! @version        26.04
//! @copyright      MIT License
//! @note           No notes at this time.
//! @todo           No items in todo list yet.
//! @bug            No bugs detected yet.
//! ****************************************************************************
//! @attention
//!
//! MIT License
//!
//! Copyright (c) 2026 Leandro Schwarz
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//!     of this software and associated documentation files (the "Software"), to
//!     deal in the Software without restriction, including without limitation
//!     the rights to use, copy, modify, merge, publish, distribute, sublicense,
//!     and/or sell copies of the Software, and to permit persons to whom the
//!     Software is furnished to do so, subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in
//!     all copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//!     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//!     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//!     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//!     OTHER DEALINGS IN THE SOFTWARE.
//!
//! ****************************************************************************
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __ATMEGA328P_HPP
#define __ATMEGA328P_HPP                2604

//!
//! @cond
//!

#include <avr/io.h>

// =============================================================================
// Port Address Constants (Zero-Overhead Aliases)
// =============================================================================

// Port B Registers (Base IO: 0x03)
// constexpr uintptr_t PinB  = 0x23;   //!< Input Pins Address
const uint8_t PinB = 0x23;
constexpr uintptr_t DdrB  = 0x24;   //!< Data Direction Address
constexpr uintptr_t PortB = 0x25;   //!< Data Register Address

// Port C Registers (Base IO: 0x06)
constexpr uintptr_t PinC  = 0x26;   //!< Input Pins Address
constexpr uintptr_t DdrC  = 0x27;   //!< Data Direction Address
constexpr uintptr_t PortC = 0x28;   //!< Data Register Address

// Port D Registers (Base IO: 0x09)
constexpr uintptr_t PinD  = 0x29;   //!< Input Pins Address
constexpr uintptr_t DdrD  = 0x2A;   //!< Data Direction Address
// constexpr uintptr_t PortD = 0x2B;   //!< Data Register Address
const uint8_t PortD = 0x2B;   //!< Data Register Address

// =============================================================================
// GPIO definitions
// =============================================================================

// Validates if the memory address corresponds to a valid GPIO register
#define IS_GPIO_ALL_INSTANCE(regAddress)    (bool_t)(           \
        (((uint16_t)regAddress >= PinB) &&((uint16_t)regAddress <= PortD))          \
        ? true                                                  \
        : false                                                 \
)

// Validates if the pin number is valid
#define IS_GPIO_ALL_PIN_NUMBER(regAddress, pinIndex)    (bool_t)(       \
        ( \
                (((regAddress >= PinB) &&(regAddress <= PortB)) &&((pinIndex >= 0) &&(pinIndex <= 7))) \
                ? true \
                : ( \
                        (((regAddress >= PinC) &&(regAddress <= PortC)) &&((pinIndex >= 0) &&(pinIndex <= 6)))\
                        ? true \
                        : ( \
                                (((regAddress >= PinD) &&(regAddress <= PortD)) &&((pinIndex >= 0) &&(pinIndex <= 7))) \
                                ? true \
                                : false \
                        ) \
                ) \
        ) \
)

#define getGpioDdrAddress(regAddress)           ((ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 1))
#define getGpioPinAddress(regAddress)           ((ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 0))
#define getGpioPortAddress(regAddress)          ((ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 2))

// =============================================================================
// INT0 definitions
// =============================================================================

#define MCU_INT0_PERIPHERAL_EXISTS

#define MCU_INT0_GPIO_REG_DIR           DDRD
#define MCU_INT0_GPIO_REG_OUT           PORTD
#define MCU_INT0_GPIO_BIT_OFFSET        PD2
#define MCU_INT0_CTRL_REG               EICRA
#define MCU_INT0_SENSE_BIT_OFFSET       ISC00
#define MCU_INT0_SENSE_BIT_MASK         0x03
#define MCU_INT0_ENABLE_REG             EIMSK
#define MCU_INT0_ENABLE_BIT_OFFSET      INT0
#define MCU_INT0_FLAG_REG               EIFR
#define MCU_INT0_FLAG_BIT_POS           INTF0

// =============================================================================
// INT1 definitions
// =============================================================================

#define MCU_INT1_PERIPHERAL_EXISTS

#define MCU_INT1_GPIO_REG_DIR           DDRD
#define MCU_INT1_GPIO_REG_OUT           PORTD
#define MCU_INT1_GPIO_BIT_OFFSET        PD3
#define MCU_INT1_CTRL_REG               EICRA
#define MCU_INT1_ENABLE_BIT_OFFSET      INT1
#define MCU_INT1_ENABLE_REG             EIMSK
#define MCU_INT1_FLAG_BIT_POS           INTF1
#define MCU_INT1_FLAG_REG               EIFR
#define MCU_INT1_SENSE_BIT_MASK         0x03
#define MCU_INT1_SENSE_BIT_OFFSET       ISC10

// =============================================================================
// PCINT0 definitions
// =============================================================================

#define MCU_PCINT0_PERIPHERAL_EXISTS

#define MCU_PCINT0_PIN_0_EXISTS
#define MCU_PCINT0_PIN_1_EXISTS
#define MCU_PCINT0_PIN_2_EXISTS
#define MCU_PCINT0_PIN_3_EXISTS
#define MCU_PCINT0_PIN_4_EXISTS
#define MCU_PCINT0_PIN_5_EXISTS
#define MCU_PCINT0_PIN_6_EXISTS
#define MCU_PCINT0_PIN_7_EXISTS

#define MCU_PCINT0_GPIO_REG_DIR         DDRB
#define MCU_PCINT0_GPIO_REG_OUT         PORTB
#define MCU_PCINT0_GPIO_PCINT0_BIT      PB0
#define MCU_PCINT0_GPIO_PCINT1_BIT      PB1
#define MCU_PCINT0_GPIO_PCINT2_BIT      PB2
#define MCU_PCINT0_GPIO_PCINT3_BIT      PB3
#define MCU_PCINT0_GPIO_PCINT4_BIT      PB4
#define MCU_PCINT0_GPIO_PCINT5_BIT      PB5
#define MCU_PCINT0_GPIO_PCINT6_BIT      PB6
#define MCU_PCINT0_GPIO_PCINT7_BIT      PB7

#define MCU_PCINT0_ENABLE_BIT_POS       PCIE0
#define MCU_PCINT0_ENABLE_REG           PCICR
#define MCU_PCINT0_FLAG_BIT             PCIF0
#define MCU_PCINT0_FLAG_REG             PCIFR
#define MCU_PCINT0_SELECTION_BIT_MASK   0xFF
#define MCU_PCINT0_SELECTION_BIT_POS    PCINT0
#define MCU_PCINT0_SELECTION_REG        PCMSK0

// =============================================================================
// PCINT1 definitions
// =============================================================================

#define MCU_PCINT1_PERIPHERAL_EXISTS

#define MCU_PCINT1_PIN_8_EXISTS
#define MCU_PCINT1_PIN_9_EXISTS
#define MCU_PCINT1_PIN_10_EXISTS
#define MCU_PCINT1_PIN_11_EXISTS
#define MCU_PCINT1_PIN_12_EXISTS
#define MCU_PCINT1_PIN_13_EXISTS
#define MCU_PCINT1_PIN_14_EXISTS
// #define MCU_PCINT1_PIN_15_EXISTS

#define MCU_PCINT1_GPIO_REG_DIR         DDRC
#define MCU_PCINT1_GPIO_REG_OUT         PORTC
#define MCU_PCINT1_GPIO_PCINT8_BIT      PC0
#define MCU_PCINT1_GPIO_PCINT9_BIT      PC1
#define MCU_PCINT1_GPIO_PCINT10_BIT     PC2
#define MCU_PCINT1_GPIO_PCINT11_BIT     PC3
#define MCU_PCINT1_GPIO_PCINT12_BIT     PC4
#define MCU_PCINT1_GPIO_PCINT13_BIT     PC5
#define MCU_PCINT1_GPIO_PCINT14_BIT     PC6
// #define MCU_PCINT1_GPIO_PCINT15_BIT     PC7

#define MCU_PCINT1_ENABLE_BIT_POS       PCIE1
#define MCU_PCINT1_ENABLE_REG           PCICR
#define MCU_PCINT1_FLAG_BIT             PCIF1
#define MCU_PCINT1_FLAG_REG             PCIFR
#define MCU_PCINT1_SELECTION_BIT_MASK   0x7F
#define MCU_PCINT1_SELECTION_BIT_POS    PCINT8
#define MCU_PCINT1_SELECTION_REG        PCMSK1

// =============================================================================
// PCINT2 definitions
// =============================================================================

#define MCU_PCINT2_PERIPHERAL_EXISTS

#define MCU_PCINT2_PIN_16_EXISTS
#define MCU_PCINT2_PIN_17_EXISTS
#define MCU_PCINT2_PIN_18_EXISTS
#define MCU_PCINT2_PIN_19_EXISTS
#define MCU_PCINT2_PIN_20_EXISTS
#define MCU_PCINT2_PIN_21_EXISTS
#define MCU_PCINT2_PIN_22_EXISTS
#define MCU_PCINT2_PIN_23_EXISTS

#define MCU_PCINT2_GPIO_REG_DIR         DDRD
#define MCU_PCINT2_GPIO_REG_OUT         PORTD
#define MCU_PCINT2_GPIO_PCINT16_BIT     PD0
#define MCU_PCINT2_GPIO_PCINT17_BIT     PD1
#define MCU_PCINT2_GPIO_PCINT18_BIT     PD2
#define MCU_PCINT2_GPIO_PCINT19_BIT     PD3
#define MCU_PCINT2_GPIO_PCINT20_BIT     PD4
#define MCU_PCINT2_GPIO_PCINT21_BIT     PD5
#define MCU_PCINT2_GPIO_PCINT22_BIT     PD6
#define MCU_PCINT2_GPIO_PCINT23_BIT     PD7

#define MCU_PCINT2_ENABLE_BIT_POS       PCIE2
#define MCU_PCINT2_ENABLE_REG           PCICR
#define MCU_PCINT2_FLAG_BIT             PCIF2
#define MCU_PCINT2_FLAG_REG             PCIFR
#define MCU_PCINT2_SELECTION_BIT_MASK   0xFF
#define MCU_PCINT2_SELECTION_BIT_POS    PCINT16
#define MCU_PCINT2_SELECTION_REG        PCMSK2

// =============================================================================
// TIMER0 definitions
// =============================================================================

#define MCU_TIMER0_PERIPHERAL_EXISTS

#define MCU_TIMER0_CTRL_A_REG                   TCCR0A
#define MCU_TIMER0_CTRL_B_REG                   TCCR0B
#define MCU_TIMER0_FORCE_COMPA_BIT_OFFSET       FOC0A
#define MCU_TIMER0_FORCE_COMPB_BIT_OFFSET       FOC0B
#define MCU_TIMER0_ENABLE_OVF_BIT_OFFSET        TOIE0
#define MCU_TIMER0_ENABLE_COMPA_BIT_OFFSET      OCIE0A
#define MCU_TIMER0_ENABLE_COMPB_BIT_OFFSET      OCIE0B
#define MCU_TIMER0_ENABLE_REG                   TIMSK0
#define MCU_TIMER0_FLAG_OVF_BIT_POS             TOV0
#define MCU_TIMER0_FLAG_COMPA_BIT_POS           OCF0A
#define MCU_TIMER0_FLAG_COMPB_BIT_POS           OCF0B
#define MCU_TIMER0_FLAG_REG                     TIFR0
#define MCU_TIMER0_OCR0A_REG                    OCR0A
#define MCU_TIMER0_OCR0B_REG                    OCR0B
#define MCU_TIMER0_COUNTER_REG                  TCNT0
#define MCU_TIMER0_MODE_BIT_0_POS               WGM00
#define MCU_TIMER0_MODE_BIT_0_MASK              0x03
#define MCU_TIMER0_MODE_BIT_2_POS               WGM02
#define MCU_TIMER0_MODE_BIT_2_MASK              0x01
#define MCU_TIMER0_CLOCK_BIT_POS                CS00
#define MCU_TIMER0_CLOCK_BIT_MASK               0x07
#define MCU_TIMER0_OUTPUT_A_MODE_BIT_POS        COM0A0
#define MCU_TIMER0_OUTPUT_A_MODE_BIT_MASK       0x03
#define MCU_TIMER0_OUTPUT_B_MODE_BIT_POS        COM0B0
#define MCU_TIMER0_OUTPUT_B_MODE_BIT_MASK       0x03

// =============================================================================
// TIMER1 definitions
// =============================================================================

#define MCU_TIMER1_PERIPHERAL_EXISTS

#define MCU_TIMER1_CTRL_A_REG                   TCCR1A
#define MCU_TIMER1_CTRL_B_REG                   TCCR1B
#define MCU_TIMER1_CTRL_C_REG                   TCCR1C
#define MCU_TIMER1_FORCE_COMPA_BIT_OFFSET       FOC1A
#define MCU_TIMER1_FORCE_COMPB_BIT_OFFSET       FOC1B
#define MCU_TIMER1_ENABLE_OVF_BIT_OFFSET        TOIE1
#define MCU_TIMER1_ENABLE_COMPA_BIT_OFFSET      OCIE1A
#define MCU_TIMER1_ENABLE_COMPB_BIT_OFFSET      OCIE1B
#define MCU_TIMER1_ENABLE_CAPT_BIT_OFFSET       ICIE1
#define MCU_TIMER1_ENABLE_REG                   TIMSK1
#define MCU_TIMER1_FLAG_OVF_BIT_POS             TOV1
#define MCU_TIMER1_FLAG_COMPA_BIT_POS           OCF1A
#define MCU_TIMER1_FLAG_COMPB_BIT_POS           OCF1B
#define MCU_TIMER1_FLAG_CAPT_BIT_POS            ICF1
#define MCU_TIMER1_COUNTER_REG                  TCNT1
#define MCU_TIMER1_FLAG_REG                     TIFR1
#define MCU_TIMER1_OCR1A_REG                    OCR1A
#define MCU_TIMER1_OCR1B_REG                    OCR1B
#define MCU_TIMER1_CAPT_REG                     ICR1
#define MCU_TIMER1_MODE_BIT_0_POS               WGM10
#define MCU_TIMER1_MODE_BIT_0_MASK              0x03
#define MCU_TIMER1_MODE_BIT_2_POS               WGM12
#define MCU_TIMER1_MODE_BIT_2_MASK              0x03
#define MCU_TIMER1_CLOCK_BIT_POS                CS10
#define MCU_TIMER1_CLOCK_BIT_MASK               0x07
#define MCU_TIMER1_OUTPUT_A_MODE_BIT_POS        COM1A0
#define MCU_TIMER1_OUTPUT_A_MODE_BIT_MASK       0x03
#define MCU_TIMER1_OUTPUT_B_MODE_BIT_POS        COM1B0
#define MCU_TIMER1_OUTPUT_B_MODE_BIT_MASK       0x03
#define MCU_TIMER1_NOISE_CANCELLER_BIT_POS      ICNC1
#define MCU_TIMER1_EDGE_SELECT_BIT_POS          ICES1

// =============================================================================
// TIMER2 definitions
// =============================================================================

#define MCU_TIMER2_PERIPHERAL_EXISTS

#define MCU_TIMER2_CTRL_A_REG                   TCCR2A
#define MCU_TIMER2_CTRL_B_REG                   TCCR2B
#define MCU_TIMER2_FORCE_COMPA_BIT_OFFSET       FOC2A
#define MCU_TIMER2_FORCE_COMPB_BIT_OFFSET       FOC2B
#define MCU_TIMER2_ENABLE_OVF_BIT_OFFSET        TOIE2
#define MCU_TIMER2_ENABLE_COMPA_BIT_OFFSET      OCIE2A
#define MCU_TIMER2_ENABLE_COMPB_BIT_OFFSET      OCIE2B
#define MCU_TIMER2_ENABLE_REG                   TIMSK2
#define MCU_TIMER2_FLAG_OVF_BIT_POS             TOV2
#define MCU_TIMER2_FLAG_COMPA_BIT_POS           OCF2A
#define MCU_TIMER2_FLAG_COMPB_BIT_POS           OCF2B
#define MCU_TIMER2_FLAG_REG                     TIFR2
#define MCU_TIMER2_OCR0A_REG                    OCR2A
#define MCU_TIMER2_OCR0B_REG                    OCR2B
#define MCU_TIMER2_COUNTER_REG                  TCNT2
#define MCU_TIMER2_MODE_BIT_0_POS               WGM20
#define MCU_TIMER2_MODE_BIT_0_MASK              0x03
#define MCU_TIMER2_MODE_BIT_2_POS               WGM22
#define MCU_TIMER2_MODE_BIT_2_MASK              0x01
#define MCU_TIMER2_CLOCK_BIT_POS                CS20
#define MCU_TIMER2_CLOCK_BIT_MASK               0x07
#define MCU_TIMER2_OUTPUT_A_MODE_BIT_POS        COM2A0
#define MCU_TIMER2_OUTPUT_A_MODE_BIT_MASK       0x03
#define MCU_TIMER2_OUTPUT_B_MODE_BIT_POS        COM2B0
#define MCU_TIMER2_OUTPUT_B_MODE_BIT_MASK       0x03

// =============================================================================
// ADC definitions
// =============================================================================

#define MCU_ADC_PERIPHERAL_EXISTS

#define MCU_ADC_CONTROL_A_REG                   ADCSRA
#define MCU_ADC_CONTROL_B_REG                   ADCSRB
#define MCU_ADC_MUX_REG                         ADMUX
#define MCU_ADC_ADJUST_BIT_OFFSET               ADLAR
#define MCU_ADC_INT_ENABLE_BIT_OFFSET           ADIE
#define MCU_ADC_ENABLE_BIT_OFFSET               ADEN
#define MCU_ADC_START_CONVERSION_BIT_OFFSET     ADSC
#define MCU_ADC_FLAG_REG                        ADCSRA
#define MCU_ADC_FLAG_BIT_POS                    ADIF
#define MCU_ADC_DIDR_REG                        DIDR0

#define MCU_ADC_TRIGGER_SOURCE_BIT_POS          ADTS0
#define MCU_ADC_AUTO_TRIGGER_BIT_POS            ADATE
#define MCU_ADC_REFERENCE_BIT_POS               REFS0
#define MCU_ADC_PRESCALER_BIT_POS               ADPS0
#define MCU_ADC_MUX_BIT_POS                     MUX0


//!
//! @endcond
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __ATMEGA328P_HPP

// =============================================================================
// End of file (atmega328p.hpp)
// =============================================================================
