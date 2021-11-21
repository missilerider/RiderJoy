#include <Arduino.h>
#include "button.h"

Button::Button(Input input, uint8_t jButton) {
    this->input = input;
    this->jButton = jButton;
}

uint8_t Button::getHighestJoyButton() {
    return this->jButton;
}

Button *Button::i() {
    this->inverted = !this->inverted;
    return this;
}

Button *Button::momentary() {
    if(this->timer == NULL)
        this->timer = new Timer();

    return this;
}

void Button::init() {
    this->setupPullup(this->input);
    p(this->input);
    p("=>");
    pln(this->jButton);
}

void Button::process(Joystick_ *j) {
    // AlwaysOn o Momentary?
    if(this->timer == NULL) {
        j->setButton(
            this->jButton, 
            this->readDigital(this->input) == LOW ? 
                (this->inverted ? 0 : 1) : 
                (this->inverted ? 1 : 0)
        );
    } else {
        this->timer->tick(this->readDigital(this->input) == (this->inverted ? HIGH : LOW));

        j->setButton(this->jButton, this->timer->isPushed() ? 1 : 0);
    }
}
