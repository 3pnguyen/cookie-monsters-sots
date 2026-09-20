#pragma once

// ------------------------------------ Macros ------------------------------------

#define JOYSTICK_CENTER_DEADBAND 0.1f // in percent, applied to both top and bottom

// --------------------------------------------------------------------------------

class WirelessCommunication {
    public:
        WirelessCommunication(const WirelessCommunication&) = delete;
        WirelessCommunication(WirelessCommunication&&) = delete;
        WirelessCommunication& operator=(const WirelessCommunication&) = delete;
        WirelessCommunication& operator=(WirelessCommunication&&) = delete;

        static WirelessCommunication& getInstance();

        void begin();

        void bindJoystickX(void (*callable)(float));
        void bindJoystickY(void (*callable)(float));
        void update();

    private:
        WirelessCommunication() = default;
        ~WirelessCommunication() = default;

        void (*joystickBindingX)(float);
        void (*joystickBindingY)(float);
    
};
