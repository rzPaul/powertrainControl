#include "PowertrainManager.h"

void Powertrain::s_PowertrainTask(void *pvParameters)
{
    Powertrain *manager = static_cast<Powertrain *>(pvParameters);
    const TickType_t xPowertrainFrequency = pdMS_TO_TICKS(20);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Wire.begin(SDA_PIN, SCL_PIN);
    manager->_servoDriver = Adafruit_PWMServoDriver(SERVO_DRIVER_ADDR);
    manager->_servoDriver.begin();
    manager->_servoDriver.setPWMFreq(50);
    
    manager->_Clutch->linkDrv(&(manager->_servoDriver));
    manager->_Gearbox->linkDrv(&(manager->_servoDriver));

    manager->startupSequence();


    while(1)
    {

        manager->_shiftCommand = ulTaskNotifyTake(pdTRUE, 0);

        if (manager->_shiftCommand != 0)
        {
            manager->shift(manager->_shiftCommand);            
        }

        if (manager->_targetThrottlePercent.load() >= 20)
        {
            manager->_Motor->sendMotorCommand(manager->_targetThrottlePercent.load());
        }
        else
        {
            manager->_Motor->sendMotorCommand(IDLE_THROTTLE_PERCENT);
        }

        vTaskDelayUntil(&xLastWakeTime, xPowertrainFrequency);
    }
}

Powertrain::Powertrain (Motor *motor, Clutch *clutch, Gearbox *gearbox)
{
    _Motor = motor;
    _Clutch = clutch;
    _Gearbox = gearbox;
}

void Powertrain::shift(int shiftCommand)
{
    if (shiftCommand == 1)
    {  
        _Gearbox->shiftUp();
    }
    else if (shiftCommand == 2)
    {
        _Gearbox->shiftDown();
    }

    vTaskDelay(pdMS_TO_TICKS(150));
}

void Powertrain::setTargetThrottle(int throttlePercent)
{
    _targetThrottlePercent.store(throttlePercent);
}

TaskHandle_t Powertrain::getTaskHandle()
{
    return _PowertrainTaskHandle;
}

void Powertrain::startupSequence()
{
    _Clutch->disengage();
    vTaskDelay(200);
    _Motor->sendMotorCommand(IDLE_THROTTLE_PERCENT);
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