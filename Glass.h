#ifndef GLASS_H
#define GLASS_h

#include <assert.h>
#include <Servo.h>
#include <Vector.h>

class Glass {
  private:
    static Vector<Glass*> GlassArray;

  public:
    const int StartDeg;
    const int EndDeg;
    const int CenterDeg;

    Glass(int startDeg, int endDeg) 
    : StartDeg(startDeg), EndDeg(endDeg), CenterDeg(startDeg + (endDeg / 2))
    {
      assert(startDeg > 0);
      assert(endDeg > startDeg);
      assert(endDeg <= 180);
    }

    static int DetectGlasses(Servo& base, int (*checkObstacle)());

    static int Get(int i, Glass* glass);
};

#endif