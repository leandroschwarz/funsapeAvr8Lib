//!
//! \file           globalDefines.hpp
//! \brief          Global definitions file
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        Global definitions file.
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __GLOBAL_DEFINES_HPP
#define __GLOBAL_DEFINES_HPP                    2304

// =============================================================================
// Basic definitions
// =============================================================================

#ifndef F_CPU
#   define F_CPU    16000000UL
#endif

// =============================================================================
// Dependencies
// =============================================================================

//     //////////////////     AVR STANDARD LIBRARY     //////////////////     //
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "pinout.hpp"
#if !defined(__PINOUT_HPP)
#   error "Header file (pinout.hpp) is corrupted!"
#elif __PINOUT_HPP != __GLOBAL_DEFINES_HPP
#   error "Version mismatch between header file and library dependency (pinout.hpp)!"
#endif

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

#define inlined                         inline __attribute__((always_inline))
#define weakened                        __attribute__((weak))

// =============================================================================
// New data types
// =============================================================================

//     ////////////////////     BASIC VARIABLES     /////////////////////     //
typedef bool                            bool_t;
typedef char                            char_t;

//     ///////////////////     CONSTANT VARIABLES    ////////////////////     //
typedef const bool_t                    cbool_t;
typedef const char_t                    cchar_t;
typedef const int8_t                    cint8_t;
typedef const int16_t                   cint16_t;
typedef const int32_t                   cint32_t;
typedef const int64_t                   cint64_t;
typedef const uint8_t                   cuint8_t;
typedef const uint16_t                  cuint16_t;
typedef const uint32_t                  cuint32_t;
typedef const uint64_t                  cuint64_t;

//     ///////////////////     VOLATILE VARIABLES    ////////////////////     //
typedef volatile bool_t                 vbool_t;
typedef volatile char_t                 vchar_t;
typedef volatile int8_t                 vint8_t;
typedef volatile int16_t                vint16_t;
typedef volatile int32_t                vint32_t;
typedef volatile int64_t                vint64_t;
typedef volatile uint8_t                vuint8_t;
typedef volatile uint16_t               vuint16_t;
typedef volatile uint32_t               vuint32_t;
typedef volatile uint64_t               vuint64_t;

//     /////////////////     AVR PLATFORM VARIABLES    //////////////////     //
typedef int16_t                         int_t;          // 16-bit (AVR)
typedef uint16_t                        uint_t;         // 16-bit (AVR)
typedef cint16_t                        cint_t;         // 16-bit (AVR)
typedef cuint16_t                       cuint_t;        // 16-bit (AVR)
typedef vint16_t                        vint_t;         // 16-bit (AVR)
typedef vuint16_t                       vuint_t;        // 16-bit (AVR)
typedef uint8_t                         ioPinIndex_t;   // 8-bit (AVR)
typedef vuint8_t                       *ioRegAddress_t; // 8-bit address (AVR)

//     //////////////////     BINARY ENUMERATIONS     ///////////////////     //
enum class Activation : cbool_t {
    OFF                                 = false,
    ON                                  = true
};

enum class DisplayOrientation : cbool_t {
    LANDSCAPE                           = false,
    PORTRAIT                            = true
};

enum class DriverMode : cbool_t {
    PUSH_PULL                           = false,
    OPEN_DRAIN                          = true,
};

enum class Edge : cbool_t {
    FALLING                             = false,
    RISING                              = true
};

enum class IoOperation : cbool_t {
    WRITE                               = false,
    READ                                = true
};

enum class LogicLevel : cbool_t {
    LOW                                 = false,
    HIGH                                = true
};

enum class PinDirection : cbool_t {
    INPUT                               = false,
    OUTPUT                              = true,
};

enum class Rotation : cbool_t {
    CLOCKWISE                           = false,
    COUNTERCLOCKWISE                    = true
};

enum class State : cbool_t {
    OFF                                 = false,
    ON                                  = true
};

//     ///////////////////     PLAIN ENUMERATIONS    ////////////////////     //
enum class Axis : cuint8_t {
    //                                     Z-AXIS     Y-AXIS     X-AXIS
    NONE                                = (0 << 2) | (0 << 1) | (0 << 0),
    X                                   = (0 << 2) | (0 << 1) | (1 << 0),
    Y                                   = (0 << 2) | (1 << 1) | (0 << 0),
    XY                                  = (0 << 2) | (1 << 1) | (1 << 0),
    Z                                   = (1 << 2) | (0 << 1) | (0 << 0),
    XZ                                  = (1 << 2) | (0 << 1) | (1 << 0),
    YZ                                  = (1 << 2) | (1 << 1) | (0 << 0),
    ALL                                 = (1 << 2) | (1 << 1) | (1 << 0)
};

