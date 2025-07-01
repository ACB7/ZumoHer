#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

// Een eenvoudige motorcontrollerklasse voor links/rechts aandrijving
class Motors {
public:
    Motors();
    void setSpeeds(int leftSpeed, int rightSpeed);

private:
    // Pas deze pinnen aan naar jouw hardwareconfiguratie
    const uint8_t leftPWM = 5;
    const uint8_t leftDir = 4;
    const uint8_t rightPWM = 6;
    const uint8_t rightDir = 7;

    void setupPins();
    void setMotor(uint8_t pwmPin, uint8_t dirPin, int speed);
};

extern Motors motors; // Globale instantie (zoals gebruikt in Controller.cpp)

#endif // MOTORS_H
