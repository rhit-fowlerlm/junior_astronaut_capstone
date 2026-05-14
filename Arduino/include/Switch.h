#ifndef SWITCH_H
#define SWITCH_H
#include "Arduino.h"
#include "Toggle.h"

class Switch{
    public:
        Switch();
        void begin(uint8_t pin, boolean normally_high=true, uint8_t debounce=1);
        boolean is_on();
        boolean is_off();
        boolean just_flipped_on();
        boolean just_flipped_off();
        void update();
    private:
        Toggle s = Toggle();
};

#endif