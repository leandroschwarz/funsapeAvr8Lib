//!
//! ****************************************************************************
//! @file           globalDefines.hpp
//! @author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! @brief          Global definitions file.
//! @details        This file provides new data types, constants and other basic
//!                     elements that are useful throughout all other modules
//!                     of the FunSAPE++ AVR8 Library.
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

#ifndef __GLOBAL_DEFINES_HPP
#define __GLOBAL_DEFINES_HPP            2604

// =============================================================================
// Basic definitions
// =============================================================================

#ifndef F_CPU
#   define F_CPU    16000000UL
#endif

// =============================================================================
// Dependencies
// =============================================================================

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

// *INDENT-OFF*
#include "config/mcuDevice.hpp"
#ifndef __MCU_DEVICE_HPP
#   error [globalDefines.hpp] Error 1 - Header file (mcuDevice.hpp) is missing \
        or corrupted!
#elif __MCU_DEVICE_HPP != __GLOBAL_DEFINES_HPP
#   error [globalDefines.hpp] Error 2 - Build mismatch between file \
        (mcuDevice.hpp) and global definitions file (globalDefines.hpp)!
#endif
// *INDENT-ON*

//     //////////////////     AVR STANDARD LIBRARY     //////////////////     //

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <util/delay.h>

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Global_Definitions
//! @brief          System global definitions.
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
// Doxygen: Start subgroup "Alias" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Alias
//! @brief          Alias definitions.
//! @{
//!

//!
//! @details        Alias to shorten unused attribute.
//!
#define ignored     __attribute__((unused))

//!
//! @details        Alias to shorten inline attribute.
//!
#define inlined     inline __attribute__((always_inline))

//!
//! @details        Alias to shorten weak attribute.
//!
#define weakened    __attribute__((weak))

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Alias" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Macro functions
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Validity" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Data_Validity
//! @brief          Data validation macro-functions.
//! @{
//!

//     //////////////////////     DATA VALIDITY    //////////////////////     //

//!
//! @def            isGpioAddressValid(gpioPort)
//! @details        Checks if the given parameter @a gpioPort is a valid GPIO
//!                     port address. Valid GPIO addresses are @c DDRx, @c PORTx
//!                     and @c PINx register addresses.
//! @param[in]      gpioPort            GPIO port address
//! @retval         true                if GPIO address is valid
//! @retval         false               if GPIO address is not valid
//!
#define isGpioAddressValid(gpioPort)    (bool_t)(       \
        (IS_GPIO_ALL_INSTANCE(gpioPort))                \
        ? true                                          \
        : false                                         \
)

//!
//! @def            isGpioPinIndexValid(gpioPort, gpioPin)
//! @details        Checks if the given parameter @a gpioPin of the given
//!                     @a gpioPort is a valid GPIO pin index.
//! @param[in]      gpioPort            GPIO port address
//! @param[in]      gpioPin             GPIO pin index
//! @retval         true                if GPIO pin index is valid
//! @retval         false               if GPIO pin index is not valid
//!
#define isGpioPinIndexValid(gpioPort, gpioPin)    (bool_t)(     \
        (IS_GPIO_ALL_PIN_NUMBER(gpioPort, gpioPin))             \
        ? true                                                  \
        : false                                                 \
)

//!
//! @def            isPointerValid(ptr)
//! @details        Checks if the given parameter @a ptr is a valid pointer
//!                     address.
//! @param[in]      ptr                 pointer address
//! @retval         true                if pointer address is valid
//! @retval         false               if pointer address is not valid
//!
#define isPointerValid(ptr)             (bool_t)(       \
        ((void *)(ptr))                                 \
        ? true                                          \
        : false                                         \
)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Validity" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Bit_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Bit_Handling
//! @details        Performs bitwise operations in one bit of a variable or
//!                     register.
//! @{
//!

//     //////////////////////     BIT HANDLING     //////////////////////     //

#ifndef clrBit
//!
//! @def            clrBit(reg, pos)
//! @details        Clears the bit at position @a pos of the register or
//!                     variable @a reg.
//! @param[in,out]  reg                 register or variable
//! @param[in]      pos                 position of the bit to be cleared
//!
#   define clrBit(reg, pos)             do{     \
        (reg) &= ~(1 << (pos));                 \
    }while(0)
#endif

#ifndef cplBit
//!
//! @def            cplBit(reg, pos)
//! @details        Complements (invert) the bit at position @a pos of the
//!                     register or variable @a reg.
//! @param[in,out]  reg                 register or variable
//! @param[in]      pos                 position of the bit to be complemented
//!
#   define cplBit(reg, pos)             do{     \
        (reg) ^= (1 << (pos));                  \
    }while(0)
#endif

#ifndef setBit
//!
//! @def            setBit(reg, pos)
//! @details        Sets the bit at position @a pos of the register or variable
//!                     @a reg.
//! @param[in,out]  reg                 register or variable
//! @param[in]      pos                 position of the bit to be set
//!
#   define setBit(reg, pos)             do{     \
        (reg) |= (1 << (pos));                  \
    }while(0)
#endif

//     ///////////////////////     BIT TESTING    ///////////////////////     //

#ifndef isBitClr
//!
//! @def            isBitClr(reg, pos)
//! @details        Verifies if the bit at position @a pos at the register or
//!                     variable @a reg is cleared.
//! @param[in]      reg                 register or variable
//! @param[in]      pos                 position of the bit to be evaluated
//! @retval         true                if the bit is cleared
//! @retval         false               if the bit is set
//!
#   define isBitClr(reg, pos)           (bool_t)(!isBitSet(reg,pos))
#endif

#ifndef isBitSet
//!
//! @def            isBitSet(reg, pos)
//! @details        Verifies if the bit at position @a pos at the register or
//!                     variable @a reg is set.
//! @param[in]      reg                 register or variable
//! @param[in]      pos                 position of the bit to be evaluated
//! @retval         true                if the bit is set
//! @retval         false               if the bit is cleared
//!
#   define isBitSet(reg, pos)           (bool_t)(((reg) >> (pos)) & 1)
#endif

//     ///////////////////////     BIT LOOPING    ///////////////////////     //

