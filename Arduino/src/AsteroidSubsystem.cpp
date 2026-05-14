#include "AsteroidSubsystem.h"

AsteroidSubsystem::AsteroidSubsystem(){

}

void AsteroidSubsystem::begin(uint8_t create_led, uint8_t create_but, uint8_t destroy_led, uint8_t destroy_but, uint8_t other_led, uint8_t other_but){
    this->create_button.begin(create_led, create_but);
    this->destroy_button.begin(destroy_led, destroy_but);
    this->other_button.begin(other_led, other_but);
}

void AsteroidSubsystem::update(){
    this->update_components();

    if(this->create_button.button_just_pressed()){
        Serial.println("ASTEROID CREATE");
    }

    if(this->destroy_button.button_just_pressed()){
        Serial.println("ASTEROID SINGLE_DESTROY");
    }

    if(this->destroy_button.button_is_released()){
        this->super_destroy_available = true;
    }

    if(this->destroy_button.button_hold_duration_ms() > this->super_destroy_hold_duration_ms && this->super_destroy_available){
        Serial.println("ASTEROID SUPER_DESTROY");
        this->super_destroy_available = false;
    }

    this->create_button.led_set(this->create_button.button_is_pressed());
    this->destroy_button.led_set(this->destroy_button.button_is_pressed());
    this->other_button.led_set(this->create_button.button_is_pressed() || this->destroy_button.button_is_pressed() || this->other_button.button_is_pressed());
}

void AsteroidSubsystem::update_components(){
    this->create_button.update();
    this->destroy_button.update();
    this->other_button.update();
}