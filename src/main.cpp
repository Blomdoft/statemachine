#include <Arduino.h>
#include <Servo.h>
#include "Panel.h"
#include "State.h"
#include "WebConnector.h"
#include "QuadStateMadness.h"

Panel panel;
WebConnector webConnector;

State* currentState;
State* states[6];

void setup() {
  panel.init();
  webConnector.init();

  // initialize all states
  states[0] = NULL;
  states[1] = new StartState();
  states[2] = new CountdownState();
  states[3] = new AllaliveState();
  states[4] = new EndState();
  states[5] = new FunkyState();

  for (int i = 0; i<6; i++) {
    if (states[i] != NULL) {
      states[i]->init(&panel);
    }
  }

  // set starting state and prestate it
  currentState = states[1];
  currentState->preState();
}

void loop() {

  delay(30);

  webConnector.handleConnection();
  if (webConnector.hasNewValue()) {
    panel.quickBeep();
    panel.setNewWebValue(webConnector.getActiveCommand());
  }
  panel.checkButtonPresses();

  int newStateInt = currentState->inState();
  if (newStateInt !=0) {
    currentState->postState();
    // change state
    currentState = states[newStateInt];
    currentState->preState();
    // make sure to reset all triggers
    panel.resetButtonStates();
  }

}
