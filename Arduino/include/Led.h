#ifndef LED_H
#define LED_H
#include "Arduino.h"

class Led{
    public:
        Led();
        void begin(uint8_t pin);
        void set(boolean state);
        void on();
        void off();
        void toggle();
        boolean is_on();
    private:
        uint8_t pin;
        boolean state;
};

#endif