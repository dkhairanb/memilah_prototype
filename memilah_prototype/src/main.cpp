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
  vTaskDelay(10);
  firebase_loop();
  // delay(5000);

  if (objectDetected == true) {
    MoveStepper();
    resetObjectDetected();
  }
}

void MoveStepper() {
  // Stepper will run here
  stepper_loop();

  // Give the stepper time to complete its cycle
  // delay(10000);
}
