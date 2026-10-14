#pragma once

#include <Arduino.h>

// ------------------------------------ Macros ------------------------------------

#define EN1_PIN 26 
#define EN2_PIN 25 
#define EN3_PIN 3
#define EN4_PIN 1

#define LPWM1_PIN 33
#define RPWM1_PIN 32 
#define LPWM2_PIN 22
#define RPWM2_PIN 23

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
        void steer(float steer_percent);

    private:
        Drivebase() = default;
        ~Drivebase() = default;

};
