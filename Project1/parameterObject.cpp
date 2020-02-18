//
// Created by Raggdoll on 2/1/2020.
//

#include "parameterObject.hpp"

void parameterObject::addParent(long long l1, long long l2)
{
    parent[l1] = l2;
}

bool parameterObject::findVisited(long long i)
{
    return (visited.find(i) == visited.end());
}

void parameterObject::incrementDepthLimit()
{
    if ((depthLimit + 1) > maxDepth)
    {
        maxDepth = depthLimit + 1;
    }
    depthLimit++;
}

