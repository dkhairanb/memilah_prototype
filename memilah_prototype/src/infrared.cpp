#include "infrared.h"

void InfraredSensor() {

  int state = digitalRead(SENSOR_PIN);

  if (state == LOW) {
    ObjectDetected = true;
    // Serial.println("Object Detected");
    // delay(2000);
  }
  else {
    ObjectDetected = false;
    // Serial.println("Object Not Detected");
    // delay(2000);
  }

}