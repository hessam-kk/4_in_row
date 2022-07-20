#include "datas.hpp"
#include "board.hpp"

#include <iostream>
#include <string>

int insert_piece(const int column,
                 const enum Color color,
                 enum Color board[8][8])
{
    // wrong column number
    if (column < 0 || column > 7)
    {
        std::cout << "Error on insert: wrong column number" << std::endl;
        return -1;
    }

    // column is full
    if (board[column][0] != EMPTY)
    {
        std::cout << "Error on insert: Column is full" << std::endl;
        return -1;
    }

    for (int i = 7; i >= 0; i--)
    {
        if (board[column][i] == EMPTY)
        {
            std::cout << "insert on " << i << "color " << color << std::endl;
            board[column][i] = color;
            return i;
        }
    }

    std::cout << "Nothing added!!" << std::endl;
    return -1;
}

bool reset_board(enum Color board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
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

bool validation(int pieces[8], const enum Color board[8][8])
{
    /*
        + + + +
        + + + +
        # # # #
        + + + +
    */
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[col][row] != EMPTY &&
                board[col][row] == board[col][row + 1] &&
                board[col][row] == board[col][row + 2] &&
                board[col][row] == board[col][row + 3])
            {
                pieces[0] = col;
                pieces[1] = row;
                pieces[2] = col;
                pieces[3] = row + 1;
                pieces[4] = col;
                pieces[5] = row + 2;
                pieces[6] = col;
                pieces[7] = row + 3;

                return true;
            }
        }
    }

    /*
        + + # +
        + + # +
        + + # +
        + + # +
    */
    for (int col = 0; col < 5; col++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (board[col][row] != EMPTY &&
                board[col][row] == board[col + 1][row] &&
                board[col][row] == board[col + 2][row] &&
                board[col][row] == board[col + 3][row])
            {
                pieces[0] = col;
                pieces[1] = row;
                pieces[2] = col + 1;
                pieces[3] = row;
                pieces[4] = col + 2;
                pieces[5] = row;
                pieces[6] = col + 3;
                pieces[7] = row;
                
                return true;
            }
        }
    }

    /*
        + + + #
        + + # +
        + # + +
        # + + +
    */
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (board[col][row] != EMPTY &&
                board[col][row] == board[col + 1][row + 1] &&
                board[col][row] == board[col + 2][row + 2] &&
                board[col][row] == board[col + 3][row + 3])
            {
                pieces[0] = col;
                pieces[1] = row;
                pieces[2] = col + 1;
                pieces[3] = row + 1;
                pieces[4] = col + 2;
                pieces[5] = row + 2;
                pieces[6] = col + 3;
                pieces[7] = row + 3;                

                return true;
            }
        }
    }
    /*
        # + + +
        + # + +
        + + # +
        + + + #
    */
    for (int row = 0; row < 5; row++)
    {
        for (int col = 4; col < 8; col++)
        {
            if (board[col][row] != EMPTY &&
                board[col][row] == board[col - 1][row + 1] &&
                board[col][row] == board[col - 2][row + 2] &&
                board[col][row] == board[col - 3][row + 3])
            {
                pieces[0] = col;
                pieces[1] = row;
                pieces[2] = col - 1;
                pieces[3] = row + 1;
                pieces[4] = col - 2;
                pieces[5] = row + 2;
                pieces[6] = col - 3;
                pieces[7] = row + 3;

                return true;
            }
        }
    }
    return false;
}