// =============================================================================
// Project:         FunSAPE test project
// File:            main.cpp
// Author:          Leandro Schwarz
// Created:         2024-10-03
// Modified:        2024-10-03
// Version:         1.0
// Notes:           This project is used to test the FunSAPE AVR Library
//                      features.
// =============================================================================

// =============================================================================
// Precompiler constant defintions
// =============================================================================

#define F_CPU 16000000UL

// =============================================================================
// Dependencies
// =============================================================================

#include "funsape/funsapeLibGlobalDefines.hpp"
#include "funsape/peripheral/funsapeLibGpioPin.hpp"
#include "funsape/peripheral/funsapeLibGpioBus.hpp"
#include "funsape/peripheral/funsapeLibTwi.hpp"
#include "funsape/device/funsapeLibHd44780.hpp"
#include "funsape/util/funsapeLibCircularBuffer.hpp"
//#include "funsape/device/funsapeLibBme280.hpp"

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Static function declarations
// =============================================================================

// NONE
void debugLed()
{
    while(1) {
        cplBit(PORTB, PB5);
        delayMs(500);
    }
}

// =============================================================================
// Global variables
// =============================================================================

CircularBuffer<uint8_t> usartRxBuffer;

// =============================================================================
// Main function
// =============================================================================

int main()
{
    // Local variables
    GpioPin lcdControlRs;
    GpioPin lcdControlEn;
    GpioBus lcdDataBus;
    Hd44780 lcd;
    Error lastError = Error::NONE;

    // Configures LED
    setBit(DDRB, PB5);

    // LCD configuration
    lcdControlRs.init(&DDRB, GpioPin::PinIndex::P0);
    lcdControlEn.init(&DDRB, GpioPin::PinIndex::P1);
    lcdDataBus.init(&DDRD, GpioBus::PinIndex::P4, 4);
    lcd.setControlPort(&lcdControlEn, &lcdControlRs);
    lcd.setDataPort(&lcdDataBus);
    lcd.init(Hd44780::Size::LCD_16X2, Hd44780::Font::FONT_5X8);

    // Shows splash screen
    lcd.stdio();
    lcd.clearScreen();
    printf(" BME280 example \n");
    printf("   2024-12-13   \n");
    delayMs(300);
    lcd.clearScreen();

    // Buffer configuration
    if(!usartRxBuffer.init(500)) {
        // Shows error
        lastError = usartRxBuffer.getLastError();
        lcd.cursorHome();
        printf("0 init()\nError = %04x\n", (uint16_t)lastError);
        systemHalt();
    }

    char message1[] = "$GPRMC,181408.00,A,2736.71935,S,04835.10243,W,1.404,70.64,161224,,,A*54\r\n";
    char message2[] = "$GPVTG,70.64,T,,M,1.404,N,2.601,K,A*0C\r\n";
    char message3[] = "$GPGGA,181408.00,2736.71935,S,04835.10243,W,1,06,1.69,35.0,M,-0.9,M,,*7A\r\n";
    char message4[] = "$GPGSA,A,3,21,02,08,10,03,32,,,,,,,2.93,1.69,2.39*06\r\n";
    char message5[] = "$GPGSV,3,1,09,02,27,219,34,03,12,266,25,08,49,290,33,10,28,127,23*7D\r\n";
    char message6[] = "$GPGSV,3,2,09,21,45,214,37,27,40,340,,28,31,053,,31,20,025,10*7E\r\n";
    char message7[] = "$GPGSV,3,3,09,32,56,138,19*40\r\n";
    char message8[] = "$GPGLL,2736.71935,S,04835.10243,W,181408.00,A,A*65\r\n";

    usartRxBuffer.pushBuffer((uint8_t *)message1, strlen(message1));
    usartRxBuffer.pushBuffer((uint8_t *)message2, strlen(message2));
    usartRxBuffer.pushBuffer((uint8_t *)message3, strlen(message3));
    usartRxBuffer.pushBuffer((uint8_t *)message4, strlen(message4));
    usartRxBuffer.pushBuffer((uint8_t *)message5, strlen(message5));
    usartRxBuffer.pushBuffer((uint8_t *)message6, strlen(message6));
    usartRxBuffer.pushBuffer((uint8_t *)message7, strlen(message7));
    usartRxBuffer.pushBuffer((uint8_t *)message8, strlen(message8));

    // Main loop
    while(1) {
        lcd.cursorHome();
        printf("%u/%u\n\n",
                usartRxBuffer.getOccupation(),
                usartRxBuffer.getFreeSpace()
        );

        // Start measurement
        cplBit(PORTB, PB5);
        delayMs(100);
    }

    return 0;
}

// =============================================================================
// Static function definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions definitions
// =============================================================================

// NONE
