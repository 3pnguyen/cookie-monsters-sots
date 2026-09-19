#include "singletons/WirelessCommunication.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h> // preferred to be in the header but only works in the cpp file

WirelessCommunication& WirelessCommunication::getInstance() {
    static WirelessCommunication instance;
    return instance;
}

void WirelessCommunication::begin() {
    Dabble.begin("ESP32 Car");
}

void WirelessCommunication::bindJoystickX(void (*callable)(float)) {
    joystickBindingX = callable;
}

void WirelessCommunication::bindJoystickY(void (*callable)(float)) {
    joystickBindingY = callable;
}

void WirelessCommunication::update() {
    Dabble.processInput();

    float joystickInputX = GamePad.getXaxisData() / 7;
    if (joystickInputX < JOYSTICK_DEADBAND) joystickInputX = 0.0;
    if (joystickInputX > 1.0 - JOYSTICK_DEADBAND) joystickInputX = 1.0;
    if (joystickBindingX != nullptr) joystickBindingX(joystickInputX);

    float joystickInputY = GamePad.getYaxisData() / 7;
    if (joystickInputY < JOYSTICK_DEADBAND) joystickInputY = 0.0;
    if (joystickInputY > 1.0 - JOYSTICK_DEADBAND) joystickInputY = 1.0;
    if (joystickBindingY != nullptr) joystickBindingY(joystickInputY);
    
}
