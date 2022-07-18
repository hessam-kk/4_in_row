#pragma once
#include "datas.hpp"

int insert_piece(const int column, const enum Color color, enum Color board[8][8]);
bool reset_board(enum Color board[8][8]);
int x_square(const int x);
int y_square(const int y);
int convert_string_to_int(const char str);