#include "Controller.h"
#include "LineFollower.h"

// Constructor initialiseert motorsnelheid
Controller::Controller() : currentSpeed(200) {}

// Vooruit bewegen als lijn recht is
void Controller::GoForward() {
    LineFollower lf;

    // Lijn gevonden?
    if (lf.FindLine()) {
        // Lees de sensorpositie
        unsigned int sensorValues[5];
        int position = lf.lineSensors.readLine(sensorValues);

        // Controleer of de lijn recht ligt (tussen 1800 - 2200)
        if (position > 1800 && position < 2200) {
            motors.setSpeeds(currentSpeed, currentSpeed); // recht vooruit
        } else {
            // Als lijn wel aanwezig is maar niet recht: laat LineFollower het overnemen
            lf.FollowLine();
        }
    } else {
        // Lijn kwijt: achteruit gaan tot lijn weer gevonden is
        GoBack();
    }
}

// Achteruit bewegen tot lijn weer gevonden is
void Controller::GoBack() {
    LineFollower lf;

    while (!lf.FindLine()) {
        motors.setSpeeds(-currentSpeed, -currentSpeed);  // achteruit
        delay(100);  // korte stapjes
    }

    // Zodra de lijn teruggevonden is, stop kort en hervat
    motors.setSpeeds(0, 0);
    delay(100);
}

// Maak een draai naar links of rechts
void Controller::MakeTurn(const char* direction) {
    int turnSpeed = currentSpeed;

    if (strcmp(direction, "left") == 0) {
        motors.setSpeeds(-turnSpeed, turnSpeed); // draai naar links
    } else if (strcmp(direction, "right") == 0) {
        motors.setSpeeds(turnSpeed, -turnSpeed); // draai naar rechts
    } else {
        motors.setSpeeds(0, 0); // ongeldige input
    }

    delay(300); // draai even en dan stoppen
    motors.setSpeeds(0, 0);
}
