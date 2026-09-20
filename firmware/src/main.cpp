#include <Arduino.h>

#include "singletons/Drivebase.h"
#include "singletons/WirelessCommunication.h"

#define drivebase Drivebase::getInstance()
#define wirelessCommunication WirelessCommunication::getInstance()

void setup() {
  Serial.begin(115200);
  
  drivebase.begin();

  wirelessCommunication.bindJoystickY([](float speed_percent) -> void {
    drivebase.drive(speed_percent);
  });
  wirelessCommunication.bindJoystickX([](float steer_percent) -> void {
    drivebase.steer(steer_percent);
  });
  wirelessCommunication.begin();
}

void loop() {
  wirelessCommunication.update();
}
