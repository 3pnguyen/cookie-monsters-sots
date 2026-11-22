#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_BNO08x_Arduino_Library.h>

// ------------------------------------ Macros ------------------------------------

#define IN1_PIN 26 //placeholders
#define IN2_PIN 12 
#define IN3_PIN 27
#define IN4_PIN 14
#define ENA_PIN 25
#define ENB_PIN 33

#define LED_CHANNEL_ENA 12
#define LED_CHANNEL_ENB 13

#define TURN_P_GAIN 111 // basically full speed all the time 
#define STRAIGHT_ADJUSTMENT_SPEED 0.7
#define TOLERANCE 2.5

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
        void pivotSteer(float steer_percent);
        void stop();

        void resetHeading();
        void updateIMU();
        float getHeading();
        void turnToHeading(float targetHeading, bool usePivotSteer);
        void gyroStraight(float speed_percent);

        bool drivingStraight = false;

    private:
        Drivebase() = default;
        ~Drivebase() = default;

        BNO08x imu;
        float yaw = 0.0;
        bool yawAvaliable = false;

};
