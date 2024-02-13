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


bool objectDetectionHandled = false; 

void setTrashCategory(int trashCategory);

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
  ultrasonic_setup();
}

void loop() {

  firebase_loop();

  bool hasRun = false;

  stepper_loop();

    // Check for serial input
  if (objectDetected == true && !objectDetectionHandled)
  {
    int newTrashCategory = trashCategory;
    if (newTrashCategory >= 0)
    {
      setTrashCategory(newTrashCategory);
      Serial.print("New trashCategory set: ");
      Serial.println(newTrashCategory);
    }
   
    resetObjectDetected();

    // Set the flag to true to indicate that resetObjectDetected has been called
    objectDetectionHandled = true;
  }
  else if(objectDetected == false){
    objectDetectionHandled = false;
  }

}


