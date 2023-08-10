#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "led.h"
#include "state.h"

// Serial
#define BAUD_RATE 115200

// BLE
#define BLE_DEVICE_NAME "Chuoi-LED"
#define BLE_SERVICE_UUID "27186965-c935-47a2-8fdb-486f1573081d"
#define BLE_CHARACTERISTIC_UUID "cd530ace-578a-4144-81ec-40e8bccdc311"

// Constants
const uint8_t LED_PIN = 13;
const uint8_t NUM_PIXELS = 24;
const uint8_t SOUND_PIN = 14;

// Global variables
Led *led;
State state;

void runFX()
{
    uint16_t sv = 0;

    if (state.colors.size() == 0)
    {
        state.colors.push_back(0xffffff);
    }

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
    case RAINBOW:
        led->rainbow(state.wait);
        break;
    case FADING_PULSE:
        led->fadingPulse(state.colors[0], state.wait, state.wait, state.wait);
        break;
    case SPARKLE:
        led->sparkle(state.colors[0], 3, state.wait);
        break;
    case RUNNING_LIGHTS:
        led->runningLights(state.colors[0], 3, state.wait);
        break;
    case COLOR_BOUNCE:
        led->colorBounce(state.colors[0], 3, state.wait);
        break;
    case RANDOM_FLICKER:
        led->randomFlicker(state.colors[0], 3, state.wait);
        break;
    case METEOR_SHOWER:
        led->meteorShower(state.colors[0], 3, 3, state.wait);
        break;
    case COLOR_FADE:
        if (state.colors.size() < 2)
        {
            state.colors.push_back(0xffffff);
        }
        led->colorFade(state.colors[0], state.colors[1], 100, state.wait);
        break;
    case CYLON_EYE:
        led->cylonEye(state.colors[0], 4, 3, state.wait);
        break;
    case HEARTBEAT:
        led->heartbeat(state.colors[0], 3, state.wait, 255);
        break;
    case FIRE_EFFECT:
        led->fireEffect(state.colors[0], state.wait, 1);
        break;
    case SOUND_REACTIVE:
        sv = map(analogRead(SOUND_PIN), 0, 4095, 0, 10000);
        Serial.println(sv);
        led->reactToSound(sv, state.colors, state.wait);
        break;
    default:
        break;
    }
}

class MyBLECharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();

        // Handle the received data from the central client
        state.fromJson(value);
        Serial.println("FX: " + String(state.fx));
        Serial.println("Colors: " + String(state.colors[0]));
        Serial.println("Wait: " + String(state.wait));
    }
};

void setupBLE()
{
    BLEDevice::init(BLE_DEVICE_NAME);
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(BLE_SERVICE_UUID);

    BLECharacteristic *pCharacteristic = pCharacteristic = pService->createCharacteristic(
        BLE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE);
    pCharacteristic->setCallbacks(new MyBLECharacteristicCallbacks());

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
    pAdvertising->start();
}

void setup()
{
    // Initialize the serial
    Serial.begin(BAUD_RATE);

    // Initialize the LED ring
    state = State();
    led = new Led(LED_PIN, NUM_PIXELS);

    // Initialize the sound sensor
    pinMode(SOUND_PIN, INPUT);
    pinMode(34, INPUT);

    // Initialize the BLE
    Serial.println("[BLE] starting...");
    setupBLE();
    Serial.println("[BLE] started");
}

void loop()
{
    runFX();
}
