#pragma once

#include <Arduino.h>

class Drivebase {
    public:
        Drivebase(const Drivebase&) = delete;
        Drivebase(Drivebase&&) = delete;
        Drivebase& operator=(const Drivebase&) = delete;
        Drivebase& operator=(Drivebase&&) = delete;

        static Drivebase& getInstance();
        
        void begin();
        void drive(float speed);

    private:
        Drivebase() = default;
        ~Drivebase() = default;

        int in1Pin = 0; // placeholders
        int in2Pin = 0;
        int in3Pin = 0;
        int in4Pin = 0;
        int enAPin = 0;
        int enBPin = 0;
};
