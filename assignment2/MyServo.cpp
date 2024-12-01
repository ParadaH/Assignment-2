  #include "MyServo.h"

MyServo::MyServo(int pin) {
  this->pin = pin;
  motor.attach(pin);
  motor.write(90);
  delay(10);  //technically waiting for the servo to be on neutral position(0)
  motor.detach();
}

void MyServo::open() {
  this->setPosition(180);  // opened : 180°
}

void MyServo::close() {
  this->setPosition(90); // neutral position : 90°
}

void MyServo::empty() {
  this->setPosition(0); // empty position : 0°
}

void MyServo::setPosition(int finalPos) {

  motor.attach(pin);
  if (pos > finalPos) {  // negative movement
    for (; pos >= finalPos; pos -= 1) {
      motor.write(pos);
      delay(5); 
    }
  } else if (pos < finalPos) {  // positive movement
    for (; pos <= finalPos; pos += 1) {
      motor.write(pos);
      delay(5);
    }
  }
  motor.detach();
}

bool MyServo::checkPos(int value) {
  if (this->pos == value) {
    return true;
  }
  return false;
}