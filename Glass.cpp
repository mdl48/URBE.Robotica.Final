#include "Glass.h"

Vector<Glass*> Glass::GlassArray;

int Glass::Get(int i, Glass* glass) {
  if (i < 0 || i >= GlassArray.size()) 
    return 0;

  glass = GlassArray[i];
  return 1;
}

int Glass::DetectGlasses(Servo& servo, int (*checkObstacle)()){
  servo.write(0);
  delay(3000);
  
  for (int i = 0; i < GlassArray.size(); i++)
    delete GlassArray[i];
  GlassArray.clear();

  int startDeg = -1;
  int endDeg = 0;
  for(int i = 0; i <= 180; i++)
  {
    servo.write(i);
    if (checkObstacle() > 0)
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

      GlassArray.push_back(new Glass(startDeg, endDeg));

      startDeg = -1;
      servo.write(i);
      delay(3000);
    }
  }
  return GlassArray.size();
}