#pragma once

#define ADD_BUTTON(i, j) ((Button*)(c[last++] = new Button(i, j)))

#define ADD_SWITCH3(i1, i2, j1, j2, j3) ((Switch*)(c[last++] = new Switch(i1, i2, j1, j2, j3)))
#define ADD_SWITCH2(i1, i2, j1, j2) ((Switch*)(c[last++] = new Switch(i1, i2, j1, j2)))

#define ADD_ROTARY_BUTTONS(i1, i2, j1, j2, s) ((RotaryButton*)(c[last++] = new RotaryButton(i1, i2, j1, j2, s)))

#define ADD_ROTARY_AXIS(i1, i2, a, s) ((RotaryAxis*)(c[last++] = new RotaryAxis(i1, i2, a, s)))

#define ADD_POT(i, a) ((Pot*)(c[last++] = new Pot(i, a)))

void readConfig(Control **c, uint8_t *retLast) {
    //c = new Control*[128];
    uint8_t last = 0;

    #include "config_controls.h"

    *retLast = last;
}