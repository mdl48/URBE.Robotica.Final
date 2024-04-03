#ifndef GLASS_H
#define GLASS_H

#include <assert.h>
#include <Servo.h>
#include <Vector.h>

typedef int(*MeasureFunc)(void);
typedef float(*TiltFunc)(float);

class Glass {
public:
    int StartDeg;
    int EndDeg;
    int CenterDeg;
    float Distance;
    int RequiredTilt;

    Glass(int startDeg, int endDeg) 
    : StartDeg(startDeg), EndDeg(endDeg), CenterDeg(startDeg + (endDeg / 2))
    {
      assert(startDeg > 0);
      assert(endDeg > startDeg);
      assert(endDeg <= 180);
    }

    static int DetectGlasses(Servo& base, MeasureFunc measure);
};

static float closenessThreshold;
static TiltFunc calcTilt;
static Vector<Glass> glasses;

#endif
