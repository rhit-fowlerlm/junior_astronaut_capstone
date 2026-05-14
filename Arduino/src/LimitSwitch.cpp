#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(){

}

void LimitSwitch::begin(uint8_t pin, boolean normally_high, uint8_t debounce){
    this->limit_switch.begin(pin, normally_high=normally_high, debounce=debounce);
}

boolean LimitSwitch::is_pressed(){
    return this->limit_switch.is_pressed();
}

boolean LimitSwitch::is_released(){
    return this->limit_switch.is_released();
}

boolean LimitSwitch::just_pressed(){
    return this->limit_switch.just_pressed();
}

boolean LimitSwitch::just_released(){
    return this->limit_switch.just_released();
}

void LimitSwitch::update(){
    this->limit_switch.update();
}