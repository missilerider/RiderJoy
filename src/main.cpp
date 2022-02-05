#include <Arduino.h>

#include "config_global.h"
#include "debug.h"

#include "control.h"
#include "button.h"
#include "switch3p.h"
#include "switch2p.h"
#include "rotaryButton.h"
//#include "rotaryAxis.h"
#include "pot.h"

#include <Joystick.h>
#include "HID-Project.h"

#include "config_macros.h"

#define UPDATEMILLIS 10 // Milisegundos entre actualizaciones de USB

Control *ctrl[128];
Control *pollCtrl[128];
uint8_t numC, numPoll;

Joystick_ *joy;
Adafruit_MCP23X17 mcp[8];

uint8_t rawhidData[120];
uint8_t featureData[64];

unsigned long now;
unsigned long lastUpdate = 0;

uint8_t n;

void setup() {
#ifdef DEBUG
  Serial1.begin(115200);
#endif

  pln("");
  pln("RiderIndustries HOTAS init...");


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

  RawHID.begin(rawhidData, sizeof(rawhidData));
  // Let the feature report data directly point at the led array
  RawHID.setFeatureReport(featureData, sizeof(featureData));
  RawHID.enableFeatureReport();

  joy = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, 
    JOYSTICK_TYPE_GAMEPAD, 
    //JOYSTICK_TYPE_JOYSTICK, 
    buttons + 1,
    JOYSTICK_DEFAULT_HATSWITCH_COUNT,
    axis[AXIS_X]>0, axis[AXIS_Y]>0, axis[AXIS_Z]>0, 
    axis[AXIS_RX]>0, axis[AXIS_RY]>0, axis[AXIS_RZ]>0, 
    axis[AXIS_RUDDER]>0, axis[AXIS_THROTTLE]>0, false, false, false); //axis[AXIS_RUDDER]>0, axis[AXIS_THROTTLE]>0, axis[AXIS_ACCEL]>0, axis[AXIS_BRAKE]>0, axis[AXIS_STEERING]>0);

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
  joy->setRudderRange(0, 1024);
  joy->setThrottleRange(0, 1024);

/*  joy->setAcceleratorRange(0, 1024);
  joy->setBrakeRange(0, 1024);
  joy->setSteeringRange(0, 1024); */

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

  auto bytesAvailable = RawHID.available();
  if (bytesAvailable) {
      // Mirror data via Serial
      while (bytesAvailable--) {
          Serial1.print(RawHID.read()); Serial1.print(',');
      }
      Serial1.println();
  }

  // Si no es momento de actualizar, salimos
  if(now - lastUpdate < UPDATEMILLIS) return;

  // Procesa todos los controles
  for(n = 0; n < numC; n++) {
    ctrl[n]->process(joy);
  }

  // Actualiza el joystick
  joy->sendState();
  lastUpdate = now;
}
