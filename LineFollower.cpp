#include "LineFollower.h"

// Constructor initialiseert de lijnsensoren
LineFollower::LineFollower() {
    lineSensors.initFiveSensors();
}

// Start de motoren met standaard snelheid vooruit
void LineFollower::StartMotor() {
    SetMotorSpeed(200, 200);  // Beide motoren vooruit met snelheid 200
}

// Stop de motoren volledig
void LineFollower::StopMotor() {
    motors.setSpeeds(0, 0);
}

// Stel de snelheden van linker- en rechtermotor in
void LineFollower::SetMotorSpeed(int leftSpeed, int rightSpeed) {
    motors.setSpeeds(leftSpeed, rightSpeed);
}
// Zoek naar een lijn (zwart of groen) en return true als gevonden
bool LineFollower::FindLine() {
    lineSensors.read(lineSensorValues);

    // Gemiddelde reflectie berekenen
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += lineSensorValues[i];
    }
    int average = total / 5;

    // Stel drempel in op basis van experiment (wit is meestal > 800)
    return average < 800; // Lijn gevonden als gemiddelde lager is dan wit
}

// Volg de lijn met PID-regelaar
void LineFollower::FollowLine() {
    static int lastError = 0;
    static int integral = 0;

    // PID parameters (pas aan indien nodig)
    const float Kp = 0.2;
    const float Ki = 0.0;
    const float Kd = 5.0;

    // Lees lijnpositie (0 - 4000). Middenlijn is ongeveer 2000.
    int position = lineSensors.readLine(lineSensorValues);
    int error = position - 2000;

    integral += error;
    int derivative = error - lastError;

    int correction = Kp * error + Ki * integral + Kd * derivative;

    lastError = error;

    // Basis snelheid
    int baseSpeed = 200;

    // Pas motor snelheden aan op basis van correctie
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    // Beperk snelheden tot [-400, 400]
    leftSpeed = constrain(leftSpeed, -400, 400);
    rightSpeed = constrain(rightSpeed, -400, 400);

    SetMotorSpeed(leftSpeed, rightSpeed);
}
