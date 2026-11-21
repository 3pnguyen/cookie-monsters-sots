#include "singletons/WirelessCommunication.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h> // preferred to be in the header but only works in the cpp file

WirelessCommunication& WirelessCommunication::getInstance() {
    static WirelessCommunication instance;
    return instance;
}

void WirelessCommunication::begin() {
    pinMode(LED_BUILTIN, OUTPUT);
    Dabble.begin("Cookie Monsters Car");
}

float WirelessCommunication::getJoystickX() {
    // normalize to one because readings go up to 7 for some reason
    float input = GamePad.getXaxisData() / 7;
    if (abs(input) < JOYSTICK_CENTER_DEADBAND) input = 0.0;
    return input;
}

float WirelessCommunication::getJoystickY() {
    // normalize to one because readings go up to 7 for some reason
    float input = GamePad.getYaxisData() / 7;
    if (abs(input) < JOYSTICK_CENTER_DEADBAND) input = 0.0;
    return input;
}

void WirelessCommunication::bindUpButton(Function callable) {
    buttonBindingUp = callable;
}

void WirelessCommunication::bindRightButton(Function callable) {
    buttonBindingRight = callable;
}

void WirelessCommunication::bindDownButton(Function callable) {
    buttonBindingDown = callable;
}

void WirelessCommunication::bindLeftButton(Function callable) {
    buttonBindingLeft = callable;
}

void WirelessCommunication::bindDefaultDrivebaseBinding(Function callable) {
    defaultDrivebaseBinding = callable;
}

void WirelessCommunication::bindTriangleButton(Function callable) {
    buttonBindingTriangle = callable;
} 

void WirelessCommunication::bindDefaultTriangleBinding(Function callable) {
    defaultBindingTriangle = callable;
}

void WirelessCommunication::bindCircleButton(Function callable) {
    buttonBindingCircle = callable;
}

void WirelessCommunication::bindDefaultCircleBinding(Function callable) {
    defaultBindingCircle = callable;
}

void WirelessCommunication::bindXButton(Function callable) {
    buttonBindingX = callable;
}

void WirelessCommunication::bindDefaultXBinding(Function callable) {
    defaultBindingX = callable;
}

void WirelessCommunication::bindSquareButton(Function callable) {
    buttonBindingSquare = callable;
} 

void WirelessCommunication::bindDefaultSquareBinding(Function callable) {
    defaultBindingSquare = callable;
}

void WirelessCommunication::update() {
    Dabble.processInput();

    if (buttonBindingUp != nullptr && GamePad.isUpPressed())
        buttonBindingUp();

    if (buttonBindingRight != nullptr && GamePad.isRightPressed())
        buttonBindingRight();

    if (buttonBindingDown != nullptr && GamePad.isDownPressed())
        buttonBindingDown();

    if (buttonBindingLeft != nullptr && GamePad.isLeftPressed())
        buttonBindingLeft();

    if (
        !GamePad.isUpPressed() && 
        !GamePad.isRightPressed() &&
        !GamePad.isDownPressed() &&
        !GamePad.isLeftPressed() &&
        defaultDrivebaseBinding != nullptr
    )
        defaultDrivebaseBinding();

    if (buttonBindingTriangle != nullptr && GamePad.isTrianglePressed()) 
        buttonBindingTriangle();
    else if (defaultBindingTriangle != nullptr)
        defaultBindingTriangle();

    if (buttonBindingCircle != nullptr && GamePad.isCirclePressed()) 
        buttonBindingCircle();
    else if (defaultBindingCircle != nullptr)
        defaultBindingCircle();

    if (buttonBindingX != nullptr && GamePad.isCrossPressed()) 
        buttonBindingX();
    else if (defaultBindingX != nullptr)
        defaultBindingX();

    if (buttonBindingSquare != nullptr && GamePad.isSquarePressed()) 
        buttonBindingSquare();
    else if (defaultBindingSquare != nullptr)
        defaultBindingSquare();

    // built-in LED

    if (
        GamePad.isUpPressed() ||
        GamePad.isRightPressed() ||
        GamePad.isDownPressed() ||
        GamePad.isLeftPressed() ||
        GamePad.isTrianglePressed() ||
        GamePad.isCirclePressed() ||
        GamePad.isCrossPressed() ||
        GamePad.isSquarePressed()
    )
        digitalWrite(LED_BUILTIN, HIGH);
    else
        digitalWrite(LED_BUILTIN, LOW);

}
