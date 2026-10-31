#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include "Config.h"


constexpr uint8_t gearAngles[4] = {0 ,45, 90, 135};

class Gearbox
{
private:
        Adafruit_PWMServoDriver *_servoDriver;      
        int _currentGear;
public:
        void linkDrv(Adafruit_PWMServoDriver * driver);
        void shiftUp();
        void shiftDown();
};

