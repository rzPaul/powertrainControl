#include "Motor.h"

int  Motor::getCurrentThrottle()
{
    return _currentThrottlePercent;
}

void Motor::sendMotorCommand(int throttlePercent)
{   
    _currentThrottlePercent = throttlePercent;
    int pwmValue = map(throttlePercent, 0, 100, 0, 255);
    analogWrite(DC_MOTOR_DIR_PIN, pwmValue);   
}
