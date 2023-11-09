#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>

#include "camera.h"

#define API_KEY "AIzaSyCjr5U8W62B2LGcdZiRl_A9FX5FEUzawRo"
#define FIREBASE_PROJECT_ID "segrebox"

#define USER_EMAIL "qwerty@gmail.com"
#define USER_PASSWORD "12345678"

#define STORAGE_BUCKET_ID "segrebox.appspot.com"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

extern String TrashType;
boolean takeNewPhoto = true;


bool taskCompleted = false;

unsigned long dataMillis = 0;

String detectionResultString;

String getPhotoPath() {
  return String("/") + WiFi.macAddress() + ".jpg";
}

String getBucketPhoto() {
  return String("/waste-detections/") + WiFi.macAddress() + ".jpg";
}

void fcsUploadCallback(FCS_UploadStatusInfo info);

void capturePhotoSaveLittleFS(void) {
  // Dispose of the first pictures because of bad quality
  camera_fb_t* fb = NULL;
  // Skip the first 3 frames (increase/decrease the number as needed).
  for (int i = 0; i < 4; i++) {
    fb = esp_camera_fb_get();
    esp_camera_fb_return(fb);
    fb = NULL;
  }

  // Turn on the flash
  pinMode(4, OUTPUT); // Built-in LED pin
  digitalWrite(4, HIGH); // Turn on the flash

  // Take a new photo
  fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  // Turn off the flash
  digitalWrite(4, LOW); // Turn off the flash
  pinMode(4, INPUT); // Release the LED pin

  // Photo file name
  String photoPath = getPhotoPath();
  Serial.printf("Picture file name: %s\n", photoPath.c_str());
  File file = LittleFS.open(photoPath.c_str(), FILE_WRITE);

  // Insert the data into the photo file
  if (!file) {
    Serial.println("Failed to open file in writing mode");
  } else {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.print("The picture has been saved in ");
    Serial.print(photoPath.c_str());
    Serial.print(" - Size: ");
    Serial.print(fb->len);
    Serial.println(" bytes");
  }
  // Close the file
  file.close();
  esp_camera_fb_return(fb);
}

void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An Error has occurred while mounting LittleFS");
    ESP.restart();
  } else {
    delay(500);
    Serial.println("LittleFS mounted successfully");
  }
}

// Function to write data to Firebase Firestore
void writeDataToFirebase() {
  // Create a FirebaseJson object to set the data you want to write
  FirebaseJson content;

  content.set("fields/detail/stringValue", "...");
  content.set("fields/detection-result/stringValue", "plastic");
  content.set("fields/event/stringValue", "uuid event");
  content.set("fields/imageUrl/stringValue", "imageurl");
  content.set("fields/location/geoPointValue/latitude", 1.486284);
  content.set("fields/location/geoPointValue/longitude", 1.5555);
  content.set("fields/name/stringValue", "nama bin");
  content.set("fields/fill-levels/mapValue/fields/other/doubleValue", 0.2);
  content.set("fields/fill-levels/mapValue/fields/paper/doubleValue", 0.3);
  content.set("fields/fill-levels/mapValue/fields/plastic/doubleValue", 0.4);

  // Specify the document path
  String documentPath = "trash-bins/" + WiFi.macAddress();

  Serial.print("Creating document... ");

  if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw()))
    Serial.printf("OK\n%s\n\n", fbdo.payload().c_str());
  else
    Serial.println(fbdo.errorReason());
}

// Function to get data from Firebase Firestore
void getDataFromFirebase() {
  String documentPath = "trash-bins/" + WiFi.macAddress();
  //String mask = "`fill-levels`";
  String mask = "`detection-result`";

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), mask.c_str())) {
    Serial.println("Data fetched successfully.");

    // Parse the JSON data using ArduinoJson
    DynamicJsonDocument doc(2048);  // Adjust the size according to your data
    DeserializationError error = deserializeJson(doc, fbdo.payload());

    if (error) {
      Serial.print("Failed to parse JSON data: ");
      Serial.println(error.c_str());
    } else {

      detectionResultString = doc["fields"]["detection-result"]["stringValue"].as<String>();
      TrashType  = doc["fields"]["detection-result"]["stringValue"].as<String>();

      Serial.println("Detection result: ");
      Serial.print(detectionResultString);
    }
  } else {
    Serial.print("Failed to fetch data: ");
    Serial.println(fbdo.errorReason());
  }
}

void updateFirestoreFieldValue(const String& documentPath, const String& fieldPath, const String& newValue) {
  // Create a FirebaseJson object to hold the data you want to update
  FirebaseJson content;

  content.clear();

  // Set the new value for the field you want to update
  content.set(fieldPath.c_str(), newValue);

  String variablesUpdated = "name";

  Serial.print("Updating document... ");

  if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw(), variablesUpdated.c_str()))
    Serial.printf("OK\n%s\n\n", fbdo.payload().c_str());
  else
    Serial.println(fbdo.errorReason());
}

void shotAndSend() {
  if (takeNewPhoto) {
    capturePhotoSaveLittleFS();
    takeNewPhoto = false;
  }
  delay(1);
  if (Firebase.ready()) {
    Serial.print("Uploading picture... ");

    if (Firebase.Storage.upload(&fbdo, STORAGE_BUCKET_ID, getPhotoPath().c_str(), mem_storage_type_flash, getBucketPhoto().c_str(), "image/jpeg", fcsUploadCallback)) {
      Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
  FirebaseJson content;

  content.set("fields/url/stringValue", "waste-detections/" + WiFi.macAddress() + ".jpg" );

  // Specify the document path
  String documentPath = "waste-detections/" + WiFi.macAddress();

  Serial.print("Creating photo document... ");

  if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw()))
    Serial.printf("OK\n%s\n\n", fbdo.payload().c_str());
  else
    Serial.println(fbdo.errorReason());

}

void firebase_setup() {

  initLittleFS();
  // Turn off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  initCamera();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the API key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign-in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long-running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Comment or pass false value when WiFi reconnection will be controlled by your code or third-party library, e.g., WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer needs to be set.
  // Large data transmission may require a larger RX buffer, otherwise connection issues or data read timeout can occur.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of the response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void firebase_loop() {
  if (Firebase.ready() && (millis() - dataMillis > 15000 || dataMillis == 0)) {
    dataMillis = millis();

    if (!taskCompleted) {
      taskCompleted = true;
      writeDataToFirebase(); // Call the write data function
    }

    if (ObjectDetected == true){ //Trigger take pic 
      shotAndSend();
      takeNewPhoto = true;
    }
    

    getDataFromFirebase(); // Call the get data function

    String documentPath = "trash-bins/" + WiFi.macAddress();
    String fieldPath = "fields/name/stringValue";
    String newValue = "asuuuuuu";

  }
}

void fcsUploadCallback(FCS_UploadStatusInfo info) {
  if (info.status == firebase_fcs_upload_status_init) {
    Serial.printf("Uploading file %s (%d) to %s\n", info.localFileName.c_str(), info.fileSize, info.remoteFileName.c_str());
  } else if (info.status == firebase_fcs_upload_status_upload) {
    Serial.printf("Uploaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
  } else if (info.status == firebase_fcs_upload_status_complete) {
    Serial.println("Upload completed\n");
    FileMetaInfo meta = fbdo.metaData();

  } else if (info.status == firebase_fcs_upload_status_error) {
    Serial.printf("Upload failed, %s\n", info.errorMsg.c_str());
  }
}