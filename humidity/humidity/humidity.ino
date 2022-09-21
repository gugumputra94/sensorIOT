const int refresh=3;//read every 3 seconds
boolean showSerial =true;//true or false

unsigned int unit=2;//0=C, 1=F, 2=Humidity
char *title[]={"Temperature","Temperature","Humidity"};
char *unitText[]={"&deg;C","&deg;F","%"};

#include "DHT.h"
#define DHTPIN 2 
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
float temperatureValue,temperatureFValue, humidityValue;// 
// ****** DHT settings end (Robojax.com )

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "INOSE-X";
const char *password = "lekassembuh";

WebServer server(80);


void sendTemp() {
//see video https://youtu.be/JXCcmZUmzy8
  String page = "<!DOCTYPE html>\n";
  page +="<html>\n";  
  page +="<head>\n";
  page +="<title>Robojax DHT</title>\n";
  page +="    <meta http-equiv='refresh' content='";
  page += String(refresh);// how often temperature is read
  page +="'/>\n";  

  page +="<head>\n";  
  page +="<body>\n"; 
  page +="<h1>Robojax.com DHT Code</h1>\n";    
  page +="<p style=\"font-size:50px;\">";
  page +=title[unit];
  page +="<br/>";  
  page +="<p style=\"color:red; font-size:50px;\">";
 if (DHTTYPE ==DHT11){
  page += String((int)temperatureValue);  
}else{
  page += String(temperatureValue, 1);
}

  page +=unitText[unit]; 
  page +="</p>\n</body>";  
  page +="</html>\n";  
 server.send(200,  "text/html",page);

}


void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);

}

void setup(void) {
  // Robojax.com code for ESP32 DHT11 DHT22
   dht.begin();

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Open: http://");
  Serial.print(WiFi.localIP());
  Serial.println(" to read temperature");

  if (MDNS.begin("robojaxDHT")) {
    Serial.println("MDNS responder started");
    Serial.println("or open http://robojaxDHT");
  }

  server.on("/", sendTemp);
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  //see video https://youtu.be/JXCcmZUmzy8
}


void loop(void) {
  //Robojax.com code for ESP32 DHT11 DHT22
  server.handleClient();
  temperatureValue = dht.readTemperature();// Read temperature as Celsius (the default)
  humidityValue = dht.readHumidity();// Reading humidity 
  temperatureFValue = dht.readTemperature(true);// Read temperature as Fahrenheit (isFahrenheit = true)
  if(unit ==1)
  {
   temperatureValue =temperatureFValue; //
  }else if(unit==3)
  {
    temperatureValue =humidityValue;   
  }else{
    temperatureValue =temperatureValue;
  }
  if(showSerial){
      Serial.print(title[unit]);
      Serial.print(": ");
      if (DHTTYPE ==DHT11){
     Serial.println((int)temperatureValue);  
      }else{
       Serial.print(temperatureValue,1);
      }
      
  }
  Serial.println();//just adds new line

  delay(300);// change this to larger value (1000 or more) if you don't need very often reading
  // Robojax.com code for ESP32 and DHT11 DHT22  
  //see video https://youtu.be/JXCcmZUmzy8
}
