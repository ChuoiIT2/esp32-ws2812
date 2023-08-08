#include <sound.h>

Sound::Sound(uint8_t pin)
{
    Sound::pin = pin;
    pinMode(Sound::pin, INPUT);
}

uint32_t Sound::getData()
{
    return analogRead(Sound::pin);
}