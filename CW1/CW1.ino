#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

const char* ssid = "Galaxy S10+00ef";
const char* password = "ConnorH01";
const char* server = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

const char* gid = "EEGhyIgq";

float temp_in_c;

String json_str;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  server_con.connect();
}

float[] getTemperatures(){
  float temps[16];
  for(i = 0; i < 16; ++i) {
    sensors.requestTemperatures();
    temps[i] = temp_in_c = sensors.getTempCByIndex(0);
    Serial.println(temps[i]);
  }

  return temps;
}

void loop() {
  // put your main code here, to run repeatedly:

 //json_str = "{ \"device\" : \""+String(gid)+"\", \"average\": 19.4, \"values\" : [ {\"timestamp\" : 1034, \"value\": 19.5}, {\"timestamp\" : 1134, \"value\": 19.4}, {\"timestamp\" : 1234, \"value\": 19.2}, {\"timestamp\" : 1334, \"value\": 19.4} }";

   server_con.sendJSON(json_str); // where json_str is a String containing the command payload
}
