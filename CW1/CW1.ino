#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

const char* ssid = "Galaxy S10+00ef";
const char* password = "ConnorH01";
const char* ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, server);

const char* gid = "EEGhyIgq";

float temp_in_c;

String json_str;

dotDevice server_con(ssid, password, ws);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  server_con.connect();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  temp_in_c = sensors.getTempCByIndex(0);
  Serial.println(temp_in_c);

 json_str = "{ \"device\" : \""+String(gid)+"\", \"average\": 19.4, \"values\" : [ {\"timestamp\" : 1034, \"value\": 19.5}] }";

   server_con.sendJSON(json_str); // where json_str is a String containing the command payload
}
