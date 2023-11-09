#include <Wire.h>
#include <Arduino.h>
#include "WiFi.h"

#include "stepper.h"
#include "ultrasonic.h"
#include "espnow_slave.h"

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

  pinMode(FLASH_GPIO_NUM, OUTPUT);

  //Stepper Settings
  stepper_setup();

  //Ultrasonic Settings
  // ultrasonic_setup();

  xTaskCreatePinnedToCore(MoveStepper, "MoveStepper", 2048, NULL, 2, NULL, 0); 
}

void loop() {

  vTaskDelay(0);
  




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




