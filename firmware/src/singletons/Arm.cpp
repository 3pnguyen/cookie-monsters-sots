// continuous servo reference:
// 0. Full speed clockwise.
// 1 to 89. Variable speed clockwise (closer to 90 is slower).
// 90. Stop (neutral point).
// 91 to 179. Variable speed counterclockwise (closer to 90 is slower).
// 180. Full speed counterclockwise.

#include "singletons/Arm.h"

Arm& Arm::getInstance() {
    static Arm instance;
    return instance;    
}

void Arm::begin() {
    // servo configurations
    pivotServo.setPeriodHertz(50);
    clawServo.setPeriodHertz(50);
    rackPinionServo.setPeriodHertz(50);

    pivotServo.attach(PIVOT_SERVO_PIN);
    clawServo.attach(CLAW_SERVO_PIN);
    rackPinionServo.attach(RACK_PINION_SERVO_PIN);
    
}

void Arm::pivotToGrab() {
    if (!pivotServo.attached()) {
        pivotServo.attach(PIVOT_SERVO_PIN);
    }

    pivotServo.write(45); // servo clockwise goes down
    delay(PIVOT_DOWN_TIME);

    pivotServo.write(90);
    pivotServo.detach();

}

void Arm::pivotToLoad() {
    if (!pivotServo.attached()) {
        pivotServo.attach(PIVOT_SERVO_PIN);
    }

    pivotServo.write(135); // servo counterclockwise goes up
    delay(PIVOT_UP_TIME);

    pivotServo.write(90);
    pivotServo.detach();
}

void Arm::openClaw() {
    clawServo.write(CLAW_OPEN_POSITION);
}

void Arm::closeClaw() {
    clawServo.write(CLAW_CLOSED_POSITION);
}

void Arm::pushOut() {
    if (!rackPinionServo.attached()) {
        rackPinionServo.attach(RACK_PINION_SERVO_PIN);
    }

    rackPinionServo.write(45); // assumes clockwise is out and vice versa
    delay(PUSH_TIME_MS);
    rackPinionServo.write(135);
    delay(PUSH_TIME_MS);

    rackPinionServo.write(90);
    rackPinionServo.detach();

}
