#pragma once

#include "control.h"

class Button : public Control {
private:
    Input input = 0;
    uint8_t jButton = 0, jButton2 = 255;
    bool inverted = false;
    Timer *timer = NULL;

public: 
    Button(Input input, uint8_t j);
    Button(Input input, uint8_t j1, uint8_t j2);

    // Config
    uint8_t getHighestJoyButton();
    Button *i();
    Button *momentary();
    Button *momentaryFull();

    // Process
    void init();
    void process(Joystick_ *j);
};
