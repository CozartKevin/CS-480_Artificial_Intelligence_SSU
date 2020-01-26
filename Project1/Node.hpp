//
// Created by Raggdoll on 1/25/2020.
//

#ifndef PROJECT1_NODE_HPP
#define PROJECT1_NODE_HPP
#include <vector>
#include <string>

class Node {
public:
    explicit Node(std::vector<int> v, int level = 0);

    std::string static convertVector(std::vector<int> v);
    std::vector<int> getVector(){return vector;}
    std::string getString(){return string;}
    int getLevel(){return curLevel;};
    void setLevel(int x){curLevel = x;}
    void setVector(std::vector<int> &vectorSetTo){vector = vectorSetTo;}
    void setString(std::string &s){string = s;}
    void printVector();
    void printString();

private:
        std::vector<int> vector;
        std::string string;
        int curLevel;
};





#endif //PROJECT1_NODE_HPP
