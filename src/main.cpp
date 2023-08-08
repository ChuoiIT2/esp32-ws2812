#include <Adafruit_NeoPixel.h>
#include "led.h"
#include "state.h"
#include "sound.h"

// Serial
#define BAUD_RATE 115200

// Constants
const uint8_t LED_PIN = 13;
const uint8_t NUM_PIXELS = 24;
const uint8_t SOUND_PIN = 14;
const uint32_t NOISE = 16;

// Global variables
Led *led;
Sound *sound;
State state;

int lvl = 0, minLvl = 0, maxLvl = 300; // tweak the min and max as needed

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
    Serial.println("setup");
}

void loop()
{
    // int n = random(0, 4096);
    // n = map(n, 0, 4096, 0, NUM_PIXELS);
    // led->music(10, 100);
    int n = random(1, 24);
    led->music(n, 100);
    Serial.println("hello");
}