inlined Axis operator|(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<cint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Axis &operator|=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Axis operator&(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inlined Axis &operator&=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

enum class Direction : cuint8_t {
    LEFT                                = 0,
    RIGHT                               = 1,
    UP                                  = 2,
    DOWN                                = 3
};

enum class InterfaceMode : cuint8_t {
    BLOCKING_MODE                       = 0,
    INTERRUPT_MODE                      = 1,
    DMA_MODE                            = 2
};

enum class ThermometricScale : cuint8_t {
    CELSIUS                             = 0,
    DELISLE                             = 1,
    FAHRENHEIT                          = 2,
    KELVIN                              = 3,
    NEWTON                              = 4,
    RANKINE                             = 5,
    REAUMUR                             = 6,
    ROMER                               = 7
};

enum class Error : cuint16_t {
    // General error codes
    NONE                                                = 0x0000,   // Success - No errors occurred
    AXIS_INVALID                                        = 0x0001,   // Invalid axis
    NOT_IMPLEMENTED                                     = 0x0002,   // Not implemented yet
    UNDER_DEVELOPMENT                                   = 0x0003,   // This part of the code is still under development
    NOT_INITIALIZED                                     = 0x0004,   // Not initialized
    // BUSY                                                = 0x0005,   // TODO: Describe parameter
    // DEVICE_NOT_SUPPORTED                                = 0x0006,   // Device is not currently supported
    FEATURE_NOT_SUPPORTED                               = 0x0007,   // Unsupported feature or configuration
    // FUNCTION_POINTER_NULL                               = 0x0008,   // TODO: Describe parameter
    // INSTANCE_INVALID                                    = 0x0009,   // Invalid instance
    // LOCKED                                              = 0x000A,   // Accessed a locked device
    MEMORY_ALLOCATION                                   = 0x000B,   // Memory allocation failed
    // MODE_NOT_SUPPORTED                                  = 0x000C,   // Mode is not currently supported
    // NOT_READY                                           = 0x000D,   // TODO: Describe parameter
    // READ_PROTECTED                                      = 0x000E,   // Tried to read a read protected device
    // WRITE_PROTECTED                                     = 0x000F,   // Tried to write a write protected device

    // Function arguments related error codes
    ARGUMENT_CANNOT_BE_ZERO                             = 0x0010,   // TODO: Describe parameter
    ARGUMENT_POINTER_NULL                               = 0x0011,   // NULL pointer was passed as an argument to function
    ARGUMENT_VALUE_INVALID                              = 0x0012,   // TODO: Describe parameter
    // ARGUMENTS_MISMATCH                                  = 0x0013,   // A function was called with dubious argument values
    // ARGUMENTS_WRONG_NUMBER                              = 0x0014,   // A function was called with wrong number of arguments
    // ARGUMENT_GENERIC_ERROR_5                            = 0x0015,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_6                            = 0x0016,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_7                            = 0x0017,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_8                            = 0x0018,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_9                            = 0x0019,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_10                           = 0x001A,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_11                           = 0x001B,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_12                           = 0x001C,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_13                           = 0x001D,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_14                           = 0x001E,   // Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR                              = 0x001F,   // Generic error (use only on temporary basis)

    // Buffer related error codes
    // BUFFER_EMPTY                                        = 0x0020,   // Buffer is empty
    // BUFFER_FULL                                         = 0x0021,   // Buffer is full
    // BUFFER_NOT_ENOUGH_ELEMENTS                          = 0x0022,   // Not enough space in buffer to perform operation
    // BUFFER_NOT_ENOUGH_SPACE                             = 0x0023,   // Not enough space in buffer to perform operation
    // BUFFER_POINTER_NULL                                 = 0x0024,   // Buffer size was set to zero
    BUFFER_SIZE_TOO_LARGE                               = 0x0025,   // Buffer size was set to a large value
    BUFFER_SIZE_TOO_SMALL                               = 0x0026,   // Buffer size was set to a very small value
    // BUFFER_SIZE_ZERO                                    = 0x0027,   // Buffer size was set to zero
    // BUFFER_GENERIC_ERROR_8                              = 0x0028,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_9                              = 0x0029,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_10                             = 0x002A,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_11                             = 0x002B,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_12                             = 0x002C,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_13                             = 0x002D,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_14                             = 0x002E,   // Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_15                             = 0x002F,   // Generic error (use only on temporary basis)

    // Clock configuration related error codes
    CLOCK_PRESCALER_CHANGE_FAILED                       = 0x0030,   // Clock prescaler change failed
    CLOCK_PRESCALER_NOT_SUPPORTED                       = 0x0031,   // Clock prescaler configuration unsupported
    CLOCK_SPEED_TOO_HIGH                                = 0x0032,   // TODO: Describe parameter
    CLOCK_SPEED_TOO_LOW                                 = 0x0033,   // TODO: Describe parameter
    // CLOCK_GENERIC_ERROR_4                               = 0x0034,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_5                               = 0x0035,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_6                               = 0x0036,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_7                               = 0x0037,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_8                               = 0x0038,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_9                               = 0x0039,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_10                              = 0x003A,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_11                              = 0x003B,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_12                              = 0x003C,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_13                              = 0x003D,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_14                              = 0x003E,   // Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_15                              = 0x003F,   // Generic error (use only on temporary basis)

    // Communication related error codes
    COMMUNICATION_FAILED                                = 0x0040,   // TODO: Describe parameter
    COMMUNICATION_NO_DEVICE_SELECTED                    = 0x0041,   // TODO: Describe parameter
    // COMMUNICATION_PORT_NOT_SET                          = 0x0042,   // TODO: Describe parameter
    COMMUNICATION_TIMEOUT                               = 0x0043,   // The operation timed out
    // COMMUNICATION_DEVICE_ID_MATCH_FAILED                = 0x0044,   // TODO: Describe parameter
    // CHECKSUM_ERROR                                      = 0x0045,   // TODO: Describe parameter
    // FRAME_ERROR                                         = 0x0046,   // TODO: Describe parameter
    // PACKAGE_AWAITING                                    = 0x0047,   // Try to write data to a ready package
    // PACKAGE_NOT_READY                                   = 0x0048,   // Try to read data from a not ready package
    // COMMUNICATION_GENERIC_ERROR_9                       = 0x0049,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_10                      = 0x004A,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_11                      = 0x004B,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_12                      = 0x004C,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_13                      = 0x004D,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_14                      = 0x004E,   // Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_15                      = 0x004F,   // Generic error (use only on temporary basis)

    // DateTime class related error codes
    DATE_NOT_INITIALIZED                                = 0x0050,   // TODO: Describe parameter
    // HOUR_INVALID                                        = 0x0051,   // TODO: Describe parameter
    // MILLISECOND_INVALID                                 = 0x0052,   // TODO: Describe parameter
    // MINUTE_INVALID                                      = 0x0053,   // TODO: Describe parameter
    // MONTH_DAY_INVALID                                   = 0x0054,   // TODO: Describe parameter
    // MONTH_INVALID                                       = 0x0055,   // TODO: Describe parameter
    // SECOND_INVALID                                      = 0x0056,   // TODO: Describe parameter
    TIME_NOT_INITIALIZED                                = 0x0057,   // TODO: Describe parameter
    // TIMEZONE_INVALID                                    = 0x0058,   // TODO: Describe parameter
    // YEAR_INVALID                                        = 0x0059,   // TODO: Describe parameter
    DATE_INVALID                                        = 0x005A,   // TODO: Describe parameter
    TIME_INVALID                                        = 0x005B,   // TODO: Describe parameter
    // GENERIC_ERROR_13                                    = 0x005C,   // Generic error (use only on temporary basis)
    // GENERIC_ERROR_14                                    = 0x005D,   // Generic error (use only on temporary basis)
    // GENERIC_ERROR_15                                    = 0x005F,   // Generic error (use only on temporary basis)

    // Handler related error codes
    BUS_HANDLER_NOT_SUPPORTED                           = 0x0060,   // TODO: Describe parameter
    BUS_HANDLER_POINTER_NULL                            = 0x0061,   // TODO: Describe parameter
    // HANDLER_GENERIC_ERROR_2                             = 0x0062,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_3                             = 0x0063,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_4                             = 0x0064,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_5                             = 0x0065,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_6                             = 0x0066,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_7                             = 0x0067,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_8                             = 0x0068,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_9                             = 0x0069,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_10                            = 0x006A,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_11                            = 0x006B,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_12                            = 0x006C,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_13                            = 0x006D,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_14                            = 0x006E,   // Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_15                            = 0x006F,   // Generic error (use only on temporary basis)

    // External interrupts related error codes
    // INTERRUPT_NOT_AVAILABLE                             = 0x0070,   // TODO: Describe parameter
    // INTERRUPT_PORT_OUTPUT_MODE_NOT_SUPPORTED            = 0x0071,   // TODO: Describe parameter
    // INTERRUPT_SENSE_MODE_NOT_SUPPORTED                  = 0x0072,   // TODO: Describe parameter
    // INTERRUPT_GENERIC_ERROR_3                           = 0x0073,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_4                           = 0x0074,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_5                           = 0x0075,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_6                           = 0x0076,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_7                           = 0x0077,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_8                           = 0x0078,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_9                           = 0x0079,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_10                          = 0x007A,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_11                          = 0x007B,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_12                          = 0x007C,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_13                          = 0x007D,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_14                          = 0x007E,   // Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_15                          = 0x007F,   // Generic error (use only on temporary basis)


    // Package API class related error codes
    // PACKAGE_API_PACKAGE_DATA_FULL                       = 0x0080,   // TODO: Describe parameter
    // PACKAGE_API_PACKAGE_NOT_READY                       = 0x0081,   // TODO: Describe parameter
    // PACKAGE_API_PAYLOAD_DATA_NULL                       = 0x0082,   // TODO: Describe parameter
    // PACKAGE_API_PAYLOAD_SIZE_NULL                       = 0x0083,   // TODO: Describe parameter
    // PACKAGE_API_SOURCE_ADDRESS_INVALID                  = 0x0084,   // TODO: Describe parameter
    // PACKAGE_API_GENERIC_ERROR_5                         = 0x0085,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_6                         = 0x0086,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_7                         = 0x0087,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_8                         = 0x0088,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_9                         = 0x0089,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_10                        = 0x008A,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_11                        = 0x008B,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_12                        = 0x008C,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_13                        = 0x008D,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_14                        = 0x008E,   // Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_15                        = 0x008F,   // Generic error (use only on temporary basis)

    // SPI related error codes
    // SPI_BUSY_FLAG                                       = 0x0090,   // TODO: Describe parameter
    // SPI_CRC                                             = 0x0091,   // TODO: Describe parameter
    // SPI_DMA                                             = 0x0092,   // TODO: Describe parameter
    // SPI_MODE_FAULT                                      = 0x0093,   // TODO: Describe parameter
    // SPI_OVERRUN                                         = 0x0094,   // TODO: Describe parameter
    // SPI_GENERIC_ERROR_5                                 = 0x0095,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_6                                 = 0x0096,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_7                                 = 0x0097,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_8                                 = 0x0098,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_9                                 = 0x0099,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_10                                = 0x009A,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_11                                = 0x009B,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_12                                = 0x009C,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_13                                = 0x009D,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_14                                = 0x009E,   // Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_15                                = 0x009F,   // Generic error (use only on temporary basis)

    // TWI related error codes
    // TWI_AF_FLAG                                         = 0x00A0,   // TWI AF flag error
    // TWI_ARBITRATION_LOST                                = 0x00A1,   // TWI bus arbitration lost
    // TWI_BUS_ERROR                                       = 0x00A2,   // TWI bus error
    // TWI_DMA                                             = 0x00A3,   // DMA parameter error
    // TWI_DMA_PARAM                                       = 0x00A4,   // DMA transfer error
    // TWI_OVERRUN                                         = 0x00A5,   // TWI overrun
    // TWI_SIZE_MANAGEMENT_ERROR                           = 0x00A6,   // Size management error
    // TWI_INVALID_DEVICE_ADDRESS                          = 0x00A7,   // TODO: Describe parameter
    // TWI_GENERIC_ERROR_8                                 = 0x00A8,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_9                                 = 0x00A9,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_10                                = 0x00AA,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_11                                = 0x00AB,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_12                                = 0x00AC,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_13                                = 0x00AD,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_14                                = 0x00AE,   // Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_15                                = 0x00AF,   // Generic error (use only on temporary basis)

    // USART related error codes
    USART_BAUD_RATE_NOT_SUPPORTED                       = 0x00B0,   // TODO: Describe parameter
    // USART_CONFIGURATION_PARAMETER_WRONG                 = 0x00B1,   // TODO: Describe parameter
    USART_DATA_SIZE_NOT_SUPPORTED                       = 0x00B2,   // TODO: Describe parameter
    USART_FRAME_FORMAT_NOT_SUPPORTED                    = 0x00B3,   // TODO: Describe parameter
    USART_PARITY_NOT_SUPPORTED                          = 0x00B4,   // TODO: Describe parameter
    USART_STOP_BIT_NOT_SUPPORTED                        = 0x00B5,   // TODO: Describe parameter
    USART_MODE_NOT_SUPPORTED                            = 0x00B6,   // TODO: Describe parameter
    // USART_GENERIC_ERROR_7                               = 0x00B7,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_8                               = 0x00B8,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_9                               = 0x00B9,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_10                              = 0x00BA,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_11                              = 0x00BB,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_12                              = 0x00BC,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_13                              = 0x00BD,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_14                              = 0x00BE,   // Generic error (use only on temporary basis)
    // USART_GENERIC_ERROR_15                              = 0x00BF,   // Generic error (use only on temporary basis)

    // LCD related error codes
    // LCD_CONTROL_PORT_NOT_SET                            = 0x00C0,   // TODO: Describe parameter
    // LCD_CONTROL_PIN_E_INVALID                           = 0x00C1,   // TODO: Describe parameter
    // LCD_CONTROL_PIN_RS_INVALID                          = 0x00C2,   // TODO: Describe parameter
    // LCD_CONTROL_PIN_RW_INVALID                          = 0x00C3,   // TODO: Describe parameter
    // LCD_DATA_PORT_NOT_SET                               = 0x00C4,   // TODO: Describe parameter
    // LCD_DATA_PIN_INDEX_OUT_OF_BOUNDARIES                = 0x00C5,   // TODO: Describe parameter
    // LCD_GENERIC_ERROR_6                                 = 0x00C6,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_7                                 = 0x00C7,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_8                                 = 0x00C8,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_9                                 = 0x00C9,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_10                                = 0x00CA,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_11                                = 0x00CB,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_12                                = 0x00CC,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_13                                = 0x00CD,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_14                                = 0x00CE,   // Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_15                                = 0x00CF,   // Generic error (use only on temporary basis)

    // GPIO related error codes
    GPIO_PORT_NOT_SET                                   = 0x00D0,   // Gpio port was not set before use
    GPIO_DATA_PORT_NOT_SET                              = 0x00D1,   // Gpio data port was not set before use
    GPIO_CONTROL_PORT_NOT_SET                           = 0x00D2,   // Gpio control port was not set before use
    GPIO_PORT_INVALID                                   = 0x00D3,   // Gpio port address is invalid
    GPIO_DATA_PORT_INVALID                              = 0x00D4,   // Gpio data port address is invalid
    GPIO_CONTROL_PORT_INVALID                           = 0x00D5,   // Gpio control port address is invalid
    GPIO_PIN_INDEX_INVALID                              = 0x00D6,   // Invalid GPIO Pin
    GPIO_PIN_INDEX_OUT_OF_BOUNDARIES                    = 0x00D7,   // Gpio pin index was out of bounds after processing
    // GPIO_NO_PIN_SET                                     = 0x00D8,   // No pin selected at Gpio peripheral
    // GPIO_ADDRESS_INVALID                                = 0x00D9,   // Invalid GPIO Port
    // GPIO_PORT_LOGIC_CONTENTION                          = 0x00DA,   // TODO: Describe parameter
    // GPIO_GENERIC_ERROR_11                               = 0x00DB,   // Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_12                               = 0x00DC,   // Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_13                               = 0x00DD,   // Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_14                               = 0x00DE,   // Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_15                               = 0x00DF,   // Generic error (use only on temporary basis)

    // HAL related error codes
    // HAL_UNKNOWN_ERROR                                   = 0x00E0,   // TODO: Describe parameter
    // HAL_STATUS_ERROR                                    = 0x00E1,   // TODO: Describe parameter
    // HAL_STATUS_BUSY                                     = 0x00E2,   // TODO: Describe parameter
    // HAL_STATUS_TIMEOUT                                  = 0x00E3,   // TODO: Describe parameter
    // HAL_GENERIC_ERROR_4                                 = 0x00E4,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_5                                 = 0x00E5,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_6                                 = 0x00E6,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_7                                 = 0x00E7,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_8                                 = 0x00E8,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_9                                 = 0x00E9,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_10                                = 0x00EA,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_11                                = 0x00EB,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_12                                = 0x00EC,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_13                                = 0x00ED,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_14                                = 0x00EE,   // Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_15                                = 0x00EF,   // Generic error (use only on temporary basis)

    // System related error codes
    // SYSTEM_US_TIMER_HANDLER_NULL                        = 0x00F0,   // TODO: Describe parameter
    // SYSTEM_GENERIC_ERROR_1                              = 0x00F1,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_2                              = 0x00F2,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_3                              = 0x00F3,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_4                              = 0x00F4,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_5                              = 0x00F5,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_6                              = 0x00F6,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_7                              = 0x00F7,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_8                              = 0x00F8,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_9                              = 0x00F9,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_10                             = 0x00FA,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_11                             = 0x00FB,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_12                             = 0x00FC,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_13                             = 0x00FD,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_14                             = 0x00FE,   // Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_15                             = 0x00FF,   // Generic error (use only on temporary basis)

    // FatFs related error codes
    // FAT_FS_UNKNOWN_ERROR                                = 0x0100,   // TODO: Describe parameter
    // FAT_FS_DRIVE_UNSUPPORTED                            = 0x0101,   // TODO: Describe parameter
    // FAT_FS_DISK_NOT_INSERTED                            = 0x0102,   // TODO: Describe parameter
    // FAT_FS_INITIALIZATION_FAILED                        = 0x0103,   // TODO: Describe parameter
    // FAT_FS_GENERIC_ERROR_4                              = 0x0104,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_5                              = 0x0105,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_6                              = 0x0106,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_7                              = 0x0107,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_8                              = 0x0108,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_9                              = 0x0109,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_10                             = 0x010A,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_11                             = 0x010B,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_12                             = 0x010C,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_13                             = 0x010D,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_14                             = 0x010E,   // Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_15                             = 0x010F,   // Generic error (use only on temporary basis)

    // Uncategorized error codes
    // LCD_OUT_OF_BOUNDARIES                               = 0xFFF1,   // TODO: Describe parameter
    // CONTROLLER_NOT_SUPPORTED                            = 0xFFF2,   // Unsupported controller
    // DEVICE_ID_MATCH_FAILED                              = 0xFFF3,   // Device ID doesn't match
    // DMA_NOT_SUPPORTED                                   = 0xFFF4,   // DMA interface mode is not supported for this module
    // DMA_TRANSFER_ERROR                                  = 0xFFF5,   // DMA transfer error
    // MESSAGE_TOO_LONG                                    = 0xFFF6,   // Message is to long to be stored inside buffer
    // VALID_DATA_NOT_AVAILABLE                            = 0xFFF7,   // Valid data was unavailable
    // PERIPHERAL_NOT_READY                                = 0xFFF8,   // TODO: Describe parameter
    // STOPWATCH_NOT_STARTED                               = 0xFFF9,   // TODO: Describe parameter
    // UNCATEGORIZED_GENERIC_ERROR_10                      = 0xFFFA,   // Generic error (use only on temporary basis)
    // UNCATEGORIZED_GENERIC_ERROR_11                      = 0xFFFB,   // Generic error (use only on temporary basis)
    // UNCATEGORIZED_GENERIC_ERROR_12                      = 0xFFFC,   // Generic error (use only on temporary basis)
    // UNCATEGORIZED_GENERIC_ERROR_13                      = 0xFFFD,   // Generic error (use only on temporary basis)
    // UNCATEGORIZED_GENERIC_ERROR_14                      = 0xFFFE,   // Generic error (use only on temporary basis)

    KEYPAD_COLUMNS_PIN_INDEX_INVALID                    = 0xFFF9,
    KEYPAD_LINES_PIN_INDEX_INVALID                      = 0xFFFA,

    KEYPAD_LINES_GPIO_PORT_INVALID                      = 0xFFFB,
    KEYPAD_COLUMNS_GPIO_PORT_INVALID                    = 0xFFFC,
    KEYPAD_TYPE_UNSUPPORTED                             = 0xFFFD,
    KEY_VALUES_NOT_SET                                  = 0xFFFE,
    // "I don't have the slightest idea" error code
    UNKNOWN                                             = 0xFFFF,   // Unknown error - Ops!!!!
};

// =============================================================================
// Macrofunctions
// =============================================================================

//     //////////////////////     DATA VALIDITY    //////////////////////     //
#define isGpioAddressValid(gpioPort)    (       \
        (IS_GPIO_ALL_INSTANCE(gpioPort))        \
        ? (bool_t)true                          \
        : (bool_t)false)
#define isGpioPinIndexValid(gpioPin)    (       \
        (IS_GPIO_ALL_PIN_NUMBER(gpioPin))       \
        ? (bool_t)true                          \
        : (bool_t)false)
