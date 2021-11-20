#pragma once

#include "control.h"

class Pot : public Control {
private:
    Input input = 0;
    uint8_t axis = 0;
    bool inverted = false;

public: 
    Pot(Input input, uint8_t axis);

    // Config
    void getAxisRequirements(uint8_t *axisArray);
    Pot *i();

    // Process
    void init();
    void process(Joystick_ *j);
};
