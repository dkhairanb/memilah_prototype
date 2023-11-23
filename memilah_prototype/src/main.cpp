#include <Wire.h>
#include <Arduino.h>

#include "stepper.h"
#include "ultrasonic.h"
#include "firebase_functions.h"
#include "wifi_setup.h"

// Ultrasonic variables
long duration;
float distanceCm;
float distanceInch;

void MoveStepper();

void setup() {
  Serial.begin(115200);

  // WiFi Settings
  WiFiConnect();

  // Firebase Settings
  firebase_setup();

  // Stepper Settings
  stepper_setup();

  // Ultrasonic Settings
  // ultrasonic_setup();
}

void loop() {

  firebase_loop();
  // delay(5000);
  bool hasRun = false;

  while (objectDetected == true) {
    hasRun = stepper_loop();
    // delay(6000);
    if(hasRun){
      // delay(5000);
      break;
    }
    // delay(6000);
    // resetObjectDetected();
  }
    // resetObjectDetected();

}


