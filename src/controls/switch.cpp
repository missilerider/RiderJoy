#include <Arduino.h>
#include "switch.h"

Switch::Switch(Input i1, Input i2, uint8_t j1, uint8_t j2, uint8_t j3) {
    this->i1 = i1;
    this->i2 = i2;
    this->j1 = j1;
    this->j2 = j2;
    this->j3 = j3;
}

Switch::Switch(Input i1, Input i2, uint8_t j1, uint8_t j2) {
    this->i1 = i1;
    this->i2 = i2;
    this->j1 = j1;
    this->j2 = 255; // Boton intermedio opcional
    this->j3 = j2;
}

uint8_t Switch::getHighestJoyButton() {
    uint8_t max = this->j1;

    if(this->j3 > max) max = this->j3;

    if((this->j2 != 255) && (this->j2 > max)) max = this->j2;

    return max;
}

Switch *Switch::alwaysOn() {
    this->isAlwaysOn = true;
    return this;
}

Switch *Switch::i() {
    uint8_t tmp = this->j1;
    this->j1 = this->j2;
    this->j2 = tmp;
    return this;
}

void Switch::init() {
    this->setupPullup(i1);
    this->setupPullup(i2);
}

void Switch::process(Joystick_ *j) {
    uint8_t pin1 = this->readDigital(this->i1);
    uint8_t pin2 = this->readDigital(this->i2);

    // 3 botones
    if(this->isAlwaysOn) {
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
    }
}
