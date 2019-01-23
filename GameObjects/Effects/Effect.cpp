//
// Created by Kringle on 19/10/2018.
//

#include "Effect.h"


Effect::Effect(Map &map) :Object(map)
{
    Effect_Id = nextE_Id;

}
int Effect::nextE_Id = 0;