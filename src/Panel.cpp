#include "Panel.h"

Servo servoD3;
/*
We are very primitive on this, only using half of the potential
for simplicity. It does not matter if a switch is moved from 0 to 1 or 1 to 0
or if a button is pressed or depressed. We only care about changes
*/
void Panel::init() {

  PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA2_U, FUNC_GPIO9);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA3_U, FUNC_GPIO10);

  //setup inputs & outputs
  pinMode(D0, OUTPUT); // SI1
  pinMode(D1, OUTPUT); // S12
  pinMode(D2, OUTPUT); // SI3
  servoD3.attach(D3); // SI4
  pinMode(D8, OUTPUT); // SI22

  pinMode(D5, INPUT_PULLUP); // B1, Switch On/Off
  pinMode(D6, INPUT_PULLUP); // B2, Green Button
  pinMode(D7, INPUT_PULLUP); // B3, Small Button
  pinMode(D4, INPUT_PULLUP); // B4, Side Switch On/Off

  // read initial state and reset
  resetButtonStates();

}

void Panel::resetButtonStates() {
  lastStateTopSwitch = digitalRead(D5);
  topSwitchMoved = false;
  lastStateGreenButton = digitalRead(D6);
  greenButtonPressed = false;
  lastStateSmallButton = digitalRead(D7);
  smallButtonPressed = false;
  lastStateSideSwitch = digitalRead(D4);
  sideSwitchMoved = false;

  newWebValue = false;
}
void Panel::checkButtonPresses() {

  boolean newStateTopSwitch = digitalRead(D5);
  if (lastStateTopSwitch != newStateTopSwitch) {
      topSwitchMoved = true;
      quickBeep();
  }
  lastStateTopSwitch = newStateTopSwitch;

  boolean newStateGreenButton= digitalRead(D6);

  if (newStateGreenButton == false) {
    greenButtonPressed = true;
    if (lastStateGreenButton != newStateGreenButton) {
      quickBeep();
    }
  }
  lastStateGreenButton= newStateGreenButton;

  boolean newStateSmallButton= digitalRead(D7);
  if (newStateSmallButton == false) {
    smallButtonPressed = true;
    if (lastStateSmallButton != newStateSmallButton) {
      quickBeep();
    }
  }
  lastStateSmallButton= newStateSmallButton;

  boolean newStateSideSwitch= digitalRead(D4);
  if (lastStateSideSwitch != newStateSideSwitch) {
    sideSwitchMoved = true;
    quickBeep();
  }
  lastStateSideSwitch= newStateSideSwitch;

}

boolean Panel::wasGreenButtonPressed() {
  return greenButtonPressed;
}

boolean Panel::wasSmallButtonPressed() {
  return smallButtonPressed;
}

boolean Panel::wasSideSwitchMoved() {
  return sideSwitchMoved;
}

boolean Panel::wasTopSwitchMoved() {
  return topSwitchMoved;
}

boolean Panel::greenAndSmallCurrentlyPressed() {
    return (!digitalRead(D6) && !digitalRead(D7));
}

int Panel::distanceToObstacle() {
  return 0; // not implemented yet
}

void Panel::setSI1(boolean on) {
  digitalWrite(D0, on);
}

void Panel::setSI2(boolean on) {
  digitalWrite(D1, on);
}

void Panel::setSI3(int degrees) {
  servoD3.write(degrees);
}

void Panel::setSI4(boolean on) {
  digitalWrite(D2, on);
}

void Panel::quickBeep() {
  digitalWrite(D8, HIGH);
  delay(3);
  digitalWrite(D8, LOW);
}

void Panel::beepSI22(int times) {
// need to make this non-blocking async
  int interval = 300/times;
  for( int i=0; i<times; i++) {
    digitalWrite(D8, HIGH);
    delay(interval);
    digitalWrite(D8, LOW);
    delay(interval/2);
  }
}

boolean Panel::hasNewWebValue() {
  return newWebValue;
}
String Panel::getWebValue() {
  newWebValue = false;
  return webValue;
}

void Panel::setNewWebValue(String activeCommand) {
  webValue = activeCommand;
  newWebValue = true;
}
