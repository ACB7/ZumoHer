#include "Controller.h"
#include "LineFollower.h"

// Constructor initialiseert motorsnelheid
Controller::Controller() : currentSpeed(200) {}

// Vooruit bewegen als lijn recht is
void Controller::GoForward() {
    LineFollower lf;

    if (lf.FindLine()) {
        // Zet snelheid op basis van lijnkleur
        if (lf.isGreenDetected()) {
            SetSpeed(150);  // langzamer bij groen
        } else {
            SetSpeed(300);  // sneller bij zwart
        }

        // Lees lijnpositie
        unsigned int sensorValues[5];
        int position = lf.lineSensors.readLine(sensorValues);

        // Recht vooruit als de lijn gecentreerd is
        if (position > 1800 && position < 2200) {
            motors.setSpeeds(currentSpeed, currentSpeed);
        } else {
            lf.FollowLine();  // bochten → PID
        }
    } else {
        GoBack();  // lijn kwijt
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
// Huidige snelheid ophalen
int Controller::GetSpeed() const {
    return currentSpeed;
}

// Huidige snelheid instellen (geclamped tussen min en max)
void Controller::SetSpeed(int speed) {
    currentSpeed = constrain(speed, minSpeed, maxSpeed);
}

// Verhoog snelheid stapgewijs
void Controller::Accelerate(int step) {
    SetSpeed(currentSpeed + step);
}

// Verlaag snelheid stapgewijs
void Controller::Decelerate(int step) {
    SetSpeed(currentSpeed - step);
}
