#define ENABLE_FN_NUMPAD
#ifdef ENABLE_FN_NUMPAD
    #define FN_NUMPAD_PIN0 MCP0(0)
    #define FN_NUMPAD_PIN1 MCP0(0)
    #define FN_NUMPAD_PIN2 MCP0(0)
    #define FN_NUMPAD_PIN3 MCP0(0)
    #define FN_NUMPAD_PIN4 MCP0(0)
    #define FN_NUMPAD_PIN5 MCP0(0)
    #define FN_NUMPAD_PIN6 MCP0(0)
    //, MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0), MCP0(0)]
#endif


int kk = 0;
for(kk = 0; kk < 128; kk++) {
    ADD_BUTTON(PIN(5), kk); //  - 
    //p(kk); p("/"); pln(freeMemory());
}

c[1].setMomentary(CONTROL_MOMENTARY_SIMPLE);
c[2].setMomentary(CONTROL_MOMENTARY_FULL);

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
ADD_BUTTON(MCP1(14), 30); //  - 
ADD_BUTTON(MCP1(15), 31); //  - 
ADD_ROTARY_BUTTONS(PIN(6), PIN(7), 33, 32, 2); //  - 
ADD_ROTARY_BUTTONS(PIN(8), PIN(9), 35, 34, 2); //  - 
ADD_POT(A0, AXIS_X);
ADD_POT(A1, AXIS_Y);
ADD_POT(A2, AXIS_Z);
*/

p("MAX kk: ");
pln(kk);
p("MEM: ");
pln(freeMemory());


/*

// OK
//ADD_BUTTON(PIN(7), 0);

//ADD_BUTTON(PIN(7), 1)->momentary();

//ADD_BUTTON(MCP1(0), 3);

//ADD_SWITCH2(PIN(14), PIN(15), 2, 3)->alwaysOn();

//ADD_SWITCH3(PIN(14), PIN(15), 4, 5, 6)->alwaysOn();

/*ADD_POT(PIN(A0), AXIS_X);
ADD_POT(PIN(A0), AXIS_Y);
ADD_POT(PIN(A0), AXIS_Z);
ADD_POT(PIN(A0), AXIS_RX);
ADD_POT(PIN(A0), AXIS_RY);
ADD_POT(PIN(A0), AXIS_RZ);* /


// PRUEBAS

//ADD_ROTARY_BUTTONS(PIN(8), PIN(9), 2, 3, 2)->minIdle(20);
//ADD_ROTARY_BUTTONS(PIN(4), PIN(5), 4, 5, 4);

//ADD_ROTARY_AXIS(PIN(8), PIN(9), AXIS_X, 2)->i();

uint8_t j = 0;

ADD_BUTTON(PIN(7), j++)->momentary(); // TEST - Boton 0
ADD_SWITCH2(PIN(7), j++, j++)->momentary()->i(); // TEST - Switch 4-5
ADD_SWITCH3(PIN(14), PIN(15), j++, j++, j++)->momentary(); // TEST - Switch 1-2-3
//ADD_ROTARY_BUTTONS(PIN(7), PIN(8), j++, j++, j++)->minIdle(20)->i()->a(1, 1); // TEST - Rotary 6-7
/* */