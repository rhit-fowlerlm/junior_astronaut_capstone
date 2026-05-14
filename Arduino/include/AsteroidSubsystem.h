#ifndef ASTEROID_SUBSYSTEM_H
#define ASTEROID_SUBSYSTEM_H
#include "Arduino.h"
#include "LedButton.h"

class AsteroidSubsystem{
    public:
        AsteroidSubsystem();
        void begin(uint8_t asteroid1_led, uint8_t asteroid1_but, uint8_t asteroid2_led, uint8_t asteroid2_but, uint8_t asteroid3_led, uint8_t asteroid3_but);
        void update();
    private:
        LedButton create_button = LedButton();
        LedButton destroy_button = LedButton();
        LedButton other_button = LedButton();

        const uint32_t super_destroy_hold_duration_ms = 1000;
        bool super_destroy_available = true;

        void update_components();
};

#endif