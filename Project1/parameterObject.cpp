//
// Created by Raggdoll on 2/1/2020.
//

#include "parameterObject.hpp"

void parameterObject::addParent(std::string s1, std::string s2)
{
    parent[s1] = s2;
}

bool parameterObject::findVisited(std::string s)
{
    return (visited.find(s) == visited.end());
}

void parameterObject::incrementDepthLimit()
{
    if ((depthLimit + 1) > maxDepth)
    {
        maxDepth = depthLimit + 1;
    }
    depthLimit++;
}

