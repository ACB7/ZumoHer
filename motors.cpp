#include "motors.h"

// Constructor: zet de pinnetjes als output
Motors::Motors() {
    setupPins();
}

// Stel de snelheden in voor beide motoren
void Motors::setSpeeds(int leftSpeed, int rightSpeed) {
    setMotor(leftPWM, leftDir, leftSpeed);
    setMotor(rightPWM, rightDir, rightSpeed);
}

// Initialiseer de pinnen als output
void Motors::setupPins() {
    pinMode(leftPWM, OUTPUT);
    pinMode(leftDir, OUTPUT);
    pinMode(rightPWM, OUTPUT);
    pinMode(rightDir, OUTPUT);
}

// Zet een enkele motor aan met PWM en richting
void Motors::setMotor(uint8_t pwmPin, uint8_t dirPin, int speed) {
    bool forward = speed >= 0;
    digitalWrite(dirPin, forward ? HIGH : LOW);
    analogWrite(pwmPin, abs(speed));
}

// Definieer de globale instantie
Motors motors;