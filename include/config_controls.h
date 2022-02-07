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
#define B   (b++)

ADD_BUTTON(PIN(4), B); //  - 
ADD_BUTTON(PIN(4), B)->momentary(); //  - 

/*
ADD_SWITCH3(PIN(4), PIN(5), B, B, B);
ADD_SWITCH3(PIN(4), PIN(5), B, B, B)->momentary();
ADD_SWITCH3(PIN(4), PIN(5), B, B, B)->momentaryFull();
*/

/*
ADD_SWITCH2(PIN(4), B, B);
ADD_SWITCH2(PIN(4), B, B)->momentary();
ADD_SWITCH2(PIN(4), B, B)->momentaryFull();

*/

ADD_POT(A0, AXIS_X);

//ADD_ROTARY_BUTTONS(PIN(6), PIN(7), 33, 32, 2); //  - 


/*
c[1].setMomentary(CONTROL_MOMENTARY_SIMPLE);
c[2].setMomentary(CONTROL_MOMENTARY_FULL);


p("MAX kk: ");
pln(kk);
p("MEM: ");
pln(freeMemory());
*/



// Config UFC

/*
ADD_BUTTON(MCP0(0), 0); //  - 
ADD_BUTTON(MCP0(1), 1); //  - 
ADD_BUTTON(MCP0(2), 2); //  - 
ADD_BUTTON(MCP0(3), 3); //  - 
ADD_BUTTON(MCP0(4), 4); //  - 
ADD_BUTTON(MCP0(5), 5); //  - 
ADD_BUTTON(MCP0(6), 6); //  - 
ADD_BUTTON(MCP0(7), 7); //  - 
ADD_BUTTON(MCP0(8), 8); //  - 
ADD_BUTTON(MCP0(9), 9); //  - 
ADD_BUTTON(MCP0(10), 10); //  - 
ADD_BUTTON(MCP0(11), 11); //  - 
ADD_BUTTON(MCP0(12), 12); //  - 
ADD_BUTTON(MCP0(13), 13); //  - 
ADD_BUTTON(MCP0(14), 14); //  - 
ADD_BUTTON(MCP0(15), 15); //  - 
ADD_BUTTON(MCP1(0), 16); //  - 
ADD_BUTTON(MCP1(1), 17); //  - 
ADD_BUTTON(MCP1(2), 18); //  - 
ADD_BUTTON(MCP1(3), 19); //  - 
ADD_BUTTON(MCP1(4), 20); //  - 
ADD_BUTTON(MCP1(5), 21); //  - 

ADD_SWITCH3(MCP1(6), MCP1(7), 22, 23, 36)->momentary();

ADD_BUTTON(MCP1(8), 24); //  - 
ADD_BUTTON(MCP1(9), 25); //  - 
ADD_BUTTON(MCP1(10), 26); //  - 
ADD_BUTTON(MCP1(11), 27); //  - 
ADD_BUTTON(MCP1(12), 28); //  - 
ADD_BUTTON(MCP1(13), 29); //  - 

ADD_ROTARY_BUTTONS(PIN(6), PIN(7), 33, 32, 2); //  - 
ADD_ROTARY_BUTTONS(PIN(8), PIN(9), 35, 34, 2); //  - 
ADD_POT(A0, AXIS_X);
ADD_POT(A1, AXIS_Y);
ADD_POT(A2, AXIS_Z);

ADD_SWITCH3(MCP1(14), MCP1(15), 30, 31, 40)->momentary();
ADD_SWITCH3(PIN(5), PIN(4), 37, 38, 39)->momentary();

ADD_BUTTON(MCP2(8), 41); //  - 
ADD_BUTTON(MCP2(9), 42); //  - 
ADD_BUTTON(MCP2(10), 43); //  - 
ADD_SWITCH2(MCP2(11), 44, 45)->momentary(); //  - 

*/