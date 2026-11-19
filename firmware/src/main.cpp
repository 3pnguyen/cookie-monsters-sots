#include <Arduino.h>

#include "singletons/Drivebase.h"
#include "singletons/Shooter.h"
#include "singletons/WirelessCommunication.h"

#define drivebase Drivebase::getInstance()
#define shooter Shooter::getInstance()
#define wirelessCommunication WirelessCommunication::getInstance()

void setup() {
  Serial.begin(115200);

  wirelessCommunication.bindUpButton([]() -> void { drivebase.gyroStraight(true); });
  wirelessCommunication.bindDownButton([]() -> void { drivebase.gyroStraight(-true); });
  wirelessCommunication.bindLeftButton([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.steer(-true); 
  });
  wirelessCommunication.bindRightButton([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.steer(true); 
  });
  wirelessCommunication.bindDefaultDrivebaseBinding([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.stop(); 
  });
  wirelessCommunication.bindCircleButton([]() -> void { shooter.shoot(1.0); });
  wirelessCommunication.bindDefaultCircleBinding([]() -> void { shooter.shoot(0.0); });

  wirelessCommunication.begin(); // has to be called first before other singletons >:(
  drivebase.begin();
  //shooter.begin(); // bricks code for some reason

}

void loop() {
  drivebase.updateIMU();
  wirelessCommunication.update();

  //shooter.shoot(0.3); // test 

}
