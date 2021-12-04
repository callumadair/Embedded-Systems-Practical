#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

// Setup the DallasTemperature library
OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

// Configuration
const char* gid = "EEGhyIgq";
const char* ssid = "Callum's iPhone";
const char* password = "data parasite";
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
  float temp;
  unsigned long timestamp;
  unsigned long start = millis();

  // Initialise the JSON payload
  String temp_json = "{ \"device\": \""+String(gid)+"\", \"average\": ";

  // Collect 16 temperature readings
  float sum = 0.0;
  String vals_json = "\"values\": [ ";
  for(int i = 0; i < 16; ++i) {
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    timestamp = millis() - start;
    if(i != 15) {
      vals_json += "{\"timestamp\" : "+String(timestamp)+", \"value\": "+String(temp)+"}, ";
    } else {
      vals_json += "{\"timestamp\" : "+String(timestamp)+", \"value\": "+String(temp)+"} ]}";
    }
    sum += temp;
  }
  
  // Calculate average temperature and finish JSON payload construction
  float average = sum / 16;
  temp_json += ""+String(average)+", ";
  temp_json += vals_json;
  
  Serial.println(temp_json); // FIXME: DEBUG PURPOSES ONLY
  return temp_json;
}

void loop() {
   unsigned long start = millis();
   server_con.sendJSON(getTemperaturesJson());

   // Delay ~30s between each payload
   unsigned long end = millis();
   delay(30000 - (end - start));
}
