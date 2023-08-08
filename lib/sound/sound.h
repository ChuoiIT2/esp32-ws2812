#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <Arduino.h>

class Sound
{
private:
    uint8_t pin;

public:
    Sound(uint8_t pin);
    uint32_t getData();
};

#endif