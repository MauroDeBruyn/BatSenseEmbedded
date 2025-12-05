#pragma once

#include "Arduino.h"
#include <SPI.h>
#include "SD.h"
#include "FS.h"
#include "logging.h"
#include "string.h"

#define LED_ON 0
#define LED_OFF 1

#define SD_CS		    4
#define MISO_PIN		12
#define MOSI_PIN		13
#define SCLK_PIN		14
#define CS_SENSE	    5
#define SPI_BLOCKOUT_PERIOD	20000UL


class LED{
    bool state{0};
    u8 pin;
public:
    LED(u8 pin) : pin{pin}{pinMode(pin, OUTPUT);}
    ~LED(){}
    inline void toggle(){digitalWrite(pin,!state); state = !state;}
};

class SDinterface{
    friend void SDGiveControl();
    static volatile unsigned long _spiBlockoutTime;
    static bool _weTookBus;
    char buffer[1024]{""};
    logger* logs;                  

public:
    SDinterface();
    ~SDinterface(){}
    void takeBusControl();
    void relinquishBusControl();
    bool canWeTakeBus();
    bool read_file(const char* filename); 
    String sdFiles_HTML_Format();
};