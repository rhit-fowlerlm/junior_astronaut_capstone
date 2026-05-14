#ifndef LAUNCH_SUBSYSTEM_H
#define LAUNCH_SUBSYSTEM_H
#include "Arduino.h"
#include "LedButton.h"
#include "SevenSegmentDisplay.h"
#include "Wire.h"

class LaunchSubsystem{
    public:
        LaunchSubsystem();
        void begin(uint8_t display_address, uint8_t button_led_pin, uint8_t button_pin);
        void update();
    private:
        SevenSegmentDisplay display = SevenSegmentDisplay();
        LedButton launch_button = LedButton();

        const uint32_t t0_time_ms = 39000;
        const uint32_t flash_freq_half = 1000;
        const uint32_t total_time_ms = 60000;
        const uint32_t launch_show_time_ms = 1000;

        bool is_launching = false;
        unsigned long launch_start_time_ms = 0;

        void start_launch();
        void update_launch();
        void abort_launch();
        void update_components();
};

#endif