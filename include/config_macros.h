#pragma once

#define ADD_BUTTON(i, j) ((c[last++].setup(CONTROL_TYPE_BUTTON, i, j)))

#define ADD_SWITCH3(i1, i2, j1, j2, j3) ((c[last++].setup(CONTROL_TYPE_SWITCH3, i1, i2, j1, j2, j3)))
#define _ADD_SWITCH3(i1, i2, j1, j2, j3) ((Switch3p*)(c[last++] = new Switch3p(i1, i2, j1, j2, j3)))


#define ADD_SWITCH2(i1, j1, j2) ((c[last++].setup(CONTROL_TYPE_SWITCH2, i1, j1, j2)))
#define _ADD_SWITCH2(i, j1, j2) ((Switch2p*)(c[last++] = new Switch2p(i, j1, j2)))

#define ADD_POT(i, a) ((c[last++].setup(CONTROL_TYPE_POT, i, a)))
#define _ADD_POT(i, a) ((Pot*)(c[last++] = new Pot(i, a)))

#define ADD_ROTARY_BUTTONS(i1, i2, j1, j2, s) ((c[last++].setupRotary(CONTROL_TYPE_ROTARY_B, i1, i2, j1, j2, s)))
#define _ADD_ROTARY_BUTTONS(i1, i2, j1, j2, s) ((RotaryButton*)(c[last++] = new RotaryButton(i1, i2, j1, j2, s)))

#define _ADD_ROTARY_AXIS(i1, i2, a, s) ((RotaryAxis*)(c[last++] = new RotaryAxis(i1, i2, a, s)))

void readConfig(ControlData *c, uint8_t *retLast) {
    uint8_t last = 0;

    #include "config_controls.h"

    *retLast = last;
}
