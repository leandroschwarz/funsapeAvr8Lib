#define F_CPU 16000000UL

#include "funsape/globalDefines.hpp"
#include "funsape/device/hd44780.hpp"

int main()
{

    Hd44780 lcd;
    uint16_t dia = 17;
    uint16_t mes = 4;
    uint16_t ano = 23;
    uint16_t hora = 22;
    uint16_t minuto = 43;
    uint16_t segundo = 37;

    lcd.controlPortSet(&DDRB, PB2, PB3, PB4);
    lcd.dataPortSet(&DDRD, PD2);
    lcd.init(Hd44780::Size::LCD_16X2, Hd44780::Font::FONT_5X8, true, true);
    lcd.stdio();
    printf(" %02d/%02d/20%02d %3s\n", dia, mes, ano, "SEG");
    printf("    %02d:%02d:%02d    \n", hora, minuto, segundo);

    setBit(DDRB, PB5);

    while(1) {
        cplBit(PORTB, PB5);
        delayMs(250);
    }

    return 0;
}
