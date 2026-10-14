#include "singletons/Drivebase.h"

namespace {

constexpr int kPwmMax = 255;

int percentToPwm(float percent) {
    return static_cast<int>(abs(percent) * kPwmMax);
}

// A BTS760 uses L_EN/R_EN solely to enable its H-bridge.  Direction is
// selected by driving exactly one of LPWM/RPWM; driving both PWM inputs is
// not a valid direction command.
void setMotor(
    int leftEnablePin, 
    int rightEnablePin, 
    int leftPwmPin, 
    int rightPwmPin, 
    float percent
) {
    const int pwm = percentToPwm(percent);

    if (pwm == 0) {
        analogWrite(leftPwmPin, 0);
        analogWrite(rightPwmPin, 0);
        digitalWrite(leftEnablePin, LOW);
        digitalWrite(rightEnablePin, LOW);
        return;
    }

    digitalWrite(leftEnablePin, HIGH);
    digitalWrite(rightEnablePin, HIGH);

    if (percent > 0.0F) {
        analogWrite(leftPwmPin, 0);
        analogWrite(rightPwmPin, pwm);
    } else {
        analogWrite(leftPwmPin, pwm);
        analogWrite(rightPwmPin, 0);
    }
}

} // namespace

Drivebase& Drivebase::getInstance() {
    static Drivebase instance;
    return instance;    
}

void Drivebase::begin() {
    // motor controller configurations
    pinMode(EN1_PIN, OUTPUT);
    pinMode(EN2_PIN, OUTPUT);
    pinMode(EN3_PIN, OUTPUT);
    pinMode(EN4_PIN, OUTPUT);
    pinMode(LPWM1_PIN, OUTPUT);
    pinMode(RPWM1_PIN, OUTPUT);
    pinMode(LPWM2_PIN, OUTPUT);
    pinMode(RPWM2_PIN, OUTPUT);

    digitalWrite(EN1_PIN, LOW);
    digitalWrite(EN2_PIN, LOW);
    digitalWrite(EN3_PIN, LOW);
    digitalWrite(EN4_PIN, LOW);

    analogWrite(LPWM1_PIN, 0);
    analogWrite(RPWM1_PIN, 0);
    analogWrite(LPWM2_PIN, 0);
    analogWrite(RPWM2_PIN, 0);
}

void Drivebase::drive(float speed_percent) {
    if (abs(speed_percent) > 1.0) return;

    setMotor(EN1_PIN, EN2_PIN, LPWM1_PIN, RPWM1_PIN, speed_percent);
    setMotor(EN3_PIN, EN4_PIN, LPWM2_PIN, RPWM2_PIN, speed_percent);
}

void Drivebase::steer(float steer_percent) {
    if (abs(steer_percent) > 1.0) return;

    setMotor(EN1_PIN, EN2_PIN, LPWM1_PIN, RPWM1_PIN, steer_percent);
    setMotor(EN3_PIN, EN4_PIN, LPWM2_PIN, RPWM2_PIN, -steer_percent);
}
