#ifndef HELPERS_H
#define HELPERS_H

#include "Glass.h"
#include "Config.h"

float ScanWaterLevel();

void MoveHeadToGlass(Glass& glass);

void PourWater(int lengthMilliseconds);

void DebugWrite(const char* dat, RobotState state = 0);

void FadeLEDsTo(uint8_t pwmLevel);

void SetAllLEDsTo(int mode);

#endif