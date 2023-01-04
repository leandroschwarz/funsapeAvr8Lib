

#include "funsape/funsapeAvrGlobalDefines.hpp"

int main()
{
    DDRB = 1 << PB5;
    while(1) {
        cplBit(PORTB, PB5);
        delayMs(1000);                    // Solve simulation issues
    }
}
