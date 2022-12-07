//!
//! \file           funsapeAvrUsart0.hpp
//! \brief          Usart communication peripheral control for the FunSAPE AVR8 Library
//! \details        TODO
//! \author         Leandro Schwarz
//! \version        22.0
//! \date           2022-12-02
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_AVR_USART0_HPP
#define __FUNSAPE_AVR_USART0_HPP                        220

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#if __has_include("../funsapeAvrGlobalDefines.hpp")
#   include "../funsapeAvrGlobalDefines.hpp"
#   if !defined(__FUNSAPE_AVR_GLOBAL_DEFINES_HPP)
#       error "Global definitions file is corrupted!"
#   elif __FUNSAPE_AVR_GLOBAL_DEFINES_HPP != __FUNSAPE_AVR_USART0_HPP
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

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

void usartReceptionCompleteCallback(void);
void usartTransmissionBufferEmptyCallback(void);
void usartTransmissionCompleteCallback(void);

// =============================================================================
// Usart Class
// =============================================================================

class Usart0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ///////////////     USART0 Operation Mode     ////////////////     //
    //!
    //! \enum           Mode
    //!     \details    Operation mode associated with the USART0.
    //!     \warning    The value associate with the symbolic names may change between builds and might not reflect the register/bits real values. In order to ensure compatibility between builds, always refer to the SYMBOLIC NAME, instead of the VALUE.
    //!
    enum class Mode : uint8_t {
        ASSYNCHRONOUS                   = 0,    //!< Peripheral in UART without double speed mode.
        ASSYNCHRONOUS_DOUBLE_SPEED      = 1,    //!< Peripheral in UART with double speed mode.
        SYNCHRONOUS_XCK_FALLING         = 2,    //!< Peripheral in USART mode on falling edge.
        SYNCHRONOUS_XCK_RISING          = 3,    //!< Peripheral in USART mode on rising edge.
        MASTER_SPI_LEADING              = 4,    //!< Peripheral in master SPI mode with leading edge.
        MASTER_SPI_TRAILING             = 5,    //!< Peripheral in master SPI mode with trailing edge.
    };
    enum class ReceptionError : uint8_t {
        NONE                            = 0,            //
        FRAME_ERROR                     = (1 << 0),     //
        PARITY_ERROR                    = (1 << 1),     //
        DATA_OVERRUN_ERROR              = (1 << 2)      //
    };
    enum class Parity : uint8_t {
        NONE                            = 0,    //!< No parity.
        ODD                             = 1,    //!< Odd parity.
        EVEN                            = 2     //!< Even parity.
    };
    enum class StopBits : uint8_t {
        SINGLE                          = 0,    //!< One stop bit
        DOUBLE                          = 1     //|< Two stop bits
    };
    enum class DataSize : uint8_t {
        DATA_5_BITS                     0,
        DATA_6_BITS                     1,
        DATA_7_BITS                     2,
        DATA_8_BITS                     3,
        DATA_9_BITS                     7,
    };

    enum class FrameFormat {
        //                      = 0bDDDDPPSS
        // DDDD -> Number of data bits (5-8)
        // PP   -> Parity (NONE / ODD / EVEN)
        // SS   -> Number of stop bits (1-2)
        USART_FRAME_FORMAT_8_N_1        = 0b10000001,
        USART_FRAME_FORMAT_8_O_1        = 0b10000101,
        USART_FRAME_FORMAT_8_E_1        = 0b10001001,
        USART_FRAME_FORMAT_8_N_2        = 0b10000010,
        USART_FRAME_FORMAT_8_O_2        = 0b10000110,
        USART_FRAME_FORMAT_8_E_2        = 0b10001010,
        USART_FRAME_FORMAT_9_N_1        = 0b10010001,
        USART_FRAME_FORMAT_9_O_1        = 0b10010101,
        USART_FRAME_FORMAT_9_E_1        = 0b10011001,
        USART_FRAME_FORMAT_9_N_2        = 0b10010010,
        USART_FRAME_FORMAT_9_O_2        = 0b10010110,
        USART_FRAME_FORMAT_9_E_2        = 0b10011010,
        USART_FRAME_FORMAT_5_N_1        = 0b01010001,
        USART_FRAME_FORMAT_5_O_1        = 0b01010101,
        USART_FRAME_FORMAT_5_E_1        = 0b01011001,
        USART_FRAME_FORMAT_5_N_2        = 0b01010010,
        USART_FRAME_FORMAT_5_O_2        = 0b01010110,
        USART_FRAME_FORMAT_5_E_2        = 0b01011010,
        USART_FRAME_FORMAT_6_N_1        = 0b01100001,
        USART_FRAME_FORMAT_6_O_1        = 0b01100101,
        USART_FRAME_FORMAT_6_E_1        = 0b01101001,
        USART_FRAME_FORMAT_6_N_2        = 0b01100010,
        USART_FRAME_FORMAT_6_O_2        = 0b01100110,
        USART_FRAME_FORMAT_6_E_2        = 0b01101010,
        USART_FRAME_FORMAT_7_N_1        = 0b01110001,
        USART_FRAME_FORMAT_7_O_1        = 0b01110101,
        USART_FRAME_FORMAT_7_E_1        = 0b01111001,
        USART_FRAME_FORMAT_7_N_2        = 0b01110010,
        USART_FRAME_FORMAT_7_O_2        = 0b01110110,
        USART_FRAME_FORMAT_7_E_2        = 0b01111010
    } usartFrameFormat_e;




    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Usart0(
            void
    );
    ~Usart0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //
    bool_t          init(
    );
    inlined void disableReceiver(void) {
        clrBit(UCSR0B, RXEN0);
        return;
    }
    inlined void disableTransmitter(void) {
        clrBit(UCSR0B, TXEN0);
        return;
    }
    inlined void enableReceiver(void) {
        setBit(UCSR0B, RXEN0);
        return;
    }
    inlined void enableTransmitter(void) {
        setBit(UCSR0B, TXEN0);
        return;
    }

    void setDataSize(const DataSize dataSize_p) {

        // Reset data members
        this->_isInitialized = false;

        if (isBitSet((uint8_t)dataSize_p, 2)) {
            setBit(UCSR0B, UCSZ02);
        } else {
            clrBit(UCSR0B, UCSZ02);
        }
        clrMaskOffset(UCSR0C, 0x03, UCSZ00);
        setMaskOffset(UCSR0C, (0x03 & (uint8_t)dataSize_p), UCSZ00);

        return true;
    }

    //     ///////////////////////     STATUS    ////////////////////////     //
    inlined bool_t  isReceptionComplete(void) {
        return isBitSet(UCSR0A, RXC0);
    }
    inlined bool_t  isTransmissionBufferEmpty(void) {
        return isBitSet(UCSR0A, UDRE0);
    }
    inlined bool_t  isTransmissionComplete(void) {
        return isBitSet(UCSR0A, TXC0);
    }
    bool_t          getReceptionStatus(
            ReceptionError *errorCode_p
    );

    //     /////////////////////     INTERRUPTS    //////////////////////     //
    inlined void    activateReceptionCompleteInterrupt(void) {
        setBit(UCSR0B, RXCIE0);
        return;
    }
    inlined void    activateTransmissionBufferEmptyInterrupt(void) {
        setBit(UCSR0B, UDRIE0);
        return;
    }
    inlined void    activateTransmissionCompleteInterrupt(void) {
        setBit(UCSR0B, TXCIE0);
        return;
    }
    inlined void    deactivateReceptionCompleteInterrupt(void) {
        clrBit(UCSR0B, RXCIE0);
        return;
    }
    inlined void    deactivateTransmissionBufferEmptyInterrupt(void) {
        clrBit(UCSR0B, UDRIE0);
        return;
    }
    inlined void    deactivateTransmissionCompleteInterrupt(void) {
        clrBit(UCSR0B, TXCIE0);
        return;
    }



    // UCSRA    U2X0
    // UCSRA    MPCM0

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
    uint8_t _dataBitsCount                              : 3;
    Mode    _mode                                       : 2;
}; // class Usart0

// =============================================================================
// Inlined class functions
// =============================================================================

inlined Usart0::ReceptionError operator|(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

inlined Usart0::ReceptionError &operator|=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

inlined Usart0::ReceptionError operator&(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) & static_cast<cuint8_t>(b));
}

inlined Usart0::ReceptionError &operator&=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) & static_cast<cuint8_t>(b));
}

// NONE

// =============================================================================
// External global variables
// =============================================================================

extern Usart0 usart0;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_AVR_USART0_HPP

// =============================================================================
// END OF FILE
// =============================================================================




#define DEBUG_USART0                    0xFFFF

bool_t Usart0::getReceptionStatus(ReceptionError *errorCode_p)
{
    // Marks passage for debugging purpose
    debugMark("Usart0::getReceptionStatus(ReceptionError *)", DEBUG_USART0);

    // Local variables
    uint8_t aux8 = 0;

    // Checks for errors
    if (!isPointerValid(errorCode_p)) {
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
