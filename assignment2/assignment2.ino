#include "Sonar.h"
#include "Pir.h"
#include "MyServo.h"
#include "Led.h"
#include "LCD_screen_display.h"
#include <avr/sleep.h>

//Pin & Const
#define SONAR_TRIGPIN 8
#define SONAR_ECHOPIN 7
#define PIR_PIN 2
#define SERVO_PIN 4
#define CALIBRATION_TIME 3  //sec
#define EMPTY_BTN 5
#define TMP36_PIN A0

#define RED_PIN 11
#define GREEN_PIN 10
#define OPEN_BTN 13
#define CLOSE_BTN 12

#define T3 15000                 // 15 seconds -> before standby (SLEEP MODE)
#define T2 4000                  // 4 seconds -> Timer for the opening counter (OPEN)
#define STANDBY_TIMEOUT_MS 5000  // 3 seconds -> for the empty routine (EMPTY)

#define THRESHOLD_MAXWASTE 0.3
#define TEMP_THRESHOLD 20

//Objects
Sonar* wasteDetector;
Pir* pir;
MyServo* door;
Led* greenL;
Led* redL;

//Variables needed
#define EMPTY 101
#define FULL 102
#define OPEN 103
#define CLOSE 104
#define ALARM 105
#define SLEEP 106
#define IDLE 107

#define garbage_limit 97
// enum State { IDLE,
//              OPEN,
//              CLOSE,
//              FULL,
//              ALARM,
//              SLEEP,
//              EMPTY } state;
unsigned long lastMotionTime;
unsigned long openTimer;
unsigned long emptyTimerStart;
bool open;
unsigned long openInterval;

int full_flag = 0;
int alarm_flag = 0;
int idle_flag = 0;
int state;

void setup() {
  Serial.begin(9600);
  wasteDetector = new Sonar(SONAR_TRIGPIN, SONAR_ECHOPIN);
  pir = new Pir(PIR_PIN);
  door = new MyServo(SERVO_PIN);
  greenL = new Led(GREEN_PIN);
  redL = new Led(RED_PIN);
  pir->calibrating(CALIBRATION_TIME);
  LCDInit();
  LCDupdate(pressOpenMsg);
  state = IDLE;
}

void loop() {

  float temperature = readTemperature();
  // Serial.println(temperature);

  if (temperature > TEMP_THRESHOLD && state != ALARM) {
    state = ALARM;
    LCDupdate(containerAlarm);
    door->close();
  }
  switch (state) {
    case IDLE:
      {
        if (Serial.available() > 0) {
          String received = Serial.readStringUntil('\n');
          int receivedState = received.toInt();

          if (receivedState == 101) {
            state = receivedState;
          }
          delay(100);
        }

        full_flag = 0;
        alarm_flag = 0;
        if (idle_flag == 0) {
          log(state);
          LCDupdate(pressOpenMsg);
          greenL->switchOn();
          idle_flag = 1;
        }

        bool detected = pir->detecting();
        if (detected) {
          resetMotionTimer();
        }
        bool isOpenButtonPressed = digitalRead(OPEN_BTN);
        if (isOpenButtonPressed) {
          state = OPEN;
          LCDupdate(pressCloseMsg);
        }
        if (millis() - lastMotionTime > T3) {
          state = SLEEP;
        }
        break;
      }

    case OPEN:
      {
        log(state);
        door->open();
        openTimer = millis();
        state = CLOSE;
        break;
      }

    case CLOSE:
      {

        bool isClosedButtonPressed = digitalRead(CLOSE_BTN);
        if (isClosedButtonPressed || millis() - openTimer >= T2) {
          log(state);
          door->close();
          LCDupdate(wasteReceivedMsg);

          float garbage_bin_level = wasteDetector->getDistance();
          log((int)garbage_bin_level);

          if (garbage_bin_level > garbage_limit) {
            state = FULL;
            LCDupdate(containerFullMsg);
          } else {
            returnToIdle();
            LCDupdate(wasteReceivedMsg);
          }

          resetMotionTimer();
          delay(2000);
        }
        break;
      }

    case EMPTY:
      {
        if (millis() - emptyTimerStart >= STANDBY_TIMEOUT_MS) {
          log(EMPTY);
          door->close();
          returnToIdle();
          resetMotionTimer();

          float garbage_bin_level = wasteDetector->getDistance();
          log((int)garbage_bin_level);

          if (garbage_bin_level > garbage_limit) {
            state = FULL;
            LCDupdate(containerFullMsg);
          } else {
            returnToIdle();
            LCDupdate(wasteReceivedMsg);
          }

          resetMotionTimer();
          delay(2000);
        }
        break;
      }

    case FULL:
      {
        if (full_flag == 0) {
          log(state);
          greenL->switchOff();
          redL->switchOn();
          full_flag = 1;
        }

        if (Serial.available() > 0) {
          String received = Serial.readStringUntil('\n');
          int receivedState = received.toInt();

          if (receivedState == 101) {
            state = EMPTY;
            door->empty();
          }
          delay(100);
        }
        break;
      }

    case ALARM:
      {
        if (alarm_flag == 0) {
          log(state);
          redL->switchOn();
          greenL->switchOff();
          alarm_flag = 1;
        }

        if (Serial.available() > 0) {
          String received = Serial.readStringUntil('\n');
          int receivedState = received.toInt();

          if (receivedState == 107) {
            redL->switchOff();
            greenL->switchOn();
            returnToIdle();
            resetMotionTimer();
          }
          delay(100);
        }
        break;
      }

    case SLEEP:
      log(state);
      goingToSleep();
      returnToIdle();
      resetMotionTimer();
      break;

    default:
      returnToIdle();
      break;
  }
}

float readTemperature() {
  int sensorValue = analogRead(TMP36_PIN);
  float voltage = (sensorValue / 1024) * 5.0;
  return (voltage - .5) * 100.0;
}

void wakeUp() {}

void resetMotionTimer() {
  lastMotionTime = millis();
}

void log(int message) {
  Serial.println(message);
}

void goingToSleep() {
  LCDTurnOff();
  greenL->switchOff();
  redL->switchOff();
  Serial.flush();
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, CHANGE);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  delay(100);  //debounce
  LCDTurnOn();
  LCDupdate(pressOpenMsg);
  detachInterrupt(digitalPinToInterrupt(PIR_PIN));
}

void returnToIdle() {
  state = IDLE;
  idle_flag = 0;
}