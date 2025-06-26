#include "Controller.h"

// PWM pinnen voor motors (moet overeenkomen met wiring uit .ino)
const int LEFT_FORWARD = 9;
const int LEFT_BACKWARD = 10;
const int RIGHT_FORWARD = 5;
const int RIGHT_BACKWARD = 6;

// Constructor: stel een startsnelheid in
Controller::Controller() {
    currentSpeed = 150;  // standaardwaarde
    pinMode(LEFT_FORWARD, OUTPUT);
    pinMode(LEFT_BACKWARD, OUTPUT);
    pinMode(RIGHT_FORWARD, OUTPUT);
    pinMode(RIGHT_BACKWARD, OUTPUT);
}

// Stel de snelheid in (binnen grenzen)
void Controller::setSpeed(int speed) {
    if (speed > maxSpeed) speed = maxSpeed;
    if (speed < minSpeed) speed = minSpeed;
    currentSpeed = speed;
}

// Laat robot vooruit rijden
void Controller::GoForward() {
    writeMotors(currentSpeed, 0, currentSpeed, 0);
}

// Laat robot achteruit rijden
void Controller::GoBack() {
    writeMotors(0, currentSpeed, 0, currentSpeed);
}

// Stop de robot
void Controller::Stop() {
    writeMotors(0, 0, 0, 0);
}

// Interne functie: stuur waardes naar de motoren
void Controller::writeMotors(int leftF, int leftB, int rightF, int rightB) {
    analogWrite(LEFT_FORWARD, leftF);
    analogWrite(LEFT_BACKWARD, leftB);
    analogWrite(RIGHT_FORWARD, rightF);
    analogWrite(RIGHT_BACKWARD, rightB);
}
