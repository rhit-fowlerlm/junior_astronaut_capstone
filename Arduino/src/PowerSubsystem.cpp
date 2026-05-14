#include "PowerSubsystem.h"

PowerSubsystem::PowerSubsystem(){

}

void PowerSubsystem::begin(uint8_t volt_dial_pin, uint8_t ripple_switch_pin, uint8_t minmax_switch_pin, uint8_t random_switch_pin, uint8_t noise_switch_pin, uint8_t sin_wave_pin, uint8_t increase_V_button_pin, uint8_t increase_V_led_pin, uint8_t decrease_V_button_pin, uint8_t decrease_V_led_pin){
    this->volt_dial.begin(volt_dial_pin);
    this->s_ripple.begin(ripple_switch_pin, false);
    this->s_minmax.begin(minmax_switch_pin, false);
    this->s_random.begin(random_switch_pin, false);
    this->s_noise.begin(noise_switch_pin, false);
    this->s_sin.begin(sin_wave_pin, false);
    this->b_increase.begin(increase_V_led_pin, increase_V_button_pin);
    this->b_decrease.begin(decrease_V_led_pin, decrease_V_button_pin);
}

void PowerSubsystem::update(){
    this->update_components();

    // RIPPLE
    if(this->s_ripple.just_flipped_on() || this->s_ripple.just_flipped_off()){
        this->volt_dial.start_oscillation();
    }

    // MINMAX
    if(this->s_minmax.just_flipped_on()){
        this->volt_dial.set_max();
    }

    if(this->s_minmax.just_flipped_off()){
        this->volt_dial.set_min();
    }

    // RANDOM
    if(this->s_random.just_flipped_on() || this->s_random.just_flipped_off()){
        this->volt_dial.setpoint(random(500) * (3.0f/500) + 1);
    }

    // NOISE
    this->volt_dial.set_noise(this->s_noise.is_on());

    // SINUSOIDAL
    this->volt_dial.set_sin_wave(this->s_sin.is_on());

    // DECREASE
    if(this->b_decrease.button_is_pressed()){
        this->volt_dial.decrease();

        this->b_decrease.led_on();
        this->b_increase.led_off();
    }

    // INCREASE
    if(this->b_increase.button_is_pressed()){
        this->volt_dial.increase();

        this->b_increase.led_on();
        this->b_decrease.led_off();
    }
}

void PowerSubsystem::update_components(){
    this->volt_dial.update();
    this->s_ripple.update();
    this->s_minmax.update();
    this->s_random.update();
    this->s_noise.update();
    this->s_sin.update();
    this->b_increase.update();
    this->b_decrease.update();
}