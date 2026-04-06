// =============================================================================
// Project:         FunSAPE test project
// File:            buttonSevenSegmentsMux.cpp
// Author:          Leandro Schwarz
// Created:         2026-04-03
// Modified:        2024-04-03
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

#include "funsape/globalDefines.hpp"
#include "funsape/peripheral/gpioBus.hpp"
#include "funsape/peripheral/gpioPin.hpp"
#include "funsape/peripheral/pcint1.hpp"
#include "funsape/device/sevenSegmentsMuxDisplay.hpp"

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

typedef union {
    struct {
        bool_t      updateValue         : 1;
        bool_t      isPressedButtonM    : 1;
        bool_t      isPressedButtonC    : 1;
        bool_t      isPressedButtonD    : 1;
        bool_t      isPressedButtonU    : 1;
    };
    uint8_t         allFlags;

} systemFlags_t;


// =============================================================================
// Static function declarations
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

volatile systemFlags_t systemFlags;

vuint16_t counterValue  = 1234;

// =============================================================================
// Main function
// =============================================================================

int main()
{
    // -------------------------------------------------------------------------
    // Local variables
    // -------------------------------------------------------------------------

    pcint1.init(
            Pcint1::Pin::PIN_PCINT8     |
            Pcint1::Pin::PIN_PCINT9     |
            Pcint1::Pin::PIN_PCINT10    |
            Pcint1::Pin::PIN_PCINT11
    );
    pcint1.setPinMode(
            (
                    Pcint1::Pin::PIN_PCINT8     |
                    Pcint1::Pin::PIN_PCINT9     |
                    Pcint1::Pin::PIN_PCINT10    |
                    Pcint1::Pin::PIN_PCINT11
            ),
            PinMode::INPUT_PULLED_UP
    );
    pcint1.clearInterruptRequest();
    pcint1.activateInterrupt();

    GpioBus displayControl;
    GpioBus displaySegments;
    SevenSegmentsMuxDisplay display;

    uint8_t digits[4] = {0, 0, 0, 0};

    systemFlags.allFlags = 0;
    systemFlags.updateValue = true;

    displayControl.init(&DDRB, PinIndex::P0, 4);
    displaySegments.init(&DDRD, PinIndex::P0, 8);
    display.setPorts(&displaySegments, &displayControl, LogicLevel::LOW);
    display.init(SevenSegmentsDisplayType::COMMON_ANODE);
    display.updateDigitValues(digits);

    // -------------------------------------------------------------------------
    // Enables global interrupt handling
    // -------------------------------------------------------------------------

    sei();

    // -------------------------------------------------------------------------
    // Main loop
    // -------------------------------------------------------------------------

    while(1) {
        // ---------------------------------------------------------------------
        // Reads buttons
        // ---------------------------------------------------------------------

        if(systemFlags.updateValue) {
            digits[0] = (counterValue % 10);
            digits[1] = ((counterValue / 10) % 10);
            digits[2] = ((counterValue / 100) % 10);
            digits[3] = ((counterValue / 1000) % 10);
            display.updateDigitValues(digits);
            systemFlags.updateValue = false;
        }

        display.showNextDigit();
        delayMs(10);

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

void pcint1InterruptCallback(void)
{
    if(isBitClr(PINC, PC0)) {
        if(!systemFlags.isPressedButtonU) {
            systemFlags.isPressedButtonU = true;
            counterValue += 1;
            counterValue %= 10000;
            systemFlags.updateValue = true;
        }
    } else {
        systemFlags.isPressedButtonU = false;
    }

    if(isBitClr(PINC, PC1)) {
        if(!systemFlags.isPressedButtonD) {
            systemFlags.isPressedButtonD = true;
            counterValue += 10;
            counterValue %= 10000;
            systemFlags.updateValue = true;
        }
    } else {
        systemFlags.isPressedButtonD = false;
    }

    if(isBitClr(PINC, PC2)) {
        if(!systemFlags.isPressedButtonC) {
            systemFlags.isPressedButtonC = true;
            counterValue += 100;
            counterValue %= 10000;
            systemFlags.updateValue = true;
        }
    } else {
        systemFlags.isPressedButtonC = false;
    }

    if(isBitClr(PINC, PC3)) {
        if(!systemFlags.isPressedButtonM) {
            systemFlags.isPressedButtonM = true;
            counterValue += 1000;
            counterValue %= 10000;
            systemFlags.updateValue = true;
        }
    } else {
        systemFlags.isPressedButtonM = false;
    }
}

// =============================================================================
// End of file (buttonSevenSegmentsMux.cpp)
// =============================================================================
