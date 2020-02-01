#include <iostream>
#include <sstream>
#include <iterator>
#include <set>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include "Node.hpp"


bool BFS(Node &initialNode, Node &goalNode);

bool IDS(Node &initialNode, Node &goalNode);

bool DFS(Node &initialNode,Node &goalNode, int depthLimit);
std::vector<std::vector<int> > adjacent(std::vector<int> nums);
void display_path(std::unordered_map<std::string, std::string> &parents, std::string src);

int main()
{


    std::string userInput;
    char stringChar[10];
    std::cout
            << "Enter an array of integers with spaces in between them.  Once done enter a 0 to signal the end of array."
            << std::endl;
    std::cout << "Enter input here:";
    /*
      while(std::cin >>  number && number != 0){
              vectorInput[i] = number
                      i++;
      }
      for(int j = 0; j < vectorInput.size();j++){
          std::cout <<
      }*/
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
    /*
    for (int i = 0; i < vectorInput.size(); i++)
    {
        if (vectorInput[i] < 0)
        {
            std::cout << "Invalid input: Inputted negative numbers." << std::endl;
            std::cout << "Please run program again." << std::endl;
            exit(1);
        }
    }
*/

    //std::cout << vectorInput.size() << " Vector size" << std::endl;
/*
   std::set<int> testSet(vectorInput.begin(), vectorInput.end());
    std::cout << testSet.size() << " Set size" << std::endl;
    if (testSet.size() != vectorInput.size())
    {
        std::cout << "Invalid input: Either a non-digit, duplicate digits or not enough digits were entered as input."
                  << std::endl;
        std::cout << "Please run program again. " << std::endl;
        exit(1);
    }
    */
    Node initialNode(vectorInput);
    //vectorInput.assign(testSet.begin(),testSet.end());
    Node goalNode(goalVector);
    //initialNode.printVector();
   // goalNode.printVector();
    //BFS

    BFS(initialNode,goalNode);


    //IDS
    IDS(initialNode,goalNode);
    // std::cout << " Count " << count << std::endl;
    //  std::cout <<"IDS Found at level: " << IDS(vectorInput) << std::endl;




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
        //std::cout << "BTS Found it at this level: " << currentNode.getLevel() << std::endl;
        //  return 1;
        //return true;
        return true;
    }
    // initialNode.printVector();
    // std::vector<Node> parent;
    //std::unordered_set<std::string>::const_iterator got;
    while (!q.empty())
    {
        //  std::cout << " --------------------------------Top ! Empty q" << std::endl;
        Node currentNode = q.front();
        q.pop();
        if (currentNode.getString() == goalNode.getString())
        {
            display_path(parent,currentNode.getString());
          //  std::cout << " Current node printout" << std::endl;
            //std::cout << "BTS Found it at this level: " << currentNode.getLevel() << std::endl;
            //  return 1;
            //return true;
            return true;
        }
       // std::cout << " Before nei loop " << std::endl;
        for (std::vector<int> nei : adjacent(currentNode.getVector())) {
                Node neiNode(nei);
            if(neiNode.getString() == goalNode.getString()){
                parent[neiNode.getString()] = currentNode.getString();
                display_path(parent,neiNode.getString());
                std::cout << "The total number of states visited was " << visited.size() << std::endl;
                std::cout << "The max size of the queue/stack was " << queueSize << std::endl;
                return true;
            }
            if(visited.find(neiNode.getString()) == visited.end()){
                visited.insert(neiNode.getString());
                parent[neiNode.getString()] = currentNode.getString();
                q.push(neiNode);
                if (q.size() > queueSize)
                {
                    queueSize = q.size();
                }
            }
            //std::cout << "Bottom of Nei Loop" << std::endl;
        }
        /*
        std::vector v = currentNode.getVector();
        for (int i = 0; i < currentNode.getVector().size(); i++)
        {
            for (int j = i + 1; j < currentNode.getVector().size(); j++)
            {

                reverse(v.begin() + i, v.begin() + j + 1);
                Node vect(v);
                //  vect.printVector();
                //    std::cout << i << " i Printout          " << j << " J print out ----------------" << std::endl;
                reverse(v.begin() + i, v.begin() + j + 1);
                if (goalTest(vect.getVector()))
                {
                    // for(int i = 0; i < parentNodes.size(); i++){
                    //parentNodes.at(vect.getString());
                    // }
                    // std::cout << " Current node printout" << std::endl;
                    //  vect.printVector();
                    std::cout << "The total number of states visited was " << visited.size() << std::endl;
                    std::cout << "The max size of the queue/stack was " << queueSize << std::endl;
                    //std::cout << "Found it at this level: " << vect.getLevel() << std::endl;
                    // return 1;
                    return true;
                }
                got = visited.find(vect.getString());
                if (got == visited.end())
                {
                    visited.insert(vect.getString());
                }


                q.push(vect);
                if (q.size() > queueSize)
                {
                    queueSize = q.size();
                }
            }
//std::cout << " End of inside loop $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
        }
        // parent.push_back(currentNode);
        */
    }
