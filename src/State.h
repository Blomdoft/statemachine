#ifndef state_h
#define state_h

#include "Panel.h"

class State {
    public:
        virtual void init(Panel* _panel);
        virtual void preState();
        virtual void postState();
        virtual int inState();
};

#endif