#define isPointerValid(ptr)             (       \
        ((void *)(ptr))                         \
        ? (bool_t)true                          \
        : (bool_t)false)

//     //////////////////////     BIT HANDLING     //////////////////////     //
#ifndef setBit
#   define setBit(reg, bit)                     ((reg) |= (1 << (bit)))
#endif
#ifndef clrBit
#   define clrBit(reg, bit)                     ((reg) &= ~(1 << (bit)))
#endif
#ifndef cplBit
#   define cplBit(reg, bit)                     ((reg) ^= (1 << (bit)))
#endif

//     ///////////////////////     BIT TESTING    ///////////////////////     //
#ifndef isBitSet
#   define isBitSet(reg, bit)                   (((reg) >> (bit)) & 1)
#endif
#ifndef isBitClr
#   define isBitClr(reg, bit)                   (!isBitSet(reg,bit))
#endif

//     ///////////////////////     BIT LOOPING    ///////////////////////     //
#ifndef waitUntilBitIsSet
#   define waitUntilBitIsSet(reg, bit)          do{     \
        doNothing();                                    \
    } while (isBitClr((reg), (bit)))
#endif
#ifndef waitUntilBitIsClear
#   define waitUntilBitIsClear(reg, bit)        do{     \
        doNothing();                                    \
    }while(isBitSet((reg), (bit)))
