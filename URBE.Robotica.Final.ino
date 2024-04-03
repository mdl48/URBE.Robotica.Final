#define __ASSERT_USE_STDERR

#include <Arduino.h>
#include <Servo.h>
#include "Glass.h"
#include "Config.h"
#include "Helpers.h"

Servo Base;
Servo Head;

void setup() {
  for (int i = 0; i < STATE_LEDS_OUT_LEN; i++)
    pinMode(STATE_LEDS_OUT[i], OUTPUT);
  
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