#ifndef waitUntilBitIsClear
//!
//! @def            waitUntilBitIsClear(reg, pos)
//! @details        Blocks the code execution while the bit in position @a pos
//!                     in register or variable @a reg is set.
//! @param[in]      reg                 register or variable
//! @param[in]      pos                 position of the bit to be evaluated
//!
#   define waitUntilBitIsClear(reg, pos)        do{     \
        doNothing();                                    \
    }while(isBitSet((reg), (pos)))
#endif

#ifndef waitUntilBitIsSet
//!
//! @def            waitUntilBitIsSet(reg, pos)
//! @details        Blocks the code execution while the bit in position @a pos
//!                     in register or variable @a reg is cleared.
//! @param[in]      reg                 register or variable
//! @param[in]      pos                 position of the bit to be evaluated
//!
#   define waitUntilBitIsSet(reg, pos)  do{     \
        doNothing();                            \
    } while (isBitClr((reg), (pos)))
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Bit_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Mask_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Mask_Handling
//! @details        Performs bitwise operations in a set of one bits of a
//!                     variable or register.
//! @attention      The desired bits of the mask must be always marked as '1',
//!                     even when the mask is used in a clear operation.
//! @{
//!

//     ////////////////////     BIT MASK HANDLING    ////////////////////     //

#ifndef clrMask
//!
//! @def            clrMask(reg, mask)
//! @details        Clears the bits of the register or variable @a reg that are
//!                     set on the supplied mask @a mask.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be cleared
//!
#   define clrMask(reg, mask)           do{     \
        (reg) &= ~(mask);                       \
    }while(0)
#endif

#ifndef cplMask
//!
//! @def            cplMask(reg, mask)
//! @details        Complements (inverts) the bits of the register or variable
//!                     @a reg that are set on the supplied mask @a mask.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be complemented
//!
#   define cplMask(reg, mask)           do{     \
        (reg) ^= (mask);                        \
    }while(0)
#endif

#ifndef setMask
//!
//! @def            setMask(reg, mask)
//! @details        Sets the bits of the register or variable @a reg that are
//!                     set on the supplied mask @a mask.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be set
//!
#   define setMask(reg, mask)           do{     \
        (reg) |= (mask);                        \
    }while(0)
#endif

//     ////////////////     BIT MASK OFFSET HANDLING     ////////////////     //

#ifndef clrMaskOffset
//!
//! @def            clrMaskOffset(reg, mask, offset)
//! @details        Clears the bits of the register or variable @a reg that are
//!                     set on the supplied mask @a mask. The mask is first
//!                     left-shifted by the value given in @a offset.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be cleared
//! @param[in]      offset              left-shift offset value
//!
#   define clrMaskOffset(reg, mask, offset)     do{     \
        (reg) &= ~((mask) << (offset));                 \
    }while(0)
#endif

#ifndef cplMaskOffset
//!
//! @def            cplMaskOffset(reg, mask, offset)
//! @details        Complements (inverts) the bits of the register or variable
//!                     @a reg that are set on the supplied mask @a mask. The
//!                     mask is first left-shifted by the value given in
//!                     @a offset.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be complemented
//! @param[in]      offset              left-shift offset value
//!
#   define cplMaskOffset(reg, mask, offset)     do{     \
        (reg) ^= ((mask) << (offset));                  \
    }while(0)
#endif

#ifndef setMaskOffset
//!
//! @def            setMaskOffset(reg, mask, offset)
//! @details        Sets the bits of the register or variable @a reg that are
//!                     set on the supplied mask @a mask. The mask is first
//!                     left-shifted by the value given in @a offset.
//! @param[in,out]  reg                 register or variable
//! @param[in]      mask                one-mask of the bits to be set
//! @param[in]      offset              left-shift offset value
//!
#   define setMaskOffset(reg, mask, offset)     do{     \
        (reg) |= ((mask) << (offset));                  \
    }while(0)
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Mask_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Pin_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Pin_Handling
//! @details        Performs basic bitwise operations in an I/O pin.
//! @{
//!

//     ////////////////////     I/O PIN HANDLING     ////////////////////     //

//!
//! @def            clrIoPin(portAddress, portPin)
//! @brief          Clears a GPIO pin.
//! @details        Clears the bit corresponding to @a portPin in the port
//!                     register pointed to by @a portAddress.
//! @param[in,out]  portAddress         address of the GPIO port (e.g., &PORTB)
//! @param[in]      portPin             index of the pin (0-7)
//!
#define clrIoPin(portAddress, portPin)          do{             \
        clrBit(*(getGpioPortAddress(portAddress)), portPin);    \
    } while(0)

//!
//! @def            cplIoPin(portAddress, portPin)
//! @brief          Toggles a GPIO pin.
//! @details        Complements the bit corresponding to @a portPin in the port
//!                     register pointed to by @a portAddress.
//! @param[in,out]  portAddress         address of the GPIO port (e.g., &PORTB)
//! @param[in]      portPin             index of the pin (0-7)
//!
#define cplIoPin(portAddress, portPin)          do{             \
        cplBit(*(getGpioPortAddress(portAddress)), portPin);    \
    } while(0)

//!
//! @def            setIoPin(portAddress, portPin)
//! @brief          Sets a GPIO pin.
//! @details        Sets the bit corresponding to @a portPin in the port
//!                     register pointed to by @a portAddress.
//! @param[in,out]  portAddress         address of the GPIO port (e.g., &PORTB)
//! @param[in]      portPin             index of the pin (0-7)
//!
#define setIoPin(portAddress, portPin)          do{             \
        setBit(*(getGpioPortAddress(portAddress)), portPin);    \
    } while(0)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Pin_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Data_Handling
//! @details        Performs general data handling, shifting and swapping a
//!                      variable data.
//! @{
//!

//     /////////////     DATA MANIPULATION (8-BITS WIDE)    /////////////     //

//!
//! @def            byteGetNibble1(dataByte)
//! @details        Returns the nibble 1 of the given @a dataByte byte.
//! @param[in]      dataByte            variable
//! @return         @a dataByte nibble 1, shifted to bit position 0
//!
#define byteGetNibble1(dataByte)        (       \
        ((dataByte) >> 4) & 0x0F                \
)

