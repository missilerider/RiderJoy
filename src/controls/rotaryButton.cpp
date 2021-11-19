#include "rotaryButton.h"

RotaryButton::RotaryButton(Input i1, Input i2, uint8_t j1, uint8_t j2) :
        Rotary(i1, i2) {

    this->j1 = j1;
    this->j2 = j2;
}

void RotaryButton::process(Joystick_ *j) {
    t1.tick(this->step > 0);
    t2.tick(this->step < 0);

    j->setButton(this->j1, t1.isPushed() ? LOW : HIGH);
    j->setButton(this->j2, t2.isPushed() ? LOW : HIGH);

    this->endProcess();
}
