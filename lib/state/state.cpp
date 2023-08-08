#include <Adafruit_NeoPixel.h>
#include "state.h"

State::State()
{
    this->fx = OFF;
    this->colors = std::vector<uint32_t>();
    wait = 100;
}

State::State(FX fx, std::vector<uint32_t> colors, uint32_t wait)
{
    this->fx = fx;
    this->colors = colors;
    this->wait = wait;
}

void State::fromJson(std::string json)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    this->fx = (FX)doc["fx"].as<int>();

    this->colors.clear();
    JsonArray colors = doc["colors"].as<JsonArray>();
    for (JsonVariant color : colors)
    {
        this->colors.push_back(color.as<int>());
    }

    this->wait = doc["wait"].as<int>();
}

std::string State::toJson()
{
    DynamicJsonDocument doc(1024);
    doc["fx"] = this->fx;

    JsonArray colors = doc.createNestedArray("colors");
    for (uint32_t color : this->colors)
    {
        colors.add(color);
    }

    doc["wait"] = this->wait;

    std::string json;
    serializeJson(doc, json);
    return json;
}