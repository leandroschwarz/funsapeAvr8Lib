
#ifndef __NOKIA_5110_HPP
#define __NOKIA_5110_HPP

#include "funsape/globalDefines.hpp"

#define LCD_CONTRAST 0x40


class Nokia5110
{
public:
    Nokia5110(void);

    bool_t setPort(
            ioRegAddress_t controlPort_p,
            ioPinIndex_t chipSelectPinIndex_p,
            ioPinIndex_t clockPinIndex_p,
            ioPinIndex_t dataPinIndex_p,
            ioPinIndex_t dataCommandPinIndex_p,
            ioPinIndex_t resetPinIndex_p        = 0xFF
    );
    bool_t init(void);
    bool_t clearBuffer(void);
    bool_t renderBuffer(void);
    bool_t drawPixel(cuint8_t posX_p, cuint8_t posY_p, cbool_t turnOn_p = true);
    bool_t drawLine(uint8_t posX1_p, uint8_t posY1_p, uint8_t posX2_p, uint8_t posY2_p, cbool_t turnOn_p = true);

    bool_t drawLineVertical(cuint8_t posX_p, cuint8_t posY_p, cuint8_t length_p, cbool_t turnOn_p = true);
    bool_t drawLineHorizontal(cuint8_t posX_p, cuint8_t posY_p, cuint8_t length_p, cbool_t turnOn_p = true);
    bool_t drawCircle(uint8_t centerX_p, uint8_t centerY_p, uint8_t radius_p, cbool_t turnOn_p);
    bool_t drawAndFillRectangle(uint8_t posX_p, uint8_t posY_p, uint8_t width_p, uint8_t height_p, cbool_t turnOn_p);
    bool_t drawRectangle(uint8_t posX_p, uint8_t posY_p, uint8_t width_p, uint8_t height_p, cbool_t turnOn_p);
    bool_t setCursorPosition(uint8_t posX_p, uint8_t posY_p);
    bool_t drawChar(char_t code_p, uint8_t scale_p);
    bool_t drawString(cchar_t *string_p, uint8_t scale_p, uint8_t posX_p, uint8_t posY_p);
    uint8_t getCursorXPos();
    uint8_t getCursorYPos();




    Error getLastError(void);

private:
    void _write(uint8_t data_p, bool_t isData_p);

    Error           _lastError;
    bool_t          _initialized        : 1;
    bool_t          _portsSet           : 1;
    ioRegAddress_t  _controlDdr;
    ioRegAddress_t  _controlPort;
    ioPinIndex_t    _dataIn;
    ioPinIndex_t    _chipSelect;
    ioPinIndex_t    _clock;
    ioPinIndex_t    _dc;
    ioPinIndex_t    _reset;
    uint8_t         *_data;
    uint8_t         _posX;
    uint8_t         _posY;
};


#endif
