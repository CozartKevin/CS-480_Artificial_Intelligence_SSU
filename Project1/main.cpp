#include <iostream>
#include <sstream>
#include <iterator>
#include <set>
#include <queue>
#include <unordered_set>
#include "Node.hpp"

bool goalTest(const std::vector<int> &vectorInput);

int main()
{


    std::string userInput;
    char stringChar[10];
    std::cout << "Enter the numbers 1 - 10 in any order with no duplicate numbers." << std::endl;
    std::getline(std::cin, userInput);
    std::istringstream is(userInput);
    std::vector<int> vectorInput((std::istream_iterator<int>(is)), std::istream_iterator<int>());

    for (int i = 0; i < vectorInput.size(); i++)
    {
        if (vectorInput[i] > 10 || vectorInput[i] < 1)
        {
            std::cout << "Invalid input: Inputted numbers outside of 1 - 10 range." << std::endl;
            std::cout << "Please run program again." << std::endl;
            exit(1);
        }
    }
    std::set<int> testSet(vectorInput.begin(), vectorInput.end());
    if (testSet.size() != 10)
    {
        std::cout << "Invalid input: Either a non-digit, duplicate digits or not enough digits were entered as input."
                  << std::endl;
        std::cout << "Please run program again. " << std::endl;
        exit(1);
    }

    //BFS
    Node initialNode(vectorInput);
    std::queue<Node> q;
    std::unordered_set<std::string> visited;

    q.push(initialNode);
    visited.insert(initialNode.getString());

    while (!q.empty())
    {
        Node currentNode = q.front();
        q.pop();
        if (goalTest(currentNode.getVector()))
        {
            std::cout << "BTS Found it at this level: " << currentNode.getLevel() << std::endl;
            return 1;

        }

        for (int i = 0; i < currentNode.getVector().size(); i++)
            for (int j = i + 1; j < currentNode.getVector().size(); j++)
            {
                std::vector v = currentNode.getVector();
                reverse(v.begin() + i, v.begin() + j + 1);
                Node vect(v, currentNode.getLevel() + 1);
              //  vect.printVector();
                reverse(v.begin() + i, v.begin() + j + 1);
                if (goalTest(vect.getVector()))
                {
                    std::cout << "Found it at this level: " << vect.getLevel() << std::endl;
                    return 1;
                }
                if (visited.find(vect.getString()) == visited.end())
                {
                    visited.insert(vect.getString());
                    q.push(vect);
                }
            }
    }


    //IDS


}

bool goalTest(const std::vector<int> &vectorInput)
{
    for (int i = 0; i < vectorInput.size(); i++)
    {
        if (vectorInput[i] != i + 1)
        {
            return false;
        }
    }
    return true;
}