#endif

//     ////////////////////     BIT MASK HANDLING    ////////////////////     //
#ifndef setMask
#   define setMask(reg, mask)                   ((reg) |= (mask))
#endif
#ifndef clrMask
#   define clrMask(reg, mask)                   ((reg) &= ~(mask))
#endif
#ifndef cplMask
#   define cplMask(reg, mask)                   ((reg) ^= (mask))
#endif

//     ////////////////     BIT MASK OFFSET HANDLING     ////////////////     //
#ifndef setMaskOffset
#   define setMaskOffset(reg, mask, offset)     ((reg) |= ((mask) << (offset)))
#endif
#ifndef clrMaskOffset
#   define clrMaskOffset(reg, mask, offset)     ((reg) &= ~((mask) << (offset)))
#endif
#ifndef cplMaskOffset
#   define cplMaskOffset(reg, mask, offset)     ((reg) ^= ((mask) << (offset)))
#endif

//     /////////////     DATA MANIPULATION (8-BITS WIDE)    /////////////     //
#define byteGetNibble1(dataByte)        (((dataByte) >> 4) & 0x0F)
#define byteGetNibble0(dataByte)        ((dataByte) & 0x0F)
#define byteSwitchNibbles(dataByte)     ((byteGetNibble0(dataByte) << 4) | \
        (byteGetNibble1(dataByte)))

