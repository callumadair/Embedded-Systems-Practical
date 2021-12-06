#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"
#include "esp_bt.h"

#define MILLI_TO_SECONDS 1000  /* Conversion factor for milli seconds to seconds */

// Setup the DallasTemperature library
OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

// Configuration
const char *gid = "EEGhyIgq";
const char *ssid = "Try it!";
const char *password = "N7z@5476";
const char *ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

String json_str;

void setup() {
    Serial.begin(115200);
    setCpuFrequencyMhz(80);
    sensors.setResolution(9);
}

String getTemperaturesJson() {
    float temp;
    unsigned long timestamp;
    unsigned long start = millis();

    // Collect 16 temperature readings
    float sum = 0.0;
    String vals_json = "\"values\": [ ";
    for (int i = 0; i < 16; ++i) {
        sensors.requestTemperatures();
        temp = sensors.getTempCByIndex(0);

        timestamp = millis() - start;
        if (i != 15) {
            vals_json += "{\"timestamp\" : " + String(timestamp) + ", \"value\": " + String(temp) + "}, ";
        } else {
            vals_json += "{\"timestamp\" : " + String(timestamp) + ", \"value\": " + String(temp) + "} ]}";
        }
        sum += temp;
    }

    // Calculate average temperature and finish JSON payload construction
    float average = sum / 16;
    String temp_json = "{ \"device\": \"" + String(gid) + "\", \"average\": " + String(average) + ", ";
    temp_json += vals_json;

    Serial.println(temp_json); // FIXME: DEBUG PURPOSES ONLY

    server_con.connect();
    return temp_json;
}

void loop() {
    unsigned long start = millis();
    esp_bt_controller_disable();
    server_con.sendJSON(getTemperaturesJson());
    unsigned long end = millis();

    // Delay and sleep ~30s between each payload
    unsigned long sleep_time = 28000 - (end - start);
    delay(150);
    esp_sleep_enable_timer_wakeup(sleep_time * MILLI_TO_SECONDS);
    esp_deep_sleep_start();
}