//!
//! @def            byteGetNibble0(dataByte)
//! @details        Returns the nibble 0 of the given @a dataByte byte.
//! @param[in]      dataByte            variable
//! @return         @a dataByte nibble 0
//!
#define byteGetNibble0(dataByte)        (       \
        (dataByte) & 0x0F                       \
)

//!
//! @def            byteSwitchNibbles(dataByte)
//! @details        Switches the nibbles of the given @a dataByte byte.
//! @param[in]      dataByte            variable
//! @return         @a dataByte with nibbles switched
//!
#define byteSwitchNibbles(dataByte)     (       \
        (byteGetNibble0(dataByte) << 4) |       \
        (byteGetNibble1(dataByte))              \
)

//     ////////////     DATA MANIPULATION (16-BITS WIDE)     ////////////     //

//!
//! @def            hwordGetByte1(dataHword)
//! @details        Returns the byte 1 of the given @a dataHword half-word.
//! @param[in]      dataHword           variable
//! @return         @a dataHword byte 1, shifted to bit position 0
//!
#define hwordGetByte1(dataHword)        (       \
        ((dataHword) >> 8) & 0x00FF             \
)

//!
//! @def            hwordGetByte0(dataHword)
//! @details        Returns the byte 0 of the given @a dataHword half-word.
//! @param[in]      dataHword           variable
//! @return         @a dataHword byte 0
//!
#define hwordGetByte0(dataHword)        (       \
        (dataHword) & 0x00FF                    \
)

//!
//! @def            hwordSwitchBytes(dataHword)
//! @details        Switches the bytes of the given @a dataHword half-word.
//! @param[in]      dataHword           variable
//! @return         @a dataHword with bytes switched
//!
#define hwordSwitchBytes(dataHword)     (       \
        (hwordGetByte0(dataHword) << 8) |       \
        (hwordGetByte1(dataHword))              \
)

//     ////////////     DATA MANIPULATION (32-BITS WIDE)     ////////////     //

//!
//! @def            wordGetByte3(dataWord)
//! @details        Returns the byte 3 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord byte 3, shifted to bit position 0
//!
#define wordGetByte3(dataWord)          (       \
        ((dataWord) >> 24) & 0x000000FF         \
)

//!
//! @def            wordGetByte2(dataWord)
//! @details        Returns the byte 2 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord byte 2, shifted to bit position 0
//!
#define wordGetByte2(dataWord)          (       \
        ((dataWord) >> 16) & 0x000000FF         \
)

//!
//! @def            wordGetByte1(dataWord)
//! @details        Returns the byte 1 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord byte 1, shifted to bit position 0
//!
#define wordGetByte1(dataWord)          (       \
        ((dataWord) >> 8) & 0x000000FF          \
)

//!
//! @def            wordGetByte0(dataWord)
//! @details        Returns the byte 0 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord byte 0
//!
#define wordGetByte0(dataWord)          (       \
        (dataWord) & 0x000000FF                 \
)

//!
//! @def            wordSwitchBytes(dataWord)
//! @details        Switches the bytes of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord with bytes switched
//!
#define wordSwitchBytes(dataWord)       (       \
        (wordGetByte0(dataWord) << 24) |        \
        (wordGetByte1(dataWord) << 16) |        \
        (wordGetByte2(dataWord) << 8)  |        \
        (wordGetByte3(dataWord))                \
)

//!
//! @def            wordGetHword1(dataWord)
//! @details        Returns the half word 1 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord half word 1, shifted to bit position 0
//!
#define wordGetHword1(dataWord)         (       \
        ((dataWord) >> 16) & 0x0000FFFF         \
)

//!
//! @def            wordGetHword0(dataWord)
//! @details        Returns the half word 0 of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord half word 0
//!
#define wordGetHword0(dataWord)         (       \
        (dataWord) & 0x0000FFFF                 \
)

//!
//! @def            wordSwitchHwords(dataWord)
//! @details        Switches the half words of the given @a dataWord word.
//! @param[in]      dataWord            variable
//! @return         @a dataWord with half words switched
//!
#define wordSwitchHwords(dataWord)      (       \
        (wordGetHword0(dataWord) << 16) |       \
        (wordGetHword1(dataWord))               \
)

//     ////////////     DATA MANIPULATION (64-BITS WIDE)     ////////////     //

//!
//! @def            dwordGetByte7(dataDword)
//! @details        Returns the byte 7 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 7, shifted to bit position 0
//!
#define dwordGetByte7(dataDword)        (               \
        ((dataDword) >> 56) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte6(dataDword)
//! @details        Returns the byte 6 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 6, shifted to bit position 0
//!
#define dwordGetByte6(dataDword)        (               \
        ((dataDword) >> 48) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte5(dataDword)
//! @details        Returns the byte 5 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 5, shifted to bit position 0
//!
#define dwordGetByte5(dataDword)        (               \
        ((dataDword) >> 40) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte4(dataDword)
//! @details        Returns the byte 4 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 4, shifted to bit position 0
//!
#define dwordGetByte4(dataDword)        (               \
        ((dataDword) >> 32) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte3(dataDword)
//! @details        Returns the byte 3 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 3, shifted to bit position 0
//!
#define dwordGetByte3(dataDword)        (               \
        ((dataDword) >> 24) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte2(dataDword)
//! @details        Returns the byte 2 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 2, shifted to bit position 0
//!
#define dwordGetByte2(dataDword)        (               \
        ((dataDword) >> 16) & 0x00000000000000FF        \
)

//!
//! @def            dwordGetByte1(dataDword)
//! @details        Returns the byte 1 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 1, shifted to bit position 0
//!
#define dwordGetByte1(dataDword)        (               \
        ((dataDword) >> 8) & 0x00000000000000FF     \
)

//!
//! @def            dwordGetByte0(dataDword)
//! @details        Returns the byte 0 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword byte 0
//!
#define dwordGetByte0(dataDword)        (               \
        (dataDword) & 0x00000000000000FF        \
)

//!
//! @def            dwordSwitchBytes(dataDword)
//! @details        Switches the bytes of the given @a dataDWord double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword with bytes switched
//!
#define dwordSwitchBytes(dataDword)     (       \
        (dwordGetByte0(dataDword) << 56) |      \
        (dwordGetByte1(dataDword) << 48) |      \
        (dwordGetByte2(dataDword) << 40) |      \
        (dwordGetByte3(dataDword) << 32) |      \
        (dwordGetByte4(dataDword) << 24) |      \
        (dwordGetByte5(dataDword) << 16) |      \
        (dwordGetByte6(dataDword) << 8)  |      \
        (dwordGetByte7(dataDword))              \
)

