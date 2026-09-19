#pragma once

#include <Arduino.h>

// ------------------------------------ Macros ------------------------------------

#define IN1_PIN 0 //placeholders
#define IN2_PIN 0
#define IN3_PIN 0 
#define IN4_PIN 0
#define ENA_PIN 0
#define ENB_PIN 0 

// --------------------------------------------------------------------------------

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

};
