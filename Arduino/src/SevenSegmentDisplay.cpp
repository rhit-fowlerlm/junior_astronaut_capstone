#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay()
{
  
}

int SevenSegmentDisplay::begin(TwoWire *wire, const uint8_t ledAddress)
{
    this->pWire = wire;
    this->ledAddress = ledAddress >> 1; 
    this->pWire->begin();
    if(this->i2cdetect() != 0){
        return -1;
    }
    this->i2cWriteCmd(this->CMD_HT16K33_OSCON);
    this->on();
    this->setBrightness(14);
    print('8', '8', '8', '8', '8', '8', '8', '8', 0xFF);
    print(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0x00);
    return 0;
}

void SevenSegmentDisplay::print(const char c0, const char c1, const char c2, const char c3, const char c4, const char c5, char c6, const char c7, const uint8_t decimal_points){

    uint8_t d_new[8] = {
        get_char_code(c0),
        get_char_code(c1),
        get_char_code(c2),
        get_char_code(c3),
        get_char_code(c4),
        get_char_code(c5),
        get_char_code(c6),
        get_char_code(c7),
    };

    for(uint8_t i = 0; i < 8; i++){
        if(decimal_points & _BV(7-i)){
            d_new[i] |= DECIMAL_POINT;
        }

        if(this->d[i] != d_new[i]){
            this->d[i] = d_new[i];
            this->i2cWriteLights(i, this->d[i]);
        }
    }
}

uint8_t SevenSegmentDisplay::get_char_code(char c){
    uint8_t xc = (uint8_t)c;
    if(xc < 0x20){
        return 0x00;
    }
    if(xc > 0x60){
        return 0x00;
    }
    return CHARACTERS[xc - 0x20];
}

void SevenSegmentDisplay::on()
{
    this->i2cWriteCmd(0x01);        
    this->i2cWriteCmd(this->CMD_HT16K33_DISPLAYON); 
}

void SevenSegmentDisplay::off()
{
    this->i2cWriteCmd(0x00);         
    this->i2cWriteCmd(this->CMD_HT16K33_DISPLAYOFF); 
}

void SevenSegmentDisplay::setBrightness(const uint8_t brightnessValue)
{
    this->i2cWriteCmd(0xE0|brightnessValue);
}

void SevenSegmentDisplay::i2cWriteCmd(const uint8_t cmd)
{
  pWire->beginTransmission(this->ledAddress);
  pWire->write(cmd);
  pWire->endTransmission();
}

void SevenSegmentDisplay::i2cWriteLights(const uint8_t reg, const uint8_t data)
{
  pWire->beginTransmission(this->ledAddress);
  pWire->write(reg*2);
  pWire->write(data);
  pWire->endTransmission();
}

int SevenSegmentDisplay::i2cdetect()
{
  pWire->beginTransmission(this->ledAddress);
  if(pWire->endTransmission() == 0)
  {
      return  0;
  }
  return -1;
}