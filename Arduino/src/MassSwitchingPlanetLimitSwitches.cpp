#include "MassSwitchingPlanetLimitSwitches.h"

MassSwitchingPlanetLimitSwitches::MassSwitchingPlanetLimitSwitches(){

}

void MassSwitchingPlanetLimitSwitches::begin(uint8_t bit0_pin, uint8_t bit1_pin, uint8_t bit2_pin){
    this->bit0.begin(bit0_pin);
    this->bit1.begin(bit1_pin);
    this->bit2.begin(bit2_pin);
}

uint8_t MassSwitchingPlanetLimitSwitches::planet(){
    uint8_t idx = (bit2.is_pressed() << 2) | (bit1.is_pressed() << 1) | bit0.is_pressed();
    return this->index_to_planet[idx];
}

void MassSwitchingPlanetLimitSwitches::update(){
    this->bit0.update();
    this->bit1.update();
    this->bit2.update();
    Serial.print(this->planet_cmd);
    Serial.println(this->planet());
}