//     ////////////     DATA MANIPULATION (16-BITS WIDE)     ////////////     //
#define hwordGetByte1(dataHword)        (((dataHword) >> 8) & 0x00FF)
#define hwordGetByte0(dataHword)        ((dataHword) & 0x00FF)
#define hwordSwitchBytes(dataHword)     ((hwordGetByte0(dataHword) << 8) | \
        (hwordGetByte1(dataHword)))

//     ////////////     DATA MANIPULATION (32-BITS WIDE)     ////////////     //
#define wordGetByte3(dataWord)          (((dataWord) >> 24) & 0x000000FF)
#define wordGetByte2(dataWord)          (((dataWord) >> 16) & 0x000000FF)
#define wordGetByte1(dataWord)          (((dataWord) >> 8) & 0x000000FF)
#define wordGetByte0(dataWord)          ((dataWord) & 0x000000FF)
#define wordSwitchBytes(dataWord)       ((wordGetByte0(dataWord) << 24)  | \
        (wordGetByte1(dataWord) << 16) | \
        (wordGetByte2(dataWord) << 8)  | \
        (wordGetByte3(dataWord)))
#define wordGetHword1(dataWord)         (((dataWord) >> 16) & 0x0000FFFF)
#define wordGetHword0(dataWord)         ((dataWord) & 0x0000FFFF)
#define wordSwitchHwords(dataWord)      ((wordGetHword0(dataWord) << 16) | \
        (wordGetHword1(dataWord)))

