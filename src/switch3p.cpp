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

    if(this->j2 > max) max = this->j2;

    if(this->j3 > max) max = this->j3;

    return max;
}

uint8_t Switch3p::getHighestJoyButton(ControlData *d) {
    uint8_t max = d->button[0];

    if(d->button[1] > max) max = d->button[1];

    if(d->button[2] > max) max = d->button[2];

    return max;
}

Switch3p *Switch3p::momentary() {
    this->timer = new Timer(MOMENTARY_LONG_MS);
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

void Switch3p::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
    Control::setupPullup(d->pin[1]);
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
        switch(status) {
            case 1:
                j->setButton(this->j1, 1);
                j->setButton(this->j2, 0);
                j->setButton(this->j3, 0);
                break;

            case 2:
                j->setButton(this->j1, 0);
                j->setButton(this->j2, 1);
                j->setButton(this->j3, 0);
                break;

            case 3:
                j->setButton(this->j1, 0);
                j->setButton(this->j2, 0);
                j->setButton(this->j3, 1);
                break;
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

void Switch3p::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    uint8_t pin1 = Control::readDigital(d->pin[0]);
    uint8_t pin2 = Control::readDigital(d->pin[1]);
    uint8_t status;
    if(pin1 == LOW) status = 1; // Pos 1
    else if(pin2 == LOW) status = 3; // Pos 3
    else status = 2; // Pos central
    uint8_t stage = d->getStage();

    switch(d->getMomentary()) {
        case CONTROL_MOMENTARY_NO:
            j->setButton(d->button[0], status == 1 ? 1 : 0);
            j->setButton(d->button[1], status == 2 ? 1 : 0);
            j->setButton(d->button[2], status == 3 ? 1 : 0);
            break;

        case CONTROL_MOMENTARY_SIMPLE:
            // Stage 1-3 == status 1 a 3 en pulsación
            // Stage 4-6 == status 1 a 3 en idle

            // Si hay cambio de estado
            if((status == 1 && stage != CTRL_MOMENTARY_STAGE1) || 
                (status == 2 && stage != CTRL_MOMENTARY_STAGE2) || 
                (status == 3 && stage != CTRL_MOMENTARY_STAGE3)) {

                d->timeout = MOMENTARY_LONG_MS;

                switch(status) {
                    case 1: d->setStage1(); break;
                    case 2: d->setStage2(); break;
                    case 3: d->setStage3(); break;
                }

                j->setButton(d->button[0], status == 1 ? 1 : 0);
                j->setButton(d->button[1], status == 2 ? 1 : 0);
                j->setButton(d->button[2], status == 3 ? 1 : 0);

            } else {
                // Estado no cambiado. Tempus fugit
                if(d->loop(elapsed)) {
                    // Timeout no cumplido
                    j->setButton(d->button[0], status == 1 ? 1 : 0);
                    j->setButton(d->button[1], status == 2 ? 1 : 0);
                    j->setButton(d->button[2], status == 3 ? 1 : 0);
                } else { // Timeout expirado
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);
                    j->setButton(d->button[2], 0);
                }
            }

            break;

        case CONTROL_MOMENTARY_FULL:
            // Stage 1-3 == status 1 a 3 en pulsación
            // Stage 4-6 == status 1 a 3 en idle
            if(stage >= CTRL_MOMENTARY_STAGE4) { // Fase Idle
                if(d->loop(elapsed)) {
                    // Timeout en marcha (haciendo idle)
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);
                    j->setButton(d->button[2], 0);
                } else {
                    // Timeout idle expirado. Cambiamos de valor si debe
                    if((status == 1 && stage != CTRL_MOMENTARY_STAGE4) || 
                        (status == 2 && stage != CTRL_MOMENTARY_STAGE5) || 
                        (status == 3 && stage != CTRL_MOMENTARY_STAGE6)) {
                            // Estamos en estado distinto del anterior. Empezamos nueva pulsación en posición actual
                            switch(status) {
                                case 1: d->setStage1(); break;
                                case 2: d->setStage2(); break;
                                case 3: d->setStage3(); break;
                            }

                            d->timeout = MOMENTARY_LONG_MS; // Empezamos a contar la pulsacion desde cero
                        }
                }
            } else {
                // Pulsacion
                if(d->loop(elapsed)) {
                    j->setButton(d->button[0], stage == CTRL_MOMENTARY_STAGE1 ? 1 : 0);
                    j->setButton(d->button[1], stage == CTRL_MOMENTARY_STAGE2 ? 1 : 0);
                    j->setButton(d->button[2], stage == CTRL_MOMENTARY_STAGE3 ? 1 : 0);
                } else {
                    // Pulsación recién terminada. Vamos a idle
                    j->setButton(d->button[0], 0);
                    j->setButton(d->button[1], 0);
                    j->setButton(d->button[2], 0);

                    switch(stage) { // Iniciamos idle de la posición en la que estábamos
                        default:
                        case CTRL_MOMENTARY_STAGE1: d->setStage4(); break;
                        case CTRL_MOMENTARY_STAGE2: d->setStage5(); break;
                        case CTRL_MOMENTARY_STAGE3: d->setStage6(); break;
                    }

                    d->timeout = IDLE_LONG_MS;
                }
            }
            break;
    }
}
