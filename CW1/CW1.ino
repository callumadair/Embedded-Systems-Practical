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
  uint16_t ts1;
  uint16_t val1;
  uint16_t ts2;
  uint16_t val2;
  uint16_t ts3;
  uint16_t val3;
  uint16_t ts4;
  uint16_t val4;
  uint16_t ts5;
  uint16_t val5;
  uint16_t ts6;
  uint16_t val6;
  uint16_t ts7;
  uint16_t val7;
  uint16_t ts8;
  uint16_t val8;
  uint16_t ts9;
  uint16_t val9;
  uint16_t ts10;
  uint16_t val10;
  uint16_t ts11;
  uint16_t val11;
  uint16_t ts12;
  uint16_t val12;
  uint16_t ts13;
  uint16_t val13;
  uint16_t ts14;
  uint16_t val14;
  uint16_t ts15;
  uint16_t val15;
} data_packet;
#pragma pop(1)

// Configuration
const char* gid = "EEGhyIgq";
const char* ssid = "Galaxy S10+00ef";
const char* password = "ConnorH01";
const char* ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

void setup() {
  data_packet.cmd = 1; // Should always be "b0000000000000001"
  strcpy(data_packet.gid, gid); 
  Serial.begin(115200);
  server_con.connect();
}

void collectTemperatures(struct data_packet_struct *pack) {
  // log start time
  unsigned long start = millis();

  // collect 16 temperatures and their respective timestamps
  // &pack.ts0 = ...

  // calculate the sum, then divide by 16 for the mean average
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
   collectTemperatures(&data_packet);
   server_con.sendBIN((char *)&data_packet, sizeof(data_packet));

   // Delay ~30s between each payload
   unsigned long end = millis();
   delay(30000 - (end - start));
}
