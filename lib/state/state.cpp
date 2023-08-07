#include <Adafruit_NeoPixel.h>
#include "state.h"

State::State()
{
    this->fx = OFF;
    this->colors = std::vector<uint32_t>(Adafruit_NeoPixel::Color(0, 0, 0));
    wait = 100;
}

State::State(FX fx, std::vector<uint32_t> colors, int wait)
{
    this->fx = fx;
    this->colors = colors;
    this->wait = wait;
}