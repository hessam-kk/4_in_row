#include "login.hpp"
#include "board.hpp"
#include <iostream>

using namespace std;

int login(const int user)
{
    cout << "login for user: " << user << endl;
    cout << "insert yout color number" << endl;
    cout << "Red: 0    |   Yellow: 1    |   Green: 2    |   Blue: 3" << endl;
    cout << ">>> ";
    int choice = -1;
    cin >> choice;
    while (choice < 0 || choice > 3)
    {
        cout << "wrong choice! Try again" << endl;
        cout << ">>> ";
        cin >> choice;
    }
    cout << "[+] - you chose: " << choice << endl;
    return choice;
}
