#include "Led.h"

Led::Led(){
    
}

void Led::begin(uint8_t pin){
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
    this->off();
}

void Led::set(boolean state){
    this->state = state;
    digitalWrite(this->pin, this->state);
}

void Led::on(){
    this->set(true);
}

void Led::off(){
    this->set(false);
}

void Led::toggle(){
    this->set(!this->state);
}

boolean Led::is_on(){
    return this->state;
}