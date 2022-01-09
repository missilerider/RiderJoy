#pragma once

#include <Arduino.h>

#include "config_global.h"
#include "control_macros.h"

#include "debug.h"

#include "pin_macros.h"
#include <Adafruit_MCP23X17.h>
#include <Joystick.h>

#include "timer.h"

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_RX 3
#define AXIS_RY 4
#define AXIS_RZ 5
#define AXIS_RUDDER 6
#define AXIS_THROTTLE 7

/* Ejes no usados (todavía?)
#define AXIS_ACCEL 8
#define AXIS_BRAKE 9
#define AXIS_STEERING 10
*/

class Control {
public:
    static void prepare();

    virtual void _init()=0;
    static void init(ControlData *d);
    virtual uint8_t getHighestJoyButton() { return 0; };
    static uint8_t getHighestJoyButton(ControlData *d);
    virtual void getAxisRequirements(uint8_t *axisArray) {};
    static void getAxisRequirements(ControlData *d, uint8_t *axisArray);
    
    // Process
    virtual void process(Joystick_ *j)=0;
    static void process(ControlData *d, Joystick_ *j, uint8_t elapsed);

    virtual bool hasPoll() { return false; }
    static bool hasPoll(ControlData *d);
    virtual void poll() {};

protected:
    static uint8_t readDigital(Input pin);
    static uint16_t readAnalog(Input pin);
    static uint16_t muxRead(uint8_t id, uint8_t pin);
    static void setupPullup(Input pin);
    static void setAxis(Joystick_ *j, uint8_t axis, uint16_t value);
};
