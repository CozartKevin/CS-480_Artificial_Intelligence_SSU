//
// Created by Raggdoll on 3/7/2020.
//

#include "board.hpp"
#include <iostream>
#include <fstream>
#include <string>


board::board(std::vector< std::vector<char> > userInputVector)
{
    boardVec.swap(userInputVector);

}

board::board()
{

}

void board::getBoardfromUser()
{
    std::ifstream inputStream;
do{
    std::string boardFileName;
    std::cout << "Enter name of text file containing a 4 x 4 board." << std::endl;
    std::getline(std::cin,boardFileName);

    inputStream.open(boardFileName, std::ios::in);    // open for reading
    if( ! inputStream.is_open())
    {
        std::cout << "Unable to open " << boardFileName << ". " << std::endl;

    }
}while(! inputStream.is_open());

        std::string temp;
    for(int i = 0; i < 4; i++){
       std::getline(inputStream,temp);
        for(int j = 0; j < 4; j++)
        {

                switch (toupper(temp[j]))
                {

                    case '-':
                        break;
                    case 'X':
                        this->boardVec[i][j] = 'X';
                        break;
                    case 'O':
                        this->boardVec[i][j] = 'O';
                        break;
                    default:
                        std::cout << " Unexpected error in Boardgame file please fix and rerun program" << std::endl;
                        exit(-1);
                }

        }
    }
    inputStream.close();
}

void board::printBoard()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << this->boardVec[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void board::setDepthOfK()
{
    int kDepth;
    std::cout << "Enter a depth for the search" << std::endl;
      while(!(std::cin >> kDepth) || kDepth <= 0)
      {
              std::cout << "Invalid input please enter a number from 1 - n" << std::endl;
              std::cout << "Enter a depth for the search" << std::endl;
              std::cin.clear();
              std::cin.ignore();
      }
    depthOfK = kDepth;
}

void board::setBoard(board board)
{
    this->boardVec.swap(board.boardVec);

}


