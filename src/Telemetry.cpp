#include "Telemetry.h"


void Telemetry::s_TelemetryTask(void *pvParmeters)
{
    Telemetry *manager = static_cast<Telemetry *>(pvParmeters);
    const TickType_t xTelemetryFrequency = pdMS_TO_TICKS(30);
    TickType_t xLastWakeTime = xTaskGetTickCount();


    while(1)
    {
        manager->readThrottleSensor();

        manager->_Powertrain->setTargetThrottle(manager->_throttleSensorPercent);

        xTaskDelayUntil(&xLastWakeTime, xTelemetryFrequency);
    }
}

void Telemetry::setPowertrain(Powertrain *powertrain, TaskHandle_t powertrainTaskHandle)
{
    _Powertrain = powertrain;
    _PowertrainTaskHandle = powertrainTaskHandle;

}

void Telemetry::readPaddles()
{
    _isUpshiftPressed = !digitalRead(UPSHIFT_PIN);
    _isDownshiftPressed = !digitalRead(DOWNSHIFT_PIN);

    if (_isUpshiftPressed && !_lastUpshiftState)
    {
        xTaskNotify(_PowertrainTaskHandle, 1, eSetValueWithOverwrite);
    }

    if (_isDownshiftPressed && !_lastDownshiftState)
    {
        xTaskNotify(_PowertrainTaskHandle, 2, eSetValueWithOverwrite);
    }


    _lastDownshiftState = _isDownshiftPressed;
    _lastUpshiftState = _isUpshiftPressed;
}

void Telemetry::readThrottleSensor()
{
    _throttleSensorValue = analogRead(THROTTLE_POS_PIN);
    _throttleSensorPercent = map(_throttleSensorValue, 0, 4095, 0, 100);
}

int Telemetry::getThrottleSensorValue()
{
    return _throttleSensorValue;
}

void Telemetry::beginTask()
{
    xTaskCreatePinnedToCore(
        s_TelemetryTask,
        "Telemetry Task",
        2048,
        this,
        1,
        &_TelemetryTaskHandle,
        0
    );
}