#include <Arduino.h>

#include "config_global.h"
#include "debug.h"

#include "controls/control.h"
#include "controls/button.h"
#include "controls/switch.h"
#include "controls/rotaryButton.h"
#include "controls/rotaryAxis.h"
#include "controls/pot.h"

#include <Joystick.h>

#include "config_macros.h"

#define UPDATEMILLIS 10 // Milisegundos entre actualizaciones de USB

Control *ctrl[128];
Control *pollCtrl[128];
uint8_t numC, numPoll;

Joystick_ *joy;
Adafruit_MCP23X17 mcp[8];

unsigned long now;
unsigned long lastUpdate = 0;

uint8_t n;

void setup() {
#ifdef DEBUG
  Serial1.begin(115200);
#endif

  pln("");
  pln("RiderIndustries HOTAS init...");

/*  Adafruit_MCP23X17 mcp;

  if (!mcp.begin_I2C(0x20)) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    pln("Error.");
    while (1);
  }

   // configure button pin for input with pull up
  mcp.pinMode(0, INPUT_PULLUP);

  while(1) {
    p(mcp.digitalRead(0));
  }
  return;*/

  Control::prepare();

  readConfig(ctrl, &numC);

  int buttons = -1, k;
  uint8_t axis[11];
  memset(axis, 0, sizeof(uint8_t)*11);

  for(n=0; n < numC; n++) {
    k = ctrl[n]->getHighestJoyButton();
    if(k > buttons) buttons = k;

    ctrl[n]->getAxisRequirements(axis);
  }

  p("Botones: ");
  pln(buttons);

  joy = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, 
    JOYSTICK_TYPE_GAMEPAD, 
    //JOYSTICK_TYPE_JOYSTICK, 
    buttons + 1,
    JOYSTICK_DEFAULT_HATSWITCH_COUNT,
    axis[AXIS_X]>0, axis[AXIS_Y]>0, axis[AXIS_Z]>0, 
    axis[AXIS_RX]>0, axis[AXIS_RY]>0, axis[AXIS_RZ]>0, 
    false, false, false, false, false); //axis[AXIS_RUDDER]>0, axis[AXIS_THROTTLE]>0, axis[AXIS_ACCEL]>0, axis[AXIS_BRAKE]>0, axis[AXIS_STEERING]>0);

  p("Axis: ");
  p(axis[AXIS_X]>0 ? 1 : 0);
  p(axis[AXIS_Y]>0 ? 1 : 0);
  p(axis[AXIS_Z]>0 ? 1 : 0);
  p(axis[AXIS_RX]>0 ? 1 : 0);
  p(axis[AXIS_RY]>0 ? 1 : 0);
  pln(axis[AXIS_RZ]>0 ? 1 : 0);

  joy->begin(false); // autoSendMode = false

  joy->setXAxisRange(0, 1024);
  joy->setYAxisRange(0, 1024);
  joy->setZAxisRange(0, 1024);
  joy->setRxAxisRange(0, 1024);
  joy->setRyAxisRange(0, 1024);
  joy->setRzAxisRange(0, 1024);

/*  joy->setRudderRange(0, 1024);
  joy->setAcceleratorRange(0, 1024);
  joy->setBrakeRange(0, 1024);
  joy->setSteeringRange(0, 1024);
  joy->setThrottleRange(0, 1024);*/

  k = 0;
  for(n = 0; n < numC; n++) {
    ctrl[n]->init();
    if(ctrl[n]->hasPoll()) {
      pollCtrl[k++] = ctrl[n];
    }
  }

  numPoll = k;

  p("Numpoll: ");
  pln(numPoll);
}

void loop() {
  now = millis();

  // Polling a to meter
  for(n = 0; n < numPoll; n++) {
    pollCtrl[n]->poll();
  }

  if(now - lastUpdate < UPDATEMILLIS) return;

  for(n = 0; n < numC; n++) {
    ctrl[n]->process(joy);
  }

  joy->sendState();
  lastUpdate = now;

// put your main code here, to run repeatedly:
}
