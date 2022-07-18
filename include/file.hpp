#include<fstream>
#include<iostream>
#include"player.hpp"

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
    }
}


void Write_To_File(unsigned short int all_moves ,const struct Player * first ,
                                                 const struct Player * second)
{
    std::ofstream file;
    file.open("Inf.txt" , std::ios::out);


    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "Enter Any Key To Exit" << std::endl;
        std::cin.ignore();
        getchar();
    }
    
    file << "moves : " << all_moves << std::endl;
    file << "first player : " << first->player_number << " ";
    file << return_color_number(first->color) << std::endl;


    file << "second player : " << second->player_number << " ";
    file << return_color_number(second->color) << std::endl;

    file.close();
}