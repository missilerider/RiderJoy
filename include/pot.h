#pragma once

#include "control.h"

class Pot : public Control {
private:
    Input input = 0;
    uint8_t axis = 0;
    bool inverted = false;
    float e = 1.0f;

    uint16_t lastValue;

public: 
    Pot(Input input, uint8_t axis);

    // Config
    void getAxisRequirements(uint8_t *axisArray);
    Pot *i();
    Pot *exp(float e);

    // Process
    void init();
    void process(Joystick_ *j);

private:
    uint16_t clamp(uint16_t value);
};
