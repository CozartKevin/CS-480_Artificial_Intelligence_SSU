//
// Created by Raggdoll on 2/15/2020.
//

#ifndef PROJECT1_GREATER_HPP
#define PROJECT1_GREATER_HPP
#include <utility>
#include "Node.hpp"

class greater {
public:
bool operator()(std::pair<Node,int> lhs,std::pair<Node,int> rhs){return lhs.second > rhs.second;};

};


#endif //PROJECT1_GREATER_HPP