return false;

}


bool IDS(Node &initialNode, Node &goalNode)
{
    std::cout << "Start IDS:" << std::endl;
    int depthLimit = 0;

    while (!DLS(initialNode, goalNode, depthLimit))
    {
        depthLimit++;
    }
    return true;

}

bool DFS(Node &initialNode, Node &goalNode, int depthLimit){
    //TODO call goaltest to check if output is correct.

 int queueSize = 0;
    std::stack<Node> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;
    parent[initialNode.getString()] = "";
    q.push(initialNode);
    visited.insert(initialNode.getString());



    if (initialNode.getString() == goalNode.getString())
    {
        initialNode.printVector();
        //std::cout << "BTS Found it at this level: " << currentNode.getLevel() << std::endl;
        //  return 1;
        //return true;
        return true;
    }
    // initialNode.printVector();
    // std::vector<Node> parent;
    //std::unordered_set<std::string>::const_iterator got;
    while (!q.empty())
    {
        //  std::cout << " --------------------------------Top ! Empty q" << std::endl;
        Node currentNode = q.top();
        q.pop();
        if (currentNode.getString() == goalNode.getString())
        {
            display_path(parent,currentNode.getString());
          //  std::cout << " Current node printout" << std::endl;
            //std::cout << "BTS Found it at this level: " << currentNode.getLevel() << std::endl;
            //  return 1;
            //return true;
            return true;
        }
       // std::cout << " Before nei loop " << std::endl;
        for (std::vector<int> nei : adjacent(currentNode.getVector())) {
                Node neiNode(nei);
            if(neiNode.getString() == goalNode.getString()){
                parent[neiNode.getString()] = currentNode.getString();
                display_path(parent,neiNode.getString());
                std::cout << "The total number of states visited was " << visited.size() << std::endl;
                std::cout << "The max size of the queue/stack was " << queueSize << std::endl;
                return true;
            }
            if(visited.find(neiNode.getString()) == visited.end()){
                visited.insert(neiNode.getString());
                parent[neiNode.getString()] = currentNode.getString();
                q.push(neiNode);
                if (q.size() > queueSize)
                {
                    queueSize = q.size();
                }
            }
        }
}
return false;

}


std::vector<std::vector<int> > adjacent(std::vector<int> nums) {
    std::vector<std::vector<int> > result;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            std::vector<int> curr = nums;
            reverse(curr.begin() + i, curr.begin() + j + 1);
            result.push_back(curr);
        }
    }
    return result;
}

void display_path(std::unordered_map<std::string, std::string> &parents, std::string src) {
    std::vector<std::string> path;
    while (src != "") {
        path.push_back(src);
        src = parents[src];
    }
    reverse(path.begin(), path.end());
    std::cout << " Inside display path" << std::endl;
    for (int i = 0; i < path.size(); ++i) {
            std::string output;
            std::string temp = path[i];
         for(int j = 0; j < path[i].size() - 1;j++){
                output = output + temp[j] + " ";
        }
        output += temp[path.size() + 1];
        std::cout << " After for loop display Path" << std::endl;
      std::cout << output << std::endl;
    }
}



