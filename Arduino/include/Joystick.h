#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "Arduino.h"
#include "Toggle.h"

class Joystick{
    public:
        Joystick();
        void begin(uint8_t x_pos_pin, uint8_t x_neg_pin, uint8_t y_pos_pin, uint8_t y_neg_pin, boolean normally_high=true, uint8_t debounce=1);
        int8_t x();
        int8_t y();
        void update();
    private:
        Toggle x_pos = Toggle();
        Toggle x_neg = Toggle();
        Toggle y_pos = Toggle();
        Toggle y_neg = Toggle();
};

#endif