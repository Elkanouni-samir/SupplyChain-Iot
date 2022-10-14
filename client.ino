#include <WiFi.h> // ESP32 WiFi Library
#include <WebServer.h> // WebServer Library for ESP32
#include <WebSocketsClient.h> // WebSocket Client Library for WebSocket

// Wifi Credentials
const char* ssid = "S10"; // Wifi SSID
const char* password = "yasser12"; //Wi-FI Password
WebSocketsClient webSocket; // websocket client class instance

void setup() {
  // Connect to local WiFi
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);}
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print local IP address

  //address, port, and URL path
  webSocket.begin("192.168.1.7", 3000, "/");
  // WebSocket event handler
  webSocket.onEvent(webSocketEvent);
  // if connection failed retry every 5s
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop(); // Keep the socket alive
}



void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from websocket server");
      break;
    case WStype_CONNECTED:
      Serial.println(" Connected to url: \n");
      Serial.println(*payload);
      webSocket.sendTXT("Connected"); // send message to server when Connected
      break;
    case WStype_TEXT:
      Serial.println(" get text: \n");
      Serial.println(*payload);
      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.println(" get binary length: \n");
      Serial.println(*payload);
      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      Serial.println("Error at handling event");
      break;
      
  }
}
