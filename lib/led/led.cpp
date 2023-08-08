#include "led.h"

Led::Led()
{
    this->pin = 0;
    this->numPixels = 0;
    this->pixels = new Adafruit_NeoPixel();
}

Led::Led(uint8_t pin, uint8_t numPixels)
{
    this->pin = pin;
    this->numPixels = numPixels;
    this->pixels = new Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
    this->pixels->begin();
}

void Led::offAllPixels()
{
    this->pixels->clear();
    this->pixels->show();
}

void Led::rotateColors(uint32_t color, uint32_t wait)
{
    this->offAllPixels();

    for (int i = 0; i < this->numPixels; i++)
    {
        this->pixels->setPixelColor(i, color);
        this->pixels->show();
        delay(wait);
        this->pixels->setPixelColor(i, 0);
    }
}

void Led::wipeColor(uint32_t color, uint32_t wait)
{
    this->offAllPixels();

    for (int i = 0; i < this->numPixels; i++)
    {
        this->pixels->setPixelColor(i, color);
        this->pixels->show();
        delay(wait);
    }
}

void Led::chaseTheater(uint32_t color, uint32_t wait)
{
    this->offAllPixels();

    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < this->numPixels; i = i + 3)
            {
                this->pixels->setPixelColor(i + q, color);
            }
            this->pixels->show();

            delay(wait);

            for (int i = 0; i < this->numPixels; i = i + 3)
            {
                this->pixels->setPixelColor(i + q, 0);
            }
        }
    }
}

void Led::rainbow(uint32_t wait)
{
    this->offAllPixels();

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

            this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(interpolatedRed, interpolatedGreen, interpolatedBlue));
        }

        this->pixels->show();

        delay(wait);
    }
}

void Led::fadingPulse(uint32_t color, uint32_t fadeInTime, uint32_t holdTime, uint32_t fadeOutTime)
{
    this->offAllPixels();

    int fadeSteps = 50; // Number of steps for fading in and out

    for (int step = 0; step < fadeSteps; step++)
    {
        int brightness = map(step, 0, fadeSteps - 1, 0, 255);

        for (int i = 0; i < this->numPixels; i++)
        {
            this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(
                                               ((color >> 16) & 0xFF) * brightness / 255,
                                               ((color >> 8) & 0xFF) * brightness / 255,
                                               (color & 0xFF) * brightness / 255));
        }

        this->pixels->show();
        delay(fadeInTime / fadeSteps);
    }

    delay(holdTime);

    for (int step = fadeSteps - 1; step >= 0; step--)
    {
        int brightness = map(step, 0, fadeSteps - 1, 0, 255);

        for (int i = 0; i < this->numPixels; i++)
        {
            this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(
                                               ((color >> 16) & 0xFF) * brightness / 255,
                                               ((color >> 8) & 0xFF) * brightness / 255,
                                               (color & 0xFF) * brightness / 255));
        }

        this->pixels->show();
        delay(fadeOutTime / fadeSteps);
    }
}

void Led::sparkle(uint32_t color, int numSparkles, uint32_t sparkleDuration)
{
    this->offAllPixels();

    for (int sparkle = 0; sparkle < numSparkles; sparkle++)
    {
        int randomPixel = random(0, this->numPixels); // Generate a random pixel index

        this->pixels->setPixelColor(randomPixel, color); // Turn on the random pixel
        this->pixels->show();
        delay(sparkleDuration);

        this->pixels->setPixelColor(randomPixel, 0); // Turn off the random pixel
        this->pixels->show();

        // Add a small delay between sparkles
        if (sparkle < numSparkles - 1)
        {
            delay(random(50, 200));
        }
    }
}

void Led::runningLights(uint32_t color, int numLights, uint32_t delayBetweenLights)
{
    this->offAllPixels();

    for (int startPixel = 0; startPixel <= numPixels - numLights; startPixel++)
    {
        for (int pixel = startPixel; pixel < startPixel + numLights; pixel++)
        {
            this->pixels->setPixelColor(pixel, color);
        }

        this->pixels->show();
        delay(delayBetweenLights);

        for (int pixel = startPixel; pixel < startPixel + numLights; pixel++)
        {
            this->pixels->setPixelColor(pixel, 0);
        }
    }
}

