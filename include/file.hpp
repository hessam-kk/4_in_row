#include "datas.hpp" // for enum definition

void Write_Player_Info_To_File(unsigned short int all_moves,
                                enum Color player_1 ,
                                enum Color player_2);

bool Write_Matrix_To_File(enum Color matrix_8_8[8][8]);
bool Read_Matrix_From_File(enum Color matrix_8_8[8][8]);