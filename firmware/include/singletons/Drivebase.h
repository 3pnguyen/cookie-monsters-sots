#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_BNO08x_Arduino_Library.h>

// ------------------------------------ Macros ------------------------------------

#define IN1_PIN 16 //placeholders
#define IN2_PIN 4 
#define IN3_PIN 27
#define IN4_PIN 14
// #define ENA_PIN 2
// #define ENB_PIN 12

#define TURN_P_GAIN 1.5
#define STRAIGHT_ADJUSTMENT_SPEED 1
#define TOLERANCE 2.0

#define SDA_PIN 21  
#define SCL_PIN 22
#define INT_PIN 23
#define RST_PIN 3
#define ADDRESS 0x4B

// --------------------------------------------------------------------------------

class Drivebase {
    public:
        Drivebase(const Drivebase&) = delete;
        Drivebase(Drivebase&&) = delete;
        Drivebase& operator=(const Drivebase&) = delete;
        Drivebase& operator=(Drivebase&&) = delete;

        static Drivebase& getInstance();
        
        void begin();
        
        void drive(float speed_percent);
        void tankDrive(float left_speed_percent, float right_speed_percent);
        void steer(float steer_percent);
        void stop();

        void resetHeading();
        void updateIMU();
        float getHeading();
        void turnToHeading(float targetHeading);
        void gyroStraight(float speed_percent);

        bool drivingStraight = false;

    private:
        Drivebase() = default;
        ~Drivebase() = default;

        BNO08x imu;
        float yaw = 0.0;
        bool yawAvaliable = false;

};