//     ////////////     DATA MANIPULATION (64-BITS WIDE)     ////////////     //
#define dwordGetByte7(dataDword)        (((dataDword) >> 56) & 0x00000000000000FF)
#define dwordGetByte6(dataDword)        (((dataDword) >> 48) & 0x00000000000000FF)
#define dwordGetByte5(dataDword)        (((dataDword) >> 40) & 0x00000000000000FF)
#define dwordGetByte4(dataDword)        (((dataDword) >> 32) & 0x00000000000000FF)
#define dwordGetByte3(dataDword)        (((dataDword) >> 24) & 0x00000000000000FF)
#define dwordGetByte2(dataDword)        (((dataDword) >> 16) & 0x00000000000000FF)
#define dwordGetByte1(dataDword)        (((dataDword) >> 8) & 0x00000000000000FF)
#define dwordGetByte0(dataDword)        ((dataDword) & 0x00000000000000FF)
#define dwordSwitchBytes(dataDword)     ((dwordGetByte0(dataDword) << 56)  | \
        (dwordGetByte1(dataDword) << 48) | \
        (dwordGetByte2(dataDword) << 40) | \
        (dwordGetByte3(dataDword) << 32) | \
        (dwordGetByte4(dataDword) << 24) | \
        (dwordGetByte5(dataDword) << 16) | \
        (dwordGetByte6(dataDword) << 8)  | \
        (dwordGetByte7(dataDword)))
