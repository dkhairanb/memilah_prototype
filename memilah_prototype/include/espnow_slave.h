#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

// REPLACE WITH THE MAC Address of your receiver 
 static uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xC4, 0xE3, 0x28};

// Define variables to store Ultrasonic readings to be sent
extern float fillPlastic;
extern float fillPaper;
extern float fillOthers;

// Define variables to store incoming readings
extern float incomingTrashType;

// Variable to store if sending data was successful
extern String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message_receive {
    int trashType;
} struct_message_receive;

typedef struct struct_message_send{
    float levelPlastic;
    float levelPaper;
    float levelOthers;
} struct_message_send;

extern struct_message_send UltrasonicReadings;

// Create a struct_message to hold incoming sensor readings
extern struct_message_receive incomingReadings;

extern esp_now_peer_info_t peerInfo;