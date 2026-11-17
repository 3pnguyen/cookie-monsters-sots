#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

// ------------------------------------ Macros ------------------------------------

#define PIVOT_SERVO_PIN 0 
#define CLAW_SERVO_PIN 0

// --------------------------------------------------------------------------------

class Arm {
    public:
        Arm(const Arm&) = delete;
        Arm(Arm&&) = delete;
        Arm& operator=(const Arm&) = delete;
        Arm& operator=(Arm&&) = delete;

        static Arm& getInstance();
        
        void begin();

    private:
        Arm() = default;
        ~Arm() = default;

        Servo pivotServo;
        Servo clawServo;

};
