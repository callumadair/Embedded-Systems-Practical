#include "OneWire.h"
#include "DallasTemperature.h"
#include <dotDevice.h>

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

const char* ssid = "NETGEAR35";
const char* password = "magicalfinch482";
const char* server = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234";

dotDevice ddev(ssid, password, server);

const char* gid = "EEGhyIgq";

float temp_in_c;

String json_str;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ddev.connect()
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  temp_in_c = sensors.getTempCByIndex(0);
  Serial.println(temp_in_c);

}
 json_str = "{
    \"device\" : \""+String(gid)+"\",
    "average": 19.4,
    "values":[ 
       {"timestamp" : 1034, "value": temp_in_c},
       {"timestamp" : 1134, "value": temp_in_c},
       {"timestamp" : 1234, "value": temp_in_c},
       {"timestamp" : 1334, "value": 19.4},
       {"timestamp" : 1434, "value": 19.5},
       {"timestamp" : 1534, "value": 19.4},
       {"timestamp" : 1634, "value": 19.2},
       {"timestamp" : 1734, "value": 19.5},
       {"timestamp" : 1834, "value": 19.4},
       {"timestamp" : 1934, "value": 19.2},
       {"timestamp" : 2034, "value": 19.5},
       {"timestamp" : 2134, "value": 19.4},
       {"timestamp" : 2234, "value": 19.2},
       {"timestamp" : 2334, "value": 19.5},
       {"timestamp" : 2434, "value": 19.4},
       {"timestamp" : 2534, "value": 19.2}
    ] 
  }"

   server_con.sendJSON(json_str); // where json_str is a String containing the command payload
  
  
