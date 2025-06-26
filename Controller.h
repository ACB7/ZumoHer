#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller {
public:
    Controller();               // Constructor

    void turnLeft();            // Draai naar links
    void turnRight();           // Draai naar rechts
    void setSpeed(int speed);   // Stel rijsnelheid in
    void Stop();                // Stop beide motoren
    void GoBack();              // Rijd achteruit
    void TurnLeft();            // Alternatieve schrijfwijze
    void TurnRight();           // Alternatieve schrijfwijze

private:
    int currentSpeed;           // Huidige snelheid
    const int maxSpeed = 255;   // Maximale PWM waarde
    const int minSpeed = 0;     // Minimale PWM waarde

    void applySpeed(int leftSpeed, int rightSpeed); // Helper voor motorregeling
};

#endif
