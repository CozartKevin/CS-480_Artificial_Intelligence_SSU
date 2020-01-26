//
// Created by Raggdoll on 1/25/2020.
//
#include <iostream>

#include "Node.hpp"

Node::Node(std::vector<int> v, int level)
{
    vector = v;
    string = convertVector(v);
    curLevel = level;
}

std::string Node::convertVector(std::vector<int> v)
{
    std::string convertedString;
    for(int i = 0; i < v.size(); i++)
    {
     convertedString += std::to_string(v[i]);
    }
    return convertedString;
}

void Node::printVector()
{

    for(int x = 0; x < vector.size(); x++)
    {
        std::cout << vector[x] << ' ';
    }
    std::cout << std::endl;

}

void Node::printString()
{
    std::cout << string << std::endl;

}



