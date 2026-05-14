#include "Toggle.h"

Toggle::Toggle(){

}

void Toggle::begin(uint8_t pin, boolean normally_high, uint8_t debounce){
    this->pin = pin;
    this->debounce_duration = debounce;
    this->debounce_counter = debounce_duration / 2;
    this->normally_high = normally_high;
    pinMode(this->pin, INPUT_PULLUP);
}

void Toggle::update(){
    if(digitalRead(this->pin)){
        if(this->debounce_counter < this->debounce_duration){
            this->debounce_counter++;
        }
    }
    else{
        if(this->debounce_counter > 0){
            this->debounce_counter--;
        }
    }

    this->just_went_high = false;
    this->just_went_low = false;

    if(this->debounce_counter == this->debounce_duration){
        // HIGH debounce
        if(!this->state){
            this->just_went_high = true;
        }
        this->state = true;
    }

    if(this->debounce_counter == 0){
        // LOW debounce
        if(this->state){
            this->just_went_low = true;
        }
        this->state = false;
    }

    if(this->just_pressed()){
        this->start_of_hold = millis();
    }
}

boolean Toggle::is_pressed(){
    return !this->is_released();
}

boolean Toggle::is_released(){
    return this->state == this->normally_high;
}

boolean Toggle::just_pressed(){
    if(this->normally_high){
        return this->just_went_low;
    }
    else{
        return this->just_went_high;
    }
}

boolean Toggle::just_released(){
    if(this->normally_high){
        return this->just_went_high;
    }
    else{
        return this->just_went_low;
    }
}

int64_t Toggle::hold_duration_ms(){
    if(this->is_released()){
        return -1;
    }

    return millis() - this->start_of_hold;
}