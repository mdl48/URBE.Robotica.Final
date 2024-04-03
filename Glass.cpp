#include "Glass.h"

int Glass::DetectGlasses(Servo& servo, MeasureFunc measure){
  servo.write(0);
  delay(3000);
  glasses.clear();

  int startDeg = -1;
  int endDeg = 0;
  for(int i = 0; i <= 180; i++)
  {
    servo.write(i);
    if (measure() > 0)
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
      servo.write(center);
      delay(3000);

      glasses.push_back(Glass(startDeg, endDeg));

      startDeg = -1;
      servo.write(i);
      delay(3000);
    }
  }
  return glasses.size();
}
