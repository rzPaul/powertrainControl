#pragma once 

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include "Config.h"

constexpr int MIN_CLUTCH_POS = 0;
constexpr int MAX_CLUTCH_POS = 90; 

class Clutch
{
private:
        int _currentClutchPositionDeg;
        Adafruit_PWMServoDriver *_servoDriver;

public:
    void linkDrv(Adafruit_PWMServoDriver * driver);
    void open();
    void close();
    void setPos(int posDeg);
};

