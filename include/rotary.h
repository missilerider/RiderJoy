#pragma once

#include "control.h"

class Rotary : public Control {
private:
    Input i1, i2;
    float accel = 1.0f;
    float exp = 0.0f;

    uint8_t lastA = 0, lastB = 0;

protected:
    float step = 0;

public: 
    Rotary(Input i1, Input i2);

    // Config
    uint8_t getHighestJoyButton() { return 0; }
    Rotary *i();
    Rotary *a(float accel, float exp);

    // Process
    void init();
    bool hasPoll() { return true; }
    void poll();

private:
    float calcStep();

protected:
    void endProcess();
};
