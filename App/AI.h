//
// Created by Kringle on 29/11/2018.
//

#ifndef KAPPAPRIDE_AI_H
#define KAPPAPRIDE_AI_H

#include "App.h"
#include "../tools/tools.h"
class AI: public Team {
public:
    AI(int money, int income, int spawn, App& app);
    bool tick()override;
    bool boom();
    bool rush();
    bool mass();
    std::list<char> racks_order = {1,2,2};
    enum Phase{BOOM,RUSH,MASS};
    tl::maxHeap<Node*> closestNode;
    Phase phase;
};


#endif //KAPPAPRIDE_AI_H
