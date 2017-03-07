#ifndef quadstate_h
#define quadstate_h

#include "State.h"
#include "SensorEyes.h"


// 1
class StartState : public State {
public:
  virtual void init(Panel* _panel);
  virtual void preState();
  virtual void postState();
  virtual int inState();

private:
  int count;
  Panel* panel;
};

// 2
class CountdownState : public State {
public:
  virtual void init(Panel* _panel);
  virtual void preState();
  virtual void postState();
  virtual int inState();

private:
  int count;
  Panel* panel;
};

// 3
class AllaliveState : public State {
public:
  virtual void init(Panel* _panel);
  virtual void preState();
  virtual void postState();
  virtual int inState();

private:
  int count;
  Panel* panel;
};

// 4
class EndState : public State {
public:
  virtual void init(Panel* _panel);
  virtual void preState();
  virtual void postState();
  virtual int inState();

private:
  SensorEyes* se;
  int count;
  Panel* panel;
};

// 5
class FunkyState : public State {
public:
  virtual void init(Panel* _panel);
  virtual void preState();
  virtual void postState();
  virtual int inState();

private:
  int count;
  Panel* panel;
};

#endif
