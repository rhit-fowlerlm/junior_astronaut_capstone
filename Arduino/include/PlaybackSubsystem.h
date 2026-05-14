#ifndef PLAYBACK_SUBSYSTEM_H
#define PLAYBACK_SUBSYSTEM_H
#include "Arduino.h"
#include "LedButton.h"

class PlaybackSubsystem{
    public:
        PlaybackSubsystem();
        void begin(uint8_t b1_led, uint8_t b1_but, uint8_t b2_led, uint8_t b2_but, uint8_t b3_led, uint8_t b3_but);
        void update();
    private:
        LedButton b1 = LedButton();
        LedButton b2 = LedButton();
        LedButton b3 = LedButton();

        void update_components();
        void write(uint8_t val);
        void reset();
        void set_led(uint8_t val);

        const uint32_t time_until_playback_start_ms = 3000;
        const uint32_t playback_frame_length = 1000;

        unsigned long last_press_ms = 0;
        unsigned long playback_start_ms = 0;

        
        uint8_t history[255];
        int32_t playback_idx = -1;
        int32_t write_idx = 0;

        const int32_t history_size = sizeof(history) / sizeof(history[0]);
};

#endif