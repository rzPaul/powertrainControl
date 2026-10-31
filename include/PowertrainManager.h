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
    std::atomic<int> _targetThrottle{0};
    Motor *_Motor = nullptr;
    Gearbox *_Gearbox = nullptr;
    Clutch *_Clutch = nullptr;

    Adafruit_PWMServoDriver _servoDriver;

    TaskHandle_t _PowertrainTaskHandle = nullptr;
    static void s_PowertrainTask(void *pvParameters); 
public:
    Powertrain (Motor *motor, Clutch *clutch, Gearbox *gearbox);
    void beginTask();
    TaskHandle_t getTaskHandle();
};