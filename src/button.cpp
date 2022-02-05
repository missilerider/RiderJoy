#include <Arduino.h>
#include "button.h"

Button::Button(Input input, uint8_t jButton) {
    this->input = input;
    this->jButton = jButton;
}

Button::Button(Input input, uint8_t j1, uint8_t j2) {
    this->input = input;
    this->jButton = j1;
    this->jButton2 = j2;
}

uint8_t Button::getHighestJoyButton() {
    return this->jButton;
}

uint8_t Button::getHighestJoyButton(ControlData *d) {
    return d->button[0];
}

Button *Button::i() {
    this->inverted = !this->inverted;
    return this;
}

Button *Button::momentary() {
    if(this->timer == NULL)
        this->timer = new Timer(MOMENTARY_LONG_MS);

    return this;
}

Button *Button::momentaryFull() {
    if(this->timer == NULL) {
        this->timer = new Timer(MOMENTARY_LONG_MS);
        this->timer->forceFull();
    }

    return this;
}

void Button::init() {
    this->setupPullup(this->input);
    p(this->input);
    p("=>");
    pln(this->jButton);
}

void Button::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
//    p(d->pin[0]);
//    p("=>");
//    pln(d->button[0]);
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

void Button::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    switch(d->getMomentary()) {
        case CONTROL_MOMENTARY_NO:
            j->setButton(
                d->button[0], 
                Control::readDigital(d->pin[0]) == LOW ? 1 : 0
            );
            return;

        case CONTROL_MOMENTARY_SIMPLE:
            if(Control::readDigital(d->pin[0]) == LOW) {
                // Pulsado
                switch(d->getStage()) {
                    case CTRL_MOMENTARY_STAGE0:
                        // Recién pulsado
                        d->setStage1(); // Pulsado desde un tiempo
                        d->timeout = MOMENTARY_LONG_MS; // Tiempo de pulsación máxima
                        j->setButton(d->button[0], 1);
                        break;

                    case CTRL_MOMENTARY_STAGE1:
                        // Ya pulsado antes
                        if(d->loop(elapsed)) {
                            // Timeout no cumplido
                            j->setButton(d->button[0], 1);
                        } else {
                            // Timeout finalizado
                            d->setStage2(); // Fin de pulsación
                            j->setButton(d->button[0], 1);
                        }
                        break;

                    case CTRL_MOMENTARY_STAGE2:
                        // Timeout finalizado. Ya en off
                        j->setButton(d->button[0], 0);
                        break;
                }
            } else {
                // No pulsado
                j->setButton(d->button[0], 0);
                if(d->getStage() != CTRL_MOMENTARY_STAGE0)
                    d->setStage0();
            }
            break;

        case CONTROL_MOMENTARY_FULL:
            if(Control::readDigital(d->pin[0]) == LOW) {
                // Pulsado
                switch(d->getStage()) {
                    case CTRL_MOMENTARY_STAGE0:
                        // Recién pulsado
                        d->setStage1(); // Pone en pulsado
                        d->timeout = MOMENTARY_LONG_MS; // Tiempo de pulsación máxima
                        j->setButton(d->button[0], 1);
                        break;

                    case CTRL_MOMENTARY_STAGE1:
                        // Ya pulsado antes, en pulsación
                        if(d->loop(elapsed)) {
                            // Timeout no cumplido
                            j->setButton(d->button[0], 1);
                        } else {
                            // Timeout finalizado
                            d->setStage2(); // Fase de espera
                            d->timeout = IDLE_LONG_MS; // Tiempo de espera entre pulsaciones
                            j->setButton(d->button[0], 0);
                        }
                        break;

                    case CTRL_MOMENTARY_STAGE2:
                        // Ya pulsado antes, en espera
                        if(d->loop(elapsed)) {
                            // Timeout no cumplido
                            j->setButton(d->button[0], 0);
                        } else {
                            // Timeout finalizado
                            d->setStage1(); // Fase de pulsación
                            d->timeout = MOMENTARY_LONG_MS; // Tiempo de pulsación máxima
                            j->setButton(d->button[0], 1);
                        }
                        break;
                }
            } else {
                // No pulsado
                j->setButton(d->button[0], 0);
                if(d->getStage() != CTRL_MOMENTARY_STAGE0)
                    d->setStage0();
            }
            break;
    }
}
