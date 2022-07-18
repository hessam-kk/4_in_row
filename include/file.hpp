#include<fstream>
#include<iostream>

enum Color 
{
    RED ,
    YELLOW ,
    GREEN ,
    BLUE ,
    EMPTY
};

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


void Write_To_File(unsigned short int all_moves , enum Color player_1 , enum Color player_2)
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