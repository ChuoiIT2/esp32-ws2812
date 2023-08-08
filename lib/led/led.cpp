#include "led.h"

Adafruit_NeoPixel Led::getPixels()
{
    return Led::pixels;
}

Led::Led(uint8_t pin, uint8_t numPixels)
{
    Led::pin = pin;
    Led::numPixels = numPixels;
    Led::pixels = Adafruit_NeoPixel(Led::numPixels, Led::pin, NEO_GRB + NEO_KHZ800);
    Led::pixels.begin();
}

void Led::offAllPixels()
{
    Led::pixels.clear();
    Led::pixels.show();
}

void Led::rotateColors(uint32_t color, uint32_t wait)
{
    for (int i = 0; i < Led::numPixels; i++)
    {
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(wait);
        pixels.setPixelColor(i, 0);
    }
}

void Led::wipeColor(uint32_t color, uint32_t wait)
{
    for (int i = 0; i < Led::numPixels; i++)
    {
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(wait);
    }
}

void Led::chaseTheater(uint32_t color, uint32_t wait)
{
    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < Led::numPixels; i = i + 3)
            {
                Led::pixels.setPixelColor(i + q, color);
            }
            pixels.show();

            delay(wait);

            for (int i = 0; i < Led::numPixels; i = i + 3)
            {
                Led::pixels.setPixelColor(i + q, 0);
            }
        }
    }
}

void Led::rainbow(uint32_t wait)
{
    std::vector<uint32_t> colors = {
        0xFF0000, // Red
        0xFF7F00, // Orange
        0xFFFF00, // Yellow
        0x00FF00, // Green
        0x0000FF, // Blue
        0x4B0082, // Indigo
        0x9400D3  // Violet
    };

    int numColors = colors.size();

    for (int colorIndex = 0; colorIndex < numColors; colorIndex++)
    {
        int nextColorIndex = (colorIndex + 1) % numColors;
        int currentColor = colors[colorIndex];
        int nextColor = colors[nextColorIndex];

        for (int i = 0; i < this->numPixels; i++)
        {
            int red = (currentColor >> 16) & 0xFF;
            int green = (currentColor >> 8) & 0xFF;
            int blue = currentColor & 0xFF;

            int nextRed = (nextColor >> 16) & 0xFF;
            int nextGreen = (nextColor >> 8) & 0xFF;
            int nextBlue = nextColor & 0xFF;

            int interpolatedRed = map(i, 0, this->numPixels - 1, red, nextRed);
            int interpolatedGreen = map(i, 0, this->numPixels - 1, green, nextGreen);
            int interpolatedBlue = map(i, 0, this->numPixels - 1, blue, nextBlue);

            this->pixels.setPixelColor(i, Adafruit_NeoPixel::Color(interpolatedRed, interpolatedGreen, interpolatedBlue));
        }

        this->pixels.show();

        delay(wait);
    }
}

int addLedsConstant = 4;        // how fast are LEDS added to bar
int removeLedsTimeConstant = 4; // how fast are LEDS removed from bar
int middleColorLED = 25;

int numLedsToLight = 0;

long lastRefreshTime;

void Led::music(uint32_t ledsToLight, uint32_t wait)
{

    if (ledsToLight > numLedsToLight)
    {
        numLedsToLight += addLedsConstant;
    }
    else if (ledsToLight < numLedsToLight)
    {
        if (millis() - lastRefreshTime >= removeLedsTimeConstant)
        {
            lastRefreshTime += removeLedsTimeConstant;
            numLedsToLight -= 1;
        }
    }

    if (numLedsToLight < 1)
    {
        numLedsToLight = 0;
    }
    if (numLedsToLight > this->numPixels)
    {
        numLedsToLight = this->numPixels;
    }

    for (int led = 0; led < numLedsToLight; led++)
    {
        if (led < middleColorLED)
        {
            // this->pixels.setPixelColor(led, (map(led, 0, middleColorLED - 1, 0, 255), 255, 0));
            this->pixels.setPixelColor(led, 0x00FF00);
        }
        else
        {
            this->pixels.setPixelColor(led, 0x00FF00);
        }
    }
    for (int led = this->numPixels; led >= numLedsToLight; led--)
    {
        this->pixels.setPixelColor(led, 0);
    }

    this->pixels.show();

    delay(wait);
}

void Led::turnOn(uint8_t height, uint32_t color)
{
    for (int i = 0; i < this->numPixels; i++)
    {
        if (i <= height)
        {
            this->pixels.setPixelColor(i, color);
        }
        else
        {
            this->pixels.setPixelColor(i, 0);
        }
    }

    this->pixels.show();

    delay(100);
}