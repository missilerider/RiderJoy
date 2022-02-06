//#define ENABLE_FN_NUMPAD
#ifdef ENABLE_FN_NUMPAD
    #define FN_NUMPAD_PIN0 PIN(4)
    #define FN_NUMPAD_PIN1 PIN(5)
    #define FN_NUMPAD_PIN2 PIN(6)
    #define FN_NUMPAD_PIN3 PIN(7)
    #define FN_NUMPAD_PIN4 PIN(8)
    #define FN_NUMPAD_PIN5 PIN(9)
    #define FN_NUMPAD_PIN6 PIN(15)
#endif

/*
int kk = 0;
for(kk = 0; kk < 1; kk++) {
    ADD_BUTTON(PIN(5), kk); //  - 
    //p(kk); p("/"); pln(freeMemory());
}
*/
uint8_t b = 0;
#define B   b++

ADD_BUTTON(PIN(4), B); //  - 
ADD_BUTTON(PIN(4), B)->i(); //  - 
ADD_BUTTON(PIN(4), B)->momentary(); //  - 

/*
ADD_SWITCH3(PIN(5), PIN(6), 22, 23, 36)->momentary();

ADD_ROTARY_BUTTONS(PIN(6), PIN(7), 33, 32, 2); //  - 

ADD_POT(A0, AXIS_X);

ADD_SWITCH2(PIN(5), 44, 45)->momentary(); //  - 
/*
c[1].setMomentary(CONTROL_MOMENTARY_SIMPLE);
c[2].setMomentary(CONTROL_MOMENTARY_FULL);


p("MAX kk: ");
pln(kk);
p("MEM: ");
pln(freeMemory());
*/