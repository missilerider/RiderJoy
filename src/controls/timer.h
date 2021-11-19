#include <Arduino.h>

#define MOMENTARY_MS    20;

extern unsigned long now;

class Timer {
private:
    uint16_t ms;
    unsigned long t0 = 0; // t0: pulsacion inicial
    bool lastPressed = false;

public:
    Timer() {
        this->ms = MOMENTARY_MS;
    }

    Timer(uint16_t ms) {
        this->ms = ms;
    }

    void tick(bool pressed) {
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
                t0 = 0;
                this->lastPressed = false;
            }
        }
    }

    bool isPushed() {
        return this->lastPressed ? 
            (now - t0 <= ms) : 
            false;
    }
};
