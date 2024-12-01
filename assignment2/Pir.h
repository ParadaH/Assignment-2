#ifndef __PIR__
#define __PIR__

class Pir {
    public:
        Pir(int pirPin);
        void calibrating(int calibrationTime);
        bool detecting();
    private:
        int pirPin;
};

#endif