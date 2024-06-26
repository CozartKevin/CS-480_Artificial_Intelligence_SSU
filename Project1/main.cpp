#include <iostream>
#include <sstream>
#include <iterator>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "Node.hpp"
#include "parameterObject.hpp"
#include "greater.hpp"

int visitedForDebug = 0;

bool A_Star(Node &initialNode, Node &goalNode);

void display_path(std::unordered_map<long long, long long> &parents, long long &src);
bool greaterThen(Node lhs, Node rhs);
int h(Node node);
int main()
{


    std::string userInput;
    char stringChar[10];
    std::cout
            << "Enter an array of integers with spaces in between them.  Once done enter a 0 to signal the end of array."
            << std::endl;
    std::cout << "Enter input here:";
    std::getline(std::cin, userInput);
    std::istringstream is(userInput);
    std::vector<int> vectorInput((std::istream_iterator<int>(is)), std::istream_iterator<int>());

    for (int x = 0; x < vectorInput.size(); x++)
    {
        if (vectorInput[x] == 0)
        {
            vectorInput.erase(vectorInput.begin() + x, vectorInput.end());
        }
    }

    std::vector<int> goalVector = vectorInput;
    sort(goalVector.begin(), goalVector.end());
    for (int i = 0; i < goalVector.size(); i++)
    {
        if (goalVector[i] != i + 1)
        {
            std::cout
                    << "Invalid input: Either a non-digit, duplicate digits were entered as input."
                    << std::endl;
            std::cout << "Please run program again. " << std::endl;
            exit(1);
        }
    }

    Node initialNode(vectorInput);
    Node goalNode(goalVector);

    //BFS
    std::clock_t c_start = std::clock();
    A_Star(initialNode, goalNode);
    std::clock_t c_end = std::clock();
    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms / 1000.0 << " s\n" << std::endl;
    std::cin.get();
    //IDS
    //  IDS(initialNode, goalNode);
}

bool A_Star(Node &initialNode, Node &goalNode)
{


    int queueSize = 0;
    int visited = 0;
    // std::queue<Node> q;
    std::priority_queue <std::pair<Node,int>, std::vector<std::pair<Node,int>>, greater> q;
    //std::unordered_set<long long> visited;
    std::unordered_map<long long, long long> parent;
    parent[initialNode.getNumber()] = 0;
    q.push(std::pair(initialNode,h(initialNode)));
    visited++;
    std::cout << "Start A*:" << std::endl;


    if (initialNode.getVector() == goalNode.getVector())
    {
        initialNode.printVector();
        return true;
    }

    while (!q.empty())
    {
        std::pair<Node,int> currentNode = q.top();
        q.pop();
        if (currentNode.first.getVector() == goalNode.getVector())
        {
            display_path(parent, currentNode.first.getNumber());
            return true;
        }
        Node neiNode(initialNode);
        std::vector<int> nums = currentNode.first.getVector();

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = i + 1; j < nums.size(); ++j)
            {

                reverse(nums.begin() + i, nums.begin() + j + 1);
                std::vector<int> &nei = nums;
                neiNode.setNumber(Node::convertVector(nei));
                neiNode.setVector(nei);
                if (neiNode.getVector() == goalNode.getVector())
                {
                    parent[neiNode.getNumber()] = currentNode.first.getNumber();
                    display_path(parent, neiNode.getNumber());
                    std::cout << "The total number of states visited was " << visited << std::endl;
                    std::cout << "The max size of the queue/stack was " << queueSize << std::endl;
                    return true;
                }

                visited++;

                if (parent.find(neiNode.getNumber()) == parent.end()) {

                    parent[neiNode.getNumber()] = currentNode.first.getNumber();
                }
                q.push(std::pair(neiNode,h(neiNode) + 2));
                if (q.size() > queueSize)
                {
                    queueSize = q.size();
                }

                reverse(nums.begin() + i, nums.begin() + j + 1);
            }
        }
    }
    return false;

}


bool IDS(Node &initialNode, Node &goalNode)
{
    std::clock_t c_start = std::clock();
    std::cout << "Start IDS:" << std::endl;
    std::unordered_map<long long, long long> parent;
    int depthLimit = 0;
    parameterObject state;

    while (!DFS(initialNode, goalNode, state))
    {
        state.incrementDepthLimit();
    }

    display_path(state.getParent(), goalNode.getNumber());
    std::clock_t c_end = std::clock();
    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms / 1000.0 << " s\n";
    std::cout << "The total number of states visited was " << state.getMaxVisitedStates() << std::endl;
    std::cout << "The max depth of recursion was " << state.getMaxDepth() << std::endl;

    return true;
}

bool DFS(Node &initialNode, Node &goalNode, parameterObject &state)
{
    state.incrementMaxVisitedStates();

    if (initialNode.getVector() == goalNode.getVector())
    {
        return true;
    }

    if (state.getDepthLimit() <= 0)
    {
        return false;
    }
    Node neiNode(initialNode);

    std::vector<int> nums = initialNode.getVector();

    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = i + 1; j < nums.size(); ++j)
        {
            //    std::copy(nums.begin(),nums.end(), curr.begin());
            //  curr = nums;
            reverse(nums.begin() + i, nums.begin() + j + 1);
            std::vector<int> &nei = nums;

            neiNode.setVector(nei);
            neiNode.setNumber(Node::convertVector(nei));
            state.decrementDepthLimit(); //todo find out if this call causes trouble
            if (DFS(neiNode, goalNode, state))
            {
                state.insertVisited(neiNode.getNumber());
                state.addParent(neiNode.getNumber(), initialNode.getNumber());
                return true;
            }
            state.incrementDepthLimit(); //todo find out if this call causes trouble
            if (state.findVisited(neiNode.getNumber()))
            {
                state.insertVisited(neiNode.getNumber());
            }


            reverse(nums.begin() + i, nums.begin() + j + 1);
        }


    }
    return false;
}

void display_path(std::unordered_map<long long, long long> &parents, long long &src)
{
    std::vector<std::string> path;

    while (src != 0) {
        path.push_back(std::to_string(src));
        src = parents[src];
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); ++i) {
        std::string output;
        std::string temp = path[i];
        for (int j = 0; j < path[i].size(); j++) {
            output = output + temp[j] + " ";
        }
        std::cout << output << std::endl;
    }
}

bool greaterThen(Node lhs, Node rhs){
    return lhs.getNumber() > rhs.getNumber();
}

int h(Node node)
{
    int numberOfBreakpoints = 0;
    for(int i = 0; i < node.getVector().size() - 1; i++){

        if(abs(node.getVector()[i] - node.getVector()[i+1]) != 1 ){
            numberOfBreakpoints++;
        }
    }

    return numberOfBreakpoints;
}


