#include <Arduino.h>

#include "singletons/Drivebase.h"

#define drivebase Drivebase::getInstance()

void setup() {
  drivebase.begin();
}

void loop() {

}
