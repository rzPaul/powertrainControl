#include "Clutch.h"

void Clutch::open()
{
    _servoDriver->writeMicroseconds(CLUTCH_CHANNEL, degreesToUs(MAX_CLUTCH_POS));
    _currentClutchPositionDeg = MAX_CLUTCH_POS;
}


void Clutch::close()
{
    _servoDriver->writeMicroseconds(CLUTCH_CHANNEL, degreesToUs(MIN_CLUTCH_POS));
    _currentClutchPositionDeg = MIN_CLUTCH_POS;
}


void Clutch::setPos(int posDeg)
{
    _servoDriver->writeMicroseconds(CLUTCH_CHANNEL, degreesToUs(posDeg));
    _currentClutchPositionDeg = posDeg;
}

void Clutch::linkDrv(Adafruit_PWMServoDriver * driver)
{
    _servoDriver = driver;
}
