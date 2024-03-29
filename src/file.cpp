#include<fstream>
#include<iostream>
#include "datas.hpp" // for enum definition


void Write_Player_Info_To_File(unsigned short int all_moves , enum Color player_1 , enum Color player_2)
{
    std::ofstream file;
    file.open("Player.txt" , std::ios::out);


    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "App Will Be Close" << std::endl;
        std::exit(1);
    }
    
    file << "moves : " << all_moves << std::endl;

    file << "player_1 : " << player_1 << std::endl;

    file << "player_2 : " << player_2 << std::endl;

    file.close();
}


bool Write_Matrix_To_File(enum Color matrix_8_8[8][8])
{
    std::ofstream file;
    file.open("Matrix.txt" , std::ios::out);

    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "App Will Be Close" << std::endl;
        return false;
    }

    for (int i = 0 ; i < 8 ; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            file << matrix_8_8[i][j] << " ";
        }
    }
    file.close();
    return true;
}


bool Read_Matrix_From_File(enum Color matrix_8_8[8][8])
{
    std::ifstream file;
    file.open("Matrix.txt" , std::ios::in);

    if (!file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "App Will Be Close" << std::endl;
        return false;
    }

    for (int i = 0 ; i < 8; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            int temp;
            file >> temp;
            matrix_8_8[i][j] = static_cast<Color>(temp);
        }
    }
    return true;
}