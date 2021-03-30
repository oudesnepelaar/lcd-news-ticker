#include <LiquidCrystal.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

ESP8266WebServer Server;
AutoConnect Portal(Server);

String payload = "Welcome to the News Ticker :-) by Ferrie J Bank (c) 2021";
boolean bufferDirty = false;

unsigned long lastReadTime = 0;
unsigned long readTimeDelay = 600000; // refresh news every 10 minutes (= 60 * 10 * 1000 ms)

LiquidCrystal lcd(13, 15, 5, 4, 0, 2);

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
  
  displayInit();
}

void displayInit() {

  lcd.begin(16, 2);
  lcd.print(payload);
}


void loop() {

  Portal.handleClient();
  readNews();
  
  if (bufferDirty) {

    bufferDirty = false;
    lcd.print(payload);
  }
}

void readNews() {

  unsigned long diff = millis() - lastReadTime;
  if ((lastReadTime > 0) && diff < readTimeDelay) return;
  
  lastReadTime = millis();

  HTTPClient http;
  http.begin("http://scrapert-env-1.eba-czz2mtaz.us-east-2.elasticbeanstalk.com/mix");
  
  int httpCode = http.GET();
  if (httpCode > 0) {
    
      payload = http.getString();
      bufferDirty = true;
  }
  
  http.end();
}
