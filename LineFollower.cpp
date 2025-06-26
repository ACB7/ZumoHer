#include "LineFollower.h"

// Constructor: stel drempelwaarden in (pas aan op basis van je sensor)
LineFollower::LineFollower() {
    GreenValue = 300; // voorbeeldwaarde, aanpassen op basis van test
    BlackValue = 100; // voorbeeldwaarde
    WhiteValue = 700; // voorbeeldwaarde
    ColorValue = 0;
}

// Lees kleurensensor en sla waarde op
void LineFollower::FindColor() {
    ColorValue = readColorSensor();
}

// Retourneert kleur als string
String LineFollower::GetColor() {
    if (isGreen()) return "Green";
    if (isBlack()) return "Black";
    if (isWhite()) return "White";
    return "Unknown";
}

// Zoek een lijn door te draaien tot zwart of groen wordt gedetecteerd
void LineFollower::FindLine() {
    FindColor();
    while (!isBlack() && !isGreen()) {
        // Langzaam ronddraaien
        analogWrite(5, 80);  // rechtermotor langzaam vooruit
        analogWrite(6, 0);
        analogWrite(9, 0);   // linkermotor stilstaan
        analogWrite(10, 0);

        FindColor(); // update kleur
    }
    // Stop motors als lijn gevonden is
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}

// Volg een lijn door te reageren op sensorinput
void LineFollower::FollowLine() {
    FindColor();

    if (isBlack()) {
        // Rechtdoor
        analogWrite(5, 150);
        analogWrite(6, 0);
        analogWrite(9, 150);
        analogWrite(10, 0);
    } else if (isWhite()) {
        // Lichtjes bijsturen
        analogWrite(5, 80);  // rechtermotor iets trager
        analogWrite(6, 0);
        analogWrite(9, 120); // linkermotor sneller
        analogWrite(10, 0);
    } else if (isGreen()) {
        // Bocht of kruising – kies gedrag (bijv. stop of afslaan)
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, 0);
        analogWrite(10, 0);
    }
}

// Bepaal of kleur groen is
bool LineFollower::isGreen() {
    return ColorValue >= GreenValue - 50 && ColorValue <= GreenValue + 50;
}

// Bepaal of kleur zwart is
bool LineFollower::isBlack() {
    return ColorValue >= BlackValue - 30 && ColorValue <= BlackValue + 30;
}

// Bepaal of kleur wit is
bool LineFollower::isWhite() {
    return ColorValue >= WhiteValue - 50 && ColorValue <= WhiteValue + 50;
}

// Simuleer kleurensensor (pas aan volgens jouw hardware)
int LineFollower::readColorSensor() {
    // Vervang deze regel met echte sensor code
    return analogRead(A0);  // voorbeeld: gebruik analoge poort A0
}
// Bepaal of de huidige kleur groen is
bool LineFollower::isGreen() {
    return ColorValue >= GreenValue - 30 && ColorValue <= GreenValue + 30;
}

// Bepaal of de huidige kleur zwart is
bool LineFollower::isBlack() {
    return ColorValue >= BlackValue - 20 && ColorValue <= BlackValue + 20;
}

// Bepaal of de huidige kleur wit is
bool LineFollower::isWhite() {
    return ColorValue >= WhiteValue - 40 && ColorValue <= WhiteValue + 40;
}

// Retourneer een string met de naam van de kleur
String LineFollower::GetColor() {
    if (isGreen()) return "Green";
    if (isBlack()) return "Black";
    if (isWhite()) return "White";
    return "Unknown";
}
