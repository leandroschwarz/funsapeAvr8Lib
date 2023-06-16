//!
//! \file           USART.hpp
//! \brief          USART/USART communication peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-04-05
//! \version        23.04
//! \copyright      license
//! \details        USART/USART communication peripheral control for the FunSAPE AVR8 Library
//! \todo           USART and USART in SPI mode
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __USART0_HPP
#define __USART0_HPP                            2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __USART0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __USART0_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

#include "../util/systemStatus.hpp"

extern FILE usartStream;

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

//!
//! \brief          USART Reception Complete interrupt callback function
//! \details        This function is called when the USART Reception Complete
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void usartReceptionCompleteCallback(void);

//!
//! \brief          USART Transmission Buffer Empty interrupt callback function
//! \details        This function is called when the USART Transmission Buffer
//!                     Empty interrupt is treated. It is a weak function that
//!                     can be overwritten by user code.
//!
void usartTransmissionBufferEmptyCallback(void);

//!
//! \brief          USART Transmission Complete interrupt callback function
//! \details        This function is called when the USART Transmission Complete
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void usartTransmissionCompleteCallback(void);

// =============================================================================
// Usart Class
// =============================================================================

//!
//! \brief          Usart0 class
//! \details        Usart0 class
//!
class Usart0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ///////////////     USART0 Operation Mode     ////////////////     //
    //!
    //! \brief      USART0 Operation Mode enumeration
    //! \details    Operation mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Mode : uint8_t {
        ASYNCHRONOUS                            = 0,    //!< Peripheral in UART without double speed mode.
        ASYNCHRONOUS_DOUBLE_SPEED               = 1,    //!< Peripheral in UART with double speed mode.
        SYNCHRONOUS_TX_RISING_RX_FALLING        = 2,    //!< Peripheral in USART mode on falling edge.
        SYNCHRONOUS_TX_FALLING_RX_RISING        = 3,    //!< Peripheral in USART mode on rising edge.
        MASTER_SPI_MODE_0                       = 4,    //!< Peripheral in master SPI mode 0.
        MASTER_SPI_MODE_1                       = 5,    //!< Peripheral in master SPI mode 1.
        MASTER_SPI_MODE_2                       = 6,    //!< Peripheral in master SPI mode 2.
        MASTER_SPI_MODE_3                       = 7,    //!< Peripheral in master SPI mode 3.
    };

    //     ///////////////    USART0 Reception Error     ////////////////     //
    //!
    //! \brief      USART0 Reception Error enumeration
    //! \details    Reception error associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ReceptionError : uint8_t {
        NONE                            = 0,            //!< No reception errors occurred
        FRAME_ERROR                     = (1 << 0),     //!< Frame format invalid
        PARITY_ERROR                    = (1 << 1),     //!< Parity check failed
        DATA_OVERRUN_ERROR              = (1 << 2),     //!< Data lost
        ALL                             = (1 << 0) | (1 << 1) | (1 << 2)
    };

    friend inlined ReceptionError operator|(ReceptionError a, ReceptionError b);
    friend inlined ReceptionError &operator|=(ReceptionError &a, ReceptionError b);
    friend inlined ReceptionError operator&(ReceptionError a, ReceptionError b);
    friend inlined ReceptionError &operator&=(ReceptionError &a, ReceptionError b);
    friend inlined ReceptionError operator~(ReceptionError a);

    //     /////////////////    USART0 Parity Mode     //////////////////     //
    //!
    //! \brief      USART0 Parity Mode enumeration
    //! \details    Parity mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Parity : uint8_t {
        NONE                            = 0,    //!< No parity.
        ODD                             = 1,    //!< Odd parity.
        EVEN                            = 2     //!< Even parity.
    };

    //     //////////////////     USART0 StopBits     ///////////////////     //
    //!
    //! \brief      USART0 StopBits enumeration
    //! \details    Number of stop bits associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class StopBits : uint8_t {
        SINGLE                          = 0,    //!< One stop bit
        DOUBLE                          = 1     //|< Two stop bits
    };

    //     //////////////////     USART0 DataSize     ///////////////////     //
    //!
    //! \brief      USART0 DataSize enumeration
    //! \details    Data size associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class DataSize : uint8_t {
        DATA_5_BITS                     = 0,
        DATA_6_BITS                     = 1,
        DATA_7_BITS                     = 2,
        DATA_8_BITS                     = 3,
        DATA_9_BITS                     = 7,
    };

    //     /////////////////    USART0 FrameFormat     //////////////////     //
    //!
    //! \brief      USART0 FrameFormat enumeration
    //! \details    Frame format mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class FrameFormat : uint8_t {
        //                      = 0bDDDDPPSS
        // DDDD -> Number of data bits (5-8)
        // PP   -> Parity (NONE / ODD / EVEN)
        // SS   -> Number of stop bits (1-2)
        FRAME_FORMAT_8_N_1        = 0b10000001,
        FRAME_FORMAT_8_O_1        = 0b10000101,
        FRAME_FORMAT_8_E_1        = 0b10001001,
        FRAME_FORMAT_8_N_2        = 0b10000010,
        FRAME_FORMAT_8_O_2        = 0b10000110,
        FRAME_FORMAT_8_E_2        = 0b10001010,
        FRAME_FORMAT_9_N_1        = 0b10010001,
        FRAME_FORMAT_9_O_1        = 0b10010101,
        FRAME_FORMAT_9_E_1        = 0b10011001,
        FRAME_FORMAT_9_N_2        = 0b10010010,
        FRAME_FORMAT_9_O_2        = 0b10010110,
        FRAME_FORMAT_9_E_2        = 0b10011010,
        FRAME_FORMAT_5_N_1        = 0b01010001,
        FRAME_FORMAT_5_O_1        = 0b01010101,
        FRAME_FORMAT_5_E_1        = 0b01011001,
        FRAME_FORMAT_5_N_2        = 0b01010010,
        FRAME_FORMAT_5_O_2        = 0b01010110,
        FRAME_FORMAT_5_E_2        = 0b01011010,
        FRAME_FORMAT_6_N_1        = 0b01100001,
        FRAME_FORMAT_6_O_1        = 0b01100101,
        FRAME_FORMAT_6_E_1        = 0b01101001,
        FRAME_FORMAT_6_N_2        = 0b01100010,
        FRAME_FORMAT_6_O_2        = 0b01100110,
        FRAME_FORMAT_6_E_2        = 0b01101010,
        FRAME_FORMAT_7_N_1        = 0b01110001,
        FRAME_FORMAT_7_O_1        = 0b01110101,
        FRAME_FORMAT_7_E_1        = 0b01111001,
        FRAME_FORMAT_7_N_2        = 0b01110010,
        FRAME_FORMAT_7_O_2        = 0b01110110,
        FRAME_FORMAT_7_E_2        = 0b01111010
    };

    //     //////////////////    USART0 Baud Rate     ///////////////////     //
    //!
    //! \brief      USART0 Baud Rate enumeration
    //! \details    Baud rate speed associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class BaudRate : uint32_t {
        BAUD_RATE_600                   = 600UL,
        BAUD_RATE_1200                  = 1200UL,
        BAUD_RATE_1800                  = 1800UL,
        BAUD_RATE_2400                  = 2400UL,
        BAUD_RATE_4800                  = 4800UL,
        BAUD_RATE_9600                  = 9600UL,
        BAUD_RATE_14400                 = 14400UL,
        BAUD_RATE_19200                 = 19200UL,
        BAUD_RATE_28800                 = 28800UL,
        BAUD_RATE_38400                 = 38400UL,
        BAUD_RATE_56000                 = 56000UL,
        BAUD_RATE_57600                 = 57600UL,
        BAUD_RATE_115200                = 115200UL,
        BAUD_RATE_128000                = 128000UL,
        BAUD_RATE_230400                = 230400UL,
        BAUD_RATE_256000                = 256000UL
    };
    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    //!
    //! \brief      Usart0 class constructor
    //! \details    Creates an Usart0 object
    //!
    Usart0(
            BaudRate baudRate_p = BaudRate::BAUD_RATE_9600,
            Mode mode_p = Mode::ASYNCHRONOUS,
            FrameFormat format = FrameFormat::FRAME_FORMAT_8_N_1
    );

    //!
    //! \brief      Usart0 class constructor
    //! \details    Creates an Usart0 object
    //!
    ~Usart0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Initializes the USART0 module
    //! \details    Initializes the USART0 module.
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            void
    );

    //!
    //! \brief      Disables USART receiver
    //! \details    Disables USART receiver
    //!
    void inlined disableReceiver(void);

    //!
    //! \brief      Disables USART transmitter
    //! \details    Disables USART transmitter
    //!
    void inlined disableTransmitter(void);

    //!
    //! \brief      Enables USART receiver
    //! \details    Enables USART receiver
    //!
    void inlined enableReceiver(void);

    //!
    //! \brief      Enables USART transmitter
    //! \details    Enables USART transmitter
    //!
    void inlined enableTransmitter(void);

    //!
    //! \brief          Sets data size
    //! \details        Sets data size.
    //! \param          dataSize_p      Data size
    //!
    bool_t setDataSize(
            const DataSize dataSize_p
    );

    bool_t setMode(
            const Mode mode_p
    );

    bool_t setStopBits(
            const StopBits stopBits_p
    );

    bool_t setParity(
            const Parity parity_p
    );

    bool_t setBaudRate(
            const BaudRate baudRate_p
    );

    bool_t setFrameFormat(
            const FrameFormat frameFormat_p
    );

    //     ///////////////////////     STATUS    ////////////////////////     //

    //!
    //! \brief      Verifies reception status
    //! \details    Verifies reception status.
    //! \return     bool_t              True on reception ended / False otherwise
    //!
    bool_t inlined isReceptionComplete(void);

    //!
    //! \brief      Verifies transmission buffer status
    //! \details    Verifies transmission buffer status.
    //! \return     bool_t              True on buffer empty / False otherwise
    //!
    bool_t inlined isTransmissionBufferEmpty(void);

    //!
    //! \brief      Verifies transmission status
    //! \details    Verifies transmission status.
    //! \return     bool_t              True on transmission ended / False otherwise
    //!
    bool_t inlined isTransmissionComplete(void);

    //!
    //! \brief      Get status of the last reception
    //! \details    Get status of the last reception.
    //! \param      errorCode_p         Pointer to store the reception error code
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t getReceptionStatus(
            ReceptionError *errorCode_p
    );

    //     /////////////////////     INTERRUPTS    //////////////////////     //

    //!
    //! \brief      Activates Reception Complete interrupt
    //! \details    Activates Reception Complete interrupt.
    //!
    void inlined activateReceptionCompleteInterrupt(void);

    //!
    //! \brief      Activates Transmission Buffer Empty interrupt
    //! \details    Activates Transmission Buffer Empty interrupt.
    //!
    void inlined activateTransmissionBufferEmptyInterrupt(void);

    //!
    //! \brief      Activates Transmission Complete interrupt
    //! \details    Activates Transmission Complete interrupt.
    //!
    void inlined activateTransmissionCompleteInterrupt(void);

    //!
    //! \brief      Deactivates Reception Complete interrupt
    //! \details    Deactivates Reception Complete interrupt
    //!
    void inlined deactivateReceptionCompleteInterrupt(void);

    //!
    //! \brief      Deactivates Transmission Buffer Empty interrupt
    //! \details    Deactivates Transmission Buffer Empty interrupt.
    //!
    void inlined deactivateTransmissionBufferEmptyInterrupt(void) ;

    //!
    //! \brief      Deactivates Transmission Complete interrupt
    //! \details    Deactivates Transmission Complete interrupt.
    //!
    void inlined deactivateTransmissionCompleteInterrupt(void);

    //!
    //! \brief      Redirects standard i/o streams
    //! \details    Redirects standard i/o streams.
    //!
    void inlined stdio(void);

    // UCSRA    U2X0
    // UCSRA    MPCM0

    bool_t sendData(cuint16_t data_p);
    bool_t receiveData(uint16_t *data_p);
    void flushReceptionBuffer(void);
    char receiveDataStd(FILE *stream_p);
    int16_t sendDataStd(char data_p, FILE *stream_p);


