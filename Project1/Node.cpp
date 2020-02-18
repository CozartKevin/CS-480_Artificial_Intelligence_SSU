//
// Created by Raggdoll on 1/25/2020.
//
#include <iostream>

#include "Node.hpp"

Node::Node(std::vector<int> v)
{
    vector = v;
    number = convertVector(v);
    parent;
}

long long Node::convertVector(const std::vector<int> &v)
{
    long long temp = 0;
    for (int i = 0; i < v.size(); i++)
    {
        temp += v[i];
        if(i + 1 != v.size())
        {
            temp *= 10;
        }
    }
    return temp;
}

void Node::printVector()
{

    for (int x = 0; x < vector.size(); x++)
    {
        std::cout << vector[x] << ' ';
    }
    std::cout << std::endl;

}




