#ifndef __MYSERVO__
#define __MYSERVO__

#include "Servo.h"
#include "Arduino.h"

class MyServo{
  public:
    MyServo(int pin);
    void open();
    void close();
    void empty();
    bool checkPos(int checkValue);
  private:
    Servo motor;
    int pin;
    int pos = 0;
    //int delta;
    void setPosition(int finalPos);
};

#endif