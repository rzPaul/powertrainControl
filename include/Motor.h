#pragma once

#include <Arduino.h>
#include "Config.h"

class Motor
{
private:
    int _currentThrottle;
    
public: 
    int getCurrentThrottle(); 
    void sendMotorCommand(int pwmValue);
};
