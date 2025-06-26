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

    // Volg de lijn (PID-regeling)
    void FollowLine();

    // Detecteer of een groene lijn aanwezig is
    bool isGreenDetected();

    // Lijnsensoren publiek toegankelijk voor geavanceerd gebruik
    Zumo32U4LineSensors lineSensors;

private:
    Zumo32U4Motors motors;
    unsigned int lineSensorValues[5];

    // Detectie van wit (indien nodig later te gebruiken)
    bool isWhiteDetected();
};

#endif
