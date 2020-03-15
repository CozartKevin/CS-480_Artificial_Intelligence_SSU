#include <iostream>
#include <string>
#include "board.hpp"
#include <math.h>
#include <limits>

board MinMax(board  board, int & maxNodesExpanded);

bool leaf(board board);

float eval(board board);

bool isValid(board board);

void countXO(board &board, int &xCount, int &oCount);

void MinMaxAlphaBeta(board board);

bool max_Node(board board);
bool xTurnCheck(board board);

std::vector<board> succ(board board);

void curPlayer(board &board);
char curPlayerConvert(board &board);
int main()
{
    int userChoice;
    bool validInput;
    do
    {
        std::cout << "Please enter the number of the option you would like to run: " << std::endl;
        std::cout << "1 (MinMax)" << std::endl;
        std::cout << "2 (Alpha-Beta Pruning)" << std::endl;
        std::cout << "3 (Quit) " << std::endl;
        std::cin >> userChoice;
        if(userChoice != 1 && userChoice != 2 && userChoice != 3){
            std::cout << "Invalid entry, please try again. " << std::endl;
            validInput = false;
        }else{
            validInput = true;
        }
        std::cin.ignore();
    }while(!validInput);

    board gameBoard;
    board test;
    int maxNodesExpanded = 0;

switch(userChoice){
    case 1:
        gameBoard.getBoardfromUser();
        //gameBoard.printBoard();
       gameBoard.getCurrentPlayer();
       curPlayer(gameBoard);
    //   std::cout <<  gameBoard.getCurrentPlayer() << " PRE MINMAX CUR PLAYER" << std::endl;
        test = MinMax(gameBoard, maxNodesExpanded);
        std::cout << "Playing for player: " << curPlayerConvert(gameBoard) << std::endl;
         std::cout << "Max Nodes Expanded: " << maxNodesExpanded << std::endl;
        std::cout <<  "Place move: " << std::endl;
        test.printBoard();
        std::cout << test.getVal() << " board outcome. " << std::endl;
        std::cout << std::endl;
        std::cout << "Board Outcome Key:" << std::endl;
        std::cout << "  1 = Win for Current player" << std::endl;
        std::cout << "  0 = Loss for Current player" << std::endl;
        std::cout << "  0.5 = Tie for Current player" << std::endl;
        std::cout << " -1 = Invalid Game board" << std::endl;

        std::cout << std::endl;
        break;
    case 2:
        gameBoard.getBoardfromUser();
        gameBoard.printBoard();
        gameBoard.setDepthOfK();
       std::cout << gameBoard.getDepthOfK() << " Depth of K " << std::endl;
        MinMaxAlphaBeta(gameBoard);
        break;
    default:
        exit(0);
}



}




board MinMax(board pos, int & maxNodesExpanded)
{
    maxNodesExpanded++;

    if(leaf(pos)){
        pos.setVal(eval(pos));
        return pos;
    }

if(max_Node(pos)){
    pos.setVal(-std::numeric_limits<float>::infinity());
}else pos.setVal(std::numeric_limits<float>::infinity());


std::vector<board> children =  succ(pos);
board tmp_board;

bool maxLoop = max_Node(pos);
for(int i = 0; i < children.size(); i++){

        if (maxLoop)
        {
           tmp_board = MinMax(children[i], maxNodesExpanded);

            if(tmp_board.getVal() > pos.getVal())
            {
                pos = children[i];
                pos.setVal(tmp_board.getVal());
            }
        }
        else
        {
            tmp_board = MinMax(children[i], maxNodesExpanded);
            if(tmp_board.getVal() < pos.getVal())
            {
                pos = children[i];
                pos.setVal(tmp_board.getVal());
            }
        }
    }


std::cout << pos.getVal() << " Before Return" << std::endl;
return pos;

}

bool max_Node(board board)
{

    if(board.getCurrentPlayer() == 1){

    return xTurnCheck(board);
    } else {

      return !xTurnCheck(board);
    }
}

void MinMaxAlphaBeta(board board)
{

}



float eval(board board)
{
    if(isValid(board)){
        bool isDash = false;
        bool rowX[4] = {false, false, false, false};
        bool colX[4] = {false, false, false, false};
        bool rowO[4] = {false, false, false, false};
        bool colO[4] = {false, false, false, false};
        std::vector<std::vector<char>> temp;
        temp = board.getBoard();
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(toupper((temp[i][j]) == 'O')){
                    rowO[i] = true;
                    colO[j] = true;
                }
                if(toupper((temp[i][j]) == 'X')){
                    rowX[i] = true;
                    colX[j] = true;
                }
                if(toupper((temp[i][j]) == '-')){
                    isDash = true;
                }
            }
        }
        bool xWin = true;
        bool oWin = true;
        for(int k = 0; k < 4; k++){
            if(!(rowX[k] && colX[k])){
                xWin = false;
            }
            if(!(rowO[k] && colO[k])){
                oWin = false;
            }
            if(!xWin && !oWin){
               break;
            }
        }

        if(board.getCurrentPlayer() == 1)
        {
            if (xWin)
            {
                return 1;
            }
            else if (oWin)
            {
                return 0;
            }
            else if (isDash)
            {
        //todo figure out draw states vs incomplete games
                return 2;
            }
            else
            {
                return 0.5;
            }
        }else{
            if (oWin)
            {

                return 1;
            }
            else if (xWin)
            {

                return 0;
            }
            else if (isDash)
            {
                //todo figure out draw states vs incomplete games
                return 2;
            }
            else
            {
                return 0.5;
            }
        }

    }else{

        return -1;
    }


}

bool isValid(board board)
{
    int xCount = 0;
    int oCount = 0;
    countXO(board, xCount, oCount);
    return (abs(xCount - oCount) <= 1);
}

void countXO(board &board, int &xCount, int &oCount)
{
    std::vector<std::vector<char>> temp;
    temp = board.getBoard();
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(toupper(temp[i][j]) == 'X'){
                        xCount++;
                    }else if(toupper(temp[i][j] == 'O')){
                        oCount++;
                    }
        }
    }
}


bool leaf(board board)
{
    float i = eval(board);
    return i <= 1 && i >= -1;
}

bool xTurnCheck(board board){
    int xCount = 0;
    int oCount = 0;

    countXO(board, xCount,oCount);

    if(xCount > oCount){
        return false;
    }
    return true;
}

std::vector<board> succ(board parentBoard){

        std::vector<board> childrenBoardVector;
    std::vector<std::vector<char>> temp;
    board tempBoard;

   std::cout << parentBoard.getCurrentPlayer() << " IN SUCC ParentBoard CUR PLAYER " << std::endl;
    temp = parentBoard.getBoard();

   for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(toupper(temp[i][j]) == '-'){

                        if (xTurnCheck(parentBoard))
                        {
                            temp[i][j] = 'X';
                        }
                        else
                        {
                            temp[i][j] = 'O';
                        }
                        tempBoard = parentBoard;
                        tempBoard.setBoard(temp);
                    childrenBoardVector.push_back(tempBoard);
                    temp[i][j] = '-';
            }
        }
    }
        return childrenBoardVector;
}


void curPlayer(board &board)
{

    if(xTurnCheck(board)){
        board.setCurrentPlayer(1);
    }
    else{

        board.setCurrentPlayer(0);
    }
}

char curPlayerConvert(board &board)
{
    if(board.getCurrentPlayer() == 1){
        return 'X';
    }else{
        return 'O';
    }

}
