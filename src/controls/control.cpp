#include <Arduino.h>
#include "control.h"

extern Adafruit_MCP23X17 mcp[8];

void Control::prepare() {
    for(uint8_t n = 0; n < 8; n++) {
        p("MCP ");
        p(n);

        if(mcp[n].begin_I2C(0x20 + n)) {
            pln(" OK");
        } else {
            pln(" not found!");
        }
    }
}

uint8_t Control::readDigital(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalRead(pin);

        case TYPE_MCP:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PIN(pin));
    }

    return 5;
}

uint16_t Control::readAnalog(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return analogRead(pin);

        case TYPE_MCP:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PIN(pin)) == LOW ? 1024 : 0;
    }

    return 5;
}

void Control::setupPullup(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pln(pin);
            pinMode(pin, INPUT_PULLUP);
            break;

        case TYPE_MCP:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), INPUT_PULLUP);
            break;
    }
}

void Control::setAxis(Joystick_ *j, uint8_t axis, uint16_t value) {
    switch(axis) {
        case AXIS_X: j->setXAxis(value); break;
        case AXIS_Y: j->setYAxis(value); break;
        case AXIS_Z: j->setZAxis(value); break;
        case AXIS_RX: j->setRxAxis(value); break;
        case AXIS_RY: j->setRyAxis(value); break;
        case AXIS_RZ: j->setRzAxis(value); break;
    }
}