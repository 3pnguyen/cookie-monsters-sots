#pragma once

#include <Arduino.h>

// ------------------------------------ Macros ------------------------------------

#define L_EN_PIN 17
#define R_EN_PIN 5
#define LPWM_PIN 18
#define RPWM_PIN 19

// Keep shooter PWM on timer 3, separate from the arm servos on timer 0.
#define LED_CHANNEL_LPWM 14
#define LED_CHANNEL_RPWM 15

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
