#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller {
public:
    Controller();               // Constructor

    void turnLeft();            // Draai naar links
    void turnRight();           // Draai naar rechts
    void TurnLeft();            // Alternatieve versie (bijv. langzame draai)
    void TurnRight();           // Alternatieve versie (bijv. scherpe draai)

    void GoForward();           // Vooruit rijden
    void GoBack();              // Achteruit rijden
    void setSpeed(int speed);  // Stel snelheid in (binnen limieten)
    void Stop();                // Stop de motoren

private:
    int currentSpeed;          // Huidige snelheid
    const int maxSpeed = 255;  // Maximale PWM waarde
    const int minSpeed = 60;   // Minimale bruikbare PWM waarde

    void writeMotors(int leftForward, int leftBackward, int rightForward, int rightBackward);
};

#endif
