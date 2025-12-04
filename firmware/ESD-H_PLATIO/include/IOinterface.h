#pragma once

#define LED_ON 0
#define LED_OFF 1

class LED{
    bool state{0};
    u8 pin;
public:
    LED(u8 pin) : pin{pin}{pinMode(pin, OUTPUT);}
    ~LED(){}
    inline void toggle(){digitalWrite(pin,!state); state = !state;}
};