#ifndef TOGGLE_H
#define TOGGLE_H
#include "Arduino.h"

class Toggle{
    public:
        Toggle();
        void begin(uint8_t pin, boolean normally_high=true, uint8_t debounce=1);
        boolean is_pressed();
        boolean is_released();
        boolean just_pressed();
        boolean just_released();
        int64_t hold_duration_ms();
        void update();
    private:
        uint8_t pin;
        uint8_t debounce_duration;
        uint8_t debounce_counter;

        boolean normally_high;
        boolean state;
        boolean just_went_low;
        boolean just_went_high;
        uint64_t start_of_hold;
};

#endif