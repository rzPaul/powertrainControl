#pragma once

#include <Arduino.h>
#include "Config.h"

class Motor
{
private:
    int _currentThrottlePercent;
    
public: 
    int getCurrentThrottle(); 
    void sendMotorCommand(int throttlePercent);
};
