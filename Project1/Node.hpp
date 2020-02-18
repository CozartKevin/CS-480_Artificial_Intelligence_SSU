//
// Created by Raggdoll on 1/25/2020.
//

#ifndef PROJECT1_NODE_HPP
#define PROJECT1_NODE_HPP

#include <vector>
#include <string>

class Node {
public:
    explicit Node(std::vector<int> v);
    long long static convertVector(const std::vector<int> &v);
    std::vector<int> getVector(){ return vector; }
    long long &getNumber(){ return number; }

    void setVector(std::vector<int> &vectorSetTo){ vector = vectorSetTo; }
    void setNumber(const long long &s){ number = s; }
    void printVector();

private:
    std::vector<int> vector;
    long long number;
    Node *parent;
};

#endif //PROJECT1_NODE_HPP
