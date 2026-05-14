#include "DataSubsystem.h"

DataSubsystem::DataSubsystem(){

}

void DataSubsystem::begin(uint8_t display_address, uint8_t down_led_pin, uint8_t down_button_pin, uint8_t up_led_pin, uint8_t up_button_pin){
    this->display.begin(&Wire, display_address);
    this->load_down.begin(down_led_pin, down_button_pin);
    this->load_up.begin(up_led_pin, up_button_pin);
}

void DataSubsystem::update(){
    this->update_components();
    this->update_lights();
}

void DataSubsystem::update_components(){
    this->load_down.update();
    this->load_up.update();
    this->update_display();
}

void DataSubsystem::update_lights(){
    if(this->swiping){
        return;
    }

    if(this->load_down.button_just_pressed()){
        if(this->loading_bar_max > 0 && this->loading_bar_max < 16){
            this->loading_bar_max--;
            Serial.println(this->sfx_data_down_cmd);
        }
    }
    if(this->load_up.button_just_pressed()){
        if(this->loading_bar_max < 16){
            this->loading_bar_max++;
            Serial.println(this->sfx_data_up_cmd);
        }
    }

    if(loading_bar_max == 16){
        bool blink = (millis() / this->blink_half_freq) % 2;
        load_down.led_set(blink);
        load_up.led_set(blink);
        if(load_down.button_is_pressed() && load_up.button_is_pressed()){
            this->swipe_start_time_ms = millis();
            this->swiping = true;
            Serial.println(this->sfx_data_send_cmd);
        }
    }
    else{
        load_down.led_off();
        load_up.led_off();
    }
}

void DataSubsystem::update_display(){
    if(this->swiping){
        uint32_t dt = millis() - this->swipe_start_time_ms;
        this->loading_bar_min = dt / this->swipe_speed;
        if(this->loading_bar_min == 17){
            this->swiping = false;
            this->loading_bar_max = 0;
        }
    }
    else{
        this->loading_bar_min = 0;
    }

    char c[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    const uint8_t steps_per_char = 2;

    if(this->loading_bar_max <= this->loading_bar_min){
        this->display.print(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
        return;
    }

    for(uint8_t i = 0; i < 8; i++){
        int8_t char_load_max = this->loading_bar_max - i*steps_per_char;
        int8_t char_load_min = this->loading_bar_min - i*steps_per_char;
        if(char_load_max <= 0){
            c[i] = ' ';
        }
        else if(char_load_max == 1){
            c[i] = '(';
        }
        else{
            if(char_load_min > 1){
                c[i] = ' ';
            }
            else if(char_load_min == 1){
                c[i] = ')';
            }
            else{
                c[i] = '"';
            }
        }
    }

    this->display.print(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
}