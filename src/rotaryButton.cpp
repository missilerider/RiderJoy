#include "rotaryButton.h"

uint8_t lastA = 0;
uint8_t lastB = 0;

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

uint8_t RotaryButton::getHighestJoyButton(ControlData *d) {
    return d->button[0] > d->button[1] ? d->button[0] : d->button[1];
}

RotaryButton *RotaryButton::minIdle(uint16_t idle) {
    this->t1->setIdle(idle);

    return this;
}

void RotaryButton::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
    Control::setupPullup(d->pin[1]);
}

void Rotary::poll(ControlData *d) {
    uint8_t a = Control::readDigital(d->pin[0]);
    uint8_t b = Control::readDigital(d->pin[1]);

    int8_t *step = (int8_t*)&d->button[2];

    lastA = d->getMomentary() & CONTROL_MOMENTARY_SIMPLE; // Primer bit ...01...
    lastB = d->getMomentary() & CONTROL_MOMENTARY_FULL; // Segundo bit ...10...
    // Si lastA = lastB = 1, getStage devolverá STAGE3, que son dos bits ...11...

    if((lastA == a || lastB == b) && (lastA != a || lastB != b)) {
        if(a == lastA) {
            if(a == LOW) {
                if(b == LOW) *step--;
                else *step ++;
            } else {
                if(b == LOW) *step++;
                else *step --;
            }
        } else { // a != lastA
            if(b == LOW) {
                if(a == LOW) *step++;
                else *step --;
            } else {
                if(a == LOW) *step--;
                else *step ++;
            }
        }

        // Guarda estados en stage, con STAGE1 y STAGE2
        if(a == LOW) {
            if(b == LOW) d->setMomentary(CTRLMASK_MOMENTARY); // 11
            else d->setMomentary(CONTROL_MOMENTARY_SIMPLE); // 01
        } else {
            if(b == LOW) d->setMomentary(CONTROL_MOMENTARY_FULL); // 10
            else d->setMomentary(CONTROL_MOMENTARY_NO); // 00
        }
    }
}

void RotaryButton::process(Joystick_ *j) {
    // this->button[2] es el valor de minIdle
    int8_t dir = (this->step >= this->button[2] ? 1 : (this->step <= -this->button[2] ? -1 : 0));

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

void RotaryButton::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    int8_t *step = (int8_t*)&d->button[2];
    lastA = d->getStage() >> 5; // minIdle
    lastB = (*step >= lastA ? 1 : (*step <= -lastA ? -1 : 0)); // dir = 1, izq. 2 = der. 0 = quieto

    if(this->t1->isCycleDone()) {
        this->lastDir = dir;
        //pln("Cycle Done");
    }

    this->t1->tick(lastB != 0);


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
        *step = 0;
}