#define dwordGetHword3(dataDword)       ((dataDword >> 48) & 0x000000000000FFFF)
#define dwordGetHword2(dataDword)       ((dataDword >> 32) & 0x000000000000FFFF)
#define dwordGetHword1(dataDword)       ((dataDword >> 16) & 0x000000000000FFFF)
#define dwordGetHword0(dataDword)       ((dataDword >> 0) & 0x000000000000FFFF)
#define dwordSwitchHwords(dataDword)    ((dwordGetHword0(dataDword) << 48)  | \
        (dwordGetHword1(dataDword) << 32) | \
        (dwordGetHword2(dataDword) << 16) | \
        (dwordGetHword3(dataDword)))
#define dwordGetWord1(dataDword)         (((dataDword) >> 32) & 0x00000000FFFFFFFF)
#define dwordGetWord0(dataDword)         ((dataDword) & 0x00000000FFFFFFFF)
#define dwordSwitchWords(dataDword)     ((dwordGetWord0(dataDword) << 32)  | \
        (dwordGetWord1(dataDword)))

//     /////////////////////     TRUNCATE VALUES    /////////////////////     //
#define getMaximumOf(var1, var2)        (       \
        ((var1) > (var2))                       \
        ? (var1)                                \
        : (var2))
#define getMinimumOf(var1, var2)        (       \
        ((var1) < (var2))                       \
        ? (var1)                                \
        : (var2))
