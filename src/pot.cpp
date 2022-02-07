#include <Arduino.h>
#include "pot.h"

Pot::Pot(Input input, uint8_t axis) {
    this->input = input;
    this->axis = axis;
}

void Pot::getAxisRequirements(uint8_t *axisArray) {
    axisArray[this->axis] = 1;

    p("a");
    pln(this->axis);
}

void Pot::getAxisRequirements(ControlData *d, uint8_t *axisArray) {
    axisArray[d->button[0]] = 1;

    p("a");
    pln(d->button[0]);
}

Pot *Pot::i() {
    this->inverted = !this->inverted;
    return this;
}

Pot *Pot::exp(float e) {
    this->e = e;

    return this;
}

void Pot::init() {
    this->setupPullup(this->input);
}

void Pot::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
}

void Pot::process(Joystick_ *j) {
    uint16_t v;
    v = this->readAnalog(this->input);
    
    // Si varía más que POT_ERROR o llega a un extremo, se actualiza el eje
    if((v > this->lastValue + POT_ERROR) || 
        (v < this->lastValue - POT_ERROR) || 
        (this->lastValue > 0 && v == 0) || 
        (this->lastValue < 1023 && v == 1023)) {

        this->lastValue = v;
        //pln(this->clamp(this->lastValue));

        if(this->inverted) { // Invertido
            Control::setAxis(
                j, 
                this->axis, 
                this->clamp(v)
            );
        } else {
            this->setAxis(
                j, 
                this->axis, 
                this->clamp(1023 - v)
            );
        }
    }
}

void Pot::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    uint16_t v;
    v = Control::readAnalog(d->pin[0]);
    
    uint16_t *lastValue = (uint16_t*)&d->button[1];

    // Si varía más que POT_ERROR o llega a un extremo, se actualiza el eje
    if((v > *lastValue + POT_ERROR) || 
        (v < *lastValue - POT_ERROR) || 
        (*lastValue > 0 && v == 0) || 
        (*lastValue < 1023 && v == 1023)) {

        *lastValue = v;
        //pln(this->clamp(this->lastValue));

        if(d->getStage() == CTRL_MOMENTARY_STAGE1) { // Invertido
            Control::setAxis(
                j, 
                d->button[0], 
                v
            );
        } else {
            Control::setAxis(
                j, 
                d->button[0], 
                1023 - v
            );
        }
    }
}



uint16_t Pot::clamp(uint16_t value) {
    float v = value / 1023.0f; // [0,1]

    v = powf(v, this->e);

    return (uint16_t)(v * 1023.0f);
}
