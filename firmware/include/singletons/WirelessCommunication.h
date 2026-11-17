#pragma once

// ------------------------------------ Macros ------------------------------------

#define JOYSTICK_CENTER_DEADBAND 0.1f // in percent, applied to both top and bottom

// --------------------------------------------------------------------------------

using Function = void(*)(); 

class WirelessCommunication {
    public:
        WirelessCommunication(const WirelessCommunication&) = delete;
        WirelessCommunication(WirelessCommunication&&) = delete;
        WirelessCommunication& operator=(const WirelessCommunication&) = delete;
        WirelessCommunication& operator=(WirelessCommunication&&) = delete;

        static WirelessCommunication& getInstance();

        void begin();

        float getJoystickX();
        float getJoystickY();

        void bindUpButton(Function callable);
        void bindRightButton(Function callable);
        void bindDownButton(Function callable);
        void bindLeftButton(Function callable);
        void bindTriangleButton(Function callable); 
        void bindCircleButton(Function callable);
        void bindXButton(Function callable);
        void bindSquareButton(Function callable); 

        void update();

    private:
        WirelessCommunication() = default;
        ~WirelessCommunication() = default;

        Function buttonBindingUp = nullptr;
        Function buttonBindingRight = nullptr;
        Function buttonBindingDown = nullptr;
        Function buttonBindingLeft = nullptr;
        Function buttonBindingTriangle = nullptr;
        Function buttonBindingCircle = nullptr;
        Function buttonBindingX = nullptr;
        Function buttonBindingSquare = nullptr;
    
};
