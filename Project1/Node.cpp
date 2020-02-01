//
// Created by Raggdoll on 1/25/2020.
//
#include <iostream>

#include "Node.hpp"

Node::Node(std::vector<int> v)
{
    vector = v;
    string = convertVector(v);
    parent;
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

std::vector<Node> Node::adjacent()
{

        std::vector<Node> result;
        for (int i = 0; i < vector.size(); ++i) {
            for (int j = i + 1; j < vector.size(); ++j) {
                Node curr(vector);
                reverse(curr.getVector().begin() + i, curr.getVector().end() + j + 1);
                result.push_back(curr);
            }
        }
        return result;
    }

/*
void Node::printParentVectors()
{
    std::vector<Node *> parentNodes;
    parentNodes.push_back(parent);
    while(parent->getParent()){
        parentNodes.push_back(parent->getParent());
    }

    for(int i = parentNodes.size(); i > 0;i--){
        parentNodes[i]->printVector();
    }
}
*/






