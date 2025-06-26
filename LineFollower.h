#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <Arduino.h>

// Je kunt hier je sensor bibliotheek includen als die nodig is.
// Bijvoorbeeld: #include <ColorSensor.h>

class LineFollower {
public:
    LineFollower();         // Constructor
    void FindLine();        // Zoek naar de lijn (groen of zwart)
    void FollowLine();      // Volg de lijn
    void FindColor();       // Zoek een kleur onder de sensor
    String GetColor();      // Geeft de huidige kleur terug als string
    bool isGreen();         // True als de kleur groen is
    bool isBlack();         // True als de kleur zwart is
    bool isWhite();         // True als de kleur wit is

private:
    int ColorValue;         // Huidige waarde van de kleurmeting
    int GreenValue;         // Drempelwaarde voor groen
    int BlackValue;         // Drempelwaarde voor zwart
    int WhiteValue;         // Drempelwaarde voor wit

    int readColorSensor();  // Leest de sensorwaarde (intern gebruikt)
};

#endif
