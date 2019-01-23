//
// Created by Kringla on 13.11.2018.
//

#include "Interface.h"

Interface::Interface(Map& map) : Object(map)
{
    Interface_Id = nextI_Id++;
}
int Interface::nextI_Id = 0;