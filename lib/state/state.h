#ifndef STATE_H
#define STATE_H

#include <Adafruit_NeoPixel.h>
#include <vector>
#include "led.h"

class State
{
public:
    FX fx;
    std::vector<uint32_t> colors;
    uint32_t wait;

    State();
    State(FX fx, std::vector<uint32_t> colors, uint32_t wait);
};

#endif