#include<fstream>
#include<iostream>
#include"player.hpp"


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

    file << "second player : " << second->player_number << " ";

    file.close();
}