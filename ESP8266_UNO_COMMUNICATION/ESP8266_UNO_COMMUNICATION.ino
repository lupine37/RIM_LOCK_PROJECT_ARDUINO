/*
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * Create a TCP Server on ESP8266 NodeMCU. 
 * TCP Socket Server Send Receive Demo
*/

#include <ESP8266WiFi.h>

#define SendKey 0  //Button to send data Flash BTN on NodeMCU

int port = 8888;  //Port number
WiFiServer server(port);

//Server connect to WiFi Network
const char *ssid = "MW40VD_19E7";  //Enter your wifi SSID
const char *password = "Cazp2x6U7t3A9jXg";  //Enter your wifi Password

int count=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.print(ssid);

  Serial.print("<IP address: ");
  Serial.print(WiFi.localIP()); 
  server.begin();
  
}

void loop() 
{
  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())
    {
      Serial.println("<Client Connected>");
    }
    
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read()); 
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("<Client disconnected>");    
  }
}
