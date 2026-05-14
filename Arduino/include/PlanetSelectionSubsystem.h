#ifndef PLANET_SELECTION_SUBSYSTEM_H
#define PLANET_SELECTION_SUBSYSTEM_H
#include "Arduino.h"
#include "LimitSwitch.h"

class PlanetSelectionSubsystem{
    public:
        PlanetSelectionSubsystem();
        void begin(uint8_t bit0_pin, uint8_t bit1_pin, uint8_t bit2_pin);
        uint8_t planet();
        void update();
    private:
        const String planet_cmd = "PLANET ";
        const uint8_t index_to_planet[8] = {7, 5, 6, 4, 3, 1, 2, 0};
        LimitSwitch bit0 = LimitSwitch();
        LimitSwitch bit1 = LimitSwitch();
        LimitSwitch bit2 = LimitSwitch();

        bool has_changed();
};

#endif