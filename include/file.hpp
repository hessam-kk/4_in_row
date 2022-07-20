#include "datas.hpp" // for enum definition

unsigned short int return_color_number(enum Color color);
void Write_Player_Info_To_File(unsigned short int all_moves,
                                enum Color player_1 ,
                                enum Color player_2);

void Write_Matrix_To_File(enum Color matrix_8_8[8][8]);
void Read_Matrix_From_File(enum Color matrix_8_8[8][8]);