//!
//! @def            dwordGetHword3(dataDword)
//! @details        Returns the half word 3 of the given @a dataDword double
//!                     word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword half word 3, shifted to bit position 0
//!
#define dwordGetHword3(dataDword)       (               \
        ((dataDword) >> 48) & 0x000000000000FFFF        \
)

//!
//! @def            dwordGetHword2(dataDword)
//! @details        Returns the half word 2 of the given @a dataDword double
//!                     word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword half word 2, shifted to bit position 0
//!
#define dwordGetHword2(dataDword)       (               \
        ((dataDword) >> 32) & 0x000000000000FFFF        \
)

//!
//! @def            dwordGetHword1(dataDword)
//! @details        Returns the half word 1 of the given @a dataDword double
//!                     word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword half word 1, shifted to bit position 0
//!
#define dwordGetHword1(dataDword)       (               \
        ((dataDword) >> 16) & 0x000000000000FFFF        \
)

//!
//! @def            dwordGetHword0(dataDword)
//! @details        Returns the half word 0 of the given @a dataDword double
//!                     word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword half word 0
//!
#define dwordGetHword0(dataDword)       (               \
        ((dataDword) >> 0) & 0x000000000000FFFF         \
)

//!
//! @def            dwordSwitchHwords(dataDword)
//! @details        Switches the half words of the given @a dataDWord double
//!                     word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword with half words switched
//!
#define dwordSwitchHwords(dataDword)    (       \
        (dwordGetHword0(dataDword) << 48) |     \
        (dwordGetHword1(dataDword) << 32) |     \
        (dwordGetHword2(dataDword) << 16) |     \
        (dwordGetHword3(dataDword))             \
)

//!
//! @def            dwordGetWord1(dataDword)
//! @details        Returns the word 1 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword word 1, shifted to bit position 0
//!
#define dwordGetWord1(dataDword)         (              \
        ((dataDword) >> 32) & 0x00000000FFFFFFFF        \
)

//!
//! @def            dwordGetWord0(dataDword)
//! @details        Returns the word 0 of the given @a dataDword double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword word 1
//!
#define dwordGetWord0(dataDword)         (      \
        (dataDword) & 0x00000000FFFFFFFF        \
)

//!
//! @def            dwordSwitchWords(dataDword)
//! @details        Switches the words of the given @a dataDWord double word.
//! @param[in]      dataDword           variable
//! @return         @a dataDword with words switched
//!
#define dwordSwitchWords(dataDword)     (       \
        (dwordGetWord0(dataDword) << 32) |      \
        (dwordGetWord1(dataDword))              \
)

//     /////////////////////     TRUNCATE VALUES    /////////////////////     //

//!
//! @def            getMaximumOf(var1, var2)
//! @details        Returns the greater value between @a var1 and @a var2.
//! @param[in]      var1                first value
//! @param[in]      var2                second value
//! @return         the greater value between @a var1 and @a var2
//!
#define getMaximumOf(var1, var2)        (       \
        ((var1) > (var2))                       \
        ? (var1)                                \
        : (var2)                                \
)

//!
//! @def            getMinimumOf(var1, var2)
//! @details        Returns the lower value between @a var1 and @a var2.
//! @param[in]      var1                first value
//! @param[in]      var2                second value
//! @return         the lower value between @a var1 and @a var2
//!
#define getMinimumOf(var1, var2)        (       \
        ((var1) < (var2))                       \
        ? (var1)                                \
        : (var2)                                \
)

//!
//! @def            truncateBetween(var, min, max)
//! @details        Truncates (trims) the value between maximum and minimum
//!                     values.
//! @warning        The macro-function will not work correctly if @a min is
//!                     greater than @a max.
//! @param[in]      var                 value to be truncated
//! @param[in]      max                 maximum allowed value
//! @param[in]      min                 minimum allowed value
//! @return         @a min              if the value is lower than @a min
//! @return         @a max              if the value is greater than @a max
//! @return         @a var              if the value is placed between @a min
//!                                          and @a max
//!
#define truncateBetween(var, min, max)  (       \
        ((var) < (min))                         \
        ? (min)                                 \
        : (((var) > (max))                      \
                ? (max)                         \
                : (var)                         \
        )                                       \
)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     String_Handling
//! @details        Performs general handling on @c characters and @c strings.
//! @{
//!

//     //////////////////////     STRINGIFYING    ///////////////////////     //

//!
//! @def            stringifyName(constant)
//! @brief          Converts a constant name to a string literal.
//! @param[in]      constant            The constant name to stringify.
//!
#define stringifyName(constant)         #constant

//!
//! @def            stringifyValue(constant)
//! @brief          Converts a constant value to a string literal.
//! @details        Uses a two-step expansion to stringify the value of the
//!                     macro instead of its name.
//! @param[in]      constant            The constant to stringify.
//!
#define stringifyValue(constant)        stringifyName(constant)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// New data types
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Types" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Data_Types
//! @brief          Definition of new data types.
//! @{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Single_Types" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Single_Types
//! @details        Single variables renaming or shortening names.
//! @{
//!

//     ////////////////////     BASIC VARIABLES     /////////////////////     //

//!
//! @typedef        bool_t
//! @details        Renamed to ensure code standardization.
//!
typedef bool                            bool_t;

//!
//! @typedef        char_t
//! @details        Renamed to ensure code standardization.
//!
typedef char                            char_t;

//     ///////////////////     CONSTANT VARIABLES    ////////////////////     //

//!
//! @typedef        cbool_t
//! @details        Alias for <b><tt>const bool</tt></b>.
//!
typedef const bool_t                    cbool_t;

//!
//! @typedef        cchar_t
//! @details        Alias for <b><tt>const char</tt></b>.
//!
typedef const char_t                    cchar_t;

//!
//! @typedef        cint8_t
//! @details        Alias for <b><tt>const int8_t</tt></b>.
//!
typedef const int8_t                    cint8_t;

