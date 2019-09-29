// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// Arduino port         MSX compatible
//  Pin 0 (PD2)  -----     3
//  Pin 1 (PD3)  -----     4
//  Pin 2 (PD1)  -----     2
//  Pin 3 (PD0)  -----     1
//  Pin 4 (PD4)  -----     6
//  Pin 5 (PC6)  -----     8
//  Pin 6 (PD7)  -----     7
//         +5V   -----     5
//         GND   -----     9
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// Original:
// by Matthew Heironimus
// 2016-11-24
//
// Modified:
// by Oh!Ishi / NibblesLab.
// 2019-09-29
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  10, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X, Y, and Z Axis
  false, false, false,   // Rx, but no Ry or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin(false);
  Joystick.setXAxisRange(0, 255);
  Joystick.setYAxisRange(0, 255);
}

// Last state of the buttons
int lastButtonState[4] = {1,1,1,1};
int lastButtonState_trig_A = 0x80;
int lastButtonState_trig_B = 0x10;
int lastStickState_X = 0;
int lastStickState_Y = 0;

void loop() {
  int currentButtonState;
  int currentButtonState_trig_A;
  int currentButtonState_trig_B;
  bool F_operate = false;

  // UP
  currentButtonState = PIND;
  int state = currentButtonState & 0x01;
  if (state != lastButtonState[0]) {
    if (state == 0) {
      Joystick.setYAxis(0);
    } else {
      Joystick.setYAxis(0x7f);
    }
    lastButtonState[0] = state;
    F_operate = true;
  }

  // DOWN
  state = currentButtonState & 0x02;
  if (state != lastButtonState[1]) {
    if (state == 0) {
      Joystick.setYAxis(0xff);
    } else {
      Joystick.setYAxis(0x7f);
    }
    lastButtonState[1] = state;
    F_operate = true;
  }

  // LEFT
  state = currentButtonState & 0x04;
  if (state != lastButtonState[2]) {
    if (state == 0) {
      Joystick.setXAxis(0);
    } else {
      Joystick.setXAxis(0x7f);
    }
    lastButtonState[2] = state;
    F_operate = true;
  }

  // RIGHT
  state = currentButtonState & 0x08;
  if (state != lastButtonState[3]) {
    if (state == 0) {
      Joystick.setXAxis(0xff);
    } else {
      Joystick.setXAxis(0x7f);
    }
    lastButtonState[3] = state;
    F_operate = true;
  }

  // TRIGGER A
  state = currentButtonState & 0x10;
  if (state != lastButtonState_trig_A)
  {
    if (state == 0) {
      Joystick.setButton(2, 1);
    } else {
      Joystick.setButton(2, 0);
    }
    lastButtonState_trig_A = state;
    F_operate = true;
  }

  // TRIGGER B
  state = currentButtonState & 0x80;
  if (state != lastButtonState_trig_B)
  {
    if (state == 0) {
      Joystick.setButton(1, 1);
    } else {
      Joystick.setButton(1, 0);
    }
    lastButtonState_trig_B = state;
    F_operate = true;
  }

  if (F_operate)
  {
    Joystick.sendState();
  }

  delay(10);
}
