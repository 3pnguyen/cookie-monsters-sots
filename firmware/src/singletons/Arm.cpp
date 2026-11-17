#include "singletons/Arm.h"

Arm& Arm::getInstance() {
    static Arm instance;
    return instance;    
}

void Arm::begin() {
    // servo configurations
    pivotServo.setPeriodHertz(50);
    clawServo.setPeriodHertz(50);

    pivotServo.attach(PIVOT_SERVO_PIN);
    clawServo.attach(CLAW_SERVO_PIN);
    
}
