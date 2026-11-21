#include "singletons/Shooter.h"

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
    int leftPwmChannel, 
    int rightPwmChannel, 
    float percent
) {
    int pwm = percentToPwm(percent);

    if (pwm == 0) {
        ledcWrite(leftPwmChannel, 0);
        ledcWrite(rightPwmChannel, 0);
        digitalWrite(leftEnablePin, LOW);
        digitalWrite(rightEnablePin, LOW);
        return;
    }

    digitalWrite(leftEnablePin, HIGH);
    digitalWrite(rightEnablePin, HIGH);

    if (percent > 0.0F) {
        ledcWrite(leftPwmChannel, 0);
        ledcWrite(rightPwmChannel, pwm);
    } else {
        ledcWrite(leftPwmChannel, pwm);
        ledcWrite(rightPwmChannel, 0);
    }
}

} // namespace

Shooter& Shooter::getInstance() {
    static Shooter instance;
    return instance;    
}

void Shooter::begin() {
    // motor controller configurations
    pinMode(L_EN_PIN, OUTPUT);
    pinMode(R_EN_PIN, OUTPUT);

    digitalWrite(L_EN_PIN, LOW);
    digitalWrite(R_EN_PIN, LOW);

    ledcSetup(LED_CHANNEL_LPWM, 5000, 8);
    ledcAttachPin(LPWM_PIN, LED_CHANNEL_LPWM);
    ledcWrite(LED_CHANNEL_LPWM, 0);

    ledcSetup(LED_CHANNEL_RPWM, 5000, 8);
    ledcAttachPin(RPWM_PIN, LED_CHANNEL_RPWM);
    ledcWrite(LED_CHANNEL_RPWM, 0);


}

void Shooter::shoot(float speed_percent) {
    if (abs(speed_percent) > 1.0) return;

    setMotor(L_EN_PIN, R_EN_PIN, LED_CHANNEL_LPWM, LED_CHANNEL_RPWM, speed_percent);

}
