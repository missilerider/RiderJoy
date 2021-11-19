#include "rotary.h"
#include "timer.h"

class RotaryButton : public Rotary {
private:
    uint8_t j1, j2;
    Timer t1, t2;

public:
    RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2);

    void process(Joystick_ *j);
};
