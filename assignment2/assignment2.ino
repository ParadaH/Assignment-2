#include "LCDScreenDisplay.h"
#include "LEDLights.h"

String pressOpenMsg = "PRESS OPEN TO ENTER WASTE";
String pressCloseMsg = "PRESS CLOSE WHEN DONE";
String wasteReceivedMsg = "WASTE RECEIVED";

enum {EMPTY, FULL, OPEN, CLOSE, ALARM, SLEEP} state;


void setup() {
  Serial.begin(9600);
  LCDInit();
  state = EMPTY;
}

void loop() {
  step();
}

void step(){
  switch (state){
    case EMPTY:
      LCDupdate(pressOpenMsg);
      break;

    case FULL:
      break;

    case OPEN:
      break;
    
    case CLOSE:
      break;

    case ALARM:
      break;

    case SLEEP:
      break;
  }
}
