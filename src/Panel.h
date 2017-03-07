#ifndef panel_h
#define panel_h

#include <Arduino.h>
#include <Servo.h>

class Panel {
  public:

    void init();
    void resetButtonStates();
    void checkButtonPresses();

    boolean wasGreenButtonPressed();
    boolean wasSmallButtonPressed();
    boolean wasSideSwitchMoved();
    boolean wasTopSwitchMoved();
    int distanceToObstacle();

    boolean greenAndSmallCurrentlyPressed();

    void setSI1(boolean on);
    void setSI2(boolean on);
    void setSI3(int degrees);
    void setSI4(boolean on);
    void beepSI22(int times);

    void quickBeep();


    boolean hasNewWebValue();
    String getWebValue();
    void setNewWebValue(String activeCommand);

  private:
    Servo * servo;
    boolean greenButtonPressed;
    boolean smallButtonPressed;
    boolean sideSwitchMoved;
    boolean topSwitchMoved;

    boolean lastStateGreenButton;
    boolean lastStateSmallButton;
    boolean lastStateSideSwitch;
    boolean lastStateTopSwitch;

    String webValue;
    boolean newWebValue;

};
#endif
