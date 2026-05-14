#ifndef LED_BUTTON_H
#define LED_BUTTON_H
#include "Arduino.h"
#include "Toggle.h"
#include "Led.h"

class LedButton{
    public:
        LedButton();
        void begin(uint8_t led_pin, uint8_t button_pin, boolean normally_high=true, uint8_t debounce=1);
        void led_set(boolean state);
        void led_on();
        void led_off();
        void led_toggle();
        boolean led_is_on();
        boolean button_is_pressed();
        boolean button_is_released();
        boolean button_just_pressed();
        boolean button_just_released();
        int64_t button_hold_duration_ms();
        void update();
    private:
        Toggle button = Toggle();
        Led led = Led();
};


#endif