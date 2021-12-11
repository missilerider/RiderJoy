#include "rotaryButton.h"

RotaryButton::RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t steps) :
        Rotary(i1, i2) {

    this->j1 = j1;
    this->j2 = j2;

    this->minS = steps;
}

uint8_t RotaryButton::getHighestJoyButton() {
    return this->j1 > this->j2 ? this->j1 : this->j2;
}

RotaryButton *RotaryButton::minIdle(uint16_t idle) {
    this->t1.setIdle(idle);
    this->t2.setIdle(idle);

    return this;
}

void RotaryButton::process(Joystick_ *j) {
    t1.tick(this->step >= this->minS);
    t2.tick(this->step <= -this->minS);

    if(this->step >= this->minS || this->step <= -this->minS) {
        p("s:");
        pln(this->step);
        this->endProcess();
    }

    j->setButton(this->j1, t1.isPushed() ? 1 : 0);
    j->setButton(this->j2, t2.isPushed() ? 1 : 0);
}
