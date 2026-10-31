#include <Arduino.h>
#include <Wire.h>

#include "Config.h"
#include "Motor.h"
#include "Clutch.h"
#include "Gearbox.h"
#include "Telemetry.h"
#include "PowertrainManager.h"

void setup()
{
  Serial.begin(115200);
  
  Motor g_Motor(IDLE_THROTTLE);
  Clutch g_Clutch;
  Gearbox g_Gearbox;
  Telemetry g_Telemetry; 

  Powertrain g_Powertrain(&g_Motor, &g_Clutch, &g_Gearbox);
  g_Powertrain.beginTask();
}

void loop()
{
  vTaskDelete(nullptr);
}