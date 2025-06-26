#include <Arduino.h>
#include "LineFollower.h"
#include "Controller.h"

LineFollower lineFollower;
Controller controller;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    // Initialiseer sensoren en motoren
    lineFollower.lineSensors.initFiveSensors();
    lineFollower.StartMotor();

    Serial.println("Zumo32U4 Line Follower gestart");
}

void loop() {
    // Gebruik de controller om vooruit te gaan, met automatische lijncontrole
    controller.GoForward();

    // Kleine delay voor stabiliteit
    delay(50);
}
