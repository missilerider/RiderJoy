#include <Arduino.h>
#include "switch3p.h"

Switch3p::Switch3p(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t j3) {
    this->i1 = i1;
    this->i2 = i2;

    this->j1 = j1;
    this->j2 = j2;
    this->j3 = j3;
}

uint8_t Switch3p::getHighestJoyButton() {
    uint8_t max = this->j1;

    if(this->j3 > max) max = this->j3;

    if((this->j2 != 255) && (this->j2 > max)) max = this->j2;

    return max;
}

Switch3p *Switch3p::momentary() {
    this->timer = new Timer();
    return this;
}

Switch3p *Switch3p::i() {
    uint8_t tmp = this->j1;
    this->j1 = this->j2;
    this->j2 = tmp;
    return this;
}

void Switch3p::init() {
    this->setupPullup(i1);
    this->setupPullup(i2);
}

void Switch3p::process(Joystick_ *j) {
    uint8_t pin1 = this->readDigital(this->i1);
    uint8_t pin2 = this->readDigital(this->i2);
    uint8_t status;
    if(pin1 == LOW) status = 1; // Pos 1
    else if(pin2 == LOW) status = 3; // Pos 3
    else status = 2; // Pos central

    // 3 botones
    if(this->timer == NULL) {
        // Always ON
        if(this->j2 != 255) {
            j->setButton(this->j1, pin1 == LOW ? 1 : 0);
            j->setButton(this->j3, pin2 == LOW ? 1 : 0);

            if(pin1 == HIGH && pin2 == HIGH)
                j->setButton(this->j2, 1);
            else
                j->setButton(this->j2, 0);
        } else {
            // 2 botones
            j->setButton(this->j1, pin1 == LOW ? 1 : 0);
            j->setButton(this->j3, pin2 == LOW ? 1 : 0);
        }
    } else {
        
        // Momentary
        if(status != this->lastStatus) {
            // Si cambia de estado debemos pulsar desde el principio
            this->lastStatus = status;
            this->timer->reset();
        }
        // Momentary
        this->timer->tick(true); // Siempre estamos en alguna posición
        switch(status) {
            case 1: // Pos 1
                j->setButton(this->j1, this->timer->isPushed() ? 1 : 0);
                j->setButton(this->j2, 0); // Pos 2 siempre off
                j->setButton(this->j3, 0); // Pos 3 siempre off
                break;

            case 2: // Pos 2
                j->setButton(this->j1, 0); // Pos 1 siempre off
                j->setButton(this->j2, this->timer->isPushed() ? 1 : 0);
                j->setButton(this->j3, 0); // Pos 3 siempre off
                break;

            case 3: // Pos 3
                j->setButton(this->j1, 0); // Pos 1 siempre off
                j->setButton(this->j2, 0); // Pos 2 siempre off
                j->setButton(this->j3, this->timer->isPushed() ? 1 : 0);
                break;
        }
    }
}
