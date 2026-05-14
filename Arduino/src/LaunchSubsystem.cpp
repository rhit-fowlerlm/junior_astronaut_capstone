#include "LaunchSubsystem.h"

LaunchSubsystem::LaunchSubsystem(){

}

void LaunchSubsystem::begin(uint8_t display_address, uint8_t button_led_pin, uint8_t button_pin){
    while(this->display.begin(&Wire, display_address)){
        Serial.print("Not found 7 segment at ");
        Serial.println(display_address, HEX);
        delay(1000);
    }
    this->launch_button.begin(button_led_pin, button_pin);
}

void LaunchSubsystem::update(){
   this->update_components();


    if(this->launch_button.button_just_pressed()){
        this->start_launch();
    }

    if(this->is_launching){
        this->update_launch();
        // if(this->launch_button.button_is_pressed()){
        //     this->update_launch();
        // }
        // else{
        //     this->abort_launch();
        // }
    }
}

void LaunchSubsystem::start_launch(){
    if(!this->is_launching){
        this->is_launching = true;
        this->launch_start_time_ms = millis();
        Serial.println("SFX LAUNCH_START");
    }
}

void LaunchSubsystem::update_launch(){
    uint32_t dt_ms = millis() - this->launch_start_time_ms;
    uint32_t t_minus_ms = 0;
    if(dt_ms < this->t0_time_ms){
        t_minus_ms = this->t0_time_ms - dt_ms;
    }

    if(t_minus_ms > 0){
        uint8_t t_minus_10s = (t_minus_ms / 10000) % 10;
        uint8_t t_minus_1s = (t_minus_ms / 1000) % 10;
        uint8_t t_minus_01s = (t_minus_ms / 100) % 10;

        char t_minus_10s_char = '0' + t_minus_10s;
        char t_minus_1s_char = '0' + t_minus_1s;
        char t_minus_01s_char = '0' + t_minus_01s;

        display.print(' ', 'T', '-', ' ', t_minus_10s_char, t_minus_1s_char, t_minus_01s_char, ' ', 0b00000100);
    }

    uint8_t flash = (dt_ms / flash_freq_half) % 2;

    this->launch_button.led_set(flash);

    if(dt_ms > this->total_time_ms){
        this->is_launching = false;
        display.print(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    }
    else if(t_minus_ms <= 0){
        if(dt_ms < this->t0_time_ms + this->launch_show_time_ms){
            display.print(' ', 'L', 'A', 'U', 'N', 'C', 'H', ' ');
        }
        else{
            if(flash){
                display.print('L', 'I', 'F', 'T', 'O', 'F', 'F', ' ');
            }
            else{
                display.print(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            }
        }
    }
    
}

void LaunchSubsystem::abort_launch(){
    this->is_launching = false;
    display.print(' ', 'A', 'B', 'O', 'R', 'T', ' ', ' ');
    Serial.println("SFX LAUNCH_ABORT");
}

void LaunchSubsystem::update_components(){
    this->launch_button.update();
}