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
    state = State();
    led = new Led(LED_PIN, NUM_PIXELS);

    Serial.begin(BAUD_RATE);

    Serial.println("[BLE] starting...");
    setupBLE();
    Serial.println("[BLE] started");
}

void loop()
{
    // Serial.println("Running FX...");
    // delay(200);
    // // Example
    // led->sparkle(0xFFFFFF, 5, 200);
    // led->runningLights(0xFF0000, 12, 100);
    // led->colorBounce(0x00FF00, 4, 3, 1000);
    // led->rainbow(20);
    // led->chaseTheater(0x8e44ad, 50);
    // led->randomFlicker(0x8e44ad, 5, 200);

    delay(100);
}
