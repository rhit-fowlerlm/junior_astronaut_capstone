#ifndef POWER_SUBSYSTEM_H
#define POWER_SUBSYSTEM_H
#include "Arduino.h"
#include "Switch.h"
#include "VoltDial.h"
#include "LedButton.h"

class PowerSubsystem{
    public:
        PowerSubsystem();
        void begin(uint8_t volt_dial_pin, uint8_t ripple_switch_pin, uint8_t minmax_switch_pin, uint8_t random_switch_pin, uint8_t noise_switch_pin, uint8_t sin_wave_pin, uint8_t increase_V_button_pin, uint8_t increase_V_led_pin, uint8_t decrease_V_button_pin, uint8_t decrease_V_led_pin);
        void update();
    private:
        void update_components();
        VoltDial volt_dial = VoltDial();
        Switch s_ripple = Switch();
        Switch s_minmax = Switch();
        Switch s_random = Switch();
        Switch s_noise = Switch();
        Switch s_sin = Switch();
        LedButton b_increase = LedButton();
        LedButton b_decrease = LedButton();
};

#endif