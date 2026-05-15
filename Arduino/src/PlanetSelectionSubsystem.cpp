#include "PlanetSelectionSubsystem.h"

PlanetSelectionSubsystem::PlanetSelectionSubsystem(){

}

void PlanetSelectionSubsystem::begin(uint8_t bit0_pin, uint8_t bit1_pin, uint8_t bit2_pin){
    this->bit0.begin(bit0_pin, true, 50);
    this->bit1.begin(bit1_pin, true, 50);
    this->bit2.begin(bit2_pin, true, 50);
}

uint8_t PlanetSelectionSubsystem::planet(){
    uint8_t idx = (bit2.is_pressed() << 2) | (bit1.is_pressed() << 1) | bit0.is_pressed();
    return this->index_to_planet[idx];
}

void PlanetSelectionSubsystem::update(){
    uint8_t planet_prev = this->planet();
    this->bit0.update();
    this->bit1.update();
    this->bit2.update();
    if(this->planet() != planet_prev){
        Serial.print(this->planet_cmd);
        Serial.println(this->planet());
    }
}