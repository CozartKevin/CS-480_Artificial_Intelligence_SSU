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
    parameterObject(){maxVisitedStates = 0, parent;};

    void incrementMaxVisitedStates(){maxVisitedStates++;};
    int getMaxVisitedStates(){return maxVisitedStates;};

    void addParent(std::string s1, std::string s2);

    std::unordered_map<std::string,std::string>& getParent(){return parent;};

    void insertVisited(std::string s){visited.insert(s);};
    bool findVisited(std::string s);
    void resetVisited(){visited.clear();};

    void incrementDepthLimit();;
    int getDepthLimit(){return depthLimit;};
    void decrementDepthLimit(){depthLimit--;};

    int getMaxDepth(){return maxDepth;};

private:
    int maxVisitedStates = 0;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;
    int depthLimit = 0;
    int maxDepth = 0;
};


#endif //PROJECT1_PARAMETEROBJECT_HPP
