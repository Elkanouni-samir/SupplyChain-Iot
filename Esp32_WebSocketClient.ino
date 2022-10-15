#include <WiFi.h> // ESP32 WiFi Library
#include <WebSocketsClient.h>  // WebSocket Client Library for WebSocket
#include <WebServer.h> // WebServer Library for ESP32

// Wifi Credentials
const char* ssid = "S10"; // Wifi SSID
const char* password = "yasser12"; //Wi-FI Password
WebSocketsClient webSocket; // websocket client class instance


void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for(uint32_t i = 0; i < len; i++) {
    if(i % cols == 0) { Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);}
    Serial.printf("%02X ", *src);
    src++;}
    Serial.printf("\n");}

  

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      // send message to server when Connected
      //webSocket.sendTXT("Connected");
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      delay(2000);
      // send message to server
      webSocket.sendTXT("write values here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;}}



void setup() {
  // Serial.begin(921600);
  Serial.begin(115200);

  //Serial.setDebugOutput(true);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // Connect to local WiFi
  WiFi.begin(ssid, password);
  //WiFi.disconnect();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(500);}

  Serial.printf("\n");
  Serial.printf("IP Address: ");
  Serial.println(WiFi.localIP()); // Print local IP address

  // server address, port and URL
  webSocket.begin("192.168.1.7", 3000, "/");
  // event handler
  webSocket.onEvent(webSocketEvent);
  // use HTTP Basic Authorization this is optional remove if not needed
  //webSocket.setAuthorization("user", "Password");

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

}

void loop() {
  webSocket.loop();
}
