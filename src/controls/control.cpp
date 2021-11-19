#include <Arduino.h>
#include "control.h"

extern Adafruit_MCP23X17 mcp[8];

void Control::init() {
    for(uint8_t n = 0; n < 8; n++) {
        mcp[n].begin_I2C(n);
    }
}

uint8_t Control::readDigital(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalRead(pin);

        case TYPE_MCP:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PORT(pin));
    }

    return 5;
}

uint16_t Control::readAnalog(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return analogRead(pin);

        case TYPE_MCP:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PORT(pin)) == LOW ? 1024 : 0;
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
            mcp[MCP_ID(pin)].pinMode(MCP_PORT(pin), INPUT_PULLUP);
            break;
    }
}
