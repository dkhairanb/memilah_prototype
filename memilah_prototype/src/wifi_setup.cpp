#include "wifi_setup.h"
#include <WiFiManager.h>

// void WiFiConnect(){
// WiFi.mode(WIFI_STA);
//   WiFi.begin("kayzan", "kayzan1212");
//   Serial.print("Connecting to WiFi ..");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print('.');
//     delay(1000);
//   }
//   Serial.println(WiFi.localIP());
// }

void WiFiConnect(){
  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  bool res;

  res = wm.autoConnect("AutoConnectAP", "password");

  if (!res){
    Serial.println("Failed to Connect");
    ESP.restart();
  }
  else{
    Serial.println("Connected to WiFi");;
  }



}