void Led::colorBounce(uint32_t color, int ballSize, uint32_t delayBetweenBounces)
{
    this->offAllPixels();

    for (int pixel = 0; pixel <= this->numPixels - ballSize; pixel++)
    {
        for (int i = 0; i < this->numPixels; i++)
        {
            this->pixels->setPixelColor(i, 0); // Clear all pixels
        }

        for (int i = pixel; i < pixel + ballSize; i++)
        {
            this->pixels->setPixelColor(i, color); // Set pixels for the bouncing ball
        }

        this->pixels->show();
        delay(delayBetweenBounces / (this->numPixels - ballSize));
    }

    for (int pixel = this->numPixels - ballSize; pixel >= 0; pixel--)
    {
        for (int i = 0; i < numPixels; i++)
        {
            this->pixels->setPixelColor(i, 0); // Clear all pixels
        }

        for (int i = pixel; i < pixel + ballSize; i++)
        {
            this->pixels->setPixelColor(i, color); // Set pixels for the bouncing ball
        }

        this->pixels->show();
        delay(delayBetweenBounces / (numPixels - ballSize));
    }
}

void Led::randomFlicker(uint32_t color, int numFlickers, uint32_t flickerDuration)
{
    this->offAllPixels();

    for (int flicker = 0; flicker < numFlickers; flicker++)
    {
        for (int pixel = 0; pixel < this->numPixels; pixel++)
        {
            if (random(0, 2) == 0)
            { // Randomly turn on or off the pixel
                this->pixels->setPixelColor(pixel, color);
            }
            else
            {
                this->pixels->setPixelColor(pixel, 0);
            }
        }
        this->pixels->show();
        delay(flickerDuration);
    }
}

void Led::meteorShower(uint32_t color, int numMeteors, uint32_t trailLength, uint32_t meteorDelay)
{
    this->offAllPixels(); // Turn off all pixels before starting
    for (int meteor = 0; meteor < numMeteors; meteor++)
    {

        int randomPixel = random(0, this->numPixels); // Generate a random starting pixel index

        for (int trail = 0; trail < trailLength; trail++)
        {
            this->offAllPixels(); // Clear the previous meteor's trail
            for (int pixel = randomPixel - trail; pixel <= randomPixel; pixel++)
            {
                if (pixel >= 0 && pixel < this->numPixels)
                {
                    this->pixels->setPixelColor(pixel, color); // Turn on pixel for meteor trail
                }
            }
            this->pixels->show();
            delay(meteorDelay);
        }

        this->offAllPixels(); // Turn off all pixels after meteor
        this->pixels->show();

        // Add a small delay between meteors
        if (meteor < numMeteors - 1)
        {
            delay(random(300, 1000));
        }
    }
}

