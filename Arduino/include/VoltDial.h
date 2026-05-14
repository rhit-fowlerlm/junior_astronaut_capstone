#ifndef VOLT_DIAL_H
#define VOLT_DIAL_H
#include "Arduino.h"
#include "SmoothRandom.h"

class VoltDial{
    public:
        VoltDial();
        void begin(uint8_t pin);
        void update();
        void set_max();
        void set_min();
        void increase();
        void decrease();
        void setpoint(float V);
        void start_oscillation();
        void set_noise(bool on);
        void set_sin_wave(bool on);
    private:
        void set(float V);

        uint8_t pin;
        float V_0;
        const float V_max = 5;
        const float V_offset = 1;

        const float change_rate_micros = 1e-5;

        unsigned long t_oscillation_start_millis = 0;
        unsigned long t_prev_micros = 0;
        

        const uint32_t ocillation_duration_millis = 3000;
        const float oscillation_decay = 0.5;
        const float oscillation_n_cycles = 6;

        bool is_oscillating;
        bool is_noise;
        bool is_sin_wave; 

        SmoothRandom smooth_random = SmoothRandom();
        const float smooth_random_speed = 1e-4; // rad/ms
        const float sin_wave_speed = 6e-3; // rad/ms
};


#endif