/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			spiMaster.h
 * Module:			Serial Peripheral Interface module in master mode
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 18, 2018
 * -------------------------------------------------------------------------- */

#ifndef __SPI_MASTER_H
#define __SPI_MASTER_H 1

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "../funsape/globalDefines.hpp"

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------
#define SPI_MOSI    PB3
#define SPI_MISO    PB4
#define SPI_SCLK    PB5
#define SPI_DDR     DDRB



// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum spiModes_t {
    SPI_MODE_0			= 0,
    SPI_MODE_1			,
    SPI_MODE_2			,
    SPI_MODE_3
} spiModes_t;

typedef enum spiDataOrder_t {
    SPI_MSB_FIRST		= 0,
    SPI_LSB_FIRST
} spiDataOrder_t;

typedef enum spiClockPrescaler_t {
    SPI_PRESCALER_4			= 0,
    SPI_PRESCALER_16		= 1,
    SPI_PRESCALER_64		= 2,
    SPI_PRESCALER_128		= 3,
    SPI_PRESCALER_2			= 4,
    SPI_PRESCALER_8			= 5,
    SPI_PRESCALER_32		= 6
} spiClockPrescaler_t;

typedef enum spiProtocol_t {
    SPI_BIT_BANG			= 0,
    SPI_INTERRUPT_DRIVEN	= 1
} spiProtocol_t;

typedef struct spiMaster_t {
    spiClockPrescaler_t	prescaler	: 3;
    spiModes_t			mode		: 2;
    spiDataOrder_t		dataOrder	: 1;
    spiProtocol_t		protocol	: 1;
    bool_t				initialized	: 1;
} spiMaster_t;

typedef enum pinLocation_e {
    LOCATION_PA0		= 0x00,
    LOCATION_PA1		= 0x01,
    LOCATION_PA2		= 0x02,
    LOCATION_PA3		= 0x03,
    LOCATION_PA4		= 0x04,
    LOCATION_PA5		= 0x05,
    LOCATION_PA6		= 0x06,
    LOCATION_PA7		= 0x07,
    LOCATION_PB0		= 0x10,
    LOCATION_PB1		= 0x11,
    LOCATION_PB2		= 0x12,
    LOCATION_PB3		= 0x13,
    LOCATION_PB4		= 0x14,
    LOCATION_PB5		= 0x15,
    LOCATION_PB6		= 0x16,
    LOCATION_PB7		= 0x17,
    LOCATION_PC0		= 0x20,
    LOCATION_PC1		= 0x21,
    LOCATION_PC2		= 0x22,
    LOCATION_PC3		= 0x23,
    LOCATION_PC4		= 0x24,
    LOCATION_PC5		= 0x25,
    LOCATION_PC6		= 0x26,
    LOCATION_PC7		= 0x27,
    LOCATION_PD0		= 0x30,
    LOCATION_PD1		= 0x31,
    LOCATION_PD2		= 0x32,
    LOCATION_PD3		= 0x33,
    LOCATION_PD4		= 0x34,
    LOCATION_PD5		= 0x35,
    LOCATION_PD6		= 0x36,
    LOCATION_PD7		= 0x37,
    LOCATION_PE0		= 0x40,
    LOCATION_PE1		= 0x41,
    LOCATION_PE2		= 0x42,
    LOCATION_PE3		= 0x43,
    LOCATION_PE4		= 0x44,
    LOCATION_PE5		= 0x45,
    LOCATION_PE6		= 0x46,
    LOCATION_PE7		= 0x47,
    LOCATION_PF0		= 0x50,
    LOCATION_PF1		= 0x51,
    LOCATION_PF2		= 0x52,
    LOCATION_PF3		= 0x53,
    LOCATION_PF4		= 0x54,
    LOCATION_PF5		= 0x55,
    LOCATION_PF6		= 0x56,
    LOCATION_PF7		= 0x57,
    LOCATION_PG0		= 0x60,
    LOCATION_PG1		= 0x61,
    LOCATION_PG2		= 0x62,
    LOCATION_PG3		= 0x63,
    LOCATION_PG4		= 0x64,
    LOCATION_PG5		= 0x65,
    LOCATION_PG6		= 0x66,
    LOCATION_PG7		= 0x67,
    LOCATION_PH0		= 0x70,
    LOCATION_PH1		= 0x71,
    LOCATION_PH2		= 0x72,
    LOCATION_PH3		= 0x73,
    LOCATION_PH4		= 0x74,
    LOCATION_PH5		= 0x75,
    LOCATION_PH6		= 0x76,
    LOCATION_PH7		= 0x77
} pinLocation_e;

typedef struct spiSlaveDevice_s {
    pinLocation_e		ssLocation;
    uint8_t				ddrOffset;
    uint8_t				portOffset;
    uint8_t				bitOffset;
} spiSlaveDevice_s;

// -----------------------------------------------------------------------------
// Global variable declarations ------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Macrofunctions --------------------------------------------------------------

#define spiMasterOff()	clrBit(SPI_PORT, SPI_MOSI);clrBit(SPI_PORT, SPI_MISO);clrBit(SPI_PORT, SPI_SCLK);clrBit(SPI_DDR, SPI_MOSI);clrBit(SPI_DDR, SPI_MISO);clrBit(SPI_DDR, SPI_SCLK)
#define spiMasterOn()	clrBit(SPI_PORT, SPI_MOSI);clrBit(SPI_PORT, SPI_MISO);clrBit(SPI_PORT, SPI_SCLK);setBit(SPI_DDR, SPI_MOSI);clrBit(SPI_DDR, SPI_MISO);setBit(SPI_DDR, SPI_SCLK)

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

void spiSlaveDeviceCreate(spiSlaveDevice_s *device, pinLocation_e ss);
void spiSlaveDeviceSsLow(spiSlaveDevice_s *device);
void spiSlaveDeviceSsHigh(spiSlaveDevice_s *device);



void	spiMasterInit(spiClockPrescaler_t prescaler, spiModes_t mode, spiDataOrder_t dataOrder, spiProtocol_t protocol);
void 	spiMasterEnableInterrupt(void);
void 	spiMasterDisableInterrupt(void);
void	spiMasterSendReceiveData(uint8_t *txBuffer, uint8_t *rxBuffer, uint8_t sizeBuffer);
uint8_t spiMasterSendReceiveByte(uint8_t data);

#endif