void Led::colorFade(uint32_t color1, uint32_t color2, int numSteps, uint32_t stepDuration)
{
    this->offAllPixels();

    for (int step = 0; step <= numSteps; step++)
    {
        int red1 = (color1 >> 16) & 0xFF;
        int green1 = (color1 >> 8) & 0xFF;
        int blue1 = color1 & 0xFF;

        int red2 = (color2 >> 16) & 0xFF;
        int green2 = (color2 >> 8) & 0xFF;
        int blue2 = color2 & 0xFF;

        int interpolatedRed = map(step, 0, numSteps, red1, red2);
        int interpolatedGreen = map(step, 0, numSteps, green1, green2);
        int interpolatedBlue = map(step, 0, numSteps, blue1, blue2);

        uint32_t interpolatedColor = Adafruit_NeoPixel::Color(interpolatedRed, interpolatedGreen, interpolatedBlue);

        for (int i = 0; i < this->numPixels; i++)
        {
            this->pixels->setPixelColor(i, interpolatedColor);
        }

        this->pixels->show();
        delay(stepDuration);
    }

    // swap color1 and color2
    uint32_t temp = color1;
    color1 = color2;
    color2 = temp;
    for (int step = 0; step <= numSteps; step++)
    {
        int red1 = (color1 >> 16) & 0xFF;
        int green1 = (color1 >> 8) & 0xFF;
        int blue1 = color1 & 0xFF;

        int red2 = (color2 >> 16) & 0xFF;
        int green2 = (color2 >> 8) & 0xFF;
        int blue2 = color2 & 0xFF;

        int interpolatedRed = map(step, 0, numSteps, red1, red2);
        int interpolatedGreen = map(step, 0, numSteps, green1, green2);
        int interpolatedBlue = map(step, 0, numSteps, blue1, blue2);

        uint32_t interpolatedColor = Adafruit_NeoPixel::Color(interpolatedRed, interpolatedGreen, interpolatedBlue);

        for (int i = 0; i < this->numPixels; i++)
        {
            this->pixels->setPixelColor(i, interpolatedColor);
        }

        this->pixels->show();
        delay(stepDuration);
    }
}

void Led::cylonEye(uint32_t color, int eyeSize, int numCycles, uint32_t cycleDelay)
{
    this->offAllPixels();

    for (int cycle = 0; cycle < numCycles; cycle++)
    {
        for (int pixel = 0; pixel <= this->numPixels - eyeSize; pixel++)
        {

            for (int i = pixel; i < pixel + eyeSize; i++)
            {
                this->pixels->setPixelColor(i, color);
            }

            this->pixels->show();
            delay(cycleDelay / (this->numPixels - eyeSize + 1));
        }

        for (int pixel = this->numPixels - eyeSize; pixel >= 0; pixel--)
        {
            this->offAllPixels(); // Clear the previous eye's position

            for (int i = pixel; i < pixel + eyeSize; i++)
            {
                this->pixels->setPixelColor(i, color);
            }

            this->pixels->show();
            delay(cycleDelay / (this->numPixels - eyeSize + 1));
        }
    }
}

void Led::heartbeat(uint32_t color, int numBeats, uint32_t beatDuration, int maxBrightness)
{
    this->offAllPixels();

    int initialBrightness = maxBrightness / 3;

    for (int beat = 0; beat < numBeats; beat++)
    {
        for (int brightness = initialBrightness; brightness <= maxBrightness; brightness++)
        {
            for (int i = 0; i < this->numPixels; i++)
            {
                this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(
                                                   ((color >> 16) & 0xFF) * brightness / maxBrightness,
                                                   ((color >> 8) & 0xFF) * brightness / maxBrightness,
                                                   (color & 0xFF) * brightness / maxBrightness));
            }

            this->pixels->show();
            delay(beatDuration / maxBrightness);
        }

        for (int brightness = maxBrightness - 1; brightness >= initialBrightness; brightness--)
        {
            for (int i = 0; i < this->numPixels; i++)
            {
                this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(
                                                   ((color >> 16) & 0xFF) * brightness / maxBrightness,
                                                   ((color >> 8) & 0xFF) * brightness / maxBrightness,
                                                   (color & 0xFF) * brightness / maxBrightness));
            }

            this->pixels->show();
            delay(beatDuration / maxBrightness);
        }
    }
}

void Led::fireEffect(uint32_t color, int flickerDelay, int numCycles)
{
    this->offAllPixels();

    for (int cycle = 0; cycle < numCycles; cycle++)
    {
        for (int i = 0; i < this->numPixels; i++)
        {
            int flicker = random(0, 100); // Generate a random value for flickering

            int red = ((color >> 16) & 0xFF) * flicker / 100;
            int green = ((color >> 8) & 0xFF) * flicker / 100;
            int blue = (color & 0xFF) * flicker / 100;

            this->pixels->setPixelColor(i, Adafruit_NeoPixel::Color(red, green, blue));
        }

        this->pixels->show();
        delay(flickerDelay);
    }
}
