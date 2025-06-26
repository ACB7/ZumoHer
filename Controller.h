#include "Controller.h"

// Constructor: stel standaard snelheid in
Controller::Controller() {
    currentSpeed = 150; // Standaardsnelheid
    pinMode(5, OUTPUT);  // Rechtermotor vooruit
    pinMode(6, OUTPUT);  // Rechtermotor achteruit
    pinMode(9, OUTPUT);  // Linkermotor vooruit
    pinMode(10, OUTPUT); // Linkermotor achteruit
}

// Stel snelheid in, begrensd door min/max
void Controller::setSpeed(int speed) {
    if (speed > maxSpeed) {
        currentSpeed = maxSpeed;
    } else if (speed < minSpeed) {
        currentSpeed = minSpeed;
    } else {
        currentSpeed = speed;
    }
}

// Rijd vooruit met huidige snelheid
void Controller::GoForward() {
    writeMotors(currentSpeed, 0, currentSpeed, 0);
}

// Rijd achteruit met huidige snelheid
void Controller::GoBack() {
    writeMotors(0, currentSpeed, 0, currentSpeed);
}

// Stop beide motoren
void Controller::Stop() {
    writeMotors(0, 0, 0, 0);
}

// Interne functie om PWM naar motoren te schrijven
void Controller::writeMotors(int leftForward, int leftBackward, int rightForward, int rightBackward) {
    analogWrite(9, leftForward);    // Linkermotor vooruit
    analogWrite(10, leftBackward);  // Linkermotor achteruit
    analogWrite(5, rightForward);   // Rechtermotor vooruit
    analogWrite(6, rightBackward);  // Rechtermotor achteruit
}
