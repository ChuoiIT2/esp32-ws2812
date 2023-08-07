#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include <vector>
#include "fx.h"

class Led
{
private:
    Adafruit_NeoPixel pixels;
    uint8_t pin;
    uint8_t numPixels;

public:
    Adafruit_NeoPixel getPixels();

    Led(uint8_t pin, uint8_t numPixels);

    void runFX(FX fx, uint32_t color, uint32_t wait);

    void offAllPixels();

    void rotateColors(uint32_t color, uint32_t wait);

    void wipeColor(uint32_t color, uint32_t wait);

    void chaseTheater(uint32_t color, uint32_t wait);

    void rainbow(uint32_t wait);
};

#endif