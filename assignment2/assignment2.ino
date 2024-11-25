#include "LCD_screen_display.h"
#include "LED_lights.h"
#include "container_core.h"
#include "pin_config.h"

/* Temporary global variable */
int resPot = 0;

void setup() {
  Serial.begin(9600);
  LCDInit();
  PinInit();
  container_state = FULL;
}

void loop() {

  int pot = analogRead(0);
  resPot = map(pot, 0, 1023, 0, 100);
  
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
      /* Here we should empty the storage level */
      resPot = 0;
      LCDupdate(pressOpenMsg);
      break;

    case FULL:
      LCDupdate(containerFullMsg);
      sendData(resPot);

      if (resPot > 95) {
        sendData(101);
        container_state = ALARM;
      }
      break;

    case OPEN:
      break;
    
    case CLOSE:
      break;

    case ALARM:
      LCDupdate(containerAlarm);
      break;

    case SLEEP:
      break;
  }
}

void sendData(int message){
  Serial.println(message);
}