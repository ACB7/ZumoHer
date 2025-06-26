#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <Zumo32U4.h>

class LineFollower {
public:
    // Constructor
    LineFollower();

    // Start de motoren
    void StartMotor();

    // Stop de motoren
    void StopMotor();

    // Stel de snelheid van linker- en rechtermotor in
    void SetMotorSpeed(int leftSpeed, int rightSpeed);

    // Zoek een lijn (zwart of groen)
    bool FindLine();

    // Volg de lijn (voorkeur: zwart/groen, vermijd wit)
    void FollowLine();

private:
    Zumo32U4Motors motors;
    Zumo32U4LineSensors lineSensors;

    // Sensorwaarden opslaan
    unsigned int lineSensorValues[5];

    // Detecteert of de lijn groen is
    bool isGreenDetected();

    // Detecteert of het oppervlak wit is
    bool isWhiteDetected();
};

#endif
