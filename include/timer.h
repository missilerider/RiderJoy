#include <Arduino.h>
#include "config_global.h"

#ifndef MOMENTARY_MS
    #define MOMENTARY_MS    50;
#endif
#ifndef IDLE_MS
    #define IDLE_MS    0;
#endif

extern unsigned long now;

class Timer {
private:
    uint16_t ms = MOMENTARY_MS;
    uint16_t idle = IDLE_MS;

    unsigned long t0 = 0; // t0: momento de pulsacion del botón
    bool lastPressed = false;
    bool forceFullCycle = false;

public:
    Timer() { }

    Timer(uint16_t ms) {
        this->ms = ms;
    }

    Timer(uint16_t ms, uint16_t idle) {
        this->ms = ms;
        this->idle = idle;
    }

    void setIdle(uint16_t idle) {
        this->idle = idle;
    }

    void tick(bool pressed) {
        // Si se fuerza la pulsación el ciclo completo forzamos que se mantenga el input pulsado hasta que sea necesario
        if(this->forceFullCycle) {
            if(now - t0 <= ms) {
                pressed = true;
            }
        }

        if(!this->lastPressed) {
            // Si antes estaba sin pulsar
            if(pressed) { // ...pero acabamos de pulsar
                // Guardamos tiempos y estado
                this->lastPressed = true;
                this->t0 = now;
            }
        } else {
            // Si estabamos pulsando antes
            if(!pressed) { // ...pero acabamos de soltar
                if(now > t0 + idle) { // ...y hemos pasado el tiempo de espera para repetir pulsación
                    t0 = 0;
                    this->lastPressed = false;
                }
            }
        }
    }

    bool isPushed() {
        return this->lastPressed ? 
            (now - t0 <= ms) : 
            false;
    }

    void reset() {
        this->lastPressed = false;
        this->t0 = 0;
    }

    void forceFull() {
        this->forceFullCycle = true;
    }
};
