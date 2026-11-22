#include "autos.h"

#define arm Arm::getInstance()
#define drivebase Drivebase::getInstance() // do not put in header file or else duplicate macros will conflict
#define shooter Shooter::getInstance()

const float shooterSpeedForAccuracy = 0.3; // speed of the shooter for the distance challange

void driveForTime(int timeMs, float speed) {
    unsigned long startTime = millis();

    while (true) {
        drivebase.updateIMU();

        unsigned long elapsedTime = millis() - startTime;
        drivebase.gyroStraight(speed);

        if (elapsedTime > timeMs) {
            drivebase.stop();
            break;
        }
    } 

}

void distanceAutonomous(float shooterSpeed) {
    drivebase.drivingStraight = false;
    driveForTime(3200, 0.7);
    delay(1000);
    arm.pivotToGrab();
    delay(1000);
    arm.closeClaw();
    delay(1000);
    arm.pivotToLoad();
    driveForTime(2000, -0.7);
    drivebase.turnToHeading(180, false);
    shooter.shoot(shooterSpeed);
    delay(2000); // charge up shooter
    arm.pushOut();
    delay(4000);
    shooter.shoot(0.0);

}

void accuracyAutonomous() {
    distanceAutonomous(shooterSpeedForAccuracy);
}