//!
//! @typedef        cint16_t
//! @details        Alias for <b><tt>const int16_t</tt></b>.
//!
typedef const int16_t                   cint16_t;

//!
//! @typedef        cint32_t
//! @details        Alias for <b><tt>const int32_t</tt></b>.
//!
typedef const int32_t                   cint32_t;

//!
//! @typedef        cint64_t
//! @details        Alias for <b><tt>const int64_t</tt></b>.
//!
typedef const int64_t                   cint64_t;

//!
//! @typedef        cuint8_t
//! @details        Alias for <b><tt>const uint8_t</tt></b>.
//!
typedef const uint8_t                   cuint8_t;

//!
//! @typedef        cuint16_t
//! @details        Alias for <b><tt>const uint16_t</tt></b>.
//!
typedef const uint16_t                  cuint16_t;

//!
//! @typedef        cuint32_t
//! @details        Alias for <b><tt>const uint32_t</tt></b>.
//!
typedef const uint32_t                  cuint32_t;

//!
//! @typedef        cuint64_t
//! @details        Alias for <b><tt>const uint64_t</tt></b>.
//!
typedef const uint64_t                  cuint64_t;

//     ///////////////////     VOLATILE VARIABLES    ////////////////////     //

//!
//! @typedef        vbool_t
//! @details        Alias for <b><tt>volatile bool</tt></b>.
//!
typedef volatile bool_t                 vbool_t;

//!
//! @typedef        vchar_t
//! @details        Alias for <b><tt>volatile char</tt></b>.
//!
typedef volatile char_t                 vchar_t;

//!
//! @typedef        vint8_t
//! @details        Alias for <b><tt>volatile int8_t</tt></b>.
//!
typedef volatile int8_t                 vint8_t;

//!
//! @typedef        vint16_t
//! @details        Alias for <b><tt>volatile int16_t</tt></b>.
//!
typedef volatile int16_t                vint16_t;

//!
//! @typedef        vint32_t
//! @details        Alias for <b><tt>volatile int32_t</tt></b>.
//!
typedef volatile int32_t                vint32_t;

//!
//! @typedef        vint64_t
//! @details        Alias for <b><tt>volatile int64_t</tt></b>.
//!
typedef volatile int64_t                vint64_t;

//!
//! @typedef        vuint8_t
//! @details        Alias for <b><tt>volatile uint8_t</tt></b>.
//!
typedef volatile uint8_t                vuint8_t;

//!
//! @typedef        vuint16_t
//! @details        Alias for <b><tt>volatile uint16_t</tt></b>.
//!
typedef volatile uint16_t               vuint16_t;

//!
//! @typedef        vuint32_t
//! @details        Alias for <b><tt>volatile uint32_t</tt></b>.
//!
typedef volatile uint32_t               vuint32_t;

//!
//! @typedef        vuint64_t
//! @details        Alias for <b><tt>volatile uint64_t</tt></b>.
//!
typedef volatile uint64_t               vuint64_t;

//     ////////////     AVR PLATFORM SPECIFIC VARIABLES     /////////////     //

//!
//! @typedef        int_t
//! @details        Standard <b><tt>int</tt></b> type (16-bit in AVR
//!                     processors).
//!
typedef int16_t                         int_t;

//!
//! @typedef        uint_t
//! @details        Standard <b><tt>unsigned int</tt></b> type (16-bit in AVR
//!                     processors).
//!
typedef uint16_t                        uint_t;

//!
//! @typedef        cint_t
//! @details        Standard <b><tt>const int</tt></b> type (16-bit in AVR
//!                     processors).
//!
typedef cint16_t                        cint_t;

//!
//! @typedef        cuint_t
//! @details        Standard <b><tt>const unsigned int</tt></b> type (16-bit in
//!                     AVR processors).
//!
typedef cuint16_t                       cuint_t;

//!
//! @typedef        vint_t
//! @details        Standard <b><tt>volatile int</tt></b> type (16-bit in AVR
//!                     processors).
//!
typedef vint16_t                        vint_t;

//!
//! @typedef        vuint_t
//! @details        Standard <b><tt>volatile unsigned int</tt></b> type (16-bit
//!                     in AVR processors).
//!
typedef vuint16_t                       vuint_t;

//!
//! @typedef        ioPinIndex_t
//! @details        Alias to handle a GPIO pin index.
//!
typedef uint8_t                         ioPinIndex_t;

//!
//! @typedef        ioPinMask_t
//! @details        Alias to handle a GPIO pin mask.
//!
typedef uint8_t                         ioPinMask_t;

//!
//! @typedef        ioRegAddress_t
//! @details        Alias to handle a GPIO register address.
//!
typedef vuint8_t                       *ioRegAddress_t;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Single_Types" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Binary_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Binary_Enumerations
//! @details        Enumerations with only two possible values.
//! @{
//!

//     //////////////////     BINARY ENUMERATIONS     ///////////////////     //

//!
//! @enum           Activation
//! @details        Used to refer to the activation state of a peripheral.
//!
enum class Activation : cbool_t {
    OFF             = false,            //!< Deactivated
    ON              = true              //!< Activated
};

//!
//! @enum           DisplayOrientation
//! @details        Used to refer to the orientation of a display screen.
//!
enum class DisplayOrientation : cbool_t {
    LANDSCAPE       = false,            //!< Display is in landscape orientation
    PORTRAIT        = true              //!< Display is in portrait orientation
};

//!
//! @enum           DriverMode
//! @details        Used to refer to the GPIO pin output driver mode.
//!
enum class DriverMode : cbool_t {
    PUSH_PULL       = false,            //!< Push-pull driver
    OPEN_DRAIN      = true,             //!< Open-drain driver
};

//!
//! @enum           Edge
//! @details        Used to specify the edge of a signal.
//!
enum class Edge : cbool_t {
    FALLING         = false,            //!< Falling edge of the signal
    RISING          = true              //!< Rising edge of the signal
};

//!
//! @enum           IoOperation
//! @details        Used to specify the GPIO or communications operation.
//!
enum class IoOperation : cbool_t {
    WRITE           = false,            //!< Write operation
    READ            = true              //!< Read operation
};

//!
//! @enum           LogicLevel
//! @details        Used to specify the logic level of a signal.
//!
enum class LogicLevel : cbool_t {
    LOW             = false,            //!< Low level
    HIGH            = true              //!< High level
};

