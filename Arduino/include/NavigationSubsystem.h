#ifndef NAVIGATION_SUBSYSTEM
#define NAVIGATION_SUBSYSTEM
#include "Arduino.h"
#include "LedButton.h"
#include "Joystick.h"

class NavigationSubsystem{
    public:
        NavigationSubsystem();
        void begin(uint8_t forward_led, uint8_t forward_button, uint8_t backward_led, uint8_t backward_button, uint8_t joystick_x_pos, uint8_t joystick_x_neg, uint8_t joystick_y_pos, uint8_t joystick_y_neg);
        void update();
    private:
        Joystick joystick = Joystick();
        LedButton thrust_forward = LedButton();
        LedButton thrust_backward = LedButton();

        unsigned long last_update_ms = 0;
        const uint32_t time_between_updates_ms = 100;
    
        void update_components();
        void send_joystick_data();


};

#endif