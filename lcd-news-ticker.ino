#include <LiquidCrystal.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

ESP8266WebServer Server;
AutoConnect      Portal(Server);

int const bufferSize = 8192;
char myBuffer[bufferSize] = {"Welcome to the News Ticker :-) by Ferrie J Bank (c) 2021"};
String payload;
boolean bufferDirty = false;

unsigned long lastReadTime = 0;
unsigned long readTimeDelay = 600000; // refresh news every 10 minutes

void rootPage() {
  
  char content[] = "Hello, world!";
  Server.send(200, "text/plain", content);
}

void setup () {

  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
  
//
//  displayInit();
//  
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//   
//    delay(500);
//  }
}

void displayInit() {

//  P.begin();
//  P.displayClear();
//  P.displaySuspend(false);
//  P.setIntensity(0);
//
//  P.displayScroll(myBuffer, scrollAlign, scrollEffect, scrollSpeed);
//  
//  while (!P.displayAnimate()) {yield();}
}


void loop() {

  Portal.handleClient();
  
//  readNews();
//  
//  if (bufferDirty) {
//
//    bufferDirty = false;
//
//    MAX->clear();
//    payload.toCharArray(myBuffer, bufferSize);
//    P.displayReset();
//  }
//
//  if (P.displayAnimate()) {
//    P.displayReset();
//  }
}

void readNews() {

//  unsigned long diff = millis() - lastReadTime;
//  if ((lastReadTime > 0) && diff < readTimeDelay) return;
//  
//  lastReadTime = millis();
//
//  if (WiFi.status() == WL_CONNECTED) {
//     
//    HTTPClient http;
//     
//    http.begin("http://scrapert-env-1.eba-czz2mtaz.us-east-2.elasticbeanstalk.com/mix");
//    int httpCode = http.GET();
//     
//    if (httpCode > 0) {
//       
//      payload = http.getString();
//      bufferDirty = true;
//    }
//     
//    http.end();
//  }
}
