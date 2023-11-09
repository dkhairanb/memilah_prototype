#include <Arduino.h>
#include <AccelStepper.h>

#define step1 12
#define dir1 14

#define step2 19
#define dir2 18

static AccelStepper stepper1(1, step1, dir1);
static AccelStepper stepper2(1, step2, dir2);

// extern int trash_type;

void stepper_setup();
void stepper_loop();

void trashtype_plastic();
void trashtype_paper();
void trashtype_others();

