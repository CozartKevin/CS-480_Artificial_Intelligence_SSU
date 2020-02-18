//
// Created by Raggdoll on 2/1/2020.
//
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#ifndef PROJECT1_PARAMETEROBJECT_HPP
#define PROJECT1_PARAMETEROBJECT_HPP


class parameterObject {
public:
    parameterObject(){ maxVisitedStates = 0, parent; };
    void incrementMaxVisitedStates(){ maxVisitedStates++; };
    int getMaxVisitedStates(){ return maxVisitedStates; };
    void addParent(long long s1, long long s2);
    std::unordered_map<long long, long long> &getParent(){ return parent; };
    void insertVisited(long long i){ visited.insert(i); };
    bool findVisited(long long i);
    void resetVisited(){ visited.clear(); };
    void incrementDepthLimit();;
    int getDepthLimit(){ return depthLimit; };
    void decrementDepthLimit(){ depthLimit--; };
    int getMaxDepth(){ return maxDepth; };

private:
    int maxVisitedStates = 0;
    std::unordered_map<long long, long long> parent;
    std::unordered_set<long long> visited;
    int depthLimit = 0;
    int maxDepth = 0;
};


#endif //PROJECT1_PARAMETEROBJECT_HPP
