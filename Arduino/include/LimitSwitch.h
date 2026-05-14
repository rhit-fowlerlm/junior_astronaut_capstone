#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H
#include "Arduino.h"
#include "Toggle.h"

class LimitSwitch{
    public:
        LimitSwitch();
        void begin(uint8_t pin, boolean normally_high=true, uint8_t debounce=1);
        boolean is_pressed();
        boolean is_released();
        boolean just_pressed();
        boolean just_released();
        void update();
    private:
        Toggle limit_switch = Toggle();
};

#endif