#pragma once

bool insert_piece(const int column, const enum Color color, enum Color board[8][8]);
bool reset_board(enum Color board[8][8]);
int x_square(const int x);
int y_square(const int y);
