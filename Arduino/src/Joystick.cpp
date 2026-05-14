#include "Joystick.h"

Joystick::Joystick(){

}

void Joystick::begin(uint8_t x_pos_pin, uint8_t x_neg_pin, uint8_t y_pos_pin, uint8_t y_neg_pin, boolean normally_high, uint8_t debounce){
    this->x_pos.begin(x_pos_pin, normally_high=normally_high, debounce=debounce);
    this->x_neg.begin(x_neg_pin, normally_high=normally_high, debounce=debounce);
    this->y_pos.begin(y_pos_pin, normally_high=normally_high, debounce=debounce);
    this->y_neg.begin(y_neg_pin, normally_high=normally_high, debounce=debounce);
}

int8_t Joystick::x(){
    return this->x_pos.is_pressed() - this->x_neg.is_pressed();
}

int8_t Joystick::y(){
    return this->y_pos.is_pressed() - this->y_neg.is_pressed();
}

void Joystick::update(){
    this->x_pos.update();
    this->x_neg.update();
    this->y_pos.update();
    this->y_neg.update();
}