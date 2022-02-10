#include "control.h"
#include "fnNumpad.h"

#include <Keyboard.h>

#define FN_1        0x001
#define FN_2        0x002
#define FN_3        0x004
#define FN_4        0x008
#define FN_5        0x010
#define FN_6        0x020
#define FN_7        0x040
#define FN_8        0x080
#define FN_9        0x100
#define FN_0        0x200
#define FN_STAR     0x400
#define FN_SHARP    0x800

#define IS_PRESSED(x)   (FnNumpad::status & x)
#define PRESS(x)   (FnNumpad::status |= x)
#define RELEASE(x)   (FnNumpad::status &= 0xFFFF - (x))

uint8_t FnNumpad::p0 = 0;
uint8_t FnNumpad::p1 = 0;
uint8_t FnNumpad::p2 = 0;
uint8_t FnNumpad::p3 = 0;
uint8_t FnNumpad::p4 = 0;
uint8_t FnNumpad::p5 = 0;
uint8_t FnNumpad::p6 = 0;

uint16_t FnNumpad::status = 0;

void FnNumpad::setup(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6) {
    FnNumpad::status = 0;

    FnNumpad::p0 = p0;
    FnNumpad::p1 = p1;
    FnNumpad::p2 = p2;
    FnNumpad::p3 = p3;
    FnNumpad::p4 = p4;
    FnNumpad::p5 = p5;
    FnNumpad::p6 = p6;

/*
  1: 1+2
  2: 1+0
  3: 1+4
  4: 6+2
  5: 6+0
  6: 6+4
  7: 5+2
  8: 5+0
  9: 5+4
  *: 3+2
  0: 3+0
  #: 3+4
*/
    Control::setupPullup(FnNumpad::p0);
    Control::setupPullup(FnNumpad::p2);
    Control::setupPullup(FnNumpad::p4);

    Control::setupInput(FnNumpad::p1);
    Control::setupInput(FnNumpad::p3);
    Control::setupInput(FnNumpad::p5);
    Control::setupInput(FnNumpad::p6);

    Keyboard.begin();
}

