#include <Zumo32U4.h>
#include "LineFollower.h"

LineFollower lineFollower;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;

// Kalibratie-instellingen
void calibrateSensors() {
    buzzer.play("L16 cdegreg4");
    delay(1000);
    for (int i = 0; i < 80; i++) {
        if (i < 20 || i >= 60) {
            lineFollower.SetMotorSpeed(-100, 100);  // draai links
        } else {
            lineFollower.SetMotorSpeed(100, -100);  // draai rechts
        }
        lineFollower.lineSensors.calibrate();
        delay(20);
    }
    lineFollower.StopMotor();
    buzzer.play("l16 cccc");
    delay(500);
}

// Detecteer of het groen is (lage reflectie, maar niet helemaal zwart)
bool isGreen(unsigned int* values) {
    int minVal = 1023;
    for (int i = 0; i < 5; i++) {
        if (values[i] < minVal) minVal = values[i];
    }
    // Experimenteel afstellen; groen reflecteert iets meer dan zwart
    return (minVal > 100 && minVal < 300);
}

// Detecteer of het zwart is
bool isBlack(unsigned int* values) {
    int minVal = 1023;
    for (int i = 0; i < 5; i++) {
        if (values[i] < minVal) minVal = values[i];
    }
    return (minVal <= 100);  // Zwart reflecteert heel weinig
}

void setup() {
    lineFollower.lineSensors.initFiveSensors();

    Serial.begin(9600);
    Serial.println("Druk op knop A om te starten met kalibratie...");

    // Wacht op knop A
    buttonA.waitForButton();
    calibrateSensors();

    Serial.println("Wacht op lijn...");

    // Wacht tot een lijn wordt gedetecteerd
    while (!lineFollower.FindLine()) {
        delay(10);
    }

    lineFollower.StartMotor();
    Serial.println("Lijn gevonden, starten met volgen...");
}

void loop() {
    // Lees sensoren
    lineFollower.lineSensors.read(lineFollower.lineSensorValues);

    // Detecteer kleur
    bool green = isGreen(lineFollower.lineSensorValues);
    bool black = isBlack(lineFollower.lineSensorValues);

    // Wissel gedrag op basis van kleur
    if (green) {
        // Optioneel: toon iets met LED of geluid
        Serial.println("Groene lijn gedetecteerd");
    } else if (black) {
        Serial.println("Zwarte lijn gedetecteerd");
    } else {
        Serial.println("Wit! Lijn kwijt.");
    }

    // Volg lijn ongeacht kleur, maar detectie kun je gebruiken voor gedrag
    if (green || black) {
        lineFollower.FollowLine();
    } else {
        // Lijn kwijt: stop of zoek opnieuw
        lineFollower.StopMotor();
        delay(200);
        lineFollower.StartMotor();
    }

    delay(10);
}
