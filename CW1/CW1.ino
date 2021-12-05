#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

// Setup the DallasTemperature library
OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

// Binary payload layout
#pragma pack(1)
struct data_packet_struct
{
    char gid[8];
    uint16_t cmd;
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
    data_packet.cmd = 1; // Should always be "b0000000000000001"
    // data_packet.gid = ["E", "E", "G", "h", "y", "I", "g", "q"]; // Not sure if necessary (handled by strcpy)
    strcpy(data_packet.gid, gid);
    Serial.begin(115200);
    server_con.connect();
}

uint16_t floatToFixed(float input) {
  return (uint16_t)(input * (1 << 8));
}

void collectTemperatures(struct data_packet_struct *packet) {
    // Collect 16 temperatures and their respective timestamps
    unsigned long start = millis();
    unsigned long sum = 0;
    for (int i = 0; i < 32; i + 2) {
        sensors.requestTemperatures();
        packet->data[i] = start + millis();
        packet->data[i + 1] = floatToFixed(sensors.getTempCByIndex(0));
        sum += packet->data[i + 1];
    };

    // Calculate the mean average of the temperatures
    packet->average = floatToFixed(sum / 16);
}

void loop() {
    unsigned long start = millis();
    collectTemperatures(&data_packet);
    server_con.sendBIN((char *)&data_packet, sizeof(data_packet));

    Serial.print(String(data_packet.average);

    // Delay ~30s between each payload
    unsigned long end = millis();
    delay(30000 - (end - start));
}
