

#include "nokia5110.hpp"
#include "nokia5110_chars.hpp"
#include <avr/pgmspace.h>

#include <math.h>

Nokia5110::Nokia5110()
{
    // Resets data members
    this->_initialized  = false;
    this->_portsSet     = false;
    this->_controlDdr   = nullptr;
    this->_controlPort  = nullptr;
    this->_dataIn       = 0;
    this->_chipSelect   = 0;
    this->_clock        = 0;
    this->_dc           = 0;
    this->_reset        = 0;
    this->_data         = nullptr;
    this->_posX         = 0;
    this->_posY         = 0;

    // Allocates memory
    this->_data = (uint8_t *)calloc(504, sizeof(uint8_t));
    if(!isPointerValid(this->_data)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION_FAILED;
        return;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return;
}

bool_t Nokia5110::setPort(ioRegAddress_t controlPort_p, ioPinIndex_t chipSelectPinIndex_p, ioPinIndex_t clockPinIndex_p,
        ioPinIndex_t dataPinIndex_p, ioPinIndex_t dataCommandPinIndex_p, ioPinIndex_t resetPinIndex_p)
{
    // Resets data members
    this->_initialized = false;
    this->_portsSet = false;

    if(!isGpioAddressValid(controlPort_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        return false;
    }
    // if((!isGpioPinIndexValid(chipSelectPinIndex_p)) ||
    //         (!isGpioPinIndexValid(clockPinIndex_p)) ||
    //         (!isGpioPinIndexValid(dataPinIndex_p)) ||
    //         (!isGpioPinIndexValid(dataCommandPinIndex_p))
    // ) {
    //     // Returns error
    //     this->_lastError = Error::GPIO_PIN_INDEX_INVALID;
    //     return false;
    // }

    // Updates data members
    this->_controlDdr   = getGpioDdrAddress(controlPort_p);
    this->_controlPort  = getGpioPortAddress(controlPort_p);
    this->_dataIn       = dataPinIndex_p;
    this->_chipSelect   = chipSelectPinIndex_p;
    this->_clock        = clockPinIndex_p;
    this->_dc           = dataCommandPinIndex_p;
    this->_reset        = resetPinIndex_p;
    this->_portsSet     = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::init()
{
    // Resets data members
    this->_initialized = false;

    // Checks for errors - Ports not set
    if(!this->_portsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        return false;
    }
    // Checks for errors - Buffer not allocated
    if(!isPointerValid(this->_data)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION_FAILED;
        return false;
    }

    // Configures ports
    setBit(*(this->_controlDdr), this->_dataIn);
    setBit(*(this->_controlDdr), this->_chipSelect);
    setBit(*(this->_controlDdr), this->_clock);
    setBit(*(this->_controlDdr), this->_dc);
    if(this->_reset != 0xFF) {
        setBit(*(this->_controlDdr), this->_reset);
    }

    // Resets display
    if(this->_reset != 0xFF) {
        setBit(*(this->_controlPort), this->_reset);
        setBit(*(this->_controlPort), this->_chipSelect);
        delayMs(10);
        clrBit(*(this->_controlPort), this->_reset);
        delayMs(70);
        setBit(*(this->_controlPort), this->_reset);
    }

    // Initialization procedure
    clrBit(*(this->_controlPort), this->_chipSelect);

    this->_write(0x21, false);                    // -LCD Extended Commands mode-
    this->_write(0x13, false);                    // LCD bias mode 1:48
    this->_write(0x06, false);                    // Set temperature coefficient
    this->_write(0xC2, false);                    // Default VOP (3.06 + 66 * 0.06 = 7V)
    this->_write(0x20, false);                    // Standard Commands mode, powered down
    this->_write(0x09, false);                    // LCD in normal mode
    this->_write(0x80, false);                    // Clear LCD RAM
    this->_write(LCD_CONTRAST, false);            // Set LCD constrast
    for(uint16_t i = 0; i < 504; i++) {
        this->_write(0x00, true);
    }
    this->_write(0x08, false);                    // ???
    this->_write(0x0C, false);                    // ???

    // Updates data members
    this->_initialized = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::clearBuffer(void)
{
    // Checks for errors - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    // Updates data members
    this->_posX = 0;
    this->_posY = 0;

    // Moves to position (0,0)
    this->_write(0x80, false);
    this->_write(0x40, false);

    /* Clear everything (504 bytes = 84cols * 48 rows / 8 bits) */
    for(uint16_t i = 0; i < 504; i++) {
        this->_data[i] = 0x00;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::renderBuffer(void)
{
    // Checks for errors - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    // Moves to position (0,0)
    this->_write(0x80, false);
    this->_write(0x40, false);

    /* Clear everything (504 bytes = 84cols * 48 rows / 8 bits) */
    for(uint16_t i = 0; i < 504; i++) {
        this->_write(this->_data[i], true);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawPixel(cuint8_t posX_p, cuint8_t posY_p, cbool_t turnOn_p)
{
    // Checks for errors - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    // Decodes pixel position
    uint8_t auxByte = this->_data[(posY_p / 8) * 84 + posX_p];

    if(turnOn_p) {
        setBit(auxByte, (posY_p % 8));
    } else {
        clrBit(auxByte, (posY_p % 8));
    }
    this->_data[(posY_p / 8) * 84 + posX_p] = auxByte;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

Error Nokia5110::getLastError()
{
    // Returns value
    return this->_lastError;
}

void Nokia5110::_write(uint8_t data_p, bool_t isData_p)
{
    clrBit(*(this->_controlPort), this->_chipSelect);
    if(isData_p) {
        setBit(*(this->_controlPort), this->_dc);
    } else {
        clrBit(*(this->_controlPort), this->_dc);
    }

    // Sends data bits
    for(uint8_t i = 0; i < 8; i++) {
        if((data_p >> (7 - i)) & 0x01) {
            setBit(*(this->_controlPort), this->_dataIn);
        } else {
            clrBit(*(this->_controlPort), this->_dataIn);
        }
        setBit(*(this->_controlPort), this->_clock);
        clrBit(*(this->_controlPort), this->_clock);
    }

    setBit(*(this->_controlPort), this->_chipSelect);
}

bool_t Nokia5110::drawLineVertical(cuint8_t posX_p, cuint8_t posY_p, cuint8_t length_p, cbool_t turnOn_p)
{
    // Checks for errors - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    for(uint8_t i = 0; i < length_p; i++) {
        this->drawPixel(posX_p, (posY_p + i), turnOn_p);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}
bool_t Nokia5110::drawLineHorizontal(cuint8_t posX_p, cuint8_t posY_p, cuint8_t length_p, cbool_t turnOn_p)
{
    // Checks for errors - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    for(uint8_t i = 0; i < length_p; i++) {
        this->drawPixel((posX_p + i), posY_p, turnOn_p);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawLine(uint8_t posX1_p, uint8_t posY1_p, uint8_t posX2_p, uint8_t posY2_p, cbool_t turnOn_p)
{
    int8_t dx = abs(posX2_p - posX1_p);
    int8_t dy = abs(posY2_p - posY1_p);
    int8_t sx = (posX1_p < posX2_p) ? 1 : -1;
    int8_t sy = (posY1_p < posY2_p) ? 1 : -1;
    int8_t err = dx - dy;

    while(1) {
        this->drawPixel(posX1_p, posY1_p, turnOn_p);

        if((posX1_p == posX2_p) && (posY1_p == posY2_p)) {
            break;
        }

        int e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            posX1_p += sx;
        }
        if(e2 < dx) {
            err += dx;
            posY1_p += sy;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;

#ifdef SDAASDAS

    uint8_t length, i, y, yAlt, xTmp, yTmp;
    int16_t m;
    //
    // vertical line
    //
    if(posX1_p == posX2_p) {
        // x1|y1 must be the upper point
        if(posY1_p > posY2_p) {
            yTmp = posY1_p;
            posY1_p = posY2_p;
            posY2_p = yTmp;
        }
        this->drawLineVertical(posX1_p, posY1_p, posY2_p - posY1_p, turnOn_p);

        //
        // horizontal line
        //
    } else if(posY1_p == posY2_p) {
        // x1|y1 must be the left point
        if(posX1_p > posX2_p) {
            xTmp = posX1_p;
            posX1_p = posX2_p;
            posX2_p = xTmp;
        }
        this->drawLineHorizontal(posX1_p, posY1_p, posX2_p - posX1_p, turnOn_p);

        //
        // angled line :)
        //
    } else {
        // angle >= 45
        if((posY2_p - posY1_p) >= (posX2_p - posX1_p) || (posY1_p - posY2_p) >= (posX2_p - posX1_p)) {
            // x1 must be smaller than x2
            if(posX1_p > posX2_p) {
                xTmp = posX1_p;
                yTmp = posY1_p;
                posX1_p = posX2_p;
                posY1_p = posY2_p;
                posX2_p = xTmp;
                posY2_p = yTmp;
            }

            length = posX2_p - posX1_p;        // not really the length :)
            m = ((posY2_p - posY1_p) * 200) / length;
            yAlt = posY1_p;

            for(i = 0; i <= length; i++) {
                y = ((m * i) / 200) + posY1_p;

                if((m * i) % 200 >= 100) {
                    y++;
                } else if((m * i) % 200 <= -100) {
                    y--;
                }

                this->drawLine(posX1_p + i, yAlt, posX1_p + i, y, turnOn_p);

                if(length <= (posY2_p - posY1_p) && posY1_p < posY2_p) {
                    yAlt = y + 1;
                } else if(length <= (posY1_p - posY2_p) && posY1_p > posY2_p) {
                    yAlt = y - 1;
                } else {
                    yAlt = y;
                }
            }

            // angle < 45
        } else {
            // y1 must be smaller than y2
            if(posY1_p > posY2_p) {
                xTmp = posX1_p;
                yTmp = posY1_p;
                posX1_p = posX2_p;
                posY1_p = posY2_p;
                posX2_p = xTmp;
                posY2_p = yTmp;
            }

            length = posY2_p - posY1_p;
            m = ((posX2_p - posX1_p) * 200) / length;
            yAlt = posX1_p;

            for(i = 0; i <= length; i++) {
                y = ((m * i) / 200) + posX1_p;

                if((m * i) % 200 >= 100) {
                    y++;
                } else if((m * i) % 200 <= -100) {
                    y--;
                }

                this->drawLine(yAlt, posY1_p + i, y, posY1_p + i, turnOn_p);
                if(length <= (posX2_p - posX1_p) && posX1_p < posX2_p) {
                    yAlt = y + 1;
                } else if(length <= (posX1_p - posX2_p) && posX1_p > posX2_p) {
                    yAlt = y - 1;
                } else {
                    yAlt = y;
                }
            }
        }
    }
#endif
}

bool_t Nokia5110::drawRectangle(uint8_t posX_p, uint8_t posY_p, uint8_t width_p, uint8_t height_p, cbool_t turnOn_p)
{
    // Desenha as quatro linhas do retângulo usando a função drawLine
    this->drawLine(posX_p, posY_p, posX_p + width_p, posY_p, turnOn_p);                        // Linha superior
    this->drawLine(posX_p, posY_p, posX_p, posY_p + height_p, turnOn_p);                       // Linha esquerda
    this->drawLine(posX_p + width_p, posY_p, posX_p + width_p, posY_p + height_p, turnOn_p);   // Linha direita
    this->drawLine(posX_p, posY_p + height_p, posX_p + width_p, posY_p + height_p, turnOn_p);  // Linha inferior

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawAndFillRectangle(uint8_t posX_p, uint8_t posY_p, uint8_t width_p, uint8_t height_p,
        cbool_t turnOn_p)
{
    // Desenha as linhas do retângulo e preenche o interior usando a função drawLine
    for(uint8_t i = posY_p; i < posY_p + height_p; i++) {
        this->drawLine(posX_p, i, posX_p + width_p, i, turnOn_p);  // Desenha a linha e liga o preenchimento
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawCircle(uint8_t centerX_p, uint8_t centerY_p, uint8_t radius_p, cbool_t turnOn_p)
{
    uint8_t x = radius_p;
    uint8_t y = 0;
    uint8_t decision = 1 - x;

    while(y <= x) {
        this->drawPixel(centerX_p + x, centerY_p + y, turnOn_p);   // Octante 1
        this->drawPixel(centerX_p + y, centerY_p + x, turnOn_p);   // Octante 2
        this->drawPixel(centerX_p - y, centerY_p + x, turnOn_p);   // Octante 3
        this->drawPixel(centerX_p - x, centerY_p + y, turnOn_p);   // Octante 4
        this->drawPixel(centerX_p - x, centerY_p - y, turnOn_p);   // Octante 5
        this->drawPixel(centerX_p - y, centerY_p - x, turnOn_p);   // Octante 6
        this->drawPixel(centerX_p + y, centerY_p - x, turnOn_p);   // Octante 7
        this->drawPixel(centerX_p + x, centerY_p - y, turnOn_p);   // Octante 8

        y++;
        if(decision <= 0) {
            decision += 2 * y + 1;
        } else {
            x--;
            decision += 2 * (y - x) + 1;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawChar(char_t code_p, uint8_t scale_p)
{
    uint8_t x, y;

    for(x = 0; x < 5 * scale_p; x++) {
        for(y = 0; y < 7 * scale_p; y++) {
            if(pgm_read_byte(&CHARSET[code_p - 32][x / scale_p]) & (1 << y / scale_p)) {
                this->drawPixel(this->_posX + x, this->_posY + y, true);
            } else {
                this->drawPixel(this->_posX + x, this->_posY + y, false);
            }
        }
    }

    this->_posX += 5 * scale_p + 1;
    if(this->_posX >= 84) {
        this->_posX = 0;
        this->_posY += 7 * scale_p + 1;
    }
    if(this->_posY >= 48) {
        this->_posX = 0;
        this->_posY = 0;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::setCursorPosition(uint8_t posX_p, uint8_t posY_p)
{
    if(posX_p > 83 || posY_p > 47) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        return false;
    }
    this->_posX = posX_p;
    this->_posY = posY_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Nokia5110::drawString(cchar_t *string_p, uint8_t scale_p, uint8_t posX_p, uint8_t posY_p)
{

    this->setCursorPosition(posX_p, posY_p);

    uint8_t lenght = strlen(string_p);
    for(uint8_t i = 0; i < lenght; i++) {
        this->drawChar(string_p[i], scale_p);
    }
    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}


uint8_t Nokia5110::getCursorXPos()
{
    return this->_posX;
}
uint8_t Nokia5110::getCursorYPos()
{
    return this->_posY;
}
