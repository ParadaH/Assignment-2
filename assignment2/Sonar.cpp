#include "Sonar.h"
#include "Arduino.h"

const float Sonar::temperature = 20;
const float Sonar::vs = 331.45 + 0.62*temperature;

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin,INPUT);
}

// float Sonar::getDistance(){
//     /* Triggering stage: sending the impulse */

//     digitalWrite(this->trigPin,LOW);
//     delayMicroseconds(3);
//     digitalWrite(this->trigPin,HIGH);
//     delayMicroseconds(10);
//     digitalWrite(this->trigPin,LOW);
    
//     /* Receiving the echo */

//     float tUS = pulseIn(this->echoPin, HIGH);
//     float t = tUS / 1000.0 / 1000.0 / 2;
//     float d = t*vs;
//     return d;
// };

float Sonar::getDistance(){
  float d = 0;
  float total_distance = 0;
  float tUS = 0;

  for (int i = 0; i < sonar_samples; i++){
    /* Triggering stage: sending the impulse */
    digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin,LOW);
  
    /* Receiving the echo */
    tUS = pulseIn(this->echoPin, HIGH);
    d = 0.017*tUS;
  
    if (d > 18){
      d = 20;
    }
    else if (d < 7){
      d = 0;
    }
    total_distance += d;
    delay(50); //short sampling delay
  }

    d = 100 - (total_distance/sonar_samples * 5);
    return d;
};
