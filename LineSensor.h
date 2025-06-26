#ifndef ZUMO_LINE_FOLLOWER_H
#define ZUMO_LINE_FOLLOWER_H

#include <Zumo32U4Motors.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4ButtonA.h>
#include <Zumo32U4LCD.h>

class ZumoLineFollower {
public:
    ZumoLineFollower();

    void StartMotor();
    void StopMotor();
    void SetMotorSpeed(int leftSpeed, int rightSpeed);
    void FindLine();

private:
    Zumo32U4Motors motors;
    Zumo32U4LineSensors lineSensors;
    Zumo32U4ButtonA buttonA;
    Zumo32U4LCD lcd;

    uint16_t lineSensorValues[5];
    const uint16_t greenThreshold = 3000; // voorbeeldwaarde
    const uint16_t blackThreshold = 1000; // voorbeeldwaarde
    const uint16_t whiteThreshold = 500;  // voorbeeldwaarde

    void calibrateSensors();
    bool isOnLine();
    bool isOnGreen();
    bool isOnWhite();
};

#endif
