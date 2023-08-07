#include <Adafruit_NeoPixel.h>
#include "led.h"
#include "state.h"

// Serial
#define BAUD_RATE 115200

// Constants
const uint8_t LED_PIN = 13;
const uint8_t NUM_PIXELS = 24;

// Global variables
Led *led;
State state;

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
    state = State();

    Serial.begin(BAUD_RATE);
    Serial.onReceive(onSerialReceive);
}

void loop()
{
    led->rainbow(100);
}
