#include "RotaryAxis.h"

extern unsigned long now;

RotaryAxis::RotaryAxis(Input i1, Input i2, uint8_t axis, uint8_t steps) :
        Rotary(i1, i2) {

    this->axis = axis;
    this->minS = steps;
    this->pos = 512.0f;
    this->lastStep = this->step;
}

void RotaryAxis::getAxisRequirements(uint8_t *axisArray) {
    axisArray[this->axis] = 1;

    p("a");
    pln(this->axis);
}

void RotaryAxis::process(Joystick_ *j) {
    //pln(this->step);

    if(this->step == this->lastStep) {
        if(t0 == 0) {
            t0 = now; // Empezamos a contar el tiempo
        } else {
            if(now > t0 + ROTARY_IDLE_TIMEOUT) {
                t0 = 1;
            }
        }
    } else {
        t0 = 0;
    }

    this->lastStep = this->step;
    return;

    this->pos += this->step;

    // Si nos hemos detenido, se deja de acelerar
    if(this->step < this->minS)
        this->endProcess();



    // Clamping a eje joy
    if(this->pos > 1023.0f) this->pos = 1023.0f;
    else if(this->pos < 0.0f) this->pos = 0.0f;

    this->setAxis(j, this->axis, (uint16_t)this->pos);
}
