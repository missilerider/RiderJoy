#include <Arduino.h>

#include "config_global.h"
#include "debug.h"

#include "control_macros.h"

#include "control.h"
#include "button.h"
#include "switch3p.h"
#include "switch2p.h"
#include "rotaryButton.h"
//#include "rotaryAxis.h"
#include "pot.h"

#include <Joystick.h>
#include <MemoryFree.h>

#include "config_macros.h"

#ifdef ENABLE_FN_NUMPAD
#include "fnNumpad.h"
#endif

#define UPDATEMILLIS 10 // Milisegundos entre actualizaciones de USB

ControlData ctrl[MAX_CONTROLS];
Control *pollCtrl[MAX_ROTARIES];
uint8_t numC, numPoll;

Joystick_ *joy;
Adafruit_MCP23X17 mcp[8];

unsigned long now;
unsigned long lastUpdate = 0;

uint8_t n, m;

void setup() {
#ifdef DEBUG
  Serial1.begin(115200);
#endif

  pln("");
  pln("RiderIndustries HOTAS init...");

  pln("TEST..................");

  ControlData d;
  d.specs = 0xFF;
  pbitln(d.getStage());
  d.setStage0();
  pbitln(d.getStage());
  d.setStage1();
  pbitln(d.getStage());
  d.setStage2();
  pbitln(d.getStage());
  d.setStage3();
  pbitln(d.getStage());
  d.setStage0();
  pbitln(d.getStage());

  pln("TEST..................");

  Control::prepare();

  readConfig(ctrl, &numC);

  int buttons = -1, k;
  uint8_t axis[11];
  memset(axis, 0, sizeof(uint8_t)*11);

  for(n=0; n < numC; n++) {
    k = Control::getHighestJoyButton(&ctrl[n]);
    if(k > buttons) buttons = k;

    Control::getAxisRequirements(&ctrl[n], axis);
  }

  p("Botones: ");
  pln(buttons);

  p("Axis: ");
  p(axis[AXIS_X]>0 ? 1 : 0);
  p(axis[AXIS_Y]>0 ? 1 : 0);
  p(axis[AXIS_Z]>0 ? 1 : 0);
  p(axis[AXIS_RX]>0 ? 1 : 0);
  p(axis[AXIS_RY]>0 ? 1 : 0);
  pln(axis[AXIS_RZ]>0 ? 1 : 0);

  joy = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, 
    JOYSTICK_TYPE_GAMEPAD, 
    //JOYSTICK_TYPE_JOYSTICK, 
    buttons + 1,
    JOYSTICK_DEFAULT_HATSWITCH_COUNT,
    axis[AXIS_X]>0, axis[AXIS_Y]>0, axis[AXIS_Z]>0, 
    axis[AXIS_RX]>0, axis[AXIS_RY]>0, axis[AXIS_RZ]>0, 
    axis[AXIS_RUDDER]>0, axis[AXIS_THROTTLE]>0, false, false, false); //axis[AXIS_RUDDER]>0, axis[AXIS_THROTTLE]>0, axis[AXIS_ACCEL]>0, axis[AXIS_BRAKE]>0, axis[AXIS_STEERING]>0);

  joy->begin(false); // autoSendMode = false

  joy->setXAxisRange(0, 1024);
  joy->setYAxisRange(0, 1024);
  joy->setZAxisRange(0, 1024);
  joy->setRxAxisRange(0, 1024);
  joy->setRyAxisRange(0, 1024);
  joy->setRzAxisRange(0, 1024);
  joy->setRudderRange(0, 1024);
  joy->setThrottleRange(0, 1024);

/*  joy->setAcceleratorRange(0, 1024);
  joy->setBrakeRange(0, 1024);
  joy->setSteeringRange(0, 1024); */

  k = 0;
  for(n = 0; n < numC; n++) {
    //ctrl[n]->init();
    Control::init(&ctrl[n]);
//    if(Control::hasPoll(ctrl[n])) {
//      pollCtrl[k++] = ctrl[n];
//    }
  }

  numPoll = k;

  p("Numpoll: ");
  pln(numPoll);

#ifdef ENABLE_FN_NUMPAD
FnNumpad::setup(FN_NUMPAD_PIN0, FN_NUMPAD_PIN1, FN_NUMPAD_PIN2, FN_NUMPAD_PIN3, FN_NUMPAD_PIN4, FN_NUMPAD_PIN5, FN_NUMPAD_PIN6);
#endif
}

void loop() {
  now = millis();

  // Polling a to meter
  for(n = 0; n < numPoll; n++) {
    pollCtrl[n]->poll();
  }

  // Si no es momento de actualizar, salimos
  if(now - lastUpdate < UPDATEMILLIS) return;

  // Procesa todos los controles
  for(n = 0; n < numC; n++) {
    Control::process(&ctrl[n], joy, (uint8_t)(now - lastUpdate));

    for(m = 0; m < numPoll; m++) {
      pollCtrl[m]->poll();
    }
  }

  // Actualiza el joystick
  joy->sendState();

  // Si esta configurado, lee el bloque numerico y pulsa las teclas de función
  #ifdef ENABLE_FN_NUMPAD
    FnNumpad::process();
  #endif

  lastUpdate = now;
}
