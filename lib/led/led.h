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
    Adafruit_NeoPixel *pixels;
    uint8_t pin;
    uint8_t numPixels;

public:
    Led();

    Led(uint8_t pin, uint8_t numPixels);

    void offAllPixels();

    void rotateColors(uint32_t color, uint32_t wait);

    void wipeColor(uint32_t color, uint32_t wait);

    void chaseTheater(uint32_t color, uint32_t wait);

    void rainbow(uint32_t wait);

    void fadingPulse(uint32_t color, uint32_t fadeInTime, uint32_t holdTime, uint32_t fadeOutTime);

    void sparkle(uint32_t color, int numSparkles, uint32_t sparkleDuration);

    void runningLights(uint32_t color, int numLights, uint32_t delayBetweenLights);

    void colorBounce(uint32_t color, int ballSize, int numBounces, uint32_t delayBetweenBounces);

    void randomFlicker(uint32_t color, int numFlickers, uint32_t flickerDuration);
};

#endif