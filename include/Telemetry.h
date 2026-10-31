#pragma once

#include <Arduino.h>
#include "Config.h"
#include "PowertrainManager.h"

class Telemetry
{
private:
    int _throttleSensorValue;
    bool _isUpshiftPressed = false;
    bool _isDownshiftPressed = false;

    Powertrain *_Powertrain = nullptr;

    TaskHandle_t _TelemetryTaskHandle = nullptr;
    TaskHandle_t _PowertrainTaskHandle = nullptr;
    
    static void s_TelemetryTask(void *pvParameters);

public:
    void setPowertrain(Powertrain *powertrain, TaskHandle_t powertrainTaskHandle);
    int getThrottleSensorValue();
    void beginTask();
};