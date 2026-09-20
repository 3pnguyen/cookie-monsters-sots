#include "singletons/Drivebase.h"

Drivebase& Drivebase::getInstance() {
    static Drivebase instance;
    return instance;    
}

void Drivebase::begin() {
    // motor controller configurations
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);
    pinMode(ENA_PIN, OUTPUT);
    pinMode(ENB_PIN, OUTPUT);

    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);

    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 0);

    // servo configurations
    MG995.setPeriodHertz(50);
    MG995.attach(SERVO_PIN);
}

void Drivebase::drive(float speed_percent) {
    if (abs(speed_percent) > 1.0) return;

    if (speed_percent == abs(speed_percent)) {
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        digitalWrite(IN3_PIN, HIGH);
        digitalWrite(IN4_PIN, LOW);
    } else {
        digitalWrite(IN1_PIN, LOW);
        digitalWrite(IN2_PIN, HIGH);
        digitalWrite(IN3_PIN, LOW);
        digitalWrite(IN4_PIN, HIGH);
    }

    analogWrite(ENA_PIN, (int)(abs(speed_percent) * 255));
    analogWrite(ENB_PIN, (int)(abs(speed_percent) * 255));
}

void Drivebase::steer(float steer_percent) {
    if (abs(steer_percent) > 1.0) return;
    float degrees = (int)((steer_percent * 90) + 90); // max angle is 180 and middle position is 90
    MG995.write(degrees);
}
