#include "Glass.h"

int Glass::DetectGlasses(Servo& servo, MeasureFunc measure){
  servo.write(0);
  delay(3000);
  
  glasses.clear();
  StartDeg = -1;
  for(int i = 0; i <= 180; i++)
  {
    servo.write(i);
    if (measure() < closenessThreshold)
    {
      if (StartDeg > -1)
        continue;
      
      StartDeg = i;
    }
    else
    {
      if (StartDeg == -1)
        continue;

      EndDeg = i;
      int center = StartDeg + (EndDeg / 2);
      servo.write(center);
      delay(3000);

      glasses.push_back(Glass(StartDeg, EndDeg, measure()));
      StartDeg = -1;
      servo.write(i);
      delay(3000);
    }
  }
}
