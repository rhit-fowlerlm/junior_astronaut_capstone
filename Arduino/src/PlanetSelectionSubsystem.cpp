#include "PlanetSelectionSubsystem.h"

PlanetSelectionSubsystem::PlanetSelectionSubsystem(){

}

void PlanetSelectionSubsystem::begin(uint8_t bit0_pin, uint8_t bit1_pin, uint8_t bit2_pin){
    this->bit0.begin(bit0_pin);
    this->bit1.begin(bit1_pin);
    this->bit2.begin(bit2_pin);
}

uint8_t PlanetSelectionSubsystem::planet(){
    uint8_t idx = (bit2.is_pressed() << 2) | (bit1.is_pressed() << 1) | bit0.is_pressed();
    return this->index_to_planet[idx];
}

void PlanetSelectionSubsystem::update(){
    this->bit0.update();
    this->bit1.update();
    this->bit2.update();
    if(this->has_changed()){
        Serial.print(this->planet_cmd);
        Serial.println(this->planet());
    }
}

bool PlanetSelectionSubsystem::has_changed(){
    return this->bit0.just_pressed() || this->bit0.just_released() || this->bit1.just_pressed() || this->bit1.just_released() || this-bit2.just_pressed() || this->bit2.just_released();
}