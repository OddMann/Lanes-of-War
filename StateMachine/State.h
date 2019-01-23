//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_STATE_H
#define KAPPAPRIDE_STATE_H

class Machine;

class State {
public:
    State() {}
    virtual ~State() {};
    virtual void GoNext(Machine &context) = 0;
protected:
    bool run = false;
};



#endif //KAPPAPRIDE_STATE_H
