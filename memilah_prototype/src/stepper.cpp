#include "stepper.h"

#include <string.h>

extern int trashCategory;

void stepper_setup() {
  
  //MODE 1: Rotate with accelaration
  stepper1.setMaxSpeed(500);
  // stepper1.setAcceleration(100);
  stepper1.setSpeed(500);

  stepper2.setMaxSpeed(500);
  // stepper2.setAcceleration(100);
  stepper2.setSpeed(500);

  // stepper1.moveTo(300);
  // stepper2.moveTo(-300);

  //MODE 2: Full rotation with no accelaration

}

void stepper_loop() {
  
  switch (trashCategory)
  {
  case 0:
    trashtype_plastic();
    Serial.println("Waste Type: Plastic");
    // delay(5000);
    break;
  case 1:
    trashtype_paper();
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
  // stepper1.run();
  // stepper2.run();

  stepper1.runSpeed();

  // if (stepper1.distanceToGo() == 0){
    
  //   stepper1.moveTo(-stepper1.currentPosition());
  //   delay(2000);
  //   stepper1.stop();
  // }

  // if (stepper2.distanceToGo() == 0){
  //   delay(2000);
  //   stepper2.moveTo(-stepper2.currentPosition());
  // }
}

void trashtype_paper() {
  // stepper1.run();
  // stepper2.run();

  stepper2.runSpeed();

  // if (stepper1.distanceToGo() == 0){
  //   delay(2000);
  //   stepper1.moveTo(-stepper1.currentPosition());
  //   // stepper1.stop();
  // }

  // if (stepper2.distanceToGo() == 0){
  //   delay(2000);
  //   stepper2.moveTo(-stepper2.currentPosition());
  // }
}

void trashtype_others() {
  // stepper1.run();
  // stepper2.run();

  stepper1.runSpeed();
  stepper2.runSpeed();

  // if (stepper1.distanceToGo() == 0){
  //   delay(2000);
  //   stepper1.moveTo(-stepper1.currentPosition());
  //   // stepper1.stop();
  // }

  // if (stepper2.distanceToGo() == 0){
  //   delay(2000);
  //   stepper2.moveTo(-stepper2.currentPosition());
  // }
}