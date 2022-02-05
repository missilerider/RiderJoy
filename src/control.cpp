#include <Arduino.h>
#include "control.h"
#include "config_global.h"

#include "button.h"

extern Adafruit_MCP23X17 mcp[8];

static void Control::prepare() {
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

static void Control::setupPullup(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pln(pin);
            pinMode(pin, INPUT_PULLUP);
            break;

        case TYPE_MCPa:
        case TYPE_MCPb:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), INPUT_PULLUP);
            break;
    }
}

static void Control::setupOutput(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            pln(pin);
            pinMode(pin, OUTPUT);
            break;

        case TYPE_MCPa:
        case TYPE_MCPb:
            mcp[MCP_ID(pin)].pinMode(MCP_PIN(pin), OUTPUT);
            break;
    }
}

static void Control::setupInput(Input pin) {
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

static void Control::setOutput(Input pin, uint8_t value) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalWrite(pin, value);

        case TYPE_MCPa:
        case TYPE_MCPb:
            return mcp[MCP_ID(pin)].digitalWrite(MCP_PIN(pin), value);
    }
}

static uint8_t Control::readDigital(Input pin) {
    switch(GET_PIN_TYPE(pin)) {
        case TYPE_PIN:
            return digitalRead(pin);

        case TYPE_MCPa:
        case TYPE_MCPb:
            return mcp[MCP_ID(pin)].digitalRead(MCP_PIN(pin));
    }

    return 5;
}

static uint16_t Control::readAnalog(Input pin) {
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

static uint16_t Control::muxRead(uint8_t id, uint8_t pin) {
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

static void Control::setAxis(Joystick_ *j, uint8_t axis, uint16_t value) {
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

static uint8_t Control::getHighestJoyButton(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::getHighestJoyButton(d);
        default: return 0;
    }
}

static void Control::getAxisRequirements(ControlData *d, uint8_t *axisArray) {
    switch(d->getType()) {
//        case CONTROL_TYPE_POT:
//            return Pot::getAxisRequirements(d, axisArray);

        default: return;
    }
}

static void Control::init(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::init(d);
    }
}

static bool Control::hasPoll(ControlData *d) {
    switch(d->getType()) {
        case CONTROL_TYPE_ROTARY_B: return true;
        default: return false;
    }
}

static void Control::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    switch(d->getType()) {
        case CONTROL_TYPE_BUTTON:
            return Button::process(d, j, elapsed);

        case CONTROL_TYPE_ROTARY_B: return;
    }
}
