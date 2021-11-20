#include <Arduino.h>

#include "debug.h"

#include "controls/control.h"
#include "controls/button.h"
#include "controls/switch.h"
#include "controls/rotaryButton.h"
#include "controls/pot.h"

#include "config_macros.h"

#include <Joystick.h>

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

  p("Final Axis: ");
  p(axis[AXIS_X]>0 ? 1 : 0);
  p(axis[AXIS_Y]>0 ? 1 : 0);
  p(axis[AXIS_Z]>0 ? 1 : 0);
  p(axis[AXIS_RX]>0 ? 1 : 0);
  p(axis[AXIS_RY]>0 ? 1 : 0);
  p(axis[AXIS_RZ]>0 ? 1 : 0);
  pln("");

  joy->begin(false); // autoSendMode = false

  joy->setXAxisRange(0, 1023);
  joy->setYAxisRange(0, 1023);
  joy->setZAxisRange(0, 1023);
  joy->setRxAxisRange(0, 1023);
  joy->setRyAxisRange(0, 1023);
  joy->setRzAxisRange(0, 1023);

  joy->setRudderRange(0, 1023);
  joy->setAcceleratorRange(0, 1023);
  joy->setBrakeRange(0, 1023);
  joy->setSteeringRange(0, 1023);
  joy->setThrottleRange(0, 1023);

  k = 0;
  for(n = 0; n < numC; n++) {
    ctrl[n]->init();
    if(ctrl[n]->hasPoll()) {
      pollCtrl[k++] = ctrl[n];
    }
  }

  numPoll = k;
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
