#ifndef MASS_SWITCHING_PLANET_LIMIT_SWITCHES_H
#define MASS_SWITCHING_PLANET_LIMIT_SWITCHES_H
#include "Arduino.h"
#include "LimitSwitch.h"

class MassSwitchingPlanetLimitSwitches{
    public:
        MassSwitchingPlanetLimitSwitches();
        void begin(uint8_t bit0_pin, uint8_t bit1_pin, uint8_t bit2_pin);
        uint8_t planet();
        void update();
    private:
        const String planet_cmd = "PLANET ";
        const uint8_t index_to_planet[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        LimitSwitch bit0 = LimitSwitch();
        LimitSwitch bit1 = LimitSwitch();
        LimitSwitch bit2 = LimitSwitch();
};

#endif