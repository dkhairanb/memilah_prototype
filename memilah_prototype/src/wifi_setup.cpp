#include "wifi_setup.h"

void WiFiConnect(){
WiFi.mode(WIFI_STA);
  WiFi.begin("Dhil iPhone", "12345678");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}