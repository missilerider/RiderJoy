#include <Arduino.h>

#include "debug.h"

#include "controls/control.h"
#include "controls/button.h"
#include "controls/switch.h"
#include "controls/rotaryButton.h"

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

  for(n=0; n < numC; n++) {
    k = ctrl[n]->getHighestJoyButton();
    if(k > buttons) buttons = k;
  }

  p("Botones: ");
  pln(buttons);

  joy = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, 
    JOYSTICK_TYPE_GAMEPAD, buttons + 1,
    JOYSTICK_DEFAULT_HATSWITCH_COUNT,
    false, false, false, false, false, false,
    false, false, false, false, false);

  joy->begin(false); // autoSendMode = false

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
