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
    static void getAxisRequirements(ControlData *d, uint8_t *axisArray);
    Pot *i();
    Pot *exp(float e);

    // Process
    void init();
    static void init(ControlData *d);
    void process(Joystick_ *j);
    static void process(ControlData *d, Joystick_ *j, uint8_t elapsed);

private:
    uint16_t clamp(uint16_t value);
};
