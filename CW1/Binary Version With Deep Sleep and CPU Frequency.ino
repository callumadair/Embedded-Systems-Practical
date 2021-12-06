#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

#define FIXED_POINT_FRACTIONAL_BITS 8
#define MILLI_TO_SECONDS 1000  /* Conversion factor for milli seconds to seconds */

// Setup the DallasTemperature library
OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

// Binary payload layout
#pragma pack(1)
struct data_packet_struct
{
    char gid[8] = {'E', 'E', 'G', 'h', 'y', 'I', 'g', 'q'};
    uint16_t cmd = 1;
    uint16_t average;
    uint16_t data[32];
} data_packet;
#pragma pop(1)

// Configuration
const char* gid = "EEGhyIgq";
const char* ssid = "Try it!";
const char* password = "N7z@5476";
const char* ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

void setup() {
    setCpuFrequencyMhz(80);
    sensors.setResolution(9);
}

// Converts a floating point number into a fixed integer
uint16_t floatToFixed(float input) {
    return (uint16_t)(input * (1 << FIXED_POINT_FRACTIONAL_BITS));
}

// Collect 16 temperatures and their respective timestamps, then calculate
// the mean average of those temperatures
void collectTemperatures(struct data_packet_struct *packet) {
    unsigned long start = millis();
    float sum = 0.0;
    for (int i = 0; i < 32; i += 2) {
        sensors.requestTemperatures();
        packet->data[i] = (uint16_t)(start + millis());
        float cur_temp = sensors.getTempCByIndex(0);
        packet->data[i + 1] = floatToFixed(cur_temp);
        sum += cur_temp;
    };

    packet->average = floatToFixed(sum / 16);
}

void loop() {
    unsigned long start = millis();
    collectTemperatures(&data_packet);
    server_con.connect();
    server_con.sendBIN((char *)&data_packet, sizeof(data_packet));

    // Delay ~30s between each payload
    unsigned long end = millis();
    unsigned long sleep_time = 29000 - (end - start);
    delay(150);
    esp_sleep_enable_timer_wakeup(sleep_time * MILLI_TO_SECONDS);
    esp_deep_sleep_start();
}