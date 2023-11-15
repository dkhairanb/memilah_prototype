#include <Wire.h>
#include <Arduino.h>

#include "stepper.h"
#include "ultrasonic.h"
#include "firebase_functions.h"
#include "wifi_setup.h"


//Ultrasonic variables
long duration;
float distanceCm;
float distanceInch;

static void MoveStepper(void *pvParameters);

void setup() {
  
  Serial.begin(115200);

  //WiFi Settings
  WiFiConnect();

  //Firebase Settings
  firebase_setup();

  //Stepper Settings
  stepper_setup();

  //Ultrasonic Settings
  // ultrasonic_setup();

  //Built in LED
  // pinMode(33, OUTPUT);

  xTaskCreatePinnedToCore(MoveStepper, "MoveStepper", 2048, NULL, 2, NULL, 0); 
}

void loop() {

  vTaskDelay(0);


  firebase_loop();

  // delay(5000);

 }

void MoveStepper(void *pvParameters) {

  while (1){
    
    // resetDetectionResult();
    // if(objectDetected == true){
    //   stepper_loop();
    // }
    if(objectDetected == true){
      stepper_loop();
    }

    // delay(5000);

    vTaskDelay(10);

    
  }
}




