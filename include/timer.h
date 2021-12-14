#include <Arduino.h>

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
    bool forceFullPress = false;

public:
    Timer() { }

    Timer(uint16_t ms) {
        this->ms = ms;
    }

    Timer(uint16_t ms, uint16_t idle) {
        this->ms = ms;
        this->idle = idle;
    }

    Timer(uint16_t ms, uint16_t idle, bool fullPress) {
        this->ms = ms;
        this->idle = idle;
        this->forceFullPress = fullPress;
    }

    void setIdle(uint16_t idle) {
        this->idle = idle;
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
};
