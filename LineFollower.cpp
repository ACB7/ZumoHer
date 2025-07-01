#include "LineFollower.h"

// Constructor initialiseert de lijnsensoren
LineFollower::LineFollower() {
    lineSensors.initFiveSensors();
}

// Start de motoren met standaard snelheid vooruit
void LineFollower::StartMotor() {
    SetMotorSpeed(200, 200);  // Beide motoren vooruit met snelheid 200
}

bool LineFollower::isGreenDetected() {
    lineSensors.read(lineSensorValues);

    // Stel: groene lijn reflecteert meer dan zwart maar minder dan wit
    // (experimenteel testen, hier voorbeeldwaarde)
    int center = lineSensorValues[2];

    return center > 600 && center < 900;
}

// Stop de motoren volledig
void LineFollower::StopMotor() {
    motors.setSpeeds(0, 0);
}

// Stel de snelheden van linker- en rechtermotor in
void LineFollower::SetMotorSpeed(int leftSpeed, int rightSpeed) {
    motors.setSpeeds(leftSpeed, rightSpeed);
}
// Zoek naar een lijn (zwart of groen) en return true als gevonden
bool LineFollower::FindLine() {
    lineSensors.read(lineSensorValues);

    // Both black and green reflect less than white
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += lineSensorValues[i];
    }
    int average = total / 5;

    // Assume white > 800, black < 400, green 600–900 (example, calibrate as needed)
    return average < 900; // returns true for both black and green lines
}

// Volg de lijn met PID-regelaar
void LineFollower::FollowLine() {
    static int lastError = 0;
    static int integral = 0;

    // PID parameters
    const float Kp = 3.5;
    const float Ki = 0.00001;
    const float Kd = 1.5;

    // Lees lijnpositie (0 - 4000). Middenlijn is ongeveer 2000.
    int position = lineSensors.readLine(lineSensorValues);
    int error = position - 2000;

    integral += error;
    int derivative = error - lastError;

    int correction = Kp * error + Ki * integral + Kd * derivative;

    lastError = error;

    // --- Adjust speed if green is detected ---
    int baseSpeed;
    if (isGreenDetected()) {
        baseSpeed = 100;  // Slower speed on green
    } else {
        baseSpeed = 400;  // Normal speed
    }

    // Pas motor snelheden aan op basis van correctie
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    // Beperk snelheden tot [-400, 400]
    leftSpeed = constrain(leftSpeed, -400, 400);
    rightSpeed = constrain(rightSpeed, -400, 400);

    SetMotorSpeed(leftSpeed, rightSpeed);
}
