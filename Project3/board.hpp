//
// Created by Raggdoll on 3/7/2020.
//

#ifndef PROJECT3_BOARD_HPP
#define PROJECT3_BOARD_HPP
#include <vector>

class board {
public:
    board();
    board(std::vector< std::vector<char> > userInputVector);
    void getBoardfromUser();
    std::vector<std::vector<char>> getBoard(){return boardVec;};
   // float MinMax();
   // void MinMaxAlphaBeta();
   // int eval();
    void setMaxNodeExpansion(){maxNodeExpansion++;}
    int getMaxNodeExpansion(){return maxNodeExpansion;}
    void printBoard();
    void setDepthOfK();
    void setMax(int m){max = m;};
    int getMax(){return max;};
    void setMin(int m){min = m;};
    int getMin(){return min;};
    void setVal(float v){val = v;};
    float getVal(){return val;};
    void increaseMaxNodeExpansion(){maxNodeExpansion = maxNodeExpansion + 1;};
    int getDepthOfK(){return depthOfK;};
    //int leaf(std::vector< std::vector<char> > vector);
   // bool isValid();

private:
    //Player X represented as 1, Player O represented as -1, blank space represented as a 0;
    std::vector< std::vector<char> > boardVec{{'-','-','-','-'},{'-','-','-','-'},{'-','-','-','-'},{'-','-','-','-'}};
    int maxNodeExpansion = 0;
    int depthOfK = 0;
    int min;
    int max;
    float val;





};


#endif //PROJECT3_BOARD_HPP
