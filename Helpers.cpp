#include "Helpers.h"

void MoveHeadToGlass(Glass& glass) {

}

void FadeLEDsTo(int mode, int millisecondsDelayPerFrame) {
  if (millisecondsDelayPerFrame == 0) {
    SetAllLEDsTo(mode);
    return;
  }

  if (millisecondsDelayPerFrame < 1)
    millisecondsDelayPerFrame = 1;

  SetAllLEDsTo(1 - mode);

  for (int lvl = 0; lvl <= 255; lvl++) {
    for (int i = 0; i < sizeof(SateLEDsOut); i++)
      analogWrite(StateLEDsOut[i], lvl);
    delay(millisecondsDelayPerFrame);
  }

  SetAllLEDsTo(mode);
}

void SetAllLEDsTo(int mode) {
  for (int i = 0; i < sizeof(SateLEDsOut); i++)
    digitalWrite(StateLEDsOut[i], mode);
}

float ScanWaterLevel() {
  // ((speed of sound in the air)*time)/2
  return 0;
}

void PourWater(int lengthMilliseconds) {
  if (lengthMilliseconds <= 0)
    return;

  if (lengthMilliseconds > 50000)
    lengthMilliseconds = 50000;

  digitalWrite(PumpSignalOut, HIGH);
  delay(lengthMilliseconds);
  digitalWrite(PumpSignalOut, LOW);
}


void DebugWrite(const char* dat, RobotState state = 0) {
  Serial.println(dat);
  if (state != CurrentState)
  {
    digitalWrite(StateLEDsOut[CurrentState], LOW);
    CurrentState = state;
    digitalWrite(StateLEDsOut[CurrentState], HIGH);
    Serial.print("Switched Robot state to '");
    switch (CurrentState)
    {
      case 0:
        Serial.print("Starting'"); // These have a ' at the end to match the opening one in "Switched Robot state to '". I'm aware it's ugly, but it works
        break;
      
      case 1:
        Serial.print("Analyzing'");
        break;
      
      case 2:
        Serial.print("OK'");
        break;

      case 3:
        Serial.print("Error'");
        break;

      default:
        Serial.print("Unknown'");
        break;
    }
  }
}