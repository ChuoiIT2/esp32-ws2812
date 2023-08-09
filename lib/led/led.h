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
    FADING_PULSE = 5,
    SPARKLE = 6,
    RUNNING_LIGHTS = 7,
    COLOR_BOUNCE = 8,
    RANDOM_FLICKER = 9,
    METEOR_SHOWER = 10,
    COLOR_FADE = 11,
    CYLON_EYE = 12,
    HEARTBEAT = 13,
    FIRE_EFFECT = 14,
    SOUND_REACTIVE = 15
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

    void setRTSColor(uint32_t color);

    void reactToSound(uint16_t soundValue, std::vector<uint32_t> colors, uint32_t wait);

    void rotateColors(uint32_t color, uint32_t wait);

    void wipeColor(uint32_t color, uint32_t wait);

    void chaseTheater(uint32_t color, uint32_t wait);

    void rainbow(uint32_t wait);

    void fadingPulse(uint32_t color, uint32_t fadeInTime, uint32_t holdTime, uint32_t fadeOutTime);

    void sparkle(uint32_t color, int numSparkles, uint32_t sparkleDuration);

    void runningLights(uint32_t color, int numLights, uint32_t delayBetweenLights);

    void colorBounce(uint32_t color, int ballSize, uint32_t delayBetweenBounces);

    void randomFlicker(uint32_t color, int numFlickers, uint32_t flickerDuration);

    void meteorShower(uint32_t color, int numMeteors, uint32_t trailLength, uint32_t meteorDelay);

    void colorFade(uint32_t color1, uint32_t color2, int numSteps, uint32_t stepDuration);

    void cylonEye(uint32_t color, int eyeSize, int numCycles, uint32_t cycleDelay);

    void heartbeat(uint32_t color, int numBeats, uint32_t beatDuration, int maxBrightness);

    void fireEffect(uint32_t color, int flickerDelay, int numCycles);
};

#endif