#include "OneWire.h"
#include "DallasTemperature.h"
#include "dotDevice.h"

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

const char* ssid = "Galaxy S10+00ef";
const char* password = "ConnorH01";
const char* ws = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice server_con(ssid, password, ws);

const char* gid = "EEGhyIgq";

float temp_in_c;

String json_str;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  server_con.connect();
}

String getTemperaturesJson(){
  float temps[16];
  unsigned long timestamps[16];
  //initial time = 0
  unsigned long start = millis();
  String temp_json = "{ \"device\" : \""+String(gid)+"\", \"average\": ";
  float sum = 0;
  
  for(int i = 0; i < 16; ++i) {
    sensors.requestTemperatures();
    temps[i] = sensors.getTempCByIndex(0);
    Serial.println(temps[i]);
    timestamps[i] = millis() - start;
    Serial.println(timestamps[i]);
    sum += temps[i];
  }
  float average = sum / 16;
  temp_json += ""+String(average)+", \"values\" : [ ";

  for(int j = 0; j < 15; ++j) {
    
    temp_json += "{\"timestamp\" : "+String(timestamps[j])+", \"value\" : "+String(temps[j])+" }, ";
  }
  temp_json += "{\"timestamp\" : "+String(timestamps[15])+", \"value\" : "+String(temps[15])+" ]}";
  Serial.println(temp_json);
  return temp_json;
}

void loop() {
  // put your main code here, to run repeatedly:

   json_str = "{ \"device\" : \""+String(gid)+"\", \"average\": 19.4, \"values\" : [ {\"timestamp\" : 1034, \"value\": 19.5}, {\"timestamp\" : 1134, \"value\": 19.4}, {\"timestamp\" : 1234, \"value\": 19.2}, {\"timestamp\" : 1334, \"value\": 19.4}, {\"timestamp\" : 1034, \"value\": 19.5}, {\"timestamp\" : 1134, \"value\": 19.4}, {\"timestamp\" : 1234, \"value\": 19.2}, {\"timestamp\" : 1334, \"value\": 19.4}, {\"timestamp\" : 1034, \"value\": 19.5}, {\"timestamp\" : 1134, \"value\": 19.4}, {\"timestamp\" : 1234, \"value\": 19.2}, {\"timestamp\" : 1334, \"value\": 19.4}, {\"timestamp\" : 1034, \"value\": 19.5}, {\"timestamp\" : 1134, \"value\": 19.4}, {\"timestamp\" : 1234, \"value\": 19.2}, {\"timestamp\" : 1334, \"value\": 19.4} ]}";
   //server_con.sendJSON(getTemperaturesJson());
   server_con.sendJSON(json_str); // where json_str is a String containing the command payload
   delay(3000);
}
