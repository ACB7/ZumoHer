#include <Arduino.h>
#include "LineFollower.h"
#include "Controller.h"
#include "ErrorHandling.h"

// Maak objecten aan
LineFollower lineSensor;
Controller controller;
ErrorHandling pid(&lineSensor);

// Basisloopsnelheid (aangepast voor jouw robot)
const int baseSpeed = 120;

void setup() {
  Serial.begin(9600);

  // Stel een gewenste snelheid in
  controller.setSpeed(baseSpeed);

  // Stel PID-waarden in (afhankelijk van jouw robot en testresultaten)
  pid.setPID(1.5, 0.0, 0.8);
}

void loop() {
  // Bereken fout en stuurcorrectie
  pid.computeError();
  int correction = pid.getCorrection();

  // Bereken links/rechts snelheden op basis van PID-correctie
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Beperk snelheden tot geldige PWM-waarden
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Stuur motoren individueel aan (gebruik writeMotors() alternatief)
  analogWrite(9, leftSpeed);     // LEFT_FORWARD
  analogWrite(10, 0);            // LEFT_BACKWARD
  analogWrite(5, rightSpeed);    // RIGHT_FORWARD
  analogWrite(6, 0);             // RIGHT_BACKWARD

  delay(10);  // korte delay voor stabiliteit
}