private:
    char _receiveDataStd(FILE *stream_p);
    void _clearDataOverrunError(void);
    void _clearFrameError(void);
    void _clearParityError(void);

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    //     ////////////////     RECEPTION ERROR FLAGS    ////////////////     //
    bool_t  _isDataOverrunError                         : 1;
    bool_t  _isFrameError                               : 1;
    bool_t  _isParityError                              : 1;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t  _isInitialized                              : 1;
    bool_t  _isReceiverEnabled                          : 1;
    bool_t  _isReceptionCompleteInterruptEnabled        : 1;
    bool_t  _isTransmissionBufferEmptyInterruptEnabled  : 1;
    bool_t  _isTransmissionCompleteInterruptEnabled     : 1;
    bool_t  _isTransmitterEnabled                       : 1;
    Error   _lastError;

    //     ////////////////////     CONFIGURATION    ////////////////////     //
    DataSize        _dataSize;
    Mode            _mode;
    BaudRate        _baudRate;
    Parity          _parity;
    StopBits        _stopBits;
}; // class Usart0

// =============================================================================
// Class inlined functions
// =============================================================================

void inlined Usart0::disableReceiver(void)
{
    clrBit(UCSR0B, RXEN0);
    return;
}

void inlined Usart0::disableTransmitter(void)
{
    clrBit(UCSR0B, TXEN0);
    return;
}

