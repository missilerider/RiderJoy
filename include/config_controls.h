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
ADD_POT(PIN(A0), AXIS_RZ);*/


// PRUEBAS

//ADD_ROTARY_BUTTONS(PIN(8), PIN(9), 2, 3, 2)->minIdle(20);
//ADD_ROTARY_BUTTONS(PIN(4), PIN(5), 4, 5, 4);

//ADD_ROTARY_AXIS(PIN(8), PIN(9), AXIS_X, 2)->i();

ADD_BUTTON(PIN(7), 0)->momentary()->i(); // TEST - Boton 0
ADD_SWITCH3(PIN(7), PIN(6), 1, 2, 3)->alwaysOn()->i(); // TEST - Switch 1-2-3
ADD_SWITCH2(PIN(7), PIN(8), 4, 5)->alwaysOn()->i(); // TEST - Switch 4-5
ADD_ROTARY_BUTTONS(PIN(7), PIN(8), 4, 5, 2)->minIdle(20)->i()->a(1, 1); // TEST - Rotary 6-7
