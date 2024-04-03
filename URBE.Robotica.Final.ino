#define __ASSERT_USE_STDERR

#include <Arduino.h>
#include <Servo.h>
#include "Glass.h"
#include "Config.h"
#include "Helpers.h"

Servo Base;
Servo Head;

int CheckObstacle(void) {
  return digitalRead(OIRSIGNAL_IN);
}

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
    int foundGlasses = Glass::DetectGlasses(Base, CheckObstacle);
    if(foundGlasses > 0)
    {
      DebugWrite("Found glasses to fill", RobotState::OK);
      for(int i = 0; i < foundGlasses; i++){
        MoveHeadToGlass(glasses[i]);
        while (ScanWaterLevel() < 0.9)
          PourWater(1000);
      }
    }

    if (serialEventRun) serialEventRun();
  }
        
    return 0;
}

