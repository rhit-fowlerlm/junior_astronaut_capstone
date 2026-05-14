#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include "Arduino.h"
#include "Wire.h"

constexpr uint8_t TOP = _BV(0);
constexpr uint8_t TOP_RIGHT = _BV(1);
constexpr uint8_t BOTTOM_RIGHT = _BV(2);
constexpr uint8_t BOTTOM = _BV(3);
constexpr uint8_t BOTTOM_LEFT = _BV(4);
constexpr uint8_t TOP_LEFT = _BV(5);
constexpr uint8_t MIDDLE = _BV(6);
constexpr uint8_t DECIMAL_POINT = _BV(7);

// OFFSET FROM ASCII BY 0x20
constexpr uint8_t CHARACTERS[0x40] = 
{
    0x00, // SPACE
    0x00, // !
    TOP_LEFT | BOTTOM_LEFT | TOP_RIGHT | BOTTOM_RIGHT, // "
    0x00, // #
    0x00, // $
    0x00, // %
    0x00, // &
    0x00, // '
    TOP_LEFT | BOTTOM_LEFT, // (
    TOP_RIGHT | BOTTOM_RIGHT, // )
    0x00, // *
    0x00, // +
    0x00, // ,
    MIDDLE, // -
    DECIMAL_POINT, // .
    0x00, // /
    TOP | TOP_RIGHT | TOP_LEFT | BOTTOM_RIGHT | BOTTOM_LEFT | BOTTOM, // 0
    TOP_RIGHT | BOTTOM_RIGHT, // 1
    TOP | TOP_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM, // 2
    TOP_RIGHT | BOTTOM_RIGHT | TOP | MIDDLE | BOTTOM, // 3
    TOP_LEFT | MIDDLE | TOP_RIGHT | BOTTOM_RIGHT, // 4
    TOP | TOP_LEFT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // 5
    TOP | TOP_LEFT | BOTTOM_LEFT | BOTTOM_RIGHT | MIDDLE | BOTTOM, // 6
    TOP | TOP_RIGHT | BOTTOM_RIGHT, // 7
    TOP | TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM_RIGHT | BOTTOM, // 8
    TOP | TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // 9
    0x00, // :
    0x00, // ;
    0x00, // <
    0x00, // =
    0x00, // >
    0x00, // ?
    0x00, // @
    TOP | TOP_LEFT | BOTTOM_LEFT | TOP_RIGHT | BOTTOM_RIGHT | MIDDLE, // A
    TOP_LEFT | BOTTOM_LEFT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // B
    TOP | TOP_LEFT | BOTTOM_LEFT | BOTTOM, // C
    TOP_RIGHT | BOTTOM_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM, // D
    TOP_LEFT | BOTTOM_LEFT | TOP | MIDDLE | BOTTOM, // E
    TOP_LEFT | BOTTOM_LEFT | TOP | MIDDLE, // F
    TOP | TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // G
    TOP_LEFT | BOTTOM_LEFT | MIDDLE | TOP_RIGHT | BOTTOM_RIGHT, // H
    TOP_RIGHT | BOTTOM_RIGHT, // I
    TOP_RIGHT | BOTTOM_RIGHT | BOTTOM, // J
    TOP_LEFT | BOTTOM_LEFT | MIDDLE, // K
    TOP_LEFT | BOTTOM_LEFT | BOTTOM, // L
    BOTTOM_LEFT | BOTTOM_RIGHT | TOP, // M
    TOP | TOP_LEFT | BOTTOM_LEFT | TOP_RIGHT | BOTTOM_RIGHT, // N
    TOP | TOP_RIGHT | TOP_LEFT | BOTTOM_RIGHT | BOTTOM_LEFT | BOTTOM, // O
    TOP_LEFT | BOTTOM_LEFT | TOP | TOP_RIGHT | MIDDLE, // P
    TOP_LEFT | BOTTOM_RIGHT | TOP | TOP_RIGHT | MIDDLE, // Q
    TOP_LEFT | BOTTOM_LEFT | TOP, // R
    TOP | TOP_LEFT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // S
    TOP_LEFT | BOTTOM_LEFT | MIDDLE | BOTTOM, // T
    TOP_LEFT | BOTTOM_LEFT | BOTTOM | TOP_RIGHT | BOTTOM_RIGHT, // U
    BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT, // V
    TOP_LEFT | BOTTOM | TOP_RIGHT, // W
    MIDDLE | TOP_RIGHT | BOTTOM_RIGHT, // X
    TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT | BOTTOM, // Y
    TOP | TOP_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM, // Z
    TOP_LEFT | BOTTOM_LEFT, // [
    TOP_RIGHT | BOTTOM_RIGHT, // ]
    0x00, // ^
    BOTTOM, // _
    0x00, // `
};

class SevenSegmentDisplay{
    public:
        SevenSegmentDisplay();
        int begin(TwoWire *wire, const uint8_t ledAddress);
        void on();
        void off();
        void setBrightness(const uint8_t brightnessValue);
        void print(const char c0, const char c1, const char c2, const char c3, const char c4, const char c5, const char c6, const char c7, const uint8_t decimal_points = 0x00);
    private:
        TwoWire *pWire;
        uint8_t ledAddress;

        uint8_t get_char_code(char c);

        void i2cWriteCmd(const uint8_t cmd);
        void i2cWriteLights(const uint8_t reg, const uint8_t data);
        int i2cdetect();

        uint8_t d[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        const uint8_t CMD_HT16K33_OSCOFF      = 0x20;  ///< Turn OFF the clock 
        const uint8_t CMD_HT16K33_OSCON       = 0x21;  ///< Turn ON the clock
        const uint8_t CMD_HT16K33_DISPLAYOFF  = 0x80;  ///< Turn OFF the display
        const uint8_t CMD_HT16K33_DISPLAYON   = 0x81;  ///< Turn ON the display*/
        const uint8_t CMD_HT16K33_FLASHTWOS   = 0x87;  ///< Set the mode to flash at 0.5Hz
        const uint8_t CMD_HT16K33_FLASHONES   = 0x85;  ///< Set the mode to flash at 1Hz
        const uint8_t CMD_HT16K33_FLASHHALFS  = 0x83;  ///< Set the mode to flash at 2Hz
        const uint8_t CMD_HT16K33_STOPFLASH   = 0x81;  ///< Flash end
};

#endif