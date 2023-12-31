#include "dotDevice.h"


const char* ssid = "VM1419400";
const char* password = "hrjx6wqJtqkh";
const char* server = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234"; 

const char* gid = "EEGhyIgq";

dotDevice ddev(ssid, password, server);

String halt_json;
String timer_json;
String val_json;
String load_json;
String json_str_1;
String json_str_2;
String json_str_3;
String mv_str_1;
String mv_str_2;
String size_str_1;
String size_str_2;
String run_json;

void setup() {
    Serial.begin(115200);
    ddev.connect();

    halt_json = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"HALT\" }";
    ddev.send(halt_json);

    timer_json = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"TIMER_CFG\" }";
    val_json = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"TIMER_VAL\", \"value\":500 }";
    load_json = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"LOAD\" }";

    ddev.send(timer_json);
    ddev.send(val_json);
    ddev.send(load_json);

    json_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SAY\", \"text\": \"Shut up pls!\" }";
    json_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"COLOUR\", \"colour\": \"#0317F9\" }";
    mv_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"ADJUST_XPOS\", \"dx\": 30 }";
    size_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SIZE\", \"size\": 20 }";

    ddev.send(json_str_1);
    ddev.send(json_str_2);
    ddev.send(mv_str_1);
    ddev.send(size_str_1);

    
    json_str_3 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"COLOUR\", \"colour\": \"#F90D03\" }";
    mv_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"ADJUST_XPOS\", \"dx\": -30 }";
    size_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SIZE\", \"size\": 10 }";
    ddev.send(json_str_3);
    ddev.send(mv_str_2);
    ddev.send(size_str_2);
    
    run_json = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"RUN\" }";
    ddev.send(run_json);
}


void loop() {

}
