#include "rotary.h"

class RotaryAxis : public Rotary {
private:
    uint8_t axis;
    uint8_t minS = 1;
    unsigned long t0 = 0;

    float lastStep;

    float pos = 512.0f;

public:
    RotaryAxis(Input i1, Input i2, uint8_t axis, uint8_t steps);

    // Config
    void getAxisRequirements(uint8_t *axisArray);

    // Process
    void process(Joystick_ *j);
};
