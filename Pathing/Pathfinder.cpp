//
// Created by Kringle on 15/11/2018.
//

#include "Pathfinder.h"
#include "vector"

bool pf::pfNode::compareTo(pfNode const & other)
{
    if(this->fCost() == other.fCost())
    {
        return this->h <= other.h;
    }
    else
        return this->fCost() < other.fCost();
}
bool pf::pfNode::operator==(pfNode const & n)const
{
    return (Id == n.Id);
}
bool pf::pfNode::operator!=(pfNode const & n)const
{
    return (Id != n.Id);
}
size_t pf::pfNode::hash() const
{
    return (size_t)Id;
}
pf::pf(std::vector<pth::pathVertex> &input) : vertices(input) , openNode_map(vertices.size(),false) ,closedNode_map(vertices.size(),false)
{
    for(auto v: vertices)
    {
        nodes.emplace_back(v);
    }
}

std::vector<int> pf::findPath(int begin, int goal)
{
    pfNode &start = nodes[begin];
    pfNode &end   = nodes[goal];
    std::unordered_set<pfNode> closedSet;
    std::priority_queue<pfNode> openSet;

    start.g = 0;
    start.h = getDistance(start, end);
    openSet.push(start);
    openNode_map[start.Id] = true;
    while(!openSet.empty())
    {
        //remove top element from open list
        pfNode &current = nodes[pfNode(openSet.top()).Id];
        openSet.pop();
        openNode_map[current.Id] = false;
        //put current into closed list
        closedSet.insert(current);
        closedNode_map[current.Id] = true;


        if(current == end)
        {
            return retrace(start,end); //TODO:: construct path
        }

        for(auto n: current.nb)
        {
            pfNode &child  = nodes[n];
            if (closedSet.count(child) > 0)
            {
                continue;
            }
            float tent_gScore = current.g + getDistance(current, child);

            //test if current score
            if(tent_gScore < child.g || !openNode_map[n])
            {
                child.g = (int)tent_gScore;
                child.h = getDistance(child, end);
                child.parent = &current;
                openSet.push(child);
                openNode_map[n] = true;
            }

        }
    }
    std::cout << "BREAKPOINT";
    exit(0);
}
std::vector<int> pf::retrace(pfNode start, pfNode end)
{
     std::vector<int> path;
     pfNode current = end;
     while(current != start)
     {
        path.push_back(current.Id);
        current = *current.parent;
     }
     std::reverse(path.begin(),path.end());
     return path;
}
int pf::getDistance(pfNode &n1, pfNode &n2)
{
    return (int)thor::squaredLength(n1.pos-n2.pos);
}


pf::pfNode::pfNode(pth::pathVertex & input)
{
    Id = input.Id;
    pos = input.pos;
    h = g= 0;
    parent = nullptr;
    for(auto& n: input.boundaries)
    {
        nb.emplace_back(n.first);
    }
}