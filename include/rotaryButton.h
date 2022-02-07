#include "rotary.h"

class RotaryButton {
public:
    // Config
    static uint8_t getHighestJoyButton(ControlData *d);

    // Process
    static void poll(ControlData *d);
    static void init(ControlData *d);
    static void process(ControlData *d, Joystick_ *j, uint8_t elapsed);
};
