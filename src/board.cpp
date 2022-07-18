#include "datas.hpp"
#include "board.hpp"
#include <iostream>

bool insert_piece(const int column,
                const enum Color color,
                enum Color board[8][8])
{
    // wrong column number
    if(column < 0 || column > 7){
        std::cout << "Error on insert: wrong column number" << std::endl;
        return false;
    }
    
    // column is full
    if (board[column][0] != EMPTY){
        std::cout << "Error on insert: Column is full" << std::endl;
        return false;
    }


    for(int i = 7; i >= 0; i--)
    {
        if(board[column][i] == EMPTY)
        {
            std::cout << "insert on " << i << std::endl;
            board[column][i] = color;
            return true;
        }
    }
    board[column][0] = color;
    std::cout << "Nothing added!!" << std::endl;
    return false;
}


bool reset_board(enum Color board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = EMPTY;
        }
    }
    return true;
}


int x_square(const int x)
{
    return 294 + (x * 60);
}


int y_square(const int y)
{
    return 40 + (y * 60);
}