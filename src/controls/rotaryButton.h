#include "rotary.h"

class RotaryButton : public Rotary {
private:
    uint8_t j1, j2;
    Timer t1, t2;

    uint8_t minS = 1;

public:
    RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t steps);

    // Config
    uint8_t getHighestJoyButton();
    RotaryButton *minIdle(uint16_t idle);

    // Process
    void process(Joystick_ *j);
};
