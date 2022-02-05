#define ENABLE_FN_NUMPAD
#ifdef ENABLE_FN_NUMPAD
    #define FN_NUMPAD_PIN0 PIN(4)
    #define FN_NUMPAD_PIN1 PIN(5)
    #define FN_NUMPAD_PIN2 PIN(6)
    #define FN_NUMPAD_PIN3 PIN(7)
    #define FN_NUMPAD_PIN4 PIN(8)
    #define FN_NUMPAD_PIN5 PIN(9)
    #define FN_NUMPAD_PIN6 PIN(15)
    //, MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0)]
#endif


int kk = 0;
for(kk = 0; kk < 1; kk++) {
    ADD_BUTTON(PIN(5), kk); //  - 
    //p(kk); p("/"); pln(freeMemory());
}
/*
c[1].setMomentary(CONTROL_MOMENTARY_SIMPLE);
c[2].setMomentary(CONTROL_MOMENTARY_FULL);


p("MAX kk: ");
pln(kk);
p("MEM: ");
pln(freeMemory());
*/