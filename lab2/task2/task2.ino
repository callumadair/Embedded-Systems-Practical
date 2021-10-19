#include "dotDevice.h"


const char* ssid = "VM1419400";
const char* password = "hrjx6wqJtqkh";
const char* server = "ws://ec2-52-15-138-171.us-east-2.compute.amazonaws.com:1234"; 

const char* gid = "EEGhyIgq";

dotDevice ddev(ssid, password, server);

void setup() {
    Serial.begin(115200);
    ddev.connect();

String json_str_1;
String json_str_2;
String json_str_3;
String mv_str_1;
String mv_str_2;
String size_str_1;
String size_str_2;

    delay(500);

    json_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SAY\", \"text\": \"Shut up pls!\" }";
    json_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"COLOUR\", \"colour\": \"#0317F9\" }";
    mv_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"ADJUST_XPOS\", \"dx\": 30 }";
    size_str_1 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SIZE\", \"size\": 20 }";
    //Serial.println(json_str);
    ddev.send(json_str_1);
    ddev.send(json_str_2);
    ddev.send(mv_str_1);
    ddev.send(size_str_1);

    delay(500);
    json_str_3 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"COLOUR\", \"colour\": \"#F90D03\" }";
    ddev.send(json_str_3);
    mv_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"ADJUST_XPOS\", \"dx\": -30 }";
    ddev.send(mv_str_2);
    size_str_2 = "{ \"device\" : \""+String(gid)+"\", \"cmd\" : \"SIZE\", \"size\": 10 }";
    ddev.send(size_str_2);
}

String json_str;

void loop() {

}
