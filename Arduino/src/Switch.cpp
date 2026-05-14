#include "Switch.h"

Switch::Switch(){

}

void Switch::begin(uint8_t pin, boolean normally_high, uint8_t debounce){
    this->s.begin(pin, normally_high=normally_high, debounce=debounce);
}

boolean Switch::is_on(){
    return this->s.is_pressed();
}

boolean Switch::is_off(){
    return this->s.is_released();
}

boolean Switch::just_flipped_on(){
    return this->s.just_pressed();
}

boolean Switch::just_flipped_off(){
    return this->s.just_released();
}

void Switch::update(){
    this->s.update();
}