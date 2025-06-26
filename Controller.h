#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Zumo32U4.h>

class Controller {
public:
    // Constructor
    Controller();

    // Vooruit bewegen met huidige snelheid
    void GoForward();

    // Achteruit bewegen met huidige snelheid
    void GoBack();

    // Maak een draai naar links of rechts (richting = "left" of "right")
    void MakeTurn(const char* direction);

    // Versnel tot maxSpeed (optioneel stapgrootte instellen)
    void Accelerate(int step = 20);

    // Vertraag tot minimaal 0 (optioneel stapgrootte instellen)
    void Decelerate(int step = 20);

    // Huidige snelheid instellen
    void SetSpeed(int speed);

    // Huidige snelheid ophalen
    int GetSpeed() const;

private:
    Zumo32U4Motors motors;
    int currentSpeed;         // Huidige snelheid van de robot
    const int maxSpeed = 400; // Maximale motorsnelheid
    const int minSpeed = 0;   // Minimale snelheid
};

#endif
