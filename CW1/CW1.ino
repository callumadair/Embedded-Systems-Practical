OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

float temp_in_c;

dotDevice server_con(ssid, password, ws);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  temp_in_c = sensors.getTempCByIndex(0);

  json_str = "{
    "device": "wibble00",
    "average": 19.4,
    "values":[ 
       {"timestamp" : 1034, "value": 19.5},
       {"timestamp" : 1134, "value": 19.4},
       {"timestamp" : 1234, "value": 19.2},
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
  
}
