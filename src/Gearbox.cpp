#include "Gearbox.h"

void Gearbox::shiftUp()
{
    if (_currentGear == 3)
        return;

    _servoDriver->writeMicroseconds(GEARBOX_CHANNEL, degreesToUs(gearAngles[_currentGear + 1]));
}

void Gearbox::shiftDown()
{
    if (_currentGear == 0)
        return;

    _servoDriver->writeMicroseconds(GEARBOX_CHANNEL, degreesToUs(gearAngles[_currentGear - 1]));
}

void Gearbox::linkDrv(Adafruit_PWMServoDriver * driver)
{
    _servoDriver = driver;
}