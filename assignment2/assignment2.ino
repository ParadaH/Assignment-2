#include "LCDScreenDisplay.h"
#include "LEDLights.h"
#include "ContainerCore.h"
#include "PinConfig.h"


void setup() {
  Serial.begin(9600);
  LCDInit();
  PinInit();
  container_state = FULL;
}

void loop() {

  int pot = analogRead(0);
  int resPot = map(pot, 0, 1023, 0, 100);
  
  Serial.println(resPot);

  if (Serial.available() > 0) {

    String received = Serial.readStringUntil('\n');
    int receivedState = received.toInt();
    
    container_state = receivedState;
  }
  delay(100);

  step();
}

void step(){
  switch (container_state){
    case EMPTY:
      LCDupdate(pressOpenMsg);
      break;

    case FULL:
      LCDupdate(containerFullMsg);
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
