#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pirPin) {
  this->pirPin = pirPin;
  pinMode(pirPin, INPUT);
}

void Pir::calibrating(int calibrationTime) {
  //give the sensor some time to calibrate
  Serial.print("Calibrating sensor... ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");
  delay(50);
}

bool Pir::detecting() {
  int detected = digitalRead(this->pirPin);
  return detected;
}