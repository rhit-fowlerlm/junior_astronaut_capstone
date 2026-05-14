#include "VoltDial.h"

VoltDial::VoltDial(){

}

void VoltDial::begin(uint8_t pin){
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
    this->set(0);
}

void VoltDial::increase(){
    unsigned long dt = micros() - this->t_prev_micros;
    this->setpoint(this->V_0 + this->change_rate_micros*dt);
}

void VoltDial::decrease(){
    unsigned long dt = micros() - this->t_prev_micros;
    this->setpoint(this->V_0 - this->change_rate_micros*dt);
}

void VoltDial::set_max(){
    this->setpoint(this->V_max);
}

void VoltDial::set_min(){
    this->setpoint(0);
}

void VoltDial::setpoint(float V){
    this->V_0 = V;
    if(this->V_0 > this->V_max - this->V_offset){
        this->V_0 = this->V_max - this->V_offset;
    }
    if(this->V_0 < this->V_offset){
        this->V_0 = this->V_offset;
    }
}

void VoltDial::start_oscillation(){
    if(!this->is_oscillating){
        this->is_oscillating = true;
        this->t_oscillation_start_millis = millis();
    }
}

void VoltDial::set_noise(bool on){
    this->is_noise = on;
}

void VoltDial::set_sin_wave(bool on){
    this->is_sin_wave = on;
}

void VoltDial::set(float V){
    if(V < 0){
        V = 0;
    }
    if(V > 5){
        V = 5;
    }
    const int32_t pwm_max = 255;

    int32_t pwm = pwm_max * (V/this->V_max);

    if(pwm < 0){
        pwm = 0;
    }
    if(pwm > pwm_max){
        pwm = pwm_max;
    }

    analogWrite(this->pin, pwm);
}


void VoltDial::update(){
    this->t_prev_micros = micros();

    float oscillation = 0;  // [-1, 1]
    float noise = 0;        // [-1, 1]
    float sin_wave = 0;     // [-1, 1]

    if(this->is_oscillating){
        unsigned long dt = millis() - t_oscillation_start_millis;
        if(dt > this->ocillation_duration_millis){
            this->is_oscillating = false;
        }
        else{
            float t = (dt * 1.0f) / t_oscillation_start_millis;
            oscillation = expf(-this->oscillation_decay * t) * sinf(t * this->oscillation_n_cycles * (2*PI));
        }
    }

    if(this->is_noise){
        noise = this->smooth_random.get_smooth_random(this->smooth_random_speed * millis());
    }

    if(this->is_sin_wave){
        sin_wave = sinf(this->sin_wave_speed * millis());
    }

    float transients = (oscillation + noise + sin_wave) / 3;

    if(this->V_0 > this->V_max - this->V_offset){
        this->V_0 = this->V_max - this->V_offset;
    }
    if(this->V_0 < this->V_offset){
        this->V_0 = this->V_offset;
    }

    float V = this->V_0 + transients * this->V_offset;

    this->set(V);
}