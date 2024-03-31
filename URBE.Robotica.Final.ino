#define __ASSERT_USE_STDERR

#include <Servo.h>
#include "Glass.h"
#include "Config.h"

Servo Base;
Servo Head;

void setup() {
  for (int i = 0; i < sizeof(SateLEDsOut); i++)
    pinMode(StateLEDsOut[i], OUTPUT);
  
  FadeLEDsTo(HIGH, 10);

  Serial.begin (9600);
  Base.attach(BaseSignalOut);
  Head.attach(HeadSignalOut);
  pinMode(PumpSignalOut, OUTPUT);
  pinMode(USSignalOut, OUTPUT);
  pinMode(USEchoIn, INPUT);
  pinMode(OIRSignalIn, INPUT);

  FadeLEDsTo(LOW, 2);
  FadeLEDsTo(HIGH, 2);
  FadeLEDsTo(LOW, 10);
}

void loop() {
  
}
