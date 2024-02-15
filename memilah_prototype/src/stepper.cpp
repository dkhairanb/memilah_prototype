#include "stepper.h"
#include <Arduino.h>
#include <AccelStepper.h>


extern int trashCategory;


unsigned long previousMillis = 0;
const long interval = 3000;

// int trashCategory = 2;
int originalPosition1 = 0;
int originalPosition2 = 0;
bool returningToOriginal = false;  // Flag to indicate if returning to original positions
void setTrashCategory(int trashCategory);

void stepper_setup()
{
  Serial.begin(115200); // Initialize serial communication

  // Set initial trashCategory
  setTrashCategory(trashCategory);

  // Set initial original positions
  originalPosition1 = stepper1.currentPosition();
  originalPosition2 = stepper2.currentPosition();
}

void setTrashCategory(int category)
{
  trashCategory = category;

  switch (trashCategory)
  {
  case 0:
    stepper1.setMaxSpeed(100.0);
    stepper1.setAcceleration(100.0);
    stepper1.moveTo(200);

    stepper2.setMaxSpeed(500.0);
    stepper2.setAcceleration(500.0);
    stepper2.moveTo(400);
    break;
  case 1:
    stepper1.setMaxSpeed(500.0);
    stepper1.setAcceleration(500.0);
    stepper1.moveTo(-400);

    stepper2.setMaxSpeed(100.0);
    stepper2.setAcceleration(100.0);
    stepper2.moveTo(-200);
    break;
  case 2:
    stepper1.setMaxSpeed(600.0);
    stepper1.setAcceleration(500.0);
    stepper1.moveTo(150);

    stepper2.setMaxSpeed(600.0);
    stepper2.setAcceleration(500.0);
    stepper2.moveTo(-150);
    break;
  default:
    break;
  }
}

bool stepper_loop()
{
  // Run both steppers
  stepper1.run();
  stepper2.run();

  // Check if both steppers have reached their target positions
  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0)
  {
    if (!returningToOriginal)
    {
      // Start the delay after both steppers have reached their targets
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval)
      {
        // Go back to the original positions
        stepper1.moveTo(originalPosition1);
        stepper2.moveTo(originalPosition2);

        // Set the flag to true
        returningToOriginal = true;

        // Record the start time of the delay
        previousMillis = currentMillis;

        // Print debugging information
        // Serial.println("Returning to original positions.");
      }
    }
    else
    {
      // Stop the steppers when they reach their original positions
      stepper1.stop();
      stepper2.stop();

      // Reset the flag to false
      returningToOriginal = false;

      // Print debugging information
      // Serial.println("Reached original positions. Stopping steppers.");
    }
  }
  return true;
}