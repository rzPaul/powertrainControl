#pragma once

#include <Arduino.h>
#include <atomic>
#include <Adafruit_PWMServoDriver.h>
#include "Motor.h"
#include "Gearbox.h"
#include "Clutch.h"
#include "Telemetry.h"
#include "Config.h"

class Powertrain
{
private: 
    std::atomic<int> _targetThrottlePercent{0};
    Motor *_Motor = nullptr;
    Gearbox *_Gearbox = nullptr;
    Clutch *_Clutch = nullptr;

    Adafruit_PWMServoDriver _servoDriver;

    int _shiftCommand = 0; // 1 up 2 down
    bool _automaticModeOn = false;

    TaskHandle_t _PowertrainTaskHandle = nullptr;
    static void s_PowertrainTask(void *pvParameters); 
public:
    Powertrain (Motor *motor, Clutch *clutch, Gearbox *gearbox);
    void beginTask();
    void startupSequence();
    void shift(int shiftCommand);
    void setTargetThrottle(int throttlePercent);
    TaskHandle_t getTaskHandle();
};