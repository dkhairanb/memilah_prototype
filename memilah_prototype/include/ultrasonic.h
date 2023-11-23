#include <Arduino.h>

const int trigPin = 25;
const int echoPin = 26;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

extern long duration;
extern float distanceCm;
extern float distanceInch;

void ultrasonic_setup();
void ultrasonic_loop();

