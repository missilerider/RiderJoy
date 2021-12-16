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

Pot *Pot::i() {
    this->inverted = !this->inverted;
    return this;
}

void Pot::init() {
    this->setupPullup(this->input);
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
        pln(this->lastValue);

        if(this->inverted) {
            this->setAxis(
                j, 
                this->axis, 
                v
            );
        } else {
            this->setAxis(
                j, 
                this->axis, 
                1023 - v
            );
        }
    }
}
