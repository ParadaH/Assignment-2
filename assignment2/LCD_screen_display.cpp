#include "Arduino.h"
#include "LCD_screen_display.h"
#include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2); //Hubert's board
LiquidCrystal_I2C lcd(0x3F, 16, 2); //Vincent's board

String pressOpenMsg = "PRESS OPEN TO ENTER WASTE";
String pressCloseMsg = "PRESS CLOSE WHEN DONE";
String wasteReceivedMsg = "WASTE RECEIVED";
String containerFullMsg = "CONTAINER IS FULL";
String containerAlarm = "PROBLEM DETECTED";

void LCDInit() {
  lcd.init();
  lcd.backlight();
}

void LCDupdate(String message) {
  String line1, line2;
  checkMessageLength(message, line1, line2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void checkMessageLength(const String &input, String &line1, String &line2) {
  if (input.length() <= 16) {
    line1 = input;
    line2 = "";
  } else {
    int splitIndex = input.lastIndexOf(' ', 16);

    if (splitIndex != -1) {
      line1 = input.substring(0, splitIndex);
      line2 = input.substring(splitIndex + 1);
    } else {
      line1 = input.substring(0, 16);
      line2 = input.substring(16);
    }
  }
}

void LCDTurnOff() {
  lcd.noDisplay();
  lcd.noBacklight();
}

void LCDTurnOn() {
  lcd.display();
  lcd.backlight();
}