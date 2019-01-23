//
// Created by Kringle on 15/11/2018.
//

#ifndef KAPPAPRIDE_PATHFINDER_H
#define KAPPAPRIDE_PATHFINDER_H

#include "PathData.h"
#include "Thor/Vectors.hpp"
#include "map"
#include "PathData.h"
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <queue>
class pf {
public:
    struct pfNode
    {
        pfNode()
        {
            Id = h = g = 0;
            parent = nullptr;
            pos = {0,0};
        }
        pfNode(pth::pathVertex& input);
        int Id;
        sf::Vector2f pos;
        int h;
        int g;
        int fCost()const{return h+g;}

        pfNode *parent;
        std::vector<int> nb; //neighbors

        bool compareTo(pfNode const & other);
        bool operator==(pfNode const & n)const;
        bool operator!=(pfNode const & n)const;
        bool operator <(const pf::pfNode & other)const
        {
            return fCost()> other.fCost();
        }
        size_t hash() const;

    };
    pf(std::vector<pth::pathVertex> &);
    std::vector<int> findPath(int start, int end);
    int getDistance(pfNode &n1, pfNode &n2);
    std::vector<int> retrace(pfNode start, pfNode end);
private:
    std::vector<pth::pathVertex> &vertices;
    std::vector<pfNode> nodes;
    std::vector<bool> openNode_map;
    std::vector<bool> closedNode_map;
};
namespace std
{
    template<>
    struct hash<pf::pfNode> {
        size_t operator () (const pf::pfNode &f) const { return f.hash(); }
    };

}

#endif //KAPPAPRIDE_PATHFINDER_H
