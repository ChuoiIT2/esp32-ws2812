#ifndef STATE_H
#define STATE_H

#include <Adafruit_NeoPixel.h>
#include <vector>
#include <ArduinoJson.h>
#include "led.h"

class State
{
public:
    FX fx;
    std::vector<uint32_t> colors;
    uint32_t wait;

    State();
    
    State(FX fx, std::vector<uint32_t> colors, uint32_t wait);

    void fromJson(std::string json);

    std::string toJson();
};

class ReceivedData
{
public:
    FX fx;
    std::vector<uint32_t> colors;
    uint32_t wait;

    ReceivedData();
    ReceivedData(FX fx, std::vector<uint32_t> colors, uint32_t wait);
};

#endif