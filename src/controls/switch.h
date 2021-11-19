#pragma once

#include "control.h"

class Switch : public Control {
private:
    Input i1, i2;
    uint8_t j1, j2, j3;
    bool isAlwaysOn = false;

public: 
    Switch(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t j3);
    Switch(Input i1, Input i2, uint8_t j1, uint8_t j2);

    // Config
    uint8_t getHighestJoyButton();
    Switch *alwaysOn();
    Switch *i();

    // Process
    void init();
    void process(Joystick_ *j);
};
