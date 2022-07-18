#include "board.hpp"
#include "datas.hpp"

bool place_piece(int column, enum Color color)
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
