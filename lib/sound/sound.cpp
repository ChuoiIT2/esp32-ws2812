#include <sound.h>

Sound::Sound(uint8_t pin)
{
    Sound::pin = pin;
    pinMode(Sound::pin, INPUT);
}

uint32_t Sound::getData(uint32_t NUM_PIXELS, uint32_t wait)
{
    int n = analogRead(Sound::pin);
    n = map(n, 0, 4096, 0, NUM_PIXELS);
    return n;
}