#pragma once

#include "control.h"

class Switch3p : public Control {
private:
    Input i1, i2;
    uint8_t j1, j2, j3;
    Timer *timer = NULL;
    uint8_t lastStatus = 2;

public: 
    Switch3p(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t j3);

    // Config
    uint8_t getHighestJoyButton();
    Switch3p *momentary();
    Switch3p *i();

    // Process
    void init();
    void process(Joystick_ *j);
};
