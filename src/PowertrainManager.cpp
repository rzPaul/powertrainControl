#include "PowertrainManager.h"

void Powertrain::s_PowertrainTask(void *pvParameters)
{
    Powertrain *manager = static_cast<Powertrain *>(pvParameters);
    const TickType_t xPowertrainFrequency = pdMS_TO_TICKS(50);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Wire.begin(SDA_PIN, SCL_PIN);
    manager->_servoDriver = Adafruit_PWMServoDriver(SERVO_DRIVER_ADDR);
    manager->_servoDriver.begin();
    manager->_servoDriver.setPWMFreq(50);
    
    manager->_Clutch->linkDrv(&(manager->_servoDriver));
    manager->_Gearbox->linkDrv(&(manager->_servoDriver));


    while(1)
    {
        vTaskDelayUntil(&xLastWakeTime, xPowertrainFrequency);
    }
}

Powertrain::Powertrain (Motor *motor, Clutch *clutch, Gearbox *gearbox)
{
    _Motor = motor;
    _Clutch = clutch;
    _Gearbox = gearbox;
}

TaskHandle_t Powertrain::getTaskHandle()
{
    return _PowertrainTaskHandle;
}

void Powertrain::beginTask()
{
    xTaskCreatePinnedToCore(
        s_PowertrainTask,
        "Powertrain Task",
        4096,
        this,
        2,
        &_PowertrainTaskHandle,
        1
    );
}