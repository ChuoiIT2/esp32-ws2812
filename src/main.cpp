#include <Adafruit_NeoPixel.h>
#include "led.h"
#include "state.h"
#include "sound.h"

// Serial
#define BAUD_RATE 115200
#define NOISE 16
#define TOP 26
// Constants
const uint8_t LED_PIN = 13;
const uint8_t NUM_PIXELS = 24;
const uint8_t SOUND_PIN = 14;

// Global variables
Led *led;
Sound *sound;
State state;

int lvl = 0, minLvl = 0, maxLvl = 300; // tweak the min and max as needed

// instantiate the filter class for smoothing the raw audio signal
// ExponentialFilter<long> ADCFilter(5, 0);

void runFX()
{
    switch (state.fx)
    {
    case OFF:
        led->offAllPixels();
        break;
    case WIPE_COLOR:
        led->wipeColor(state.colors[0], state.wait);
        break;
    case ROTATE_COLOR:
        led->rotateColors(state.colors[0], state.wait);
        break;
    case CHASE_THEATER:
        led->chaseTheater(state.colors[0], state.wait);
        break;
    default:
        break;
    }
}

void onSerialReceive()
{
    Serial.println("onSerialReceive");

    if (Serial.available() > 0)
    {
        Serial.println("Serial.readStringUntil('\n')");
        Serial.println(Serial.readStringUntil('\n'));
    }
}

void setup()
{
    led = new Led(LED_PIN, NUM_PIXELS);
    // sound = new Sound(SOUND_PIN);
    state = State();

    Serial.begin(BAUD_RATE);
    Serial.onReceive(onSerialReceive);
}

void loop()
{
    // int n, height;
    // n = sound->getData();
    // n = abs(4096 - n);
    // n = (n <= NOISE) ? 0 : abs(n - NOISE);
    // ADCFilter.Filter(n);
    // lvl = ADCFilter.Current();

    // height = map(lvl, minLvl, maxLvl, 0, TOP);
    // if (height < 0L)
    //     height = 0;
    // else if (height > TOP)
    //     height = TOP;
    //get random number from 0 to 24
    // int height = random(2, 24);
    // led->turnOn(height, 0x00FF00);
    // Serial.println(height);
    // Serial.println("Hmm");
    // delay(100);
    led->rainbow(100);
}
