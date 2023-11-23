#include "stepper.h"
#include <Arduino.h>
#include <AccelStepper.h>
// #include "firebase_functions.h"

extern int trashCategory;
// extern bool objectDetected;


unsigned long previousMillis = 0;
const long interval = 5000;


void stepper_setup()
{

    switch (trashCategory) {
    case 0: //paper
      stepper1.setMaxSpeed(500.0);
      stepper1.setAcceleration(500.0);
      stepper1.moveTo(400);

      stepper2.setMaxSpeed(150.0);
      stepper2.setAcceleration(150.0);
      stepper2.moveTo(200);
      break;
    case 1: //plastic
      stepper1.setMaxSpeed(150.0);
      stepper1.setAcceleration(150.0);
      stepper1.moveTo(-200);

      stepper2.setMaxSpeed(500.0);
      stepper2.setAcceleration(500.0);
      stepper2.moveTo(-400);
      break;
    case 2: //others
      stepper1.setMaxSpeed(600.0);
      stepper1.setAcceleration(500.0);
      stepper1.moveTo(100);

      stepper2.setMaxSpeed(600.0);
      stepper2.setAcceleration(500.0);
      stepper2.moveTo(-100);
      break;
    default:
      break;
  }
}

// void stepper_loop()
// {
//     // Run both steppers
//     stepper1.run();
//     stepper2.run();

//     // Check if both steppers have reached their target positions
//     if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0)
//     {
//         // Start the delay after both steppers have reached their targets
//         unsigned long currentMillis = millis();
//         if (currentMillis - previousMillis >= interval)
//         {
//             // Set new destinations for both steppers
//             stepper1.moveTo(-0);
//             stepper2.moveTo(-0);

//             // Record the start time of the delay
//             previousMillis = currentMillis;

//             // objectDetected = false;

//             // resetObjectDetected();

//             // Print debugging information
//             Serial.print("Stepper1 Pos: ");
//             Serial.print(stepper1.currentPosition());
//             Serial.print(", Stepper2 Pos: ");
//             Serial.println(stepper2.currentPosition());
//         }
//     }
// }

bool stepper_loop()
{

    // Run both steppers
    stepper1.run();
    stepper2.run();

    // Check if both steppers have reached their target positions
    if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0)
    {
        // Start the delay after both steppers have reached their targets
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            // Set new destinations for both steppers
            stepper1.moveTo(-0);
            stepper2.moveTo(-0);

            // stepper1.currentPosition();

            // Record the start time of the delay
            previousMillis = currentMillis;

            // objectDetected = false;

            // resetObjectDetected();

            // Print debugging information
            Serial.print("Stepper1 Pos: ");
            Serial.print(stepper1.currentPosition());
            Serial.print(", Stepper2 Pos: ");
            Serial.println(stepper2.currentPosition());
        }
    }
    return true;
}