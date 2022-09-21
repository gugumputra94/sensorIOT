#include <WiFi.h>
#include <WebSocketClient.h>
 
const char* ssid     = "Tekku";
const char* password = "poiuytrewq";
 
char path[] = "/test";
char host[] = "192.168.43.155";
int port = 5000;
 
WebSocketClient webSocketClient;
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  Serial.println(WiFi.status());
  Serial.println(WL_CONNECTED);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2500);
    Serial.print("connected");
    Serial.println(WiFi.status());
  Serial.println(WL_CONNECTED);
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  delay(5000);
 
  if (client.connect(host, port)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

 Serial.println("===========");
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
 
}
 
void loop() {
  String data;
 
  if (client.connected()) {
 
    //webSocketClient.sendData("Info to be echoed back");
 
   // webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
 
  } else {
    Serial.println("Client disconnected.");
  }
 
  delay(3000);
 
}
