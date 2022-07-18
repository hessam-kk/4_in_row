#include "datas.hpp"
#include "board.hpp"
#include <iostream>
#include <string>
int insert_piece(const int column,
                const enum Color color,
                enum Color board[8][8])
{
    // wrong column number
    if(column < 0 || column > 7){
        std::cout << "Error on insert: wrong column number" << std::endl;
        return -1;
    }
    
    // column is full
    if (board[column][0] != EMPTY){
        std::cout << "Error on insert: Column is full" << std::endl;
        return -1;
    }


    for(int i = 7; i >= 0; i--)
    {
        if(board[column][i] == EMPTY)
        {
            std::cout << "insert on " << i << std::endl;
            board[column][i] = color;
            return i;
        }
    }

    // board[column][0] = color;
    std::cout << "Nothing added!!" << std::endl;
    return -1;
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

int convert_string_to_int(const char str)
{
    int num = 0;
    switch (str)
    {

    case '1':
        num = 1;
        break;
    case '2':
        num = 2;
        break;
    case '3':
        num = 3;
        break;
    case '4':
        num = 4;
        break;
    case '5':
        num = 5;
        break;
    case '6':
        num = 6;
        break;
    case '7':
        num = 7;
        break;
    case '8':
        num = 8;
        break;
    default:
        num = -1;
        break;
    }
    return num;
}