#ifndef STATE_H
#define STATE_H

#include <Adafruit_NeoPixel.h>
#include <vector>
#include "fx.h"

class State
{
public:
    FX fx;
    std::vector<uint32_t> colors;
    int wait;

    State();
    State(FX fx, std::vector<uint32_t> colors, int wait);
};

#endif