void inlined Usart0::enableReceiver(void)
{
    setBit(UCSR0B, RXEN0);
    return;
}

void inlined Usart0::enableTransmitter(void)
{
    setBit(UCSR0B, TXEN0);
    return;
}

bool_t inlined Usart0::isReceptionComplete(void)
{
    return isBitSet(UCSR0A, RXC0);
}

bool_t inlined Usart0::isTransmissionBufferEmpty(void)
{
    return isBitSet(UCSR0A, UDRE0);
}

bool_t inlined Usart0::isTransmissionComplete(void)
{
    return isBitSet(UCSR0A, TXC0);
}

void inlined Usart0::activateReceptionCompleteInterrupt(void)
{
    setBit(UCSR0B, RXCIE0);
    return;
}

void inlined Usart0::activateTransmissionBufferEmptyInterrupt(void)
{
    setBit(UCSR0B, UDRIE0);
    return;
}

void inlined Usart0::activateTransmissionCompleteInterrupt(void)
{
    setBit(UCSR0B, TXCIE0);
    return;
}

void inlined Usart0::deactivateReceptionCompleteInterrupt(void)
{
    clrBit(UCSR0B, RXCIE0);
    return;
}

void inlined Usart0::deactivateTransmissionBufferEmptyInterrupt(void)
{
    clrBit(UCSR0B, UDRIE0);
    return;
}

