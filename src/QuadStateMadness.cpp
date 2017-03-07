#include "QuadStateMadness.h"

void StartState::init(Panel* _panel) {
  panel = _panel;
}

void StartState::preState() {
    count = 0;
    panel->setSI1(false);
    panel->setSI2(false);
    panel->setSI3(150);
    panel->setSI4(false);
}
void StartState::postState() {
  panel->setSI1(false);
  panel->setSI2(false);
  panel->setSI3(150);
  panel->setSI4(false);
}

int StartState::inState() {
  count++;

  if (count <50) {
    panel->setSI1(true);
    panel->setSI2(false);
    panel->setSI4(false);
  } else if (count < 100) {
    panel->setSI1(false);
    panel->setSI2(true);
    panel->setSI4(false);
  } else if (count < 150) {
    panel->setSI1(false);
    panel->setSI2(false);
    panel->setSI4(true);
  } else {
    count = 0;
  }

  if (panel->wasGreenButtonPressed()) {
      // that is all it takes to get out of the start state!
      panel->beepSI22(3);
      return 2; // goes to Countdownstate
  }

  return 0;
}


void CountdownState::init(Panel* _panel) {
  panel = _panel;
}

void CountdownState::preState() {
    count = 500;
    panel->setSI1(false);
    panel->setSI2(true);
    panel->setSI3(150);
    panel->setSI4(false);
}

void CountdownState::postState() {
  panel->setSI1(false);
  panel->setSI2(false);
  panel->setSI3(150);
  panel->setSI4(false);
}

int CountdownState::inState() {
  count--;
  if (count == 300) {
    panel->beepSI22(2);
  }
  if (count == 200) {
    panel->beepSI22(3);
  }
  if (count == 100) {
    panel->beepSI22(4);
  }
  if (count == 0) {
    panel->beepSI22(1);
    return 1;
  }

  if (panel->wasSideSwitchMoved()) {
      // that is all it takes to get out of this
      panel->beepSI22(3);
      return 3;
  }

  return 0;
}


void AllaliveState::init(Panel* _panel) {
  panel = _panel;
}

void AllaliveState::preState() {
    panel->setSI1(true);
    panel->setSI2(true);
    panel->setSI3(150);
    panel->setSI4(true);
}

void AllaliveState::postState() {
  panel->setSI1(false);
  panel->setSI2(false);
  panel->setSI3(150);
  panel->setSI4(false);
}

int AllaliveState::inState() {

  if (panel->wasSideSwitchMoved() || panel->wasGreenButtonPressed() || panel->wasSmallButtonPressed()) {
    // Takes you back to the start.
    panel->beepSI22(1);
    return 1;
  }

  if (panel->hasNewWebValue() && panel->getWebValue() == "01") {
    panel->beepSI22(3);
    return 4;
  }

  if (panel->wasTopSwitchMoved()) {
    // winner! lol
    panel->beepSI22(3);
    return 4;
  }

  return 0;
}


void EndState::init(Panel* _panel) {
  panel = _panel;
  se = new SensorEyes();
  se->init();
}

void EndState::preState() {
    panel->setSI1(false);
    panel->setSI2(false);
    panel->setSI3(30);
    panel->setSI4(false);
}

void EndState::postState() {
  panel->setSI1(false);
  panel->setSI2(false);
  panel->setSI3(30);
  panel->setSI4(false);
}

int EndState::inState() {

  if (panel->greenAndSmallCurrentlyPressed()) {
    panel->beepSI22(3);
    return 5;
  }

  if (panel->wasSideSwitchMoved() || panel->wasTopSwitchMoved() || panel->wasGreenButtonPressed()) {
      // Takes you back to the start.
      panel->beepSI22(1);
      return 1;
  }


  se->measureDistance();
  if (se->getDistance() > 10 && se->getDistance()<90) {
    panel->quickBeep();
    panel->setSI3(180-(se->getDistance()*2));
  }

  if (se->getDistance() > 10 && se->getDistance() <20) {
    panel->beepSI22(1);
    return 1;
  }

  return 0;
}

void FunkyState::init(Panel* _panel) {
  panel = _panel;
}

void FunkyState::preState() {
    panel->setSI1(false);
    panel->setSI2(false);
    panel->setSI3(30);
    panel->setSI4(false);
}

void FunkyState::postState() {
  panel->setSI1(false);
  panel->setSI2(false);
  panel->setSI3(30);
  panel->setSI4(false);
}

int FunkyState::inState() {
// immediate mode

  if (count > 360) {
    count=0;
    panel->beepSI22(10);
  }
  count++;
  panel->setSI3(count/2);
  int bo = count%3;
  if (bo == 0) {
    panel->setSI4(false);
    panel->setSI1(true);
  }
  if (bo == 1) {
    panel->setSI1(false);
    panel->setSI2(true);
  }
  if (bo == 2) {
    panel->setSI2(false);
    panel->setSI4(true);
  }

  if (panel->greenAndSmallCurrentlyPressed() && panel->wasTopSwitchMoved()) {
    panel->beepSI22(1);
    return 1;
  }
  if (panel->greenAndSmallCurrentlyPressed() && panel->wasSideSwitchMoved()) {
    panel->beepSI22(1);
    return 1;
  }

  return 0;
}
