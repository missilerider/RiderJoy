#include <Arduino.h>
#include "switch2p.h"

Switch2p::Switch2p(Input i1, uint8_t j1, uint8_t j2) {
    this->i1 = i1;
    this->j1 = j1;
    this->j2 = j2;
}

uint8_t Switch2p::getHighestJoyButton() {
    return this->j1 > this->j2 ? this->j1 : this->j2;
}

Switch2p *Switch2p::momentary() {
    this->timer = new Timer(MOMENTARY_LONG_MS);
    return this;
}

Switch2p *Switch2p::i() {
    uint8_t tmp = this->j1;
    this->j1 = this->j2;
    this->j2 = tmp;
    return this;
}

void Switch2p::init() {
    this->setupPullup(i1);
}

void Switch2p::process(Joystick_ *j) {
    uint8_t pin = this->readDigital(this->i1);

    if(this->timer == NULL) {
        // Always ON
        j->setButton(this->j1, pin == LOW ? 1 : 0);
        j->setButton(this->j2, pin == HIGH ? 1 : 0);
    } else {
        if(pin != this->lastStatus) {
            // Si cambia de estado debemos pulsar desde el principio
            this->lastStatus = pin;
            this->timer->reset();
        }
        // Momentary
        this->timer->tick(true); // Siempre en alguna posición

        if(pin == LOW) {
            // Switch en pos 1
            j->setButton(this->j1, this->timer->isPushed() ? 1 : 0);
            j->setButton(this->j2, 0); // Pos 2 siempre off
        } else {
            // Switch en pos 2
            j->setButton(this->j2, this->timer->isPushed() ? 1 : 0);
            j->setButton(this->j1, 0); // Pos 1 siempre off
        }
    }
}
