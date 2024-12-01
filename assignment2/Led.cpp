#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
  this->brightness = 0;
  this->fadeAmount = 5;
}

Led::switchOn(){
  analogWrite(pin,HIGH);
}

Led::switchOff(){
  analogWrite(pin,LOW);
}

Led::fade() {
  analogWrite(pin, brightness);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(20);
}

Led::setFadeVelocity(int value){
  this->fadeAmount = value;
}