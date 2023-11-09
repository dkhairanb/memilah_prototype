#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

// REPLACE WITH THE MAC Address of your receiver 
static uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xC4, 0xE3, 0x28};

// Define variables to store Ultrasonic readings to be sent
 float fillPlastic;
 float fillPaper;
 float fillOthers;

// Define variables to store incoming readings
 int incomingTrashType;

// Variable to store if sending data was successful
 String success;

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

 struct_message_send UltrasonicReadings;

// Create a struct_message to hold incoming sensor readings
 struct_message_receive incomingReadings;

 esp_now_peer_info_t peerInfo;

void espnow_slave_setup();
void espnow_slave_loop();

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingTrashType = incomingReadings.trashType;
}
 
void espnow_slave_setup() {
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void espnow_slave_loop() {

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &UltrasonicReadings, sizeof(UltrasonicReadings));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(10000);
}



