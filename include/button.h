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
    static uint8_t getHighestJoyButton(ControlData *d);
    Button *i();
    Button *momentary();
    Button *momentaryFull();

    // Process
    void init();
    static void init(ControlData *d);
    void process(Joystick_ *j);
    static void process(ControlData *d, Joystick_ *j, uint8_t elapsed);
};