void inlined Usart0::deactivateTransmissionCompleteInterrupt(void)
{
    clrBit(UCSR0B, TXCIE0);
    return;
}

void inlined Usart0::stdio(void)
{
    stdin = stdout = stderr = &usartStream;
    return;
}

Usart0::ReceptionError inlined operator|(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator|=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator&(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator&=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator~(Usart0::ReceptionError a)
{
    return static_cast<Usart0::ReceptionError>(static_cast<int>(Usart0::ReceptionError::ALL) ^ static_cast<int>(a));
}

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Usart0 peripheral handler object
//! \details        Usart0 peripheral handler object
//!
extern Usart0 usart0;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __USART0_HPP

// =============================================================================
// END OF FILE
// =============================================================================

/*

#define DEBUG_USART0                    0xFFFF

bool_t Usart0::getReceptionStatus(ReceptionError *errorCode_p)
{
    // Marks passage for debugging purpose
    debugMark("Usart0::getReceptionStatus(ReceptionError *)", DEBUG_USART0);

    // Local variables
    uint8_t aux8 = 0;

    // Checks for errors
    if(!isPointerValid(errorCode_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, DEBUG_USART0)
        return false;
    }

    // Retrieve reception error
    aux8 |= (isBitSet(UCSR0A, FE0)) ? (uint8_t)ReceptionError::FRAME_ERROR : 0;
    aux8 |= (isBitSet(UCSR0A, UPE0)) ? (uint8_t)ReceptionError::PARITY_ERROR : 0;
    aux8 |= (isBitSet(UCSR0A, DOR0)) ? (uint8_t)ReceptionError::DATA_OVERRUN_ERROR : 0;
    *errorCode_p = (ReceptionError)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_USART0);
    return true;
}
*/
