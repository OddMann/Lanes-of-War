//
// Created by Kringla on 12.11.2018.
//

#include "PathData.h"
namespace pth
{
    endBoundary::endBoundary(sf::Vector2f a, sf::Vector2f b, sf::Vector2f norm, sf::Vector2f perp)
    {
        this->a = a;
        this->b = b;
        this->norm = norm;
        this->perp = perp;
    }





    //nextVertex operators
    nextVertex::nextVertex()
    {
        endLine = nullptr;
        pos = {0,0};
        width = 0;
        Id = 0;
        nodeId = 0;

    }


    nextVertex::nextVertex(sf::Vector2f pos, float width, endBoundary &endLine, int Id, int nodeId)
    {
    this->pos = pos;
    this->width = width;
    this->Id = Id;
    this->endLine = &endLine;
    }


    bool nextVertex::operator==(pathVertex& n)const
    {
        return bool(this->Id == n.Id);
    }


    bool nextVertex::operator==(nextVertex& n)const
    {
        return bool(this->Id == n.Id);
    }


    void nextVertex::swap(nextVertex& first, nextVertex& second)
    {
        using std::swap;
        swap(first.pos, second.pos);
        swap(first.width, second.width);
        swap(first.endLine, second.endLine);
        swap(first.Id, second.Id);
        swap(first.nodeId, second.nodeId);
    }


    nextVertex& nextVertex::operator=(nextVertex other)
    {
        swap(*this, other);
        return *this;
    }




    //pathVertex operators
    pathVertex::pathVertex(sf::Vector2f p, float w, int nId, int lId)
    {
        pos = p;
        width = w;
        Id = PathIds::next_vId++;
        nodeId = nId;
        laneId = lId;
    }


    bool pathVertex::operator==(pathVertex& n)const
    {
        return bool(this->Id == n.Id);
    }


    bool pathVertex::operator==(nextVertex& n)const
    {
        return bool(this->Id == n.Id);
    }


    nextVertex pathVertex::operator[](int Id) {
        auto it = boundaries.find(Id);
        if (it != boundaries.end()) {
            endBoundary &data = it->second;
            return {pos, width, data, Id, nodeId};
        }
        std::cerr << "Vertex " << this->Id << " don't have path to vertex " << Id << " , terminating." << std::endl;
        std::terminate();
    }


int PathIds::next_vId = 0;    //iterator for vertex Id
int PathIds::next_pId = 0;    //iterator for path Id



    //Path class functions
    Path::Path() : vertices(dummy)
    {
        path = {};
        length = 0;
        Id = 0;
    }


    Path::Path(std::vector<pathVertex>& v) : vertices(v)
    {
        path = {0,0};
        Id = PathIds::next_pId++;
        length = 2;
    }


    Path::Path(std::vector<int> &path, std::vector<pathVertex>& v) : vertices(v), path(path)
    {
        this->path = std::move(path);
        length = this->path.size();
        Id = PathIds::next_pId++;
    }


    nextVertex Path::start(int start) const
    {
        return vertices[path[0]][start];
    }


    bool Path::nextPath(int &pi, int &prev, nextVertex& next)
    {
        if((size_t)pi < length-1)
        {
            prev = next.Id;
            next = vertices[path[pi]][path[pi+1]];
            pi++;
            return true;
        }
        return false;
    }


    int Path::operator[](int i)
    {
        return path[i];
    }


    Path& Path::operator=(Path&& s)noexcept
    {
        Id = s.Id;
        path = std::move(s.path);
        vertices = s.vertices;
        length = s.length;
        return *this;
    }
}