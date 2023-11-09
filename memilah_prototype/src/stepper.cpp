#include "stepper.h"
// #include "firebase_functions.h"

#include <string.h>

int trash_type = 0;
String TrashType;

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
  
  // switch (trash_type)
  // {
  // case 0:
  //   trashtype_paper();
  //   Serial.println("Waste Type: Paper");
  //   break;
  // case 1:
  //   trashtype_plastic();
  //   Serial.println("Waste Type: Plastic");
  //   break;
  // case 2:
  //   trashtype_others();
  //   Serial.println("Waste Type: Others");
  //   break;
  
  // default:
  //   break;
  // }

  if(TrashType == "Paper"){
    trashtype_paper();
    Serial.println(TrashType);
  }
  else if (TrashType == "Plastic")
  {
    // trashtype_plastic();
    trashtype_others();
  }
  else
  {
    // trashtype_others();
    // trashtype_plastic();
    trashtype_paper();
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