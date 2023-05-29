//!
//! \file           twi.hpp
//! \brief          TWI peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-16
//! \version        23.04
//! \copyright      license
//! \details        TWI peripheral control for the FunSAPE AVR8 Library
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __TWI_HPP
#define __TWI_HPP                               2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __TWI_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __TWI_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

#include "../util/bus.hpp"
#if !defined(__BUS_HPP)
#   error "Header file (bus.hpp) is corrupted!"
#elif __BUS_HPP != __TWI_HPP
#   error "Version mismatch between header file and library dependency (bus.hpp)!"
#endif

#include "../util/systemStatus.hpp"
#if !defined(__SYSTEM_STATUS_HPP)
#   error "Header file (systemStatus.hpp) is corrupted!"
#elif __SYSTEM_STATUS_HPP != __TWI_HPP
#   error "Version mismatch between header file and library dependency (systemStatus.hpp)!"
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

void twiInterruptCallback();

// =============================================================================
// Twi Class
// =============================================================================

//!
//! \brief          Twi class
//! \details        Twi class
//!
class Twi : public Bus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    // NONE


    //     ///////////////////     TWI operation     ////////////////////     //
    //!
    //! \brief      Brief description
    //! \details    Long description
    //!
    enum class Operation : bool_t {
        WRITE       = false,
        READ        = true
    };

private:
    //     ///////////////////     TWI operation     ////////////////////     //
    //!
    //! \brief      Brief description
    //! \details    Long description
    //!
    enum class State {
        START                           = 0x08, //!< START has been transmitted
        REP_START                       = 0x10, //!< Repeated START has been transmitted
        ARB_LOST                        = 0x38, //!< Arbitration lost
        MTX_ADR_ACK                     = 0x18, //!< SLA+W has been transmitted and ACK received
        MTX_ADR_NACK                    = 0x20, //!< SLA+W has been transmitted and NACK received
        MTX_DATA_ACK                    = 0x28, //!< Data byte has been transmitted and ACK received
        MTX_DATA_NACK                   = 0x30, //!< Data byte has been transmitted and NACK received
        MRX_ADR_ACK                     = 0x40, //!< SLA+R has been transmitted and ACK received
        MRX_ADR_NACK                    = 0x48, //!< SLA+R has been transmitted and NACK received
        MRX_DATA_ACK                    = 0x50, //!< Data byte has been received and ACK transmitted
        MRX_DATA_NACK                   = 0x58, //!< Data byte has been received and NACK transmitted
        STX_ADR_ACK                     = 0xA8, //!< Own SLA+R has been received; ACK has been returned
        STX_ADR_ACK_M_ARB_LOST          = 0xB0, //!< Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
        STX_DATA_ACK                    = 0xB8, //!< Data byte in TWDR has been transmitted; ACK has been received
        STX_DATA_NACK                   = 0xC0, //!< Data byte in TWDR has been transmitted; NOT ACK has been received
        STX_DATA_ACK_LAST_BYTE          = 0xC8, //!< Last data byte in TWDR has been transmitted (TWEA = 0); ACK has been received
        SRX_ADR_ACK                     = 0x60, //!< Own SLA+W has been received ACK has been returned
        SRX_ADR_ACK_M_ARB_LOST          = 0x68, //!< Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
        SRX_GEN_ACK                     = 0x70, //!< General call address has been received; ACK has been returned
        SRX_GEN_ACK_M_ARB_LOST          = 0x78, //!< Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
        SRX_ADR_DATA_ACK                = 0x80, //!< Previously addressed with own SLA+W; data has been received; ACK has been returned
        SRX_ADR_DATA_NACK               = 0x88, //!< Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
        SRX_GEN_DATA_ACK                = 0x90, //!< Previously addressed with general call; data has been received; ACK has been returned
        SRX_GEN_DATA_NACK               = 0x98, //!< Previously addressed with general call; data has been received; NOT ACK has been returned
        SRX_STOP_RESTART                = 0xA0, //!< A STOP condition or repeated START condition has been received while still addressed as Slave
        NO_STATE                        = 0xF8, //!< No relevant state information available; TWINT = 0
        BUS_ERROR                       = 0x00  //!< Bus error due to an illegal START or STOP condition
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    //!
    //! \brief      Twi class constructor
    //! \details    Creates an Twi object
    //!
    Twi(
            void
    );

    //!
    //! \brief      Twi class destructor
    //! \details    Destroys an Twi object
    //!
    ~Twi(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Bus::BusType getBusType(
            void
    );

    //     ////////////////////    DATA TRANSFER     ////////////////////     //
    bool_t readReg(
            cuint8_t reg_p,
            uint8_t *buffData_p,
            cuint16_t buffSize_p = 1
    );
    bool_t writeReg(
            cuint8_t reg_p,
            cuint8_t *buffData_p,
            cuint16_t buffSize_p = 1
    );

    //     //////////////////    PROTOCOL SPECIFIC     //////////////////     //
    bool_t setDevice(
            cuint16_t address_p,
            cbool_t useLongAddress_p = false
    );

protected:

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    //!
    //! \brief      Initializes the TWI module
    //! \details    Initializes the TWI module.
    //! \param      clockSpeed_p        Clock speed
    //! \param      bufferSize_p        Circular buffer size
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            cuint32_t clockSpeed_p      = 10'000,
            cuint8_t bufferSize_p       = 20
    );

    bool_t sendData(
            uint8_t devAddress_p,
            Operation readWrite_p,
            uint8_t reg_p,
            uint8_t *msg_p,
            uint8_t msgSize_p
    );

    bool_t setTimeout(
            cuint16_t timeout_p
    );

    Error getLastError(
            void
    );

    void interruptHandler(
            void
    );

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t _waitWhileIsBusy(
            void
    );

    bool_t _startTrasmission(
            void
    );

    bool_t _readFromBuffer(
            uint8_t *msg_p,
            cuint8_t msgSize_p
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:
    // NONE

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    //     /////////////     HAL DATA STRUCT VARIABLES     //////////////     //
    //     ////////////////////    DATA BUFFERS      ////////////////////     //
    bool_t               _devAddressSet                 : 1;
    bool_t               _initialized                   : 1;
    bool_t               _lastTransOk                   : 1;
    uint8_t             _twiError;
    bool_t               _useLongAddress                : 1;
    Error                _lastError;
    State                _state;
    uint8_t              _bufferIndex                   : 7;
    uint8_t              _bufferLength                  : 7;
    uint8_t              _bufferMaxSize                 : 7;
    uint16_t             _devAddress                 : 10;
    uint16_t             _timeout;
    uint8_t              *_bufferData;

}; // class Twi

// =============================================================================
// Twi - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

extern Twi twi;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __TWI_HPP

// =============================================================================
// END OF FILE
// =============================================================================
