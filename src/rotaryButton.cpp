#include "rotaryButton.h"

uint8_t lastA = 0, a;
uint8_t lastB = 0, b;
uint8_t dir, lastDir;
int8_t *step;

uint8_t RotaryButton::getHighestJoyButton(ControlData *d) {
    return d->button[0] > d->button[1] ? d->button[0] : d->button[1];
}

void RotaryButton::init(ControlData *d) {
    Control::setupPullup(d->pin[0]);
    Control::setupPullup(d->pin[1]);
}

void RotaryButton::poll(ControlData *d) {
    a = Control::readDigital(d->pin[0]);
    b = Control::readDigital(d->pin[1]);

    step = (int8_t*)&d->button[2];

    lastA = (d->getMomentary() & CONTROL_MOMENTARY_SIMPLE) ? LOW : HIGH; // Primer bit ...01...
    lastB = (d->getMomentary() & CONTROL_MOMENTARY_FULL) ? LOW : HIGH; // Segundo bit ...10...
    // Si lastA = lastB = 1, getMomentary devolverá dos bits ...11...

    if((lastA == a || lastB == b) && (lastA != a || lastB != b)) {
        if(a == lastA) {
            if(a == LOW) {
                if(b == LOW) *step -= 1;
                else *step += 1;
            } else {
                if(b == LOW) *step += 1;
                else *step -= 1;
            }
        } else { // a != lastA
            if(b == LOW) {
                if(a == LOW) *step += 1;
                else *step -= 1;
            } else {
                if(a == LOW) *step -= 1;
                else *step += 1;
            }
        }

        /*
        p(lastA);
        p(lastB);
        p("/");
        p(a == LOW ? "1" : "0");
        p(b == LOW ? "1" : "0");
        p(":");
        p(*step);
        p(">");
        */
    

        // Guarda estados en stage, con STAGE1 y STAGE2
        if(a == LOW) {
            if(b == LOW) d->setMomentary(CTRLMASK_MOMENTARY); // 11
            else d->setMomentary(CONTROL_MOMENTARY_SIMPLE); // 01
        } else {
            if(b == LOW) d->setMomentary(CONTROL_MOMENTARY_FULL); // 10
            else d->setMomentary(CONTROL_MOMENTARY_NO); // 00
        }

        lastA = (d->getMomentary() & CONTROL_MOMENTARY_SIMPLE) ? LOW : HIGH; // Primer bit ...01...
        lastB = (d->getMomentary() & CONTROL_MOMENTARY_FULL) ? LOW : HIGH; // Segundo bit ...10...

        /*
        p(lastA);
        p(lastB);
        pln();
        */
    }
}

void RotaryButton::process(ControlData *d, Joystick_ *j, uint8_t elapsed) {
    step = (int8_t*)&d->button[2];
    lastA = 0b1 << ((d->getStage() & CTRL_MOMENTARY_STAGE6) >> 6); // minIdle es 1, 2, 4 u 8
    dir = (*step >= (int8_t)lastA ? 2 : (*step <= -(int8_t)lastA ? 0 : 1)); // dir = 0, izq. 2 = der. 1 = quieto

    lastDir = (d->getStage() >> 5) & 0b11;

/*    if(dir != 1) {
        p("minIdle: ");
        p(lastA);
        p(" ");
        p("Step ");
        p(*step);
        p(" ");
        p("Dir: ");
        p(lastDir);
        p(">");
        p(dir);
        pln();
    }*/

    if(d->loop(elapsed)) {
        // Timeout no cumplido. En medio de señalización de un giro
        if(!CTRL_GET_STAGE_BIT(d, 0)) {
            // En pulsación
            j->setButton(d->button[0], lastDir == 2 ? 1 : 0);
            j->setButton(d->button[1], lastDir == 0 ? 1 : 0);
        } else {
            // En idle
            j->setButton(d->button[0], 0);
            j->setButton(d->button[1], 0);
        }
    } else {
        // Timeout terminado
        if(!CTRL_GET_STAGE_BIT(d, 0)) {
            // En pulsación; pasamos a idle
            j->setButton(d->button[0], lastDir == 2 ? 1 : 0);
            j->setButton(d->button[1], lastDir == 0 ? 1 : 0);

            d->timeout = IDLE_MS;
            d->setStageBit(0, 1);
        } else {
            // Idle terminado. Aceptamos cambios de giro y tal
            if(dir != 1) { // Gira
                if((dir > 1 && *step < lastA) ||
                    (dir < 1 && *step > -lastA)) {

                    dir = 1; // No ha girado lo suficiente, así que no hay giro
                }


                *step = 0; // Reseteamos el giro, que algo hemos rotado completamente
                
                // Iniciamos pulsación
                d->timeout = MOMENTARY_MS;
                d->setStageBit(0, 0);

                // Guardamos dirección del giro
                if(lastDir != dir) {
                    d->setStageBit(0, dir & 0b1 ? 1 : 0);
                    d->setStageBit(1, dir & 0b10 ? 1 : 0);
                }

                j->setButton(d->button[0], lastDir == 2 ? 1 : 0);
                j->setButton(d->button[1], lastDir == 0 ? 1 : 0);
            } else {
                // Acabamos de terminar timeout de idle y no giramos
                j->setButton(d->button[0], 0);
                j->setButton(d->button[1], 0);
            }
        }
    }
}
