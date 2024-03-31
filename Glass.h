#ifndef GLASS_H
#define GLASS_h

#include <assert.h>
#include <Servo.h>
#include <Vector.h>
#include "Config.h"

class Glass {
  private:
    static float GlassClosenessTreshold; 
    static float (*CalcTilt)(float);
    static Vector<Glass> GlassArray;

  public:
    const int StartDeg;
    const int EndDeg;
    const int CenterDeg;
    const float Distance;
    const int RequiredTilt;

    Glass(int startDeg, int endDeg, float distance) 
    : StartDeg(startDeg), EndDeg(endDeg), CenterDeg(startDeg + (endDeg / 2)), Distance(distance), RequiredTilt(-1)
    {
      assert(distance > 0);
      assert(startDeg > 0);
      assert(endDeg > startDeg);
      assert(endDeg <= 180);
    }

    static void Configure(float glassClosenessTreshold, float (*calcTilt)(float));

    static int DetectGlasses(Servo& base);
}

#endif