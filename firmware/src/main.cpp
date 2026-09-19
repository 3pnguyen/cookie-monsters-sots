#include <Arduino.h>

#include "singletons/Drivebase.h"
#include "singletons/WirelessCommunication.h"

#define drivebase Drivebase::getInstance()
#define wirelessCommunication WirelessCommunication::getInstance()

void setup() {
  drivebase.begin();

  wirelessCommunication.bindJoystickY([](float speed) -> void {
    drivebase.drive(speed);
  });
  wirelessCommunication.begin();
}

void loop() {
  wirelessCommunication.update();
}
