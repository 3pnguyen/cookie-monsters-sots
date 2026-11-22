#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

// ------------------------------------ Macros ------------------------------------

#define PIVOT_SERVO_PIN 2
#define CLAW_SERVO_PIN 15
#define RACK_PINION_SERVO_PIN 4

#define CLAW_CLOSED_POSITION 25
#define CLAW_OPEN_POSITION 50

#define PUSH_TIME_MS 700
#define PIVOT_UP_TIME 2900
#define PIVOT_DOWN_TIME 1800

// --------------------------------------------------------------------------------

class Arm {
    public:
        Arm(const Arm&) = delete;
        Arm(Arm&&) = delete;
        Arm& operator=(const Arm&) = delete;
        Arm& operator=(Arm&&) = delete;

        static Arm& getInstance();
        
        void begin();

        void pivotToGrab(); 
        void pivotToLoad();
        void openClaw();
        void closeClaw(); 
        void pushOut();

    private:
        Arm() = default;
        ~Arm() = default;

        Servo pivotServo;
        Servo clawServo;
        Servo rackPinionServo;

};
