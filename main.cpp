#include <iostream>
#include "StateMachine/Machine.h"
//#include "App/App.h"
#include "jsoncpp/json/json.h"

int main() {

    App app;

    Machine machine(app);

    while(machine.GetRunning())
        machine.GoNext();

    return EXIT_SUCCESS;


    return 0;
}