#ifndef __SONAR__
#define __SONAR__

#define sonar_samples 10

class Sonar {
    public:
        Sonar(int trigPin,int echoPin);
        float getDistance();
    private:
        int trigPin;
        int echoPin;
    protected:
        static const float temperature;
        static const float vs;
};

#endif