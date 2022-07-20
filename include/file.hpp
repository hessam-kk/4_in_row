#include<fstream>
#include<iostream>
#include "datas.hpp" // for enum definition

unsigned short int return_color_number(enum Color color)
{
    switch(color)
    {
        case RED:
            return 0;

        case YELLOW:
            return 1;

        case GREEN:
            return 2;

        case BLUE:
            return 3;

        case EMPTY :
            return 4;
    }

    return 4;
}


void Write_Player_Info_To_File(unsigned short int all_moves , enum Color player_1 , enum Color player_2)
{
    std::ofstream file;
    file.open("Player.txt" , std::ios::out);


    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "Enter Any Key To Exit" << std::endl;
        std::cin.ignore();
        getchar();
    }
    
    file << "moves : " << all_moves << std::endl;

    file << "player_1 : " << return_color_number(player_1) << std::endl;

    file << "player_2 : " << return_color_number(player_2) << std::endl;

    file.close();
}


void Write_Matrix_To_File(enum Color matrix_8_8[8][8])
{
    std::ofstream file;
    file.open("Matrix.txt" , std::ios::out);

    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "Enter Any Key To Exit" << std::endl;
        std::cin.ignore();
        getchar();
    }

    for (int i = 0 ; i < 8 ; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            file << return_color_number(matrix_8_8[i][j]) << " ";
        }

        file << std::endl;
    }
}


void Read_Matrix_From_File(enum Color matrix_8_8[8][8])
{
    std::ifstream file;
    file.open("Matrix.txt" , std::ios::in);

    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "Enter Any Key To Exit" << std::endl;
        std::cin.ignore();
        getchar();
    }

    for (int i = 0 ; i < 8 ; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            int temp;
            file >> temp;
            matrix_8_8[i][j] = (enum Color)temp;
        }
    }
}