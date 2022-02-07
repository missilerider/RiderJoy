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

uint8_t Switch2p::getHighestJoyButton(ControlData *d) {
    return d->button[0] > d->button[1] ? d->button[0] : d->button[1];
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

void Switch2p::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
}

void Switch2p::process(Joystick_ *j) {
}

void Switch2p::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    uint8_t status = Control::readDigital(d->pin[0]) == LOW ? 2 : 1;
    uint8_t stage = d->getStage();

    switch(d->getMomentary()) {
        case CONTROL_MOMENTARY_NO:
            j->setButton(d->button[0], status == 1 ? 1 : 0);
            j->setButton(d->button[1], status == 2 ? 1 : 0);
            break;

        case CONTROL_MOMENTARY_SIMPLE:
            // Stage 1-2 == status 1 a 2 en pulsación
            // Stage 4-5 == status 1 a 2 en idle

            // Si hay cambio de estado
            if((status == 1 && stage != CTRL_MOMENTARY_STAGE1) || 
                (status == 2 && stage != CTRL_MOMENTARY_STAGE2)) {

                d->timeout = MOMENTARY_LONG_MS;

                switch(status) {
                    case 1: d->setStage1(); break;
                    case 2: d->setStage2(); break;
                }

                j->setButton(d->button[0], status == 1 ? 1 : 0);
                j->setButton(d->button[1], status == 2 ? 1 : 0);


            } else {
                // Estado no cambiado. Tempus fugit
                if(d->loop(elapsed)) {
                    // Timeout no cumplido
                    j->setButton(d->button[0], status == 1 ? 1 : 0);
                    j->setButton(d->button[1], status == 2 ? 1 : 0);
                } else { // Timeout expirado
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);
                }
            }

            break;

        case CONTROL_MOMENTARY_FULL:
            // Stage 1-2 == status 1 a 3 en pulsación
            // Stage 4-5 == status 1 a 3 en idle
            if(stage >= CTRL_MOMENTARY_STAGE4) { // Fase Idle
                if(d->loop(elapsed)) {
                    // Timeout en marcha (haciendo idle)
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);
                } else {
                    // Timeout idle expirado. Cambiamos de valor si debe
                    if((status == 1 && stage != CTRL_MOMENTARY_STAGE4) || 
                        (status == 2 && stage != CTRL_MOMENTARY_STAGE5)) {
                            // Estamos en estado distinto del anterior. Empezamos nueva pulsación en posición actual
                            switch(status) {
                                case 1: d->setStage1(); break;
                                case 2: d->setStage2(); break;
                            }

                            d->timeout = MOMENTARY_LONG_MS; // Empezamos a contar la pulsacion desde cero
                        }
                }
            } else {
                // Pulsacion
                if(d->loop(elapsed)) {
                    j->setButton(d->button[0], stage == CTRL_MOMENTARY_STAGE1 ? 1 : 0);
                    j->setButton(d->button[1], stage == CTRL_MOMENTARY_STAGE2 ? 1 : 0);
                } else {
                    // Pulsación recién terminada. Vamos a idle
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);

                    switch(stage) { // Iniciamos idle de la posición en la que estábamos
                        default:
                        case CTRL_MOMENTARY_STAGE1: d->setStage4(); break;
                        case CTRL_MOMENTARY_STAGE2: d->setStage5(); break;
                    }

                    d->timeout = IDLE_LONG_MS;
                }
            }
            break;
    }
}
