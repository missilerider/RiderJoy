#pragma once

#include "../debug.h"

#include "../pin_macros.h"
#include <Adafruit_MCP23X17.h>
#include <Joystick.h>

class Control {
public:
    static void prepare();

    virtual void init()=0;
    virtual uint8_t getHighestJoyButton()=0;
    
    // Process
    virtual void process(Joystick_ *j)=0;

    virtual bool hasPoll() { return false; }
    virtual void poll() {};

protected:
    uint8_t readDigital(Input pin);
    uint16_t readAnalog(Input pin);
    void setupPullup(Input pin);
};
