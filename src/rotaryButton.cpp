#include "rotaryButton.h"

RotaryButton::RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t steps) :
        Rotary(i1, i2) {

    this->j1 = j1;
    this->j2 = j2;

    this->minS = steps;

    this->t1 = new Timer();

    this->t1->forceFull();
}

uint8_t RotaryButton::getHighestJoyButton() {
    return this->j1 > this->j2 ? this->j1 : this->j2;
}

RotaryButton *RotaryButton::minIdle(uint16_t idle) {
    this->t1->setIdle(idle);

    return this;
}

void RotaryButton::process(Joystick_ *j) {
    int8_t dir = (this->step >= this->minS ? 1 : (this->step <= -this->minS ? -1 : 0));

    // Si inicia un nuevo movimiento, inciamos la pulsación momentánea siempre
/*    if(dir != this->lastDir && dir != 0) {
        this->t1->reset();
        this->lastDir = dir;
    }*/

    if(this->t1->isCycleDone()) {
        this->lastDir = dir;
        //pln("Cycle Done");
    }

    this->t1->tick(dir != 0);

    // Si nos movemos
/*    if(dir != 0 && this->t1->isPushed()) {
        p("s:");
        p(this->step);
        p("/");
        pln(this->t1->isPushed() ? "1":"0");
    }*/

    if(this->lastDir > 0) {
        j->setButton(this->j1, this->t1->isPushed() ? 1 : 0);
        j->setButton(this->j2, 0);
    } else {
        j->setButton(this->j1, 0);
        j->setButton(this->j2, this->t1->isPushed() ? 1 : 0);
    }

    if(this->step >= this->minS || this->step <= -this->minS) {
        p("s:");
        switch(dir) {
            case 0: p("|"); break;
            case 1: p(">"); break;
            case -1: p("<"); break;
        }
        switch(this->lastDir) {
            case 0: p("|"); break;
            case 1: p(">"); break;
            case -1: p("<"); break;
        }
        p(this->step);
        p("/");
        p(this->t1->isPushed() ? "1":"0");
        pln(this->t1->isCycleDone() ? ":1":":0");

    }

    if(dir != 0)
        this->endProcess();
}
