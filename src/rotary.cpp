#include <Arduino.h>
#include "rotary.h"

Rotary::Rotary(Input i1, Input i2) {
    this->i1 = i1;
    this->i2 = i2;
}

Rotary *Rotary::i() {
    uint8_t tmp = this->i1;
    this->i1 = this->i2;
    this->i2 = tmp;
    return this;
}

Rotary *Rotary::a(float accel, float exp) {
    this->accel = accel;
    this->exp = exp;
    return this;
}

void Rotary::init() {
    this->setupPullup(i1);
    this->setupPullup(i2);
}

float Rotary::calcStep() {
    return this->accel + (this->step * this->exp);
}

void Rotary::poll() {
    uint8_t a = this->readDigital(this->i1);
    uint8_t b = this->readDigital(this->i2);

    if((this->lastA == a || this->lastB == b) && (this->lastA != a || this->lastB != b)) {
        if(a == this->lastA) {
            if(a == LOW) {
                if(b == LOW) this->step--;
                else this->step += this->calcStep();
            } else {
                if(b == LOW) this->step++;
                else this->step -= this->calcStep();
            }
        } else { // a != lastA
            if(b == LOW) {
                if(a == LOW) this->step++;
                else this->step -= this->calcStep();
            } else {
                if(a == LOW) this->step--;
                else this->step += this->calcStep();
            }
        }

        this->lastA = a;
        this->lastB = b;
    }
}

void Rotary::endProcess() {
    this->step = 0;
}