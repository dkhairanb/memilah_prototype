#include "stepper.h"
#include <Arduino.h>
#include <AccelStepper.h>
extern int trashCategory;

void stepper_setup() {

  switch (trashCategory)
  {
  case 0: //Plastic
    stepper1.setMaxSpeed(500);
    stepper1.setAcceleration(100);
    stepper1.moveTo(400);

    stepper2.setMaxSpeed(500);
    stepper2.setAcceleration(100);
    stepper2.moveTo(200);
    break;
  case 1: //Paper
    stepper1.setMaxSpeed(500);
    stepper1.setAcceleration(100);
    stepper1.moveTo(-200);

    stepper2.setMaxSpeed(500);
    stepper2.setAcceleration(100);
    stepper2.moveTo(-400);
    break;
  case 2: //Others
    stepper1.setMaxSpeed(500);
    stepper1.setAcceleration(100);
    stepper1.moveTo(100);

    stepper2.setMaxSpeed(500);
    stepper2.setAcceleration(100);
    stepper2.moveTo(-100);
    break;
  
  default:
    break;
  }

}

void stepper_loop() {
  
  switch (trashCategory)
  {
  case 0:
    trashtype_paper();
    
    // delay(5000);
    break;
  case 1:
    trashtype_plastic();
    Serial.println("Waste Type: Paper");
    // delay(5000);
    break;
  case 2:
    trashtype_others();
    // delay(5000);
    Serial.println("Waste Type: Others");
    break;
  
  default:
    break;
  }
}

void trashtype_plastic() {
  stepper1.run();
  stepper2.run();

  if (stepper1.distanceToGo() == 0){
    delay(2000);
    Serial.println("Waste Type: Plastic");
    stepper1.moveTo(-stepper1.currentPosition());
  }

  if (stepper2.distanceToGo() == 0){
    delay(2000);
    stepper2.moveTo(-stepper2.currentPosition());
  }
}

void trashtype_paper() {
  stepper1.run();
  stepper2.run();

  if (stepper1.distanceToGo() == 0){
    delay(2000);
    stepper1.moveTo(-stepper1.currentPosition());
  }

  if (stepper2.distanceToGo() == 0){
    delay(2000);
    stepper2.moveTo(-stepper2.currentPosition());
  }
}

void trashtype_others() {
  stepper1.run();
  stepper2.run();

  if (stepper1.distanceToGo() == 0){
    delay(2000);
    stepper1.moveTo(-stepper1.currentPosition());
  }

  if (stepper2.distanceToGo() == 0){
    delay(2000);
    stepper2.moveTo(-stepper2.currentPosition());
  }
}