# LCD screen news ticker

An LCD 1602 module is used to display news headlines, which are loaded from internet.
A NodeMCU ESP8266 12-F board drives the display, and loads the texts periodically from internet via WiFi.
AutoConnect lib delivers WiFi provisioning to connect easily to different networks.
An AWS Elastic Beanstalk Spring Boot application provides the input texts to be displayed. (see the 'scrapert' project on https://github.com/oudesnepelaar).

Parts:
 - NodeMCU ESP8266 12-F
 - .ino Sketch file to program the ESP8266
 - AutoConnect lib for ESP8266 WiFi
 - LiquidCrystal lib
 - LCD 1602 text display
 - power switch
 - micro USB connection board for power delivery
 - voltage regulator

Ferrie J Bank,
Amsterdam 21 December 2020

https://github.com/oudesnepelaar