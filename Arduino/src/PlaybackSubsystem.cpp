#include "PlaybackSubsystem.h"

PlaybackSubsystem::PlaybackSubsystem(){

}

void PlaybackSubsystem::begin(uint8_t b1_led, uint8_t b1_but, uint8_t b2_led, uint8_t b2_but, uint8_t b3_led, uint8_t b3_but){
    b1.begin(b1_led, b1_but);
    b2.begin(b2_led, b2_but);
    b3.begin(b3_led, b3_but);
}

void PlaybackSubsystem::update(){
    this->update_components();

    if(this->b1.button_just_pressed()){
        Serial.println("SFX TONE_LOW");
        this->write(1);
    }

    if(this->b2.button_just_pressed()){
        Serial.println("SFX TONE_MIDDLE");
        this->write(2);
    }

    if(this->b3.button_just_pressed()){
        Serial.println("SFX TONE_HIGH");
        this->write(3);
    }

    if(millis() - this->last_press_ms > this->time_until_playback_start_ms && this->playback_idx < 0){
        this->playback_idx = 0;
        this->playback_start_ms = millis();
    }

    if(this->playback_idx < 0){
        if(this->write_idx > 0){
            this->set_led(this->history[this->write_idx-1]);
        }
        else{
            this->set_led(0);
        }
    }
    else{
        this->set_led(this->history[this->playback_idx]);

        if(millis() - this->playback_start_ms > this->playback_frame_length){
            this->playback_idx++;
            this->playback_start_ms = millis();
            if(this->playback_idx < 255){
                switch(this->history[this->playback_idx]){
                    case 1:
                        Serial.println("SFX TONE_LOW");
                        break;
                    case 2:
                        Serial.println("SFX TONE_MIDDLE");
                        break;
                    case 3:
                        Serial.println("SFX TONE_HIGH");
                        break;
                }
            }
        }

        if(this->playback_idx == this->history_size || this->history[this->playback_idx] == 0){
            this->reset();
        }
    }
}

void PlaybackSubsystem::write(uint8_t val){
    if(this->write_idx < this->history_size && this->playback_idx < 0){
        this->last_press_ms = millis();
        this->history[this->write_idx] = val;
        this->write_idx++;
    }
}

void PlaybackSubsystem::reset(){
    for(uint8_t i = 0; i < this->history_size; i++){
        this->history[i] = 0;
    }
    this->write_idx = 0;
    this->playback_idx = -1;
}

void PlaybackSubsystem::set_led(uint8_t val){
    this->b1.led_set(val == 1);
    this->b2.led_set(val == 2);
    this->b3.led_set(val == 3);
}

void PlaybackSubsystem::update_components(){
    b1.update();
    b2.update();
    b3.update();
}