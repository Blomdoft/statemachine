#include "sensoreyes.h"

#define echoPin 10 // Echo Pin
#define trigPin D0 // Trigger Pin

const unsigned int MAX_DIST = 10000;

void SensorEyes::init() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance=0;
}

void SensorEyes::measureDistance() { // need to make all this interrupty
    long indistance = 0;
    int success = 0;
    for (int i=0; i<5; i++) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      long duration = pulseIn(echoPin, HIGH, 10000);
      if (duration>0) {
        indistance += (duration/58.2);
        success++;
      }
    }
    if (success > 0) {
      distance = indistance/success;
    } else {
      distance = 0;
    }
}

void SensorEyes::asyncHandler() {
  bool state = digitalRead(echoPin);
  if (state=HIGH) {
    Serial.println("Up");
  } else {
    Serial.println("Down");
  }
}


long SensorEyes::getDistance() {
  return distance;
}

bool SensorEyes::distanceAvailable() {
  return (distance!=0);
}
