#define __ASSERT_USE_STDERR

#include <Arduino.h>
#include <Servo.h>
#include "Glass.h"
<<<<<<< HEAD

const int SpeedOfSound = 350; // m/s, at 30C
const int BaseSignalOut = 11;
const int HeadSignalOut = 10;
const int PumpSignalOut = 4;
const int USSignalOut = 7;
const int USEchoIn = 8;
const int OIRSignalIn = 9;

const int HeadIDLEPosition = 0;
const int HeadPreparedPosition = 0;

const float LEDFadeTimeDuringFill = 8; // 8 * 255 = 2040, just over 2 seconds

const int StateLEDsOut[] = { 3, 5, 6 };

enum RobotState { Analyzing, OK, Error };
RobotState CurrentState = 0;
=======
#include "Config.h"
#include "Helpers.h"
>>>>>>> 8e281c0 (Make it compile)

Servo Base;
Servo Head;

<<<<<<< HEAD
int CheckObstacle() {
  return digitalRead(OIRSignalIn);
}

void MoveHeadToGlass(Glass* glass) {
  Base.write(glass->CenterDeg);
}

void FadeLEDTo(int pin, int mode, int millisecondsDelayPerFrame) {
  if (millisecondsDelayPerFrame == 0) {
    digitalWrite(pin, mode);
    return;
  }

  if (millisecondsDelayPerFrame < 1)
    millisecondsDelayPerFrame = 1;


  if (mode == LOW) {
    digitalWrite(pin, HIGH);
    for (int lvl = 255; lvl >= 0; lvl--) {
      analogWrite(pin, lvl);
      delay(millisecondsDelayPerFrame);
    }
    digitalWrite(pin, LOW);
  }
  else {
    digitalWrite(pin, LOW);
    for (int lvl = 0; lvl <= 255; lvl++) {
      analogWrite(pin, lvl);
      delay(millisecondsDelayPerFrame);
    }
    digitalWrite(pin, HIGH);
  }
}

void FadeLEDsTo(int mode, int millisecondsDelayPerFrame) {
  if (millisecondsDelayPerFrame == 0) {
    SetAllLEDsTo(mode);
    return;
  }

  if (millisecondsDelayPerFrame < 1)
    millisecondsDelayPerFrame = 1;

  if (mode == LOW) {
    SetAllLEDsTo(HIGH);
    for (int lvl = 255; lvl >= 0; lvl--) {
      for (int i = 0; i < sizeof(StateLEDsOut); i++)
        analogWrite(StateLEDsOut[i], lvl);
      delay(millisecondsDelayPerFrame);
    }
    SetAllLEDsTo(LOW);
  }
  else {
    SetAllLEDsTo(LOW);
    for (int lvl = 0; lvl <= 255; lvl++) {
      for (int i = 0; i < sizeof(StateLEDsOut); i++)
        analogWrite(StateLEDsOut[i], lvl);
      delay(millisecondsDelayPerFrame);
    }
    SetAllLEDsTo(HIGH);
  }
}

void SetAllLEDsTo(int mode) {
  for (int i = 0; i < sizeof(StateLEDsOut); i++)
    digitalWrite(StateLEDsOut[i], mode);
}

float ScanWaterLevel() {
  // ((speed of sound in the air)*time)/2
  return 0;
}

void PourWater() {
  digitalWrite(PumpSignalOut, HIGH);
  FadeLEDTo(StateLEDsOut[RobotState::OK], LOW, LEDFadeTimeDuringFill / 2);
  FadeLEDTo(StateLEDsOut[RobotState::OK], HIGH, LEDFadeTimeDuringFill / 2);
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

int main(void)
{
  init();

#if defined(USBCON)
  USBDevice.attach();
#endif
    
    
  for (int i = 0; i < sizeof(StateLEDsOut); i++)
    pinMode(StateLEDsOut[i], OUTPUT);

=======
void setup() {
  for (int i = 0; i < STATE_LEDS_OUT_LEN; i++)
    pinMode(STATE_LEDS_OUT[i], OUTPUT);
  
>>>>>>> 8e281c0 (Make it compile)
  FadeLEDsTo(HIGH, 10);

  Serial.begin (9600);
  Base.attach(BASE_SIGNAL_OUT);
  Head.attach(HEAD_SIGNAL_OUT);
  pinMode(PUMP_SIGNAL_OUT, OUTPUT);
  pinMode(USSIGNAL_OUT, OUTPUT);
  pinMode(USECHO_IN, INPUT);
  pinMode(OIRSIGNAL_IN, INPUT);

  FadeLEDsTo(LOW, 2);
  FadeLEDsTo(HIGH, 2);
  FadeLEDsTo(LOW, 10);
  
  for (;;) {
    
    DebugWrite("Scanning for glasses", RobotState::Analyzing);
    int foundGlasses = Glass::DetectGlasses(Base, &CheckObstacle);
    if(foundGlasses > 0)
    {
      Glass* glass;
      DebugWrite("Found glasses to fill", RobotState::OK);
      for(int i = 0; i < foundGlasses; i++){
        Glass::Get(i, glass);
        MoveHeadToGlass(glass);
        while (ScanWaterLevel() < 0.9)
          PourWater();
      }
    }

    if (serialEventRun) serialEventRun();
  }
        
    return 0;
}

