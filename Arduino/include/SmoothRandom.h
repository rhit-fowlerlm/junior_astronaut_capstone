#ifndef SMOOTH_RANDOM_H
#define SMOOTH_RANDOM_H
#include "Arduino.h"

// Generated 1000 term fourier series with random coefficients
constexpr float SIN_SMOOTH_RANDOM_FOURIER_COEFFS[10] PROGMEM = 
{0.073378,-0.13129,0.077596,0.17549,0.052366,0.11027,0.077083,-0.032018,0.030854,-0.082245};
constexpr float COS_SMOOTH_RANDOM_FOURIER_COEFFS[10] PROGMEM = 
{0.097079,-0.12472,-0.11564,-0.087141,-0.31537,0.1533,0.034485,-0.079657,0.14387,-0.1788};

class SmoothRandom{
    public:
        SmoothRandom();
        float get_smooth_random(float t);
    private:
        float offset;
};

#endif