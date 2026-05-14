#include "ButtonMatrixSubsystem.h"

ButtonMatrixSubsystem::ButtonMatrixSubsystem(){

}

void ButtonMatrixSubsystem::set_all_leds(const uint16_t led_mask){
    this->matrix11.led_set(led_mask & this->MATRIX11);
    this->matrix12.led_set(led_mask & this->MATRIX12);
    this->matrix13.led_set(led_mask & this->MATRIX13);
    this->matrix14.led_set(led_mask & this->MATRIX14);

    this->matrix21.led_set(led_mask & this->MATRIX21);
    this->matrix22.led_set(led_mask & this->MATRIX22);
    this->matrix23.led_set(led_mask & this->MATRIX23);
    this->matrix24.led_set(led_mask & this->MATRIX24);

    this->matrix31.led_set(led_mask & this->MATRIX31);
    this->matrix32.led_set(led_mask & this->MATRIX32);
    this->matrix33.led_set(led_mask & this->MATRIX33);
    this->matrix34.led_set(led_mask & this->MATRIX34);

    this->lights = led_mask;
}

void ButtonMatrixSubsystem::begin(const uint8_t matrix11_led, const uint8_t matrix11_but, const uint8_t matrix12_led, const uint8_t matrix12_but, const uint8_t matrix13_led, const uint8_t matrix13_but, const uint8_t matrix14_led, const uint8_t matrix14_but, const uint8_t matrix21_led, const uint8_t matrix21_but, const uint8_t matrix22_led, const uint8_t matrix22_but, const uint8_t matrix23_led, const uint8_t matrix23_but, const uint8_t matrix24_led, const uint8_t matrix24_but, const uint8_t matrix31_led, const uint8_t matrix31_but, const uint8_t matrix32_led, const uint8_t matrix32_but, const uint8_t matrix33_led, const uint8_t matrix33_but, const uint8_t matrix34_led, const uint8_t matrix34_but){
    this->matrix11.begin(matrix11_led, matrix11_but);
    this->matrix12.begin(matrix12_led, matrix12_but);
    this->matrix13.begin(matrix13_led, matrix13_but);
    this->matrix14.begin(matrix14_led, matrix14_but);

    this->matrix21.begin(matrix21_led, matrix21_but);
    this->matrix22.begin(matrix22_led, matrix22_but);
    this->matrix23.begin(matrix23_led, matrix23_but);
    this->matrix24.begin(matrix24_led, matrix24_but);

    this->matrix31.begin(matrix31_led, matrix31_but);
    this->matrix32.begin(matrix32_led, matrix32_but);
    this->matrix33.begin(matrix33_led, matrix33_but);
    this->matrix34.begin(matrix34_led, matrix34_but);

    for(uint8_t i = 0; i < 12; i++){
        if(random(2) == 0){
            this->lights ^= _BV(i);
        }
    }
}

void ButtonMatrixSubsystem::update(){
    this->update_components();
    this->handle_button_presses();
    this->update_lights_mode();
}

void ButtonMatrixSubsystem::update_components(){
    this->matrix11.update();
    this->matrix12.update();
    this->matrix13.update();
    this->matrix14.update();

    this->matrix21.update();
    this->matrix22.update();
    this->matrix23.update();
    this->matrix24.update();

    this->matrix31.update();
    this->matrix32.update();
    this->matrix33.update();
    this->matrix34.update();
}

void ButtonMatrixSubsystem::handle_button_presses(){
    // Column 1
    if(this->matrix11.button_just_pressed()){
        // Historical Sound
        Serial.println("SFX RANDOM_HISTORICAL");
    }

    if(this->matrix21.button_just_pressed()){
        // O2 Fan
        Serial.println("SFX STIR");
    }

    if(this->matrix31.button_just_pressed()){
        // Random Sci-Fi
        Serial.println("SFX RANDOM_SCIFI");
    }

    // Column 2

    if(this->matrix12.button_just_pressed()){
        // Decrease Animation frame length
        this->frame_length /= 2;
        if(this->frame_length < 256){
            this->frame_length = 256;
        }
    }

    if(this->matrix22.button_just_pressed()){
        // Change Animation Randomly
        this->mode = random(NUM_MODES);
    }

    if(this->matrix32.button_just_pressed()){
        // Increase Animation frame length
        this->frame_length *= 2;
        if(this->frame_length > 2048){
            this->frame_length = 2048;
        }
    }

    // Column 3

    if(this->matrix13.button_just_pressed()){

    }

    if(this->matrix23.button_just_pressed()){

    }

    if(this->matrix33.button_just_pressed()){

    }

    // Column 4

    if(this->matrix14.button_just_pressed()){

    }

    if(this->matrix24.button_just_pressed()){

    }

    if(this->matrix34.button_just_pressed()){

    }
}

void ButtonMatrixSubsystem::update_lights_mode(){
    switch(this->mode){
        case MODE_RANDOM:
            this->update_random_blink();
            break;
        case MODE_ALT_BLINK:
            this->update_animation(this->alternate_blink_anim);
            break;
        case MODE_DIAMONDS_UP:
            this->update_animation(this->diamonds_moving_up_anim);
            break;
        case MODE_ALT_DIAMONDS:
            this->update_animation(this->alternating_diamonds_anim);
            break;
        case MODE_DIAMOND_SIDEWAYS:
            this->update_animation(this->diamond_moving_sideways);
            break;
        case MODE_ALT_HALVES:
            this->update_animation(this->alternating_halves_anim);
            break;
        case MODE_OUT_SPIRAL:
            this->update_animation(this->outward_spiral_anim);
            break;
        case MODE_IN_SPIRAL:
            this->update_animation(this->inward_spiral_anim);
            break;
        case MODE_OUT_SPIRAL_2:
            this->update_animation(this->outward_spiral_2_anim);
            break;
        case MODE_IN_SPIRAL_2:
            this->update_animation(this->inward_spiral_2_anim);
            break;
        case MODE_ALT_QUARTERS:
            this->update_animation(this->alternating_quarters_anim);
            break;
        case MODE_ALT_THIRDS:
            this->update_animation(this->alternating_thirds_anim);
            break;
        case MODE_BOUNCE_DIAMOND:
            this->update_animation(this->bouncing_diamond_anim);
            break;
        default:
            this->update_random_blink();
            break;
    }
}

void ButtonMatrixSubsystem::update_random_blink(){
    for(uint8_t i = 0; i < 12; i++){
        if(random(this->frame_length) == 0){
            this->lights ^= _BV(i);
        }
    }
    this->set_all_leds(this->lights);
}

void ButtonMatrixSubsystem::update_animation(const uint16_t anim[24]){
    uint8_t i = (millis() / this->frame_length) % 24;
    this->set_all_leds(anim[i]);
};