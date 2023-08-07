#include "led.h"

Led::Led()
{
    this->pin = 0;
    this->numPixels = 0;
    this->pixels = Adafruit_NeoPixel();
}

Led::Led(uint8_t pin, uint8_t numPixels)
{
    Led::pin = pin;
    Led::numPixels = numPixels;
    Led::pixels = Adafruit_NeoPixel(Led::numPixels, Led::pin, NEO_GRB + NEO_KHZ800);
    Led::pixels.begin();
}

Adafruit_NeoPixel Led::getPixels()
{
    return Led::pixels;
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

void Led::fadingPulse(uint32_t color, uint32_t fadeInTime, uint32_t holdTime, uint32_t fadeOutTime)
{
    int fadeSteps = 50; // Number of steps for fading in and out

    for (int step = 0; step < fadeSteps; step++)
    {
        int brightness = map(step, 0, fadeSteps - 1, 0, 255);

        for (int i = 0; i < this->numPixels; i++)
        {
            pixels.setPixelColor(i, Adafruit_NeoPixel::Color(
                                        ((color >> 16) & 0xFF) * brightness / 255,
                                        ((color >> 8) & 0xFF) * brightness / 255,
                                        (color & 0xFF) * brightness / 255));
        }

        pixels.show();
        delay(fadeInTime / fadeSteps);
    }

    delay(holdTime);

    for (int step = fadeSteps - 1; step >= 0; step--)
    {
        int brightness = map(step, 0, fadeSteps - 1, 0, 255);

        for (int i = 0; i < this->numPixels; i++)
        {
            pixels.setPixelColor(i, Adafruit_NeoPixel::Color(
                                        ((color >> 16) & 0xFF) * brightness / 255,
                                        ((color >> 8) & 0xFF) * brightness / 255,
                                        (color & 0xFF) * brightness / 255));
        }

        pixels.show();
        delay(fadeOutTime / fadeSteps);
    }
}

void Led::sparkle(uint32_t color, int numSparkles, uint32_t sparkleDuration)
{
    for (int sparkle = 0; sparkle < numSparkles; sparkle++)
    {
        int randomPixel = random(0, numPixels); // Generate a random pixel index

        pixels.setPixelColor(randomPixel, color); // Turn on the random pixel
        pixels.show();
        delay(sparkleDuration);

        pixels.setPixelColor(randomPixel, 0); // Turn off the random pixel
        pixels.show();

        // Add a small delay between sparkles
        if (sparkle < numSparkles - 1)
        {
            delay(random(50, 200));
        }
    }
}