//!
//! @enum           PinDirection
//! @details        Used to specify the direction of a GPIO pin.
//!
enum class PinDirection : cbool_t {
    INPUT           = false,            //!< Pin is an input
    OUTPUT          = true,             //!< Pin is an output
};

//!
//! @enum           Rotation
//! @details        Used to specify a rotation direction.
//!
enum class Rotation : cbool_t {
    CLOCKWISE           = false,        //!< Clockwise direction
    COUNTERCLOCKWISE    = true          //!< Counter-clockwise direction
};

//!
//! @enum           State
//! @details        Used to generically refer to a state or status. For example,
//!                     the state of a LED.
//!
enum class State : cbool_t {
    OFF             = false,            //!< State is OFF
    ON              = true              //!< State is ON
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Binary_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Plain_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     Plain_Enumerations
//! @details        Enumerations with multiple possible values.
//! @{
//!

//     ///////////////////     PLAIN ENUMERATIONS    ////////////////////     //

//!
//! @enum           Axis
//! @details        Used to specify the 3D Cartesian axes.
//!
enum class Axis : cuint8_t {
    //                 Z-AXIS     Y-AXIS     X-AXIS
    NONE            = (0 << 2) | (0 << 1) | (0 << 0),   //!< No axis selected
    X               = (0 << 2) | (0 << 1) | (1 << 0),   //!< X axis selected
    Y               = (0 << 2) | (1 << 1) | (0 << 0),   //!< Y axis selected
    XY              = (0 << 2) | (1 << 1) | (1 << 0),   //!< X and Y axes selected
    Z               = (1 << 2) | (0 << 1) | (0 << 0),   //!< Z axis selected
    XZ              = (1 << 2) | (0 << 1) | (1 << 0),   //!< X and Z axes selected
    YZ              = (1 << 2) | (1 << 1) | (0 << 0),   //!< Y and Z axes selected
    ALL             = (1 << 2) | (1 << 1) | (1 << 0)    //!< X, Y and Z axes selected
};

//!
//! @cond
//!

// Implementation of bitwise operators for Axis enum class to allow mask
//      combinations.

Axis inlined operator|(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Axis inlined &operator|=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

Axis inlined operator&(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

Axis inlined &operator&=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

//!
//! @endcond
//!

//!
//! @enum           Direction
//! @details        Used to specify 2D plain directions.
//!
enum class Direction : cuint8_t {
    LEFT            = 0,                //!< Left planar direction
    RIGHT           = 1,                //!< Right planar direction
    UP              = 2,                //!< Up planar direction
    DOWN            = 3                 //!< Down planar direction
};

//!
//! @enum           InterfaceMode
//! @details        Used to specify the access mode to the peripheral.
//!
enum class InterfaceMode : cuint8_t {
    BLOCKING_MODE   = 0,                //!< Do not use interrupt or DMA
    INTERRUPT_MODE  = 1,                //!< Use the peripheral interrupt
    DMA_MODE        = 2                 //!< Use the DMA interrupt
};

//!
//! @enum       PinIndex
//! @brief      Pin number enumeration.
//! @details    Pin number enumeration.
//!
enum class PinIndex : uint8_t {
    P0          = 0,    //!< Pin located at position 0 of the port
    P1          = 1,    //!< Pin located at position 1 of the port
    P2          = 2,    //!< Pin located at position 2 of the port
    P3          = 3,    //!< Pin located at position 3 of the port
    P4          = 4,    //!< Pin located at position 4 of the port
    P5          = 5,    //!< Pin located at position 5 of the port
    P6          = 6,    //!< Pin located at position 6 of the port
    P7          = 7     //!< Pin located at position 7 of the port
};

//!
//! @enum           PinMode
//! @details        Used to specify the Gpio pin mode to the peripheral.
//!
enum class PinMode : uint8_t {
    INPUT_FLOATING      = 0,    //!< INPUT without PULL resistors (DDR=0, PORT=0)
    INPUT_PULLED_UP     = 1,    //!< INPUT with PULL-UP resistors (DDR=0, PORT=1)
    OUTPUT_PUSH_PULL    = 2,    //!< OUTPUT in PUSH PULL driver   (DDR=1)
};

//!
//! @enum           ThermometricScale
//! @details        Used to specify a Thermometric scale.
//!
enum class ThermometricScale : cuint8_t {
    CELSIUS         = 0,                //!< Celsius thermometric scale
    DELISLE         = 1,                //!< Delisle thermometric scale
    FAHRENHEIT      = 2,                //!< Fahrenheit thermometric scale
    KELVIN          = 3,                //!< Kelvin absolute temperature
    NEWTON          = 4,                //!< Newton thermometric scale
    RANKINE         = 5,                //!< Rankine thermometric scale
    REAUMUR         = 6,                //!< Reaumur thermometric scale
    ROMER           = 7                 //!< Romer thermometric scale
};

//!
//! @enum           Error
//! @details        Funsape error codes.
//!
enum class Error : cuint16_t {
    // General error codes (0x0000 - 0x003F)
    NONE                                = 0x0000,   //!< Success - No errors occurred.
    // AXIS_INVALID                        = 0x0001,   //!< The Axis is invalid.
    // INSTANCE_INVALID                    = 0x0002,   //!< Invalid instance.
    // LOCKED                              = 0x0003,   //!< Accessed a locked device
    // MEMORY_ALLOCATION_FAILED            = 0x0004,   //!< Memory allocation failed.
    // NOT_IMPLEMENTED                     = 0x0005,   //!< Feature is not implemented yet, but is marked for future implementation.
    NOT_INITIALIZED                     = 0x0006,   //!< The module was not initialized.
    // NOT_READY                           = 0x0007,   //!< The module is currently busy.
    // READ_PROTECTED                      = 0x0008,   //!< Tried to read a read protected device.
    // TIMED_OUT                           = 0x0009,   //!< The operation timed out.
    // UNDER_DEVELOPMENT                   = 0x000A,   //!< This part of the code is still under development.
    // WRITE_PROTECTED                     = 0x000B,   //!< Tried to write a write protected device.
    DEVICE_DISABLED                     = 0x000C,

    // General support related error codes (0x0040 - 0x004F)
    // DEVICE_NOT_SUPPORTED                = 0x0040,   //!< Device is not currently supported.
    // DMA_NOT_SUPPORTED                   = 0x0041,   //!< DMA interface mode is not supported for this module.
    // FEATURE_NOT_SUPPORTED               = 0x0042,   //!< Unsupported feature or configuration.
    // MODE_NOT_SUPPORTED                  = 0x0043,   //!< This operation mode is not supported by the module.

    // Function arguments related error codes (0x0050 - 0x005F)
    // ARGUMENT_CANNOT_BE_ZERO             = 0x0050,   //!< The argument value must not be zero (0).
    ARGUMENT_POINTER_NULL               = 0x0051,   //!< NULL pointer was passed as an argument to function.
    // ARGUMENT_VALUE_INVALID              = 0x0052,   //!< The argument value is not valid.
    // ARGUMENT_VALUES_MISMATCH            = 0x0053,   //!< A function was called with dubious argument values.
    // ARGUMENT_WRONG_NUMBER               = 0x0054,   //!< A function was called with the wrong number of arguments.

    // Buffer related error codes (0x0060 - 0x006F)
    // BUFFER_EMPTY                        = 0x0060,   //!< Buffer is empty.
    // BUFFER_FULL                         = 0x0061,   //!< Buffer is full.
    // BUFFER_NOT_ENOUGH_ELEMENTS          = 0x0062,   //!< Not enough elements in buffer to perform operation.
    // BUFFER_NOT_ENOUGH_SPACE             = 0x0063,   //!< Not enough space in buffer to perform operation.
    // BUFFER_POINTER_NULL                 = 0x0064,   //!< Buffer pointer cannot be a null pointer.
    // BUFFER_SIZE_TOO_LARGE               = 0x0065,   //!< Buffer size was set to a value too large.
    // BUFFER_SIZE_TOO_SMALL               = 0x0066,   //!< Buffer size was set to a value too small.
    // BUFFER_SIZE_ZERO                    = 0x0067,   //!< Buffer size was set to zero.

    // Clock configuration related error codes (0x0070 - 0x007F)
    // CLOCK_PRESCALER_CHANGE_FAILED       = 0x0070,   //!< Clock prescaler change failed.
    // CLOCK_SPEED_TOO_HIGH                = 0x0071,   //!< The clock speed is too high.
    // CLOCK_SPEED_TOO_LOW                 = 0x0072,   //!< The clock speed is too low.

    // GPIO related error codes (0x0080 - 0x008F)
    // GPIO_ADDRESS_INVALID                = 0x0080,   //!< Invalid Gpio register address.
    GPIO_BUS_SIZE_INVALID               = 0x0081,   //!< The size of the bus is invalid.
    GPIO_NOT_INITIALIZED                = 0x0082,   //!< The Gpio pin or bus was not initialized.
    GPIO_PIN_OUT_OF_BOUNDARIES          = 0x0083,   //!< The Gpio pin index was out of bounds after processing.
    GPIO_PORT_INVALID                   = 0x0084,   //!< The Gpio port is invalid.
    GPIO_PORT_NOT_SET                   = 0x0085,   //!< The Gpio port was not set before use.

    // DateTime class related error codes (0x0090 - 0x009F)
    // DATE_INVALID                        = 0x0090,   //!< The date value is invalid.
    // DATE_NOT_INITIALIZED                = 0x0091,   //!< The date was not initialized.
    // HOUR_INVALID                        = 0x0092,   //!< Hour value is invalid.
    // MILLISECOND_INVALID                 = 0x0093,   //!< Millisecond value is invalid.
    // MINUTE_INVALID                      = 0x0094,   //!< Minute value is invalid.
    // MONTH_DAY_INVALID                   = 0x0095,   //!< Day of the Month value is invalid.
    // MONTH_INVALID                       = 0x0096,   //!< Month value is invalid.
    // SECOND_INVALID                      = 0x0097,   //!< Second value is invalid.
    // TIME_INVALID                        = 0x0098,   //!< The time value is invalid.
    // TIME_NOT_INITIALIZED                = 0x0099,   //!< The time was not initialized.
    // TIMEZONE_INVALID                    = 0x009A,   //!< Timezone value is invalid.
    // YEAR_INVALID                        = 0x009B,   //!< Year value is invalid.

    // Communication related error codes (0x00A0 - 0x00AF)
    // BAUD_RATE_NOT_SUPPORTED             = 0x00A0,   //!< The baud rate value is not supported.
    // BUS_HANDLER_NOT_SUPPORTED           = 0x00A1,   //!< The specified bus handler type is not supported by this module.
    // BUS_HANDLER_POINTER_NULL            = 0x00A2,   //!< The bus handler pointer cannot be null.
    // CHECKSUM_ERROR                      = 0x00A3,   //!< Checksum does not match.
    // COMMUNICATION_FAILED                = 0x00A4,   //!< The communication has failed.
    // DATA_SIZE_NOT_SUPPORTED             = 0x00A5,   //!< The number of data bits is invalid.
    // DEVICE_ID_MATCH_FAILED              = 0x00A6,   //!< Device ID does not match.
    // DEVICE_NOT_SELECTED                 = 0x00A7,   //!< No communication device was selected.
    // FRAME_ERROR                         = 0x00A8,   //!< The frame is badly formatted or invalid.
    // FRAME_FORMAT_NOT_SUPPORTED          = 0x00A9,   //!< The format of the frame is not supported.
    // MESSAGE_TOO_LONG                    = 0x00AA,   //!< Message is too long to be stored inside buffer.
    // PARITY_ERROR                        = 0x00AB,   //!< A parity check error occurred.
    // PARITY_MODE_NOT_SUPPORTED           = 0x00AC,   //!< Parity mode not supported.
    // STOP_BIT_CONFIG_NOT_SUPPORTED       = 0x00AD,   //!< Invalid number of stop bits.

    // "I don't have the slightest idea" error code
    // UNKNOWN                             = 0xFFFF,   // Unknown error - Ops!!!!
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Plain_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Types" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Inline functions declaration
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     String_Handling
//! @details        Performs general handling on @c characters and @c strings.
//! @{
//!

//     /////////////     CHARACTER AND STRING HANDLING     //////////////     //

//!
//! @brief          Returns the lowercase version of a character.
//! @details        This function returns the lowercase version of the given
//!                     character @a character_p. If @a character_p is not an
//!                     uppercase letter, the function will return
//!                     @a character_p without change.
//! @param[in]      character_p         character to be lowercased
//! @return         the lowercase version of @a character_p
//!
char_t inlined toLowerCase(cchar_t character_p);

//!
//! @brief          Returns the uppercase version of a character.
//! @details        This function returns the uppercase version of the given
//!                     character @a character_p. If @a character_p is not a
//!                     lowercase letter, the function will return
//!                     @a character_p without change.
//! @param[in]      character_p         character to be uppercased
//! @return         the uppercase version of @a character_p
//!
char_t inlined toUpperCase(cchar_t character_p);

//     /////////////////////     DATA VALIDITY     //////////////////////     //

//!
//! @brief          Verifies if a character is an ASCII lowercase letter.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII lowercase letter.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII lowercase
//!                                         letter
//! @retval         false               if @a character_p is not an ASCII
//!                                         lowercase letter
//!
bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p);

//!
//! @brief          Verifies if a character is an ASCII uppercase letter.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII uppercase letter.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII uppercase
//!                                         letter
//! @retval         false               if @a character_p is not an ASCII
//!                                         uppercase letter
//!
bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p);

//!
//! @brief          Verifies if a character is an ASCII command character.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII command character.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII command
//!                                         character
//! @retval         false               if @a character_p is not an ASCII
//!                                         command character
//!
bool_t inlined isAsciiCommand(cchar_t character_p);

//!
//! @brief          Verifies if a character is an ASCII letter character.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII letter character.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII letter
//!                                         character
//! @retval         false               if @a character_p is not an ASCII
//!                                         letter character
//!
bool_t inlined isAsciiLetter(cchar_t character_p);

//!
//! @brief          Verifies if a character is an ASCII number character.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII number character.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII number
//!                                         character
//! @retval         false               if @a character_p is not an ASCII
//!                                         number character
//!
bool_t inlined isAsciiNumber(cchar_t character_p);

//!
//! @brief          Verifies if a character is an ASCII symbol character.
//! @details        This function verifies if the given character @a character_p
//!                     is an ASCII symbol character.
//! @param[in]      character_p         character to be evaluated
//! @retval         true                if @a character_p is an ASCII symbol
//!                                         character
//! @retval         false               if @a character_p is not an ASCII
//!                                         symbol character
//!
bool_t inlined isAsciiSymbol(cchar_t character_p);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @addtogroup     System_Functions
//! @details        General system functions.
//! @{
//!

//     /////////////////////     SOFTWARE DELAY    //////////////////////     //

void inlined delayMs(uint32_t time_p);

void inlined delayUs(uint32_t time_p);

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //

//!
//! @brief          Executes a @c NOP assembly instruction.
//! @details        This function executes a @c NOP assembly instruction.
//! @attention      This function takes one clock cycle of program execution. Do
//!                     not mistake with @ref doNothing() function, that is not
//!                     physically implemented after compilation.
//!
void inlined doNop(void);

//!
//! @brief          Do nothing placeholder.
//! @details        This function does nothing and do not generate any code.
//!                     Must be used as a placeholder (code standardization).
//! @attention      This function is not physically implemented after
//!                     compilation. Do not mistake with @ref doNop() function,
//!                     that takes one clock cycle of program execution.
//!
void inlined doNothing(void);

//!
//! @brief          Halts system execution calling a function.
//! @details        This function halts system execution and calls the given
//!                     @a callBack_p function. The function also disables the
//!                     global interrupt handling.
//! @param[in]      callBack_p          function to be called
//!
void inlined systemHalt(void (*callBack_p)(void) = nullptr);

// =============================================================================
// Inline functions definitions
// =============================================================================

//!
//! @cond
//!

//     /////////////     CHARACTER AND STRING HANDLING     //////////////     //

char_t inlined toLowerCase(cchar_t character_p)
{
    return ((isAsciiUpperCaseLetter(character_p))
                    ? (character_p + 0x20)
                    : character_p
            );
}

char_t inlined toUpperCase(cchar_t character_p)
{
    return ((isAsciiLowerCaseLetter(character_p))
                    ? (character_p - 0x20)
                    : character_p
            );
}

//     /////////////////////     DATA VALIDITY     //////////////////////     //

bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p)
{
    return (bool_t)(((character_p >= 'a') && (character_p <= 'z'))
                    ? true
                    : false
            );
}

bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p)
{
    return (bool_t)(((character_p >= 'A') && (character_p <= 'Z'))
                    ? true
                    : false
            );
}

