#ifndef DATA_SUBSYSTEM_H
#define DATA_SUBSYSTEM_H
#include "Arduino.h"
#include "LedButton.h"
#include "SevenSegmentDisplay.h"
#include "Wire.h"

class DataSubsystem{
    public:
        DataSubsystem();
        void begin(uint8_t display_address, uint8_t down_led_pin, uint8_t down_button_pin, uint8_t up_led_pin, uint8_t up_button_pin);
        void update();
    private:
        LedButton load_down = LedButton();
        LedButton load_up = LedButton();
        SevenSegmentDisplay display = SevenSegmentDisplay();

        int8_t loading_bar_max = 0;
        int8_t loading_bar_min = 0;

        const String sfx_data_down_cmd = "SFX DATA_1";
        const String sfx_data_up_cmd = "SFX DATA_2";
        const String sfx_data_send_cmd = "SFX DATA_SEND";

        const uint32_t blink_half_freq = 500;

        unsigned long swipe_start_time_ms = 0;
        bool swiping = false;
        const uint32_t swipe_speed = 1000 / 16;

        void update_components();
        void update_display();
        void update_lights();

};


#endif