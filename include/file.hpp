#include<fstream>
#include<iostream>


void Write_To_File(unsigned short int moves)
{
    std::ofstream file;
    file.open("Inf.txt" , std::ios::app);


    if (! file)
    {
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "Enter Any Key To Exit" << std::endl;
        std::cin.ignore();
        getchar();
    }
    
    file << "moves : " << moves << std::endl;
    file.close();
}