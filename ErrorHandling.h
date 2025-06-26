#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <Arduino.h>
#include "LineFollower.h"

class ErrorHandling {
public:
    ErrorHandling(LineFollower* sensor); // Constructor met sensorreferentie

    void computeError();         // Bereken de fout (error)
    int getCorrection();         // Retourneer correctiewaarde voor sturing

    void setPID(float Kp, float Ki, float Kd); // Stel PID-constanten in

private:
    LineFollower* lineSensor;    // Pointer naar de lijnvolgsensor
    int error;                   // Huidige foutwaarde
    int lastError;               // Vorige fout
    int correction;              // PID-uitgang

    float integral;
    float derivative;

    float Kp;
    float Ki;
    float Kd;
};

#endif
