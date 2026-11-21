#pragma once

#include <Arduino.h>
#include "singletons/Arm.h"
#include "singletons/Drivebase.h"
#include "singletons/Shooter.h"

void distanceAutonomous(float shooterSpeed = 1.0);

void accuracyAutonomous();
