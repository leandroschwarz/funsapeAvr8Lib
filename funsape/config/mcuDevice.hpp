//!
//! ****************************************************************************
//! @file           mcuDevice.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          MCU identification file.
//! @details        This file identifies the microcontroller in use and verifies
//!                     its compatibility with the FunSAPE++ AVR8 Library.
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

#ifndef __MCU_DEVICE_HPP
#define __MCU_DEVICE_HPP                2604

// =============================================================================
// Dependencies
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Mcu_Device"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Mcu_Device
//! @brief          Microcontroller definitions.
//! @{
//!

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Mcu_Part_Number" in "Mcu_Device"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Mcu_Part_Number
//! @brief          Microcontroller part number.
//! @{
//!

// Check for microcontroller previous definition
#if defined(_FUNSAPE_MCU)
#   error   [mcuDevice.hpp] Error 3 - Microcontroller already defined!
#endif

// Microcontroller codes
#if defined(__AVR_AT43USB320__)
#   define _FUNSAPE_MCU                 1
#elif defined(__AVR_AT43USB355__)
#   define _FUNSAPE_MCU                 2
#elif defined(__AVR_AT76C711__)
#   define _FUNSAPE_MCU                 3
#elif defined(__AVR_AT86RF401__)
#   define _FUNSAPE_MCU                 4
#elif defined(__AVR_AT90C8534__)
#   define _FUNSAPE_MCU                 5
#elif defined(__AVR_AT90CAN128__)
#   define _FUNSAPE_MCU                 6
#elif defined(__AVR_AT90CAN32__)
#   define _FUNSAPE_MCU                 7
#elif defined(__AVR_AT90CAN64__)
#   define _FUNSAPE_MCU                 8
#elif defined(__AVR_AT90PWM1__)
#   define _FUNSAPE_MCU                 9
#elif defined(__AVR_AT90PWM161__)
#   define _FUNSAPE_MCU                 10
#elif defined(__AVR_AT90PWM2__)
#   define _FUNSAPE_MCU                 11
#elif defined(__AVR_AT90PWM216__)
#   define _FUNSAPE_MCU                 12
#elif defined(__AVR_AT90PWM2B__)
#   define _FUNSAPE_MCU                 13
#elif defined(__AVR_AT90PWM3__)
#   define _FUNSAPE_MCU                 14
#elif defined(__AVR_AT90PWM316__)
#   define _FUNSAPE_MCU                 15
#elif defined(__AVR_AT90PWM3B__)
#   define _FUNSAPE_MCU                 16
#elif defined(__AVR_AT90PWM81__)
#   define _FUNSAPE_MCU                 17
#elif defined(__AVR_AT90S1200__)
#   define _FUNSAPE_MCU                 18
#elif defined(__AVR_AT90S2313__)
#   define _FUNSAPE_MCU                 19
#elif defined(__AVR_AT90S2323__)
#   define _FUNSAPE_MCU                 20
#elif defined(__AVR_AT90S2333__)
#   define _FUNSAPE_MCU                 21
#elif defined(__AVR_AT90S2343__)
#   define _FUNSAPE_MCU                 22
#elif defined(__AVR_AT90S4414__)
#   define _FUNSAPE_MCU                 23
#elif defined(__AVR_AT90S4433__)
#   define _FUNSAPE_MCU                 24
#elif defined(__AVR_AT90S4434__)
#   define _FUNSAPE_MCU                 25
#elif defined(__AVR_AT90S8515__)
#   define _FUNSAPE_MCU                 26
#elif defined(__AVR_AT90S8535__)
#   define _FUNSAPE_MCU                 27
#elif defined(__AVR_AT90SCR100__)
#   define _FUNSAPE_MCU                 28
#elif defined(__AVR_AT90USB1286__)
#   define _FUNSAPE_MCU                 29
#elif defined(__AVR_AT90USB1287__)
#   define _FUNSAPE_MCU                 30
#elif defined(__AVR_AT90USB162__)
#   define _FUNSAPE_MCU                 31
#elif defined(__AVR_AT90USB646__)
#   define _FUNSAPE_MCU                 32
#elif defined(__AVR_AT90USB647__)
#   define _FUNSAPE_MCU                 33
#elif defined(__AVR_AT90USB82__)
#   define _FUNSAPE_MCU                 34
#elif defined(__AVR_AT94K__)
#   define _FUNSAPE_MCU                 35
#elif defined(__AVR_ATA5272__)
#   define _FUNSAPE_MCU                 36
#elif defined(__AVR_ATA5505__)
#   define _FUNSAPE_MCU                 37
#elif defined(__AVR_ATA5702M322__)
#   define _FUNSAPE_MCU                 38
#elif defined(__AVR_ATA5782__)
#   define _FUNSAPE_MCU                 39
#elif defined(__AVR_ATA5790__)
#   define _FUNSAPE_MCU                 40
#elif defined(__AVR_ATA5790N__)
#   define _FUNSAPE_MCU                 41
#elif defined(__AVR_ATA5791__)
#   define _FUNSAPE_MCU                 42
#elif defined(__AVR_ATA5795__)
#   define _FUNSAPE_MCU                 43
#elif defined(__AVR_ATA5831__)
#   define _FUNSAPE_MCU                 44
#elif defined(__AVR_ATA6285__)
#   define _FUNSAPE_MCU                 45
#elif defined(__AVR_ATA6286__)
#   define _FUNSAPE_MCU                 46
#elif defined(__AVR_ATA6289__)
#   define _FUNSAPE_MCU                 47
#elif defined(__AVR_ATA6612C__)
#   define _FUNSAPE_MCU                 48
#elif defined(__AVR_ATA6613C__)
#   define _FUNSAPE_MCU                 49
#elif defined(__AVR_ATA6614Q__)
#   define _FUNSAPE_MCU                 50
#elif defined(__AVR_ATA6616C__)
#   define _FUNSAPE_MCU                 51
#elif defined(__AVR_ATA6617C__)
#   define _FUNSAPE_MCU                 52
#elif defined(__AVR_ATA664251__)
#   define _FUNSAPE_MCU                 53
#elif defined(__AVR_ATA8210__)
#   define _FUNSAPE_MCU                 54
#elif defined(__AVR_ATA8510__)
#   define _FUNSAPE_MCU                 55
#elif defined(__AVR_ATmega103__)
#   define _FUNSAPE_MCU                 56
#elif defined(__AVR_ATmega128__)
#   define _FUNSAPE_MCU                 57
#elif defined(__AVR_ATmega1280__)
#   define _FUNSAPE_MCU                 58
#elif defined(__AVR_ATmega1281__)
#   define _FUNSAPE_MCU                 59
#elif defined(__AVR_ATmega1284__)
#   define _FUNSAPE_MCU                 60
#elif defined(__AVR_ATmega1284P__)
#   define _FUNSAPE_MCU                 61
#elif defined(__AVR_ATmega1284RFR2__)
#   define _FUNSAPE_MCU                 62
#elif defined(__AVR_ATmega128A__)
#   define _FUNSAPE_MCU                 63
#elif defined(__AVR_ATmega128RFA1__)
#   define _FUNSAPE_MCU                 64
#elif defined(__AVR_ATmega128RFR2__)
#   define _FUNSAPE_MCU                 65
#elif defined(__AVR_ATmega16__)
#   define _FUNSAPE_MCU                 66
#elif defined(__AVR_ATmega161__)
#   define _FUNSAPE_MCU                 67
#elif defined(__AVR_ATmega162__)
#   define _FUNSAPE_MCU                 68
#elif defined(__AVR_ATmega163__)
#   define _FUNSAPE_MCU                 69
#elif defined(__AVR_ATmega164A__)
#   define _FUNSAPE_MCU                 70
#elif defined(__AVR_ATmega164P__)
#   define _FUNSAPE_MCU                 71
#elif defined(__AVR_ATmega164PA__)
#   define _FUNSAPE_MCU                 72
#elif defined(__AVR_ATmega165__)
#   define _FUNSAPE_MCU                 73
#elif defined(__AVR_ATmega165A__)
#   define _FUNSAPE_MCU                 74
#elif defined(__AVR_ATmega165P__)
#   define _FUNSAPE_MCU                 75
#elif defined(__AVR_ATmega165PA__)
#   define _FUNSAPE_MCU                 76
#elif defined(__AVR_ATmega168__)
#   define _FUNSAPE_MCU                 77
#elif defined(__AVR_ATmega168A__)
#   define _FUNSAPE_MCU                 78
#elif defined(__AVR_ATmega168P__)
#   define _FUNSAPE_MCU                 79
#elif defined(__AVR_ATmega168PA__)
#   define _FUNSAPE_MCU                 80
#elif defined(__AVR_ATmega168PB__)
#   define _FUNSAPE_MCU                 81
#elif defined(__AVR_ATmega169__)
#   define _FUNSAPE_MCU                 82
#elif defined(__AVR_ATmega169A__)
#   define _FUNSAPE_MCU                 83
#elif defined(__AVR_ATmega169P__)
#   define _FUNSAPE_MCU                 84
#elif defined(__AVR_ATmega169PA__)
#   define _FUNSAPE_MCU                 85
#elif defined(__AVR_ATmega16A__)
#   define _FUNSAPE_MCU                 86
#elif defined(__AVR_ATmega16HVA__)
#   define _FUNSAPE_MCU                 87
#elif defined(__AVR_ATmega16HVA2__)
#   define _FUNSAPE_MCU                 88
#elif defined(__AVR_ATmega16HVB__)
#   define _FUNSAPE_MCU                 89
#elif defined(__AVR_ATmega16HVBREVB__)
#   define _FUNSAPE_MCU                 90
#elif defined(__AVR_ATmega16M1__)
#   define _FUNSAPE_MCU                 91
#elif defined(__AVR_ATmega16U2__)
#   define _FUNSAPE_MCU                 92
#elif defined(__AVR_ATmega16U4__)
#   define _FUNSAPE_MCU                 93
#elif defined(__AVR_ATmega2560__)
#   define _FUNSAPE_MCU                 94
#elif defined(__AVR_ATmega2561__)
#   define _FUNSAPE_MCU                 95
#elif defined(__AVR_ATmega2564RFR2__)
#   define _FUNSAPE_MCU                 96
#elif defined(__AVR_ATmega256RFR2__)
#   define _FUNSAPE_MCU                 97
#elif defined(__AVR_ATmega32__)
#   define _FUNSAPE_MCU                 98
#elif defined(__AVR_ATmega323__)
#   define _FUNSAPE_MCU                 99
#elif defined(__AVR_ATmega324A__)
#   define _FUNSAPE_MCU                 100
#elif defined(__AVR_ATmega324P__)
#   define _FUNSAPE_MCU                 101
#elif defined(__AVR_ATmega324PA__)
#   define _FUNSAPE_MCU                 102
#elif defined(__AVR_ATmega325__)
#   define _FUNSAPE_MCU                 103
#elif defined(__AVR_ATmega3250__)
#   define _FUNSAPE_MCU                 104
#elif defined(__AVR_ATmega3250A__)
#   define _FUNSAPE_MCU                 105
#elif defined(__AVR_ATmega3250P__)
#   define _FUNSAPE_MCU                 106
#elif defined(__AVR_ATmega3250PA__)
#   define _FUNSAPE_MCU                 107
#elif defined(__AVR_ATmega325A__)
#   define _FUNSAPE_MCU                 108
#elif defined(__AVR_ATmega325P__)
#   define _FUNSAPE_MCU                 109
#elif defined(__AVR_ATmega325PA__)
#   define _FUNSAPE_MCU                 110
#elif defined(__AVR_ATmega328__)
#   define _FUNSAPE_MCU                 111
#elif defined(__AVR_ATmega328P__)
#   define _FUNSAPE_MCU                 112
#   include "atmega328p.hpp"
#elif defined(__AVR_ATmega329__)
#   define _FUNSAPE_MCU                 113
#elif defined(__AVR_ATmega3290__)
#   define _FUNSAPE_MCU                 114
#elif defined(__AVR_ATmega3290A__)
#   define _FUNSAPE_MCU                 115
#elif defined(__AVR_ATmega3290P__)
#   define _FUNSAPE_MCU                 116
#elif defined(__AVR_ATmega3290PA__)
#   define _FUNSAPE_MCU                 117
#elif defined(__AVR_ATmega329A__)
#   define _FUNSAPE_MCU                 118
#elif defined(__AVR_ATmega329P__)
#   define _FUNSAPE_MCU                 119
#elif defined(__AVR_ATmega329PA__)
#   define _FUNSAPE_MCU                 120
#elif defined(__AVR_ATmega32A__)
#   define _FUNSAPE_MCU                 121
#elif defined(__AVR_ATmega32C1__)
#   define _FUNSAPE_MCU                 122
#elif defined(__AVR_ATmega32HVB__)
#   define _FUNSAPE_MCU                 123
#elif defined(__AVR_ATmega32HVBREVB__)
#   define _FUNSAPE_MCU                 124
#elif defined(__AVR_ATmega32M1__)
#   define _FUNSAPE_MCU                 125
#elif defined(__AVR_ATmega32U2__)
#   define _FUNSAPE_MCU                 126
#elif defined(__AVR_ATmega32U4__)
#   define _FUNSAPE_MCU                 127
#elif defined(__AVR_ATmega32U6__)
#   define _FUNSAPE_MCU                 128
#elif defined(__AVR_ATmega406__)
#   define _FUNSAPE_MCU                 129
#elif defined(__AVR_ATmega48__)
#   define _FUNSAPE_MCU                 130
#elif defined(__AVR_ATmega48A__)
#   define _FUNSAPE_MCU                 131
#elif defined(__AVR_ATmega48P__)
#   define _FUNSAPE_MCU                 132
#elif defined(__AVR_ATmega48PA__)
#   define _FUNSAPE_MCU                 133
#elif defined(__AVR_ATmega48PB__)
#   define _FUNSAPE_MCU                 134
#elif defined(__AVR_ATmega64__)
#   define _FUNSAPE_MCU                 135
#elif defined(__AVR_ATmega640__)
#   define _FUNSAPE_MCU                 136
#elif defined(__AVR_ATmega644__)
#   define _FUNSAPE_MCU                 137
#elif defined(__AVR_ATmega644A__)
#   define _FUNSAPE_MCU                 138
#elif defined(__AVR_ATmega644P__)
#   define _FUNSAPE_MCU                 139
#elif defined(__AVR_ATmega644PA__)
#   define _FUNSAPE_MCU                 140
#elif defined(__AVR_ATmega644RFR2__)
#   define _FUNSAPE_MCU                 141
#elif defined(__AVR_ATmega645__)
#   define _FUNSAPE_MCU                 142
#elif defined(__AVR_ATmega6450__)
#   define _FUNSAPE_MCU                 143
#elif defined(__AVR_ATmega6450A__)
#   define _FUNSAPE_MCU                 144
#elif defined(__AVR_ATmega6450P__)
#   define _FUNSAPE_MCU                 145
#elif defined(__AVR_ATmega645A__)
#   define _FUNSAPE_MCU                 146
#elif defined(__AVR_ATmega645P__)
#   define _FUNSAPE_MCU                 147
#elif defined(__AVR_ATmega649__)
#   define _FUNSAPE_MCU                 148
#elif defined(__AVR_ATmega6490__)
#   define _FUNSAPE_MCU                 149
#elif defined(__AVR_ATmega6490A__)
#   define _FUNSAPE_MCU                 150
#elif defined(__AVR_ATmega6490P__)
#   define _FUNSAPE_MCU                 151
#elif defined(__AVR_ATmega649A__)
#   define _FUNSAPE_MCU                 152
#elif defined(__AVR_ATmega649P__)
#   define _FUNSAPE_MCU                 153
#elif defined(__AVR_ATmega64A__)
#   define _FUNSAPE_MCU                 154
#elif defined(__AVR_ATmega64C1__)
#   define _FUNSAPE_MCU                 155
#elif defined(__AVR_ATmega64HVE__)
#   define _FUNSAPE_MCU                 156
#elif defined(__AVR_ATmega64HVE2__)
#   define _FUNSAPE_MCU                 157
#elif defined(__AVR_ATmega64M1__)
#   define _FUNSAPE_MCU                 158
#elif defined(__AVR_ATmega64RFR2__)
#   define _FUNSAPE_MCU                 159
#elif defined(__AVR_ATmega8__)
#   define _FUNSAPE_MCU                 160
#elif defined(__AVR_ATmega8515__)
#   define _FUNSAPE_MCU                 161
#elif defined(__AVR_ATmega8535__)
#   define _FUNSAPE_MCU                 162
#elif defined(__AVR_ATmega88__)
#   define _FUNSAPE_MCU                 163
#elif defined(__AVR_ATmega88A__)
#   define _FUNSAPE_MCU                 164
#elif defined(__AVR_ATmega88P__)
#   define _FUNSAPE_MCU                 165
#elif defined(__AVR_ATmega88PA__)
#   define _FUNSAPE_MCU                 166
#elif defined(__AVR_ATmega88PB__)
#   define _FUNSAPE_MCU                 167
#elif defined(__AVR_ATmega8A__)
#   define _FUNSAPE_MCU                 168
#elif defined(__AVR_ATmega8HVA__)
#   define _FUNSAPE_MCU                 169
#elif defined(__AVR_ATmega8U2__)
#   define _FUNSAPE_MCU                 170
#elif defined(__AVR_ATtiny10__)
#   define _FUNSAPE_MCU                 171
#elif defined(__AVR_ATtiny11__)
#   define _FUNSAPE_MCU                 172
#elif defined(__AVR_ATtiny12__)
#   define _FUNSAPE_MCU                 173
#elif defined(__AVR_ATtiny13__)
#   define _FUNSAPE_MCU                 174
#elif defined(__AVR_ATtiny13A__)
#   define _FUNSAPE_MCU                 175
#elif defined(__AVR_ATtiny15__)
#   define _FUNSAPE_MCU                 176
#elif defined(__AVR_ATtiny1634__)
#   define _FUNSAPE_MCU                 177
#elif defined(__AVR_ATtiny167__)
#   define _FUNSAPE_MCU                 178
#elif defined(__AVR_ATtiny20__)
#   define _FUNSAPE_MCU                 179
#elif defined(__AVR_ATtiny22__)
#   define _FUNSAPE_MCU                 180
#elif defined(__AVR_ATtiny2313__)
#   define _FUNSAPE_MCU                 181
#elif defined(__AVR_ATtiny2313A__)
#   define _FUNSAPE_MCU                 182
#elif defined(__AVR_ATtiny24__)
#   define _FUNSAPE_MCU                 183
#elif defined(__AVR_ATtiny24A__)
#   define _FUNSAPE_MCU                 184
#elif defined(__AVR_ATtiny25__)
#   define _FUNSAPE_MCU                 185
#elif defined(__AVR_ATtiny26__)
#   define _FUNSAPE_MCU                 186
#elif defined(__AVR_ATtiny261__)
#   define _FUNSAPE_MCU                 187
#elif defined(__AVR_ATtiny261A__)
#   define _FUNSAPE_MCU                 188
#elif defined(__AVR_ATtiny28__)
#   define _FUNSAPE_MCU                 189
#elif defined(__AVR_ATtiny4__)
#   define _FUNSAPE_MCU                 190
#elif defined(__AVR_ATtiny40__)
#   define _FUNSAPE_MCU                 191
#elif defined(__AVR_ATtiny4313__)
#   define _FUNSAPE_MCU                 192
#elif defined(__AVR_ATtiny43U__)
#   define _FUNSAPE_MCU                 193
#elif defined(__AVR_ATtiny44__)
#   define _FUNSAPE_MCU                 194
#elif defined(__AVR_ATtiny441__)
#   define _FUNSAPE_MCU                 195
#elif defined(__AVR_ATtiny44A__)
#   define _FUNSAPE_MCU                 196
#elif defined(__AVR_ATtiny45__)
#   define _FUNSAPE_MCU                 197
#elif defined(__AVR_ATtiny461__)
#   define _FUNSAPE_MCU                 198
#elif defined(__AVR_ATtiny461A__)
#   define _FUNSAPE_MCU                 199
#elif defined(__AVR_ATtiny48__)
#   define _FUNSAPE_MCU                 200
#elif defined(__AVR_ATtiny5__)
#   define _FUNSAPE_MCU                 201
#elif defined(__AVR_ATtiny828__)
#   define _FUNSAPE_MCU                 202
#elif defined(__AVR_ATtiny84__)
#   define _FUNSAPE_MCU                 203
#elif defined(__AVR_ATtiny841__)
#   define _FUNSAPE_MCU                 204
#elif defined(__AVR_ATtiny84A__)
#   define _FUNSAPE_MCU                 205
#elif defined(__AVR_ATtiny85__)
#   define _FUNSAPE_MCU                 206
#elif defined(__AVR_ATtiny861__)
#   define _FUNSAPE_MCU                 207
#elif defined(__AVR_ATtiny861A__)
#   define _FUNSAPE_MCU                 208
#elif defined(__AVR_ATtiny87__)
#   define _FUNSAPE_MCU                 209
#elif defined(__AVR_ATtiny88__)
#   define _FUNSAPE_MCU                 210
#elif defined(__AVR_ATtiny9__)
#   define _FUNSAPE_MCU                 211
#elif defined(__AVR_M3000__)
#   define _FUNSAPE_MCU                 212
#endif

// Final MCU Part number
#if !defined(_FUNSAPE_MCU)
#   error [mcuDevice.hpp] Error 4 - Microcontroller not defined!
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Mcu_Part_Number" in "Mcu_Device"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Mcu_Device"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __MCU_DEVICE_HPP

// =============================================================================
// End of file (mcuDevice.hpp)
// =============================================================================