#define truncateBetween(var, min, max)  (       \
        ((var) < (min))                         \
        ? (min)                                 \
        : (((var) > (max))                      \
                ? (max)                         \
                : (var)                         \
        ))

//     //////////////////////     STRINGIFYING    ///////////////////////     //
#define stringifyName(constant)         #constant
#define stringifyValue(constant)        stringifyName(constant)

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Inline functions declaration
// =============================================================================

//     ///////////////////     CHARACTER HANDLING    ////////////////////     //
char_t inlined toLowerCase(cchar_t character_p);
char_t inlined toUpperCase(cchar_t character_p);

//     /////////////////////     DATA VALIDITY     //////////////////////     //
bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p);
bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p);
bool_t inlined isAsciiCommand(cchar_t character_p);
bool_t inlined isAsciiLetter(cchar_t character_p);
bool_t inlined isAsciiNumber(cchar_t character_p);
bool_t inlined isAsciiSymbol(cchar_t character_p);

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //
void inlined die(Error errorCode_p);
void inlined doNop(void);
void inlined doNothing(void);
void inlined systemHalt(void (*function_p)(void) = nullptr);

// =============================================================================
// Inline functions definitions
// =============================================================================

//     ///////////////////     CHARACTER HANDLING    ////////////////////     //
char_t inlined toLowerCase(cchar_t character_p)
{
    return ((isAsciiUpperCaseLetter(character_p)) ? (character_p + 0x20) : character_p);
}

char_t inlined toUpperCase(cchar_t character_p)
{
    return ((isAsciiLowerCaseLetter(character_p)) ? (character_p - 0x20) : character_p);
}

//     /////////////////////     DATA VALIDITY     //////////////////////     //
bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p)
{
    return ((bool_t)(((character_p >= 'a') && (character_p <= 'z')) ? true : false));
}

bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p)
{
    return ((bool_t)(((character_p >= 'A') && (character_p <= 'Z')) ? true : false));
}

bool_t inlined isAsciiCommand(cchar_t character_p)
{
    return ((bool_t)((character_p < ' ') ? true : false));
}

bool_t inlined isAsciiLetter(cchar_t character_p)
{
    return ((bool_t)((isAsciiLowerCaseLetter(character_p) || (isAsciiUpperCaseLetter(character_p)) ? true : false)));
}

bool_t inlined isAsciiNumber(cchar_t character_p)
{
    return ((bool_t)(((character_p >= '0') && (character_p <= '9')) ? true : false));
}

bool_t inlined isAsciiSymbol(cchar_t character_p)
{
    return ((bool_t)(((!isAsciiNumber(character_p)) && (!isAsciiCommand(character_p)) &&
                                    (!isAsciiLetter(character_p))) ? true : false));
}

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //
void inlined die(Error errorCode_p)
{
    printf("Failed with error=%u (0x%04x).\r", (cuint16_t)errorCode_p, (cuint16_t)errorCode_p);
    systemHalt();

    return;
}

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
    while(1) {
        doNothing();
    }

    return;
}

// =============================================================================
// Public functions weakly defined
// =============================================================================

#define delayMs(time_p)                 _delay_ms(time_p)
#define delayUs(time_p)                 _delay_us(time_p)

weakened uint32_t getTick(void)
{
    // TODO
    return 0;
}

// =============================================================================
// Includes Low Level Abstraction Layer
// =============================================================================

#define dumpBool(auxBool)       (char_t *)((auxBool) ? "true" : "false")

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __GLOBAL_DEFINES_HPP

// =============================================================================
// END OF FILE
// =============================================================================
