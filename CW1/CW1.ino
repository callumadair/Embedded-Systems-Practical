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
  char gid[8]; // GID (8) 0-7
  uint16_t cmd; // Command (2) 8-9
  uint16_t average; // Average (2) 9-11
  // timestampX (2) valueX (2) (from 0 to 15) 11-75
  uint16_t ts0;
  uint16_t val0;
} data_packet;
#pragma pop(1)

// Configuration
const char* gid = "EEGhyIgq";
const char* ssid = "Galaxy S10+00ef";
const char* password = "ConnorH01";
const char* ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

float temp_in_c;
String json_str;

void setup() {
  Serial.begin(115200);
  server_con.connect();
}

String getTemperaturesJson() {
  
  float temps[16];
  unsigned long timestamps[16];
  unsigned long start = millis();

  // Initialise the JSON payload
  String temp_json = "{ \"device\": \""+String(gid)+"\", \"average\": ";

  // Collect 16 temperature readings
  float sum = 0.0;
  for(int i = 0; i < 16; ++i) {
    sensors.requestTemperatures();
    temps[i] = sensors.getTempCByIndex(0);
    timestamps[i] = millis() - start;
    sum += temps[i];
  }
  
  // Calculate average temperature and finish JSON payload construction
  float average = sum / 16;
  temp_json += ""+String(average)+", \"values\": [ ";
  for(int j = 0; j < 15; ++j) {
    temp_json += "{\"timestamp\" : "+String(timestamps[j])+", \"value\": "+String(temps[j])+"}, ";
  }
  temp_json += "{\"timestamp\" : "+String(timestamps[15])+", \"value\": "+String(temps[15])+"} ]}";
  
  Serial.println(temp_json); // FIXME: DEBUG PURPOSES ONLY
  return temp_json;
}

void loop() {
   unsigned long start = millis();
   server_con.sendBIN((char *)&data_packet, sizeof(data_packet));

   // Delay ~30s between each payload
   unsigned long end = millis();
   delay(30000 - (end - start));
}
