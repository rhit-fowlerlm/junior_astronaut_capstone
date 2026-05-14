#include "SmoothRandom.h"

SmoothRandom::SmoothRandom(){
    this->offset = random(RANDOM_MAX) * (1.0f / RANDOM_MAX);
}

float SmoothRandom::get_smooth_random(float t){
    t += this->offset;
    float f = 0;

    for(uint16_t i = 0; i < 10; i++){
        uint16_t freq = i + 11;
        float s = pgm_read_float_near(SIN_SMOOTH_RANDOM_FOURIER_COEFFS + i);
        float c = pgm_read_float_near(COS_SMOOTH_RANDOM_FOURIER_COEFFS + i);
        f += s * sinf(2*PI*freq*t) + c * cosf(2*PI*freq*t);
    }

    return f;
}