#include <Arduino.h>
#include "control.h"
#include "config_global.h"

#include "button.h"
#include "switch3p.h"
#include "switch2p.h"
#include "pot.h"
#include "rotaryButton.h"

extern Adafruit_MCP23X17 mcp[8];

void Control::prepare() {
    // Inicializamos los MCP
    for(uint8_t n = 0; n < 8; n++) {
        p("MCP ");
        p(n);

        if(mcp[n].begin_I2C(0x20 + n)) {
            pln(": OK");
        } else {
            pln(" not found!");
        }
    }

    // Inicializamos los multiplexores de puertos analógicos, si existe la configuración
#if defined(AMUX_PIN_IN0) && defined(AMUX_ADDR_PIN0) && defined(AMUX_ADDR_PIN1) && defined(AMUX_ADDR_PIN2) && defined(AMUX_ADDR_PIN3)
    // Pines de señalización de puertos para los multiplexores de puertos analógicos
    pinMode(AMUX_ADDR_PIN0, OUTPUT);
    pinMode(AMUX_ADDR_PIN1, OUTPUT);
    pinMode(AMUX_ADDR_PIN2, OUTPUT);
    pinMode(AMUX_ADDR_PIN3, OUTPUT);

    // Pines de lectura analógica
    pinMode(AMUX_PIN_IN0, INPUT_PULLUP);

    #ifdef AMUX_PIN_IN1
        pinMode(AMUX_PIN_IN1, INPUT_PULLUP);
    #endif

    #ifdef AMUX_PIN_IN2
        pinMode(AMUX_PIN_IN2, INPUT_PULLUP);
    #endif

    #ifdef AMUX_PIN_IN3
        pinMode(AMUX_PIN_IN3, INPUT_PULLUP);
    #endif
#endif
}

void Control::setupPullup(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pinMode(pin, INPUT_PULLUP);
            break;

        case TYPE_MCPa:
        case TYPE_MCPb:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), INPUT_PULLUP);
            break;
    }
}

void Control::setupOutput(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pinMode(pin, OUTPUT);
            break;

        case TYPE_MCPa:
        case TYPE_MCPb:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), OUTPUT);
            break;
    }
}

void Control::setupInput(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pinMode(pin, INPUT);
            break;

        case TYPE_MCPa:
        case TYPE_MCPb:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), INPUT);
            break;
    }
}

void Control::setOutput(Input pin, uint8_t value) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalWrite(pin, value);

        case TYPE_MCPa:
        case TYPE_MCPb:
            return mcp[MCP_ID(pin)].digitalWrite(MCP_PIN(pin), value);
    }
}

uint8_t Control::readDigital(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalRead(pin);

        case TYPE_MCPa:
        case TYPE_MCPb:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PIN(pin));
    }

    return 5;
}

uint16_t Control::readAnalog(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return analogRead(pin);

        case TYPE_AMUX:
            return Control::muxRead(AMUX_ID(pin), AMUX_PIN(pin));

        case TYPE_MCPa:
        case TYPE_MCPb:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PIN(pin)) == LOW ? 1024 : 0;
    }

    return 5;
}

uint16_t Control::muxRead(uint8_t id, uint8_t pin) {
    digitalWrite(AMUX_ADDR_PIN0, pin & 0b1 ? HIGH : LOW);
    digitalWrite(AMUX_ADDR_PIN1, pin & 0b10 ? HIGH : LOW);
    digitalWrite(AMUX_ADDR_PIN2, pin & 0b100 ? HIGH : LOW);
    digitalWrite(AMUX_ADDR_PIN3, pin & 0b1000 ? HIGH : LOW);

    switch(id) {
        default:
        case 0: return analogRead(AMUX_PIN_IN0);
        case 1: return analogRead(AMUX_PIN_IN0);
        case 2: return analogRead(AMUX_PIN_IN0);
        case 3: return analogRead(AMUX_PIN_IN0);
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
        case AXIS_THROTTLE: j->setThrottle(value); break;
        case AXIS_RUDDER: j->setRudder(value); break;
    }
}

uint8_t Control::getHighestJoyButton(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::getHighestJoyButton(d);

        case CONTROL_TYPE_SWITCH3:
            return Switch3p::getHighestJoyButton(d);

        case CONTROL_TYPE_SWITCH2:
            return Switch2p::getHighestJoyButton(d);

        case CONTROL_TYPE_ROTARY_B:
            return RotaryButton::getHighestJoyButton(d);

        default: return 0;
    }
}

void Control::getAxisRequirements(ControlData *d, uint8_t *axisArray) {
    switch(d->getType()) {
        case CONTROL_TYPE_POT:
            return Pot::getAxisRequirements(d, axisArray);

        default: return;
    }
}

void Control::init(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::init(d);

        case CONTROL_TYPE_SWITCH3:
            return Switch3p::init(d);

        case CONTROL_TYPE_SWITCH2:
            return Switch2p::init(d);

        case CONTROL_TYPE_POT:
            return Pot::init(d);

        case CONTROL_TYPE_ROTARY_B:
            return RotaryButton::init(d);
    }
}

bool Control::hasPoll(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_ROTARY_B: return true;
        default: return false;
    }
}

void Control::poll(ControlData *d) {
    RotaryButton::poll(d);
}

void Control::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::process(d, j, elapsed);

        case CONTROL_TYPE_SWITCH3:
            return Switch3p::process(d, j, elapsed);

        case CONTROL_TYPE_SWITCH2:
            return Switch2p::process(d, j, elapsed);

        case CONTROL_TYPE_POT:
            return Pot::process(d, j, elapsed);

        case CONTROL_TYPE_ROTARY_B:
            return RotaryButton::process(d, j, elapsed);
    }
}
