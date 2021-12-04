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

unsigned long sum;
unsigned long average;

dotDevice server_con(ssid, password, ws);

void setup() {
  data_packet.cmd = 1; // Should always be "b0000000000000001"
  data_packet.gid = ["E", "E", "G", "h", "y", "I", "g", "q"];
  strcpy(data_packet.gid, gid); 
  Serial.begin(115200);
  server_con.connect();
}

void collectTemperatures(struct data_packet_struct *pack) {
  sum = 0;
  average = 0;
  // log start time
  unsigned long start = millis();
  // collect 16 temperatures and their respective timestamps
  // &pack.ts0 = ...
  sensors.requestTemperatures();
  data_packet.ts0 = start + millis();
  data_packet.val0 = sensors.getTempCByIndex(0);
  sum += data_packet.val0

  data_packet.ts1 = start + millis();
  sensors.requestTemperatures();
  data_packet.val1 = sensors.getTempCByIndex(0);
  sum += data_packet.val1

  data_packet.ts2 = start + millis();
  sensors.requestTemperatures();
  data_packet.val2 = sensors.getTempCByIndex(0);
  sum += data_packet.val2

  data_packet.ts3 = start + millis();
  sensors.requestTemperatures();
  data_packet.val3 = sensors.getTempCByIndex(0);
  sum += data_packet.val3

  data_packet.ts4 = start + millis();
  sensors.requestTemperatures();
  data_packet.val4 = sensors.getTempCByIndex(0);
  sum += data_packet.val4

  data_packet.ts5 = start + millis();
  sensors.requestTemperatures();
  data_packet.val5 = sensors.getTempCByIndex(0);
  sum += data_packet.val5

  data_packet.ts6 = start + millis();
  sensors.requestTemperatures();
  data_packet.val6 = sensors.getTempCByIndex(0);
  sum += data_packet.val6

  data_packet.ts7 = start + millis();
  sensors.requestTemperatures();
  data_packet.val7 = sensors.getTempCByIndex(0);
  sum += data_packet.val7

  data_packet.ts8 = start + millis();
  sensors.requestTemperatures();
  data_packet.val8 = sensors.getTempCByIndex(0);
  sum += data_packet.val8

  data_packet.ts9 = start + millis();
  sensors.requestTemperatures();
  data_packet.val9 = sensors.getTempCByIndex(0);
  sum += data_packet.val9

  data_packet.ts10 = start + millis();
  sensors.requestTemperatures();
  data_packet.val10 = sensors.getTempCByIndex(0);
  sum += data_packet.val10

  data_packet.ts11 = start + millis();
  sensors.requestTemperatures();
  data_packet.val11 = sensors.getTempCByIndex(0);
  sum += data_packet.val11

  data_packet.tS12 = start + millis();
  sensors.requestTemperatures();
  data_packet.val12 = sensors.getTempCByIndex(0);
  sum += data_packet.val12

  data_packet.ts13 = start + millis();
  sensors.requestTemperatures();
  data_packet.val13 = sensors.getTempCByIndex(0);
  sum += data_packet.val13

  data_packet.ts14 = start + millis();
  sensors.requestTemperatures();
  data_packet.val14 = sensors.getTempCByIndex(0);
  sum += data_packet.val14

  data_packet.ts15 = start + millis();
  sensors.requestTemperatures();
  data_packet.val15 = sensors.getTempCByIndex(0);
  sum += data_packet.val15
  // calculate the sum, then divide by 16 for the mean average
  average = sum/16;
}

void loop() {
   unsigned long start = millis();
   collectTemperatures(&data_packet);
   server_con.sendBIN((char *)&data_packet, sizeof(data_packet));

   // Delay ~30s between each payload
   unsigned long end = millis();
   delay(30000 - (end - start));
}
