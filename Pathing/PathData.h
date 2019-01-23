//
// Created by Kringla on 12.11.2018.
//

#ifndef KAPPAPRIDE_PATHDATA_H
#define KAPPAPRIDE_PATHDATA_H

#include <map>
#include <vector>
#include <iostream>
#include "Thor/Vectors.hpp"
#include <memory>

namespace pth       //Path namespace, for all path related types and functions
{

    struct endBoundary;  // struct containing data on path end
    struct nextVertex;  // struct containing data on needed instance of the next vertex
    struct pathVertex;  // struct containing all data on a vertex
    class Path;         // class containing data and function for a full path



    static std::vector<pathVertex> dummy;

    struct endBoundary
    {
        endBoundary(){a=b=norm=perp = {0,0};}
        endBoundary(sf::Vector2f a, sf::Vector2f b, sf::Vector2f norm, sf::Vector2f perp);
        sf::Vector2f a;
        sf::Vector2f b;
        sf::Vector2f norm;
        sf::Vector2f perp;
    };

    struct nextVertex
    {
        nextVertex();
        nextVertex(sf::Vector2f pos, float width, endBoundary &endLine, int Id, int nodeId);
        ~nextVertex(){endLine = nullptr;}
        sf::Vector2f pos;
        float width;
        endBoundary *endLine;
        int Id;
        int nodeId;
        bool operator==(pathVertex& n)const;
        bool operator==(nextVertex& n)const;
        void swap(nextVertex& first, nextVertex& second);
        nextVertex& operator=(nextVertex other);
    };

    struct pathVertex
    {
        pathVertex(sf::Vector2f p, float w, int nId, int lId/*, std::map<int,endBoundary> boundries*/);
        sf::Vector2f pos;
        float width;
        std::map<int,endBoundary> boundaries;
        int Id;
        int nodeId;
        int laneId;
        nextVertex operator[](int Id);
        bool operator==(pathVertex& n)const;
        bool operator==(nextVertex& n)const;
    };

    class PathIds
    {
    public:
        static int next_vId;    //iterator for vertex Id
        static int next_pId;    //iterator for path Id
        void resetIds(){next_pId = next_vId =0;}
    };

    class Path
    {
    public:
        Path();
        explicit Path(std::vector<pathVertex>& v);
        Path(std::vector<int> &path, std::vector<pathVertex>& v);
        ~Path() = default;
        nextVertex start(int start) const;
        bool nextPath(int &pi, int &prev, nextVertex& next);
        int operator[](int i);
        Path& operator=(Path&& s)noexcept;
    private:
        std::vector<pathVertex>& vertices;
        std::vector<int> path;
        size_t length;
        int Id;
    };



};

#endif //KAPPAPRIDE_PATHDATA_H







