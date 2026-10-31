#pragma once

#include <Arduino.h>

constexpr int CLUTCH_CHANNEL = 0;
constexpr int GEARBOX_CHANNEL = 1;
constexpr int UPSHIFT_PIN = 9;
constexpr int DOWNSHIFT_PIN = 10;
constexpr int DC_MOTOR_RPM_PIN = 4;
constexpr int DC_MOTOR_DIR_PIN = 5;
constexpr int THROTTLE_POS_PIN = A0;
constexpr int SDA_PIN = A4;
constexpr int SCL_PIN = A5;
constexpr uint8_t SERVO_DRIVER_ADDR = 0x40;

constexpr uint8_t IDLE_RPM = 100; // hardcoded an idle similar to a gas engine
constexpr uint8_t IDLE_THROTTLE = 51;

inline int degreesToUs(int degrees)
{
    return map(degrees, 0, 180, 500, 2500);
}