void FnNumpad::process() {
    Control::setupInput(FnNumpad::p1);
    Control::setupInput(FnNumpad::p3);
    Control::setupInput(FnNumpad::p5);
    Control::setupInput(FnNumpad::p6);


    Control::setupInput(FnNumpad::p3);
    Control::setupInput(FnNumpad::p5);
    Control::setupInput(FnNumpad::p6);

    Control::setupOutput(FnNumpad::p1);
    Control::setOutput(FnNumpad::p1, LOW);
    if(!Control::readDigital(FnNumpad::p2)) {
        // F1
        if(!IS_PRESSED(FN_1)) {
            p("_F1_ ");
            PRESS(FN_1);
            Keyboard.press(KEY_F1);
        }
    } else {
        if(IS_PRESSED(FN_1)) {
            p("^F1^ ");
            RELEASE(FN_1);
            Keyboard.release(KEY_F1);
        }
    }

    if(!Control::readDigital(FnNumpad::p0)) {
        // F2
        if(!IS_PRESSED(FN_2)) {
            p("_F2_ ");
            PRESS(FN_2);
            Keyboard.press(KEY_F2);
        }
    } else {
        if(IS_PRESSED(FN_2)) {
            p("^F2^ ");
            RELEASE(FN_2);
            Keyboard.release(KEY_F2);
        }
    }

    if(!Control::readDigital(FnNumpad::p4)) {
        // F3
        if(!IS_PRESSED(FN_3)) {
            p("_F3_ ");
            PRESS(FN_3);
            Keyboard.press(KEY_F3);
        }
    } else {
        if(IS_PRESSED(FN_3)) {
            p("^F3^ ");
            RELEASE(FN_3);
            Keyboard.release(KEY_F3);
        }
    }
    Control::setupInput(FnNumpad::p1);

    Control::setupOutput(FnNumpad::p6);
    Control::setOutput(FnNumpad::p6, LOW);
    if(!Control::readDigital(FnNumpad::p2)) {
        // F4
        if(!IS_PRESSED(FN_4)) {
            p("_F4_ ");
            PRESS(FN_4);
            Keyboard.press(KEY_F4);
        }
    } else {
        if(IS_PRESSED(FN_4)) {
            p("^F4^ ");
            RELEASE(FN_4);
            Keyboard.release(KEY_F4);
        }
    }

    if(!Control::readDigital(FnNumpad::p0)) {
        // F5
        if(!IS_PRESSED(FN_5)) {
            p("_F5_ ");
            PRESS(FN_5);
            Keyboard.press(KEY_F5);
        }
    } else {
        if(IS_PRESSED(FN_5)) {
            p("^F5^ ");
            RELEASE(FN_5);
            Keyboard.release(KEY_F5);
        }
    }

    if(!Control::readDigital(FnNumpad::p4)) {
        // F6
        if(!IS_PRESSED(FN_6)) {
            p("_F6_ ");
            PRESS(FN_6);
            Keyboard.press(KEY_F6);
        }
    } else {
        if(IS_PRESSED(FN_6)) {
            p("^F6^ ");
            RELEASE(FN_6);
            Keyboard.release(KEY_F6);
        }
    }
    Control::setupInput(FnNumpad::p6);

    Control::setupOutput(FnNumpad::p5);
    Control::setOutput(FnNumpad::p5, LOW);
    if(!Control::readDigital(FnNumpad::p2)) {
        // F7
        if(!IS_PRESSED(FN_7)) {
            p("_F7_ ");
            PRESS(FN_7);
            Keyboard.press(KEY_F7);
        }
    } else {
        if(IS_PRESSED(FN_7)) {
            p("^F7^ ");
            RELEASE(FN_7);
            Keyboard.release(KEY_F7);
        }
    }

    if(!Control::readDigital(FnNumpad::p0)) {
        // F8
        if(!IS_PRESSED(FN_8)) {
            p("_F8_ ");
            PRESS(FN_8);
            Keyboard.press(KEY_F8);
        }
    } else {
        if(IS_PRESSED(FN_8)) {
            p("^F8^ ");
            RELEASE(FN_8);
            Keyboard.release(KEY_F8);
        }
    }

    if(!Control::readDigital(FnNumpad::p4)) {
        // F9
        if(!IS_PRESSED(FN_9)) {
            p("_F9_ ");
            PRESS(FN_9);
            Keyboard.press(KEY_F9);
        }
    } else {
        if(IS_PRESSED(FN_9)) {
            p("^F9^ ");
            RELEASE(FN_9);
            Keyboard.release(KEY_F9);
        }
    }
    Control::setupInput(FnNumpad::p5);

    Control::setupOutput(FnNumpad::p3);
    Control::setOutput(FnNumpad::p3, LOW);
    if(!Control::readDigital(FnNumpad::p2)) {
        // F11
        if(!IS_PRESSED(FN_STAR)) {
            p("_FSTAR_ ");
            PRESS(FN_STAR);
            Keyboard.press(KEY_F11);
        }
    } else {
        if(IS_PRESSED(FN_STAR)) {
            p("^FSTAR^ ");
            RELEASE(FN_STAR);
            Keyboard.release(KEY_F11);
        }
    }

    if(!Control::readDigital(FnNumpad::p0)) {
        // F10
        if(!IS_PRESSED(FN_0)) {
            p("_F0_ ");
            PRESS(FN_0);
            Keyboard.press(KEY_F10);
        }
    } else {
        if(IS_PRESSED(FN_0)) {
            p("^F0^ ");
            RELEASE(FN_0);
            Keyboard.release(KEY_F10);
        }
    }

    if(!Control::readDigital(FnNumpad::p4)) {
        // F12
        if(!IS_PRESSED(FN_SHARP)) {
            p("_FSHARP_ ");
            PRESS(FN_SHARP);
            Keyboard.press(KEY_F12);
        }
    } else {
        if(IS_PRESSED(FN_SHARP)) {
            p("^FSHARP^ ");
            RELEASE(FN_SHARP);
            Keyboard.release(KEY_F12);
        }
    }
    Control::setupInput(FnNumpad::p3);
}
