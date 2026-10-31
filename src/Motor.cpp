#include "Motor.h"

int  Motor::getCurrentThrottle()
{
    return _currentThrottle;
}

void Motor::sendMotorCommand(int pwmValue)
{
    analogWrite(DC_MOTOR_DIR_PIN, pwmValue);
    _currentThrottle = map(pwmValue, 0, 255, 0, 100);
}
