#ifndef HELPERS_H
#define HELPERS_H

#include "Glass.h"
#include "Config.h"

float ScanWaterLevel();

void MoveHeadToGlass(Glass& glass);

void PourWater(int lengthMilliseconds);

void DebugWrite(const char* dat, int state = Analyzing);

void FadeLEDsTo(uint8_t mode, int millisecondsDelayPerFrame);

void SetAllLEDsTo(int mode);

#endif