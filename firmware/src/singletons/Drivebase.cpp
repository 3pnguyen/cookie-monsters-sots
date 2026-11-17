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

    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);

    // analogWrite(ENA_PIN, 0);
    // analogWrite(ENB_PIN, 0);

    // imu setup
    Wire.begin(SDA_PIN, SCL_PIN);

    // if (!imu.begin()) { 
    // while (true) {delay(10);} // freezes the code if not wired correctly
    // }

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

    // analogWrite(ENA_PIN, (int)(abs(speed_percent) * 255));
    // analogWrite(ENB_PIN, (int)(abs(speed_percent) * 255));
}

void Drivebase::tankDrive(float left_speed_percent, float right_speed_percent) {
    if (abs(left_speed_percent) > 1.0) return;
    if (abs(right_speed_percent) > 1.0) return;

    digitalWrite(IN1_PIN, (left_speed_percent == abs(left_speed_percent)) ? HIGH : LOW);
    digitalWrite(IN2_PIN, (left_speed_percent == abs(left_speed_percent)) ? LOW : HIGH);

    digitalWrite(IN3_PIN, (right_speed_percent == abs(right_speed_percent)) ? HIGH : LOW);
    digitalWrite(IN4_PIN, (right_speed_percent == abs(right_speed_percent)) ? LOW : HIGH);

    // analogWrite(ENA_PIN, (int)(abs(left_speed_percent) * 255));
    // analogWrite(ENB_PIN, (int)(abs(right_speed_percent) * 255));

}

void Drivebase::steer(float steer_percent) {
    if (abs(steer_percent) > 1.0) return;

    if (steer_percent == abs(steer_percent)) { // assumes inputs 1 & 2 are left side and vice versa
        digitalWrite(IN1_PIN, HIGH); 
        digitalWrite(IN2_PIN, LOW);
        digitalWrite(IN3_PIN, LOW);
        digitalWrite(IN4_PIN, HIGH);
    } else {
        digitalWrite(IN1_PIN, LOW);
        digitalWrite(IN2_PIN, HIGH);
        digitalWrite(IN3_PIN, HIGH);
        digitalWrite(IN4_PIN, LOW);
    }

    // analogWrite(ENA_PIN, (int)(abs(steer_percent) * 255));
    // analogWrite(ENB_PIN, (int)(abs(steer_percent) * 255));
}

void Drivebase::resetHeading() {
    imu.tareNow(true);
}

void Drivebase::updateIMU() {
    if (imu.getSensorEvent()) {
        if (imu.getSensorEventID() == SENSOR_REPORTID_GYROSCOPE_CALIBRATED) {
            yaw = imu.getYaw() * 180.0 / PI;
            yawAvaliable = true;
        }
    }
}

float Drivebase::getHeading() {
    return yaw;
}

void Drivebase::turnToHeading(float targetHeading) {
    while (true) {
        float error = fmodf((yaw - targetHeading) + 180.0f, 360.0f) - 180.0f;
        float output = constrain((error / 180) * TURN_P_GAIN, -1.0, 1.0);

        steer(output);

        if (abs(error) < 0.1)
            break;
    }
    
}
