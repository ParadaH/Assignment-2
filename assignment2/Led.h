#ifndef __LED__
#define __LED__

class Led {
  public:
    Led(int pin);
    switchOn();
    switchOff();
    fade();
    setFadeVelocity(int value);
  private:
    int pin;
    int fadeAmount;
    int brightness;
};

#endif
