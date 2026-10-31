#include "Telemetry.h"


void Telemetry::s_TelemetryTask(void *pvParmeters)
{
    Telemetry *manager = static_cast<Telemetry *>(pvParmeters);
    const TickType_t xTelemetryFrequency = pdMS_TO_TICKS(30);
    TickType_t xLastWakeTime = xTaskGetTickCount();


    while(1)
    {
        manager->_throttleSensorValue = analogRead(THROTTLE_POS_PIN);

        xTaskDelayUntil(&xLastWakeTime, xTelemetryFrequency);
    }
}

void Telemetry::setPowertrain(Powertrain *powertrain, TaskHandle_t powertrainTaskHandle)
{
    _Powertrain = powertrain;
    _PowertrainTaskHandle = powertrainTaskHandle;

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
        1
    );
}