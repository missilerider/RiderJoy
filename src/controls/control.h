#pragma once

#include "../debug.h"

#include "../pin_macros.h"
#include <Adafruit_MCP23X17.h>
#include <Joystick.h>

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_RX 3
#define AXIS_RY 4
#define AXIS_RZ 5

/* Ejes no usados (todavía?)
#define AXIS_RUDDER 6
#define AXIS_THROTTLE 7
#define AXIS_ACCEL 8
#define AXIS_BRAKE 9
#define AXIS_STEERING 10
*/

class Control {
public:
    static void prepare();

    virtual void init()=0;
    virtual uint8_t getHighestJoyButton() { return 0; };
    virtual void getAxisRequirements(uint8_t *axisArray) {};
    
    // Process
    virtual void process(Joystick_ *j)=0;

    virtual bool hasPoll() { return false; }
    virtual void poll() {};

protected:
    uint8_t readDigital(Input pin);
    uint16_t readAnalog(Input pin);
    void setupPullup(Input pin);
    void setAxis(Joystick_ *j, uint8_t axis, uint16_t value);
};
