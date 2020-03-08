#include <iostream>
#include <string>
#include "board.hpp"
#include <math.h>
#include <limits>

float MinMax(board board);

bool leaf(board board);

float eval(board board);

bool isValid(board board);

void countXO(board &board, int &xCount, int &oCount);

void MinMaxAlphaBeta(board board);

bool max_Node(board board);

std::vector<board> succ(board baord);

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
    float test = 0.00;
switch(userChoice){
    case 1:
        gameBoard.getBoardfromUser();
        gameBoard.printBoard();
         test = MinMax(gameBoard);
        std::cout << test  << " result" << std::endl;
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



float MinMax(board pos)
{


  //  std::cout << eval(pos) << std::endl;
    if(leaf(pos)){

        return eval(pos);
    }

if(max_Node(pos)){
    pos.setVal(-inf);
}else pos.setVal(inf);

//std::cout <<  " POOP " << std::endl;

std::vector<board> children =  succ(pos);
for(int i = 0; i < children.size(); i++){
        if (max_Node(pos))
        {
            pos.setVal(fmax(pos.getVal(), MinMax(children[i])));
        }
        else
        {
            pos.setVal(fmin(pos.getVal(), MinMax(children[i])));
        }
    }

return pos.getVal();

}

bool max_Node(board board)
{
    int xCount = 0;
    int oCount = 0;
    countXO(board, xCount, oCount);

    if(xCount > oCount){
        return false;
    }
    return true;
}

void MinMaxAlphaBeta(board board)
{

}



float eval(board board)
{
    if(isValid(board)){
        int xCount = 0;
        int oCount = 0;
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
           // std::cout << rowX[k] << " row x " << colX[k] << " col x " << std::endl;
         //   std::cout << rowO[k] << " row O " << colO[k] << " col O " << std::endl;
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

        if(xWin){
            std::cout << " Winnner winner chicken dinner FOR X " << std::endl;
            board.printBoard();
            return 1;
        }else if(oWin){
            std::cout << " Winnner winner chicken  FOR O" << std::endl;
            board.printBoard();
            return 0;
        }else if(isDash){
//todo figure out draw states vs incomplete games
            return 2;
        }else{
            //std::cout << "Its a Tie, WE SUCK!" << std::endl;
           // board.printBoard();
            return 0.5;
        }

    }else{
       // std::cout << " Not Valid" << std::endl;
        return -1;
    }
    //Tells us who wins by returning 1, 0.5, 0 or -1 (if invalid)

}

bool isValid(board board)
{
// verify number of moves is equal or no more than +1 from the other player.
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

std::vector<board> succ(board parentBoard){

        std::vector<board> childrenBoardVector;
    std::vector<std::vector<char>> temp;
    temp = parentBoard.getBoard();

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(toupper(temp[i][j]) == '-'){
                if(max_Node(temp)){
                    temp[i][j] = 'X';
                }else{
                    temp[i][j] = 'O';
                }
                childrenBoardVector.push_back(temp);
                temp[i][j] = '-';
            }
        }
    }

        return childrenBoardVector;
}