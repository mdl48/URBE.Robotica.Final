#include "Glass.h"

void Glass::Configure(float glassClosenessTreshold, float (*calcTilt)(float)){
  GlassClosenessTreshold = glassClosenessTreshold;
  CalcTilt = calcTilt;
}

int Glass::DetectGlasses(Servo& servo, float (*measureDistance)()){
  servo->write(0);
  delay(3000);
  
  GlassArray.clear();
  int startDeg = -1;
  for(int i = 0; i <= 180; i++)
  {
    servo->write(i);
    if (measureDistance() < SomeValue)
    {
      if (startDeg > -1)
        continue;
      
      startDeg = i;
    }
    else
    {
      if (startDeg == -1)
        continue;

      endDeg = i;
      int center = startDeg + (endDeg / 2);
      servo->write(center);
      delay(3000);

      GlassArray.push_back(new Glass(startDeg, endDeg, measureDistance()));
      startDeg = -1;
      servo->write(i);
      delay(3000);
    }
  }
}