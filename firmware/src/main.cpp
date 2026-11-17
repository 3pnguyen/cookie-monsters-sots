#include <Arduino.h>

#include "singletons/Drivebase.h"
#include "singletons/Shooter.h"
#include "singletons/WirelessCommunication.h"

#define drivebase Drivebase::getInstance()
#define shooter Shooter::getInstance()
#define wirelessCommunication WirelessCommunication::getInstance()

void setup() {
  Serial.begin(115200);

  wirelessCommunication.bindUpButton([]() -> void { drivebase.drive(true); });
  wirelessCommunication.bindDownButton([]() -> void { drivebase.drive(-true); });
  wirelessCommunication.bindLeftButton([]() -> void { drivebase.steer(-true); });
  wirelessCommunication.bindRightButton([]() -> void { drivebase.steer(true); });

  wirelessCommunication.begin(); // has to be called first before other singletons >:(

  drivebase.begin();
  //shooter.begin();

}

void loop() {
  //drivebase.updateIMU();
  wirelessCommunication.update();

}
