#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include <vector>

enum FX
{
    OFF = 0,
    WIPE_COLOR = 1,
    ROTATE_COLOR = 2,
    CHASE_THEATER = 3,
    RAINBOW = 4,
};

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

    void music(uint32_t ledsToLight, uint32_t wait);

    void turnOn(uint8_t height, uint32_t color);
};

#endif