//
// Created by Kringle on 19/10/2018.
//

#include "Space.h"

Space::Space(Map& map) : Object(map)
{
    Space_Id = nextS_Id++;
    this->width = 0;
    this->numSpaces = 0;
}
Space::Space(sf::Vector2f pos, float width, Map& map) : Object(pos, map)
{
    Space_Id = nextS_Id++;
    this->width = width;
    this->numSpaces = 0;
}

size_t Space::size()
{
    size_t s;
    s = attached_Spaces.size();
    s += spaces_Vector.size();
    s += pathVertexes.size();
    return s;
}
void Space::Attach_Space(int space_Id, sf::Vector2f pos)
{
    attached_Spaces[space_Id] = pos;
    spaces_Vector.push_back(pos);
    numSpaces++;
}
int Space::nextS_Id = 0;