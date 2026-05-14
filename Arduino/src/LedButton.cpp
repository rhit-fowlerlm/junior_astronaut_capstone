#include "LedButton.h"

LedButton::LedButton(){

}

void LedButton::begin(uint8_t led_pin, uint8_t button_pin, boolean normally_high, uint8_t debounce){
    this->led.begin(led_pin);
    this->button.begin(button_pin, normally_high=normally_high, debounce=debounce);
}

void LedButton::led_set(boolean state){
    this->led.set(state);
}

void LedButton::led_on(){
    this->led.on();
}

void LedButton::led_off(){
    this->led.off();
}

void LedButton::led_toggle(){
    this->led.toggle();
}

boolean LedButton::led_is_on(){
    return this->led.is_on();
}

boolean LedButton::button_is_pressed(){
    return this->button.is_pressed();
}

boolean LedButton::button_is_released(){
    return this->button.is_released();
}

boolean LedButton::button_just_pressed(){
    return this->button.just_pressed();
}

boolean LedButton::button_just_released(){
    return this->button_just_released();
}

int64_t LedButton::button_hold_duration_ms(){
    return this->button.hold_duration_ms();
}

void LedButton::update(){
    return this->button.update();
}