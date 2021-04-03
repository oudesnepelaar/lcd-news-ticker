#include <LiquidCrystal.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

ESP8266WebServer Server;
AutoConnect Portal(Server);

String payload = "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
boolean bufferDirty = false;

unsigned int widthChars = 16;
unsigned int heightChars = 2;
unsigned int displayCharIndex = 0;
unsigned int delayms = 350;

unsigned long lastReadTime = 0;
unsigned long refreshDelay = 1200000; // refresh news every 20 minutes (= 60 * 10 * 1000 ms)

LiquidCrystal lcd(13, 15, 5, 4, 0, 2);

void rootPage() {
  
  char content[] = "Hello, world!";
  Server.send(200, "text/plain", content);
}

void setup () {

  delay(1000);
  Server.on("/", rootPage);
  displayInit();
  printIdent();
}

void displayInit() {

  lcd.begin(widthChars, heightChars);
  lcd.clear();
}

void printIdent() {
  
  lcd.setCursor(0, 0);
  lcd.print("Ferrie Bank 2021");

  lcd.setCursor(0, 1);
  if (Portal.begin()) {
    lcd.print(WiFi.localIP().toString());
  } else {
    lcd.print("plz connect AP");
  }
}

void loop() {
  
  Portal.handleClient();
  readNews();
  
  if (bufferDirty) {

    bufferDirty = false;
    displayCharIndex = 0;
    
    lcd.print(payload);
  }

  advanceScroll();
  delay(delayms);
}

void advanceScroll() {

  lcd.setCursor(0, 0);
  lcd.print(payload.substring(displayCharIndex, displayCharIndex + widthChars));

  lcd.setCursor(0, 1);
  lcd.print(payload.substring(displayCharIndex + widthChars, displayCharIndex + widthChars + widthChars));

  displayCharIndex++;
  if (displayCharIndex == (payload.length() - widthChars - widthChars)) displayCharIndex = 0;
}

void readNews() {

  unsigned long diff = millis() - lastReadTime;
  if ((lastReadTime > 0) && diff < refreshDelay) return;
  
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
