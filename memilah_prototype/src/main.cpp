#include <Wire.h>
#include <Arduino.h>

#include "infrared.h"
#include "stepper.h"
#include "ultrasonic.h"
#include "firebase_functions.h"
#include "wifi_setup.h"

//Infrared variable
bool ObjectDetected;

//Built in LED FLASH
#define FLASH_GPIO_NUM 4

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
  // firebase_setup();

  pinMode(FLASH_GPIO_NUM, OUTPUT);

  //Stepper Settings
  stepper_setup();

  //Ultrasonic Settings
  // ultrasonic_setup();

  //Infrared Settings
  pinMode(SENSOR_PIN, INPUT);

  //Built in LED
  // pinMode(33, OUTPUT);

  xTaskCreatePinnedToCore(MoveStepper, "MoveStepper", 2048, NULL, 2, NULL, 0); 
}

void loop() {

  vTaskDelay(0);

  // if(ObjectDetected == true){
  //   delay(1000);
  //   firebase_loop();
  // }
  
  // digitalWrite(FLASH_GPIO_NUM, HIGH);
  // delay(2000);
  // digitalWrite(FLASH_GPIO_NUM, LOW);
  // delay(2000);

  // if(TrashType == "Paper"){
  //     digitalWrite(33, HIGH);
  //   }else{
  //     digitalWrite(33, HIGH);
  //   }

  InfraredSensor();

  // if(ObjectDetected == true){
  //     digitalWrite(FLASH_GPIO_NUM, HIGH);
  //     Serial.println("Object detected");
  //     delay(2000);
  //   }else{
  //     digitalWrite(FLASH_GPIO_NUM, LOW);
  //     Serial.println("Object not detected");
  //     delay(2000);
  //   }
 

 }

void MoveStepper(void *pvParameters) {

  while (1){
    
    stepper_loop();

    
    vTaskDelay(10);

    
  }
}




