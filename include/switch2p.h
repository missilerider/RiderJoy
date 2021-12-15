#pragma once

#include "control.h"

class Switch2p : public Control {
private:
    Input i1, i2;
    uint8_t j1, j2, j3;
    Timer *timer = NULL;
    uint8_t lastStatus = LOW;

public: 
    Switch2p(Input i1, uint8_t j1, uint8_t j2);

    // Config
    uint8_t getHighestJoyButton();
    Switch2p *momentary();
    Switch2p *i();

    // Process
    void init();
    void process(Joystick_ *j);
};
