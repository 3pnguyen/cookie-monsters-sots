#include "singletons/Drivebase.h"

Drivebase& Drivebase::getInstance() {
    static Drivebase instance;
    return instance;    
}

void Drivebase::begin() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(in3Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);
    pinMode(enAPin, OUTPUT);
    pinMode(enBPin, OUTPUT);

    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);

    analogWrite(enAPin, 0);
    analogWrite(enBPin, 0);
}

void Drivebase::drive(float speed) {
    if (abs(speed) > 1.0) return;

    if (speed == abs(speed)) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        digitalWrite(in3Pin, HIGH);
        digitalWrite(in4Pin, LOW);
    } else {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in3Pin, LOW);
        digitalWrite(in4Pin, HIGH);
    }

    analogWrite(enAPin, (int)(abs(speed) * 255));
    analogWrite(enBPin, (int)(abs(speed) * 255));
}
