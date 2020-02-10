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

int visitedForDebug = 0;

bool BFS(Node &initialNode, Node &goalNode);

bool IDS(Node &initialNode, Node &goalNode);

bool DFS(Node &initialNode, Node &goalNode, parameterObject &paraObj);

void display_path(std::unordered_map<std::string, std::string> &parents, std::string &src);

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
    BFS(initialNode, goalNode);
    std::clock_t c_end = std::clock();
    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms / 1000.0 << " s\n" << std::endl;

    //IDS
    IDS(initialNode, goalNode);
}

bool BFS(Node &initialNode, Node &goalNode)
{


    int queueSize = 0;
    std::queue<Node> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;
    parent[initialNode.getString()] = "";
    q.push(initialNode);
    visited.insert(initialNode.getString());
    std::cout << "Start BFS:" << std::endl;


    if (initialNode.getString() == goalNode.getString())
    {
        initialNode.printVector();
        return true;
    }

    while (!q.empty())
    {
        Node currentNode = q.front();
        q.pop();
        if (currentNode.getString() == goalNode.getString())
        {
            display_path(parent, currentNode.getString());
            return true;
        }
        Node neiNode(initialNode);
        std::vector<int> nums = currentNode.getVector();

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = i + 1; j < nums.size(); ++j)
            {

                reverse(nums.begin() + i, nums.begin() + j + 1);
                std::vector<int> &nei = nums;

                neiNode.setVector(nei);
                neiNode.setString(Node::convertVector(nei));
                if (neiNode.getString() == goalNode.getString())
                {
                    parent[neiNode.getString()] = currentNode.getString();
                    display_path(parent, neiNode.getString());
                    std::cout << "The total number of states visited was " << visited.size() << std::endl;
                    std::cout << "The max size of the queue/stack was " << queueSize << std::endl;
                    return true;
                }

                if (visited.find(neiNode.getString()) == visited.end())
                {
                    visited.insert(neiNode.getString());
                    parent[neiNode.getString()] = currentNode.getString();
                    q.push(neiNode);
                    if (q.size() > queueSize)
                    {
                        queueSize = q.size();
                    }
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
    std::unordered_map<std::string, std::string> parent;
    int depthLimit = 0;
    parameterObject state;

    while (!DFS(initialNode, goalNode, state))
    {
        state.incrementDepthLimit();
    }

    display_path(state.getParent(), goalNode.getString());
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

    if (initialNode.getString() == goalNode.getString())
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
            neiNode.setString(Node::convertVector(nei));

            state.decrementDepthLimit(); //todo find out if this call causes trouble
            if (DFS(neiNode, goalNode, state))
            {
                state.insertVisited(neiNode.getString());
                state.addParent(neiNode.getString(), initialNode.getString());
                return true;
            }
            state.incrementDepthLimit(); //todo find out if this call causes trouble
            if (state.findVisited(neiNode.getString()))
            {
                state.insertVisited(neiNode.getString());
            }


            reverse(nums.begin() + i, nums.begin() + j + 1);
        }


    }
    return false;
}

void display_path(std::unordered_map<std::string, std::string> &parents, std::string &src)
{
    std::vector<std::string> path;
    while (src != "")
    {
        path.push_back(src);
        src = parents[src];
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); ++i)
    {
        std::string output;
        std::string temp = path[i];
        for (int j = 0; j < path[i].size(); j++)
        {
            output = output + temp[j] + " ";
        }
        std::cout << output << std::endl;
    }
}




