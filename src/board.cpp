#include "board.hpp"
#include "datas.hpp"

bool insert_piece(const int column,
                const enum Color color,
                enum Color board[8][8])
{
    // wrong column number
    if(column < 0 || column > 7)
        return false;
    
    // column is full
    if (board[column][7] != EMPTY)
        return false;


    for(int i = 7; i >= 0; i--)
    {
        if(board[column][i] != EMPTY)
        {
            board[column][i+1] = color;
            return true;
        }
    }
    return false;
}

int x_square(const int x)
{
    return 294 + (x * 60);
}

int y_square(const int y)
{
    return 80 + (y * 60);
}