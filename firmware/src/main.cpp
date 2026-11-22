#include <Arduino.h>

#include "singletons/Arm.h"
#include "singletons/Drivebase.h"
#include "singletons/Shooter.h"
#include "singletons/WirelessCommunication.h"
#include "autos.h"

#define arm Arm::getInstance()
#define drivebase Drivebase::getInstance()
#define shooter Shooter::getInstance()
#define wirelessCommunication WirelessCommunication::getInstance()

void setup() {
  Serial.begin(115200);

  // drivebase bindings

  wirelessCommunication.bindUpButton([]() -> void { drivebase.gyroStraight(0.7); });
  wirelessCommunication.bindDownButton([]() -> void { drivebase.gyroStraight(-0.7); });
  wirelessCommunication.bindLeftButton([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.steer(-1.0); 
  });
  wirelessCommunication.bindRightButton([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.steer(1.0); 
  });
  wirelessCommunication.bindDefaultDrivebaseBinding([]() -> void { 
    drivebase.drivingStraight = false;
    drivebase.stop(); 
  });

  // manual shooter bindings

  wirelessCommunication.bindTriangleButton([]() -> void { shooter.shoot(0.2); });
  wirelessCommunication.bindDefaultTriangleBinding([]() -> void { shooter.shoot(0.0); });

  // manual arm bindings 
  wirelessCommunication.bindSquareButton([]() -> void { arm.closeClaw(); });
  wirelessCommunication.bindDefaultSquareBinding([]() -> void { arm.openClaw(); });

  // autos

  wirelessCommunication.bindCircleButton([]() -> void { distanceAutonomous(); });
  wirelessCommunication.bindXButton( []() -> void { accuracyAutonomous(); });

  // initialization

  wirelessCommunication.begin(); // has to be called first before other singletons >:(
  arm.begin();
  shooter.begin();
  drivebase.begin();

}

void loop() {
  drivebase.updateIMU();
  wirelessCommunication.update();

}
