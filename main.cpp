

#include "funsape/funsapeAvrGlobalDefines.hpp"
#include "funsape/peripheral/funsapeAvrAdc.hpp"
#include "funsape/peripheral/funsapeAvrTimer0.hpp"
#include "funsape/peripheral/funsapeAvrTimer1.hpp"
#include "funsape/peripheral/funsapeAvrTimer2.hpp"
#include "funsape/device/funsapeAvrSevenSegmentsDisplay.hpp"
#include "funsape/device/funsapeAvrSevenSegmentsMuxDisplay.hpp"
#include "funsape/device/funsapeAvrKeypad.hpp"

SevenSegmentsMuxDisplay display;
Keypad keypad;

int main()
{
    uint8_t digits[] = {0x00, 0x00};
    bool_t points[] = {false, false};

    display.setPorts(&DDRD, &DDRB, PB0, LogicLevel::LOW);
    display.init(2, SevenSegmentsDisplayType::COMMON_ANODE);
    display.updateDigitValues(digits, points);

    keypad.setPorts(&DDRC, PC0, &DDRB, PB2);
    // Proteus keypad
    // keypad.setKeyValues(Keypad::Type::KEYPAD_4X4,
    //         0x07, 0x08, 0x09, 0x0A,
    //         0x04, 0x05, 0x06, 0x0B,
    //         0x01, 0x02, 0x03, 0x0C,
    //         0x0E, 0x00, 0x0F, 0x0D
    // );
    // Physical keypad
    keypad.setKeyValues(Keypad::Type::KEYPAD_4X4,
            0x01, 0x02, 0x03, 0x0A,
            0x04, 0x05, 0x06, 0x0B,
            0x07, 0x08, 0x09, 0x0C,
            0x0E, 0x00, 0x0F, 0x0D
    );
    keypad.init(10);

    timer0.setCompareAValue(78);
    timer0.activateCompareAInterrupt();
    timer0.init(Timer0::Mode::CTC_OCRA, Timer0::ClockSource::PRESCALER_1024);

    sei();
    while (1) {
        uint8_t keyPressed = 0xFF;

        keypad.readKeyPressed(&keyPressed);
        if (keyPressed != 0xFF) {
            digits[0] = keyPressed;
            display.updateDigitValues(digits, points);
        }
        delayMs(10);                    // Solve simulation issues
    }
}

void timer0CompareACallback()
{
    display.showNextDigit();
}
