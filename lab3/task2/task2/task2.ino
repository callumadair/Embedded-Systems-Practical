void setup() {
    pinMode(28, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(21, OUTPUT); 
    pinMode(32, OUTPUT); 
    pinMode(33, OUTPUT); 
}


void loop() {
    digitalWrite(28, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(21, HIGH); 
    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);

    digitalWrite(28, LOW);
    digitalWrite(5, LOW);
    digitalWrite(22, LOW);
    digitalWrite(21, LOW); 
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
    
}
