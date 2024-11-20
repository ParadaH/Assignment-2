/* NOTES

LCD has to display:
  # State: Open
  - PRESS CLOSE WHEN DONE
  - WASTE RECEIVED

  # State: Empty
  - PRESS OPEN TO ENTER WASTE

  # State: Full
  - CONTAINER FULL

  # State: Alarm
  - PROBLEM DETECTED

*/

#include "Arduino.h"
#include "LCDScreenDisplay.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String pressOpenMsg = "PRESS OPEN TO ENTER WASTE";
String pressCloseMsg = "PRESS CLOSE WHEN DONE";
String wasteReceivedMsg = "WASTE RECEIVED";
String containerFullMsg = "CONTAINER IS FULL";

void LCDInit(){
  lcd.init();
  lcd.backlight();
}

void LCDupdate(String message){
  String line1, line2;
  checkMessageLength(message, line1, line2);

  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);

}

void checkMessageLength(const String &input, String &line1, String &line2){
  if(input.length() <= 16){
    line1 = input;
    line2 = "";
  }
  else{
    int splitIndex = input.lastIndexOf(' ', 16);

    if(splitIndex != -1){
      line1 = input.substring(0, splitIndex);
      line2 = input.substring(splitIndex+1);
    }
    else{
      line1 = input.substring(0, 16);
      line2 = input.substring(16);
    }
  }
}