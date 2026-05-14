#include "NavigationSubsystem.h"

NavigationSubsystem::NavigationSubsystem(){

}

void NavigationSubsystem::begin(uint8_t forward_led, uint8_t forward_button, uint8_t backward_led, uint8_t backward_button, uint8_t joystick_x_pos, uint8_t joystick_x_neg, uint8_t joystick_y_pos, uint8_t joystick_y_neg){
    this->joystick.begin(joystick_x_pos, joystick_x_neg, joystick_y_pos, joystick_y_neg);
    this->thrust_forward.begin(forward_led, forward_button);
    this->thrust_backward.begin(backward_led, backward_button);
}

void NavigationSubsystem::update(){
    this->update_components();
    thrust_backward.led_on();
    thrust_forward.led_on();

    if(millis() - this->last_update_ms > this->time_between_updates_ms){
        this->send_joystick_data();
        this->last_update_ms = millis();
    }
}

void NavigationSubsystem::update_components(){
    joystick.update();
    thrust_forward.update();
    thrust_backward.update();
}

void NavigationSubsystem::send_joystick_data(){
    const char directions[3] = {'-', '0', '+'};
    int8_t z = thrust_forward.button_is_pressed() - thrust_backward.button_is_pressed();

    Serial.print("JOYSTICK X");
    Serial.print(directions[this->joystick.x()+1]);
    Serial.print("Y");
    Serial.print(directions[this->joystick.y()+1]);
    Serial.print("Z");
    Serial.print(directions[z+1]);
    Serial.println();
}