bool_t inlined isAsciiCommand(cchar_t character_p)
{
    return (bool_t)((character_p < ' ')
                    ? true
                    : false
            );
}

bool_t inlined isAsciiLetter(cchar_t character_p)
{
    return (bool_t)((isAsciiLowerCaseLetter(character_p) || isAsciiUpperCaseLetter(character_p))
                    ? true
                    : false
            );
}

bool_t inlined isAsciiNumber(cchar_t character_p)
{
    return (bool_t)(((character_p >= '0') && (character_p <= '9'))
                    ? true
                    : false
            );
}

bool_t inlined isAsciiSymbol(cchar_t character_p)
{
    return (bool_t)(((!isAsciiNumber(character_p)) && (!isAsciiCommand(character_p)) && (!isAsciiLetter(character_p)))
                    ? true
                    : false
            );
}

//     /////////////////////     SOFTWARE DELAY    //////////////////////     //

void inlined delayMs(uint32_t time_p)
{
    _delay_ms(time_p);

    return;
}

void inlined delayUs(uint32_t time_p)
{
    _delay_us(time_p);

    return;
}

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //

void inlined doNop(void)
{
    asm volatile("nop");

    return;
}

void inlined doNothing(void)
{
    return;
}

void inlined systemHalt(void (*function_p)(void))
{
    if(isPointerValid(function_p)) {
        function_p();
    }
    cli();
    while(1) {
        doNothing();
    }

    return;
}

//!
//! @endcond
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Public functions weakly defined
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!
//! @}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __GLOBAL_DEFINES_HPP

// =============================================================================
// End of file (globalDefines.hpp)
// =============================================================================
