#include "ErrorHandling.h"

// Constructor: neem een pointer naar de lijnsensor en initialiseer PID
ErrorHandling::ErrorHandling(LineFollower* sensor) {
    lineSensor = sensor;
    error = 0;
    lastError = 0;
    correction = 0;
    integral = 0;

    // Standaard PID-waarden (af te stemmen via setPID)
    Kp = 1.5;
    Ki = 0.0;
    Kd = 0.8;
}

// Stel PID-constanten in
void ErrorHandling::setPID(float p, float i, float d) {
    Kp = p;
    Ki = i;
    Kd = d;
}

// Bereken de foutwaarde op basis van sensoroutput
void ErrorHandling::computeError() {
    lineSensor->FindColor();         // Update sensorwaarde

    int sensorValue = lineSensor->ColorValue;  // Ruwe sensorwaarde

    // Doelwaarde: tussen zwart en wit (gemiddelde)
    int target = (lineSensor->BlackValue + lineSensor->WhiteValue) / 2;

    error = sensorValue - target;
    integral += error;
    derivative = error - lastError;

    correction = (Kp * error) + (Ki * integral) + (Kd * derivative);

    lastError = error;
}

// Retourneer de PID-correctie
int ErrorHandling::getCorrection() {
    return correction;
}
