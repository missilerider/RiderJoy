#include "rotary.h"

class RotaryButton : public Rotary {
private:
    uint8_t j1, j2;
    Timer *t1, *t2;

    uint8_t minS = 1;
    int8_t lastDir = 0;

public:
    RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t steps);

    // Config
    uint8_t getHighestJoyButton();
    static uint8_t getHighestJoyButton(ControlData *d);
    RotaryButton *minIdle(uint16_t idle);

    // Process
    static void poll(ControlData *d);
    static void init(ControlData *d);
    void process(Joystick_ *j);
    static void process(ControlData *d, Joystick_ *j, uint8_t elapsed);
};
