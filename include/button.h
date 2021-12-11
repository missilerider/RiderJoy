#pragma once

#include "control.h"

class Button : public Control {
private:
    Input input = 0;
    uint8_t jButton = 0;
    bool inverted = false;
    Timer *timer = NULL;

public: 
    Button(Input input, uint8_t j);

    // Config
    uint8_t getHighestJoyButton();
    Button *i();
    Button *momentary();

    // Process
    void init();
    void process(Joystick_ *j);
};
