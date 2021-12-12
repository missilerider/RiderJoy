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
    if(this->inverted) {
        this->setAxis(
            j, 
            this->axis, 
            this->readAnalog(this->input)
        );
    } else {
        this->setAxis(
            j, 
            this->axis, 
            1023 - this->readAnalog(this->input)
        );
    }
    //pln(this->readAnalog(this->input));
}
