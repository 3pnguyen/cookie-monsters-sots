#pragma once

#include <Arduino.h>

// ------------------------------------ Macros ------------------------------------

#define L_EN_PIN 26 
#define R_EN_PIN 25 
#define LPWM_PIN 33
#define RPWM_PIN 32 

// --------------------------------------------------------------------------------

class Shooter {
    public:
        Shooter(const Shooter&) = delete;
        Shooter(Shooter&&) = delete;
        Shooter& operator=(const Shooter&) = delete;
        Shooter& operator=(Shooter&&) = delete;

        static Shooter& getInstance();
        
        void begin();

        void shoot(float speed);

    private:
        Shooter() = default;
        ~Shooter() = default;

};
