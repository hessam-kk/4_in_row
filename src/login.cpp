#include "login.hpp"
#include "board.hpp"

#include <limits>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define login_x 560
#define login_y 600

using namespace std;

int login1(int user)
{
    sf::RenderWindow window(sf::VideoMode(login_x, login_y), "login user 1", sf::Style::Close);

    // Add Background
    sf::Texture background_texture;
    if (!background_texture.loadFromFile(string("../assets/login") + to_string(user) + string(".jpg")))
        cout << "Error On Loading login " << user << "Image" << endl;
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    window.draw(background_sprite);
    // End Of Adding Background

    window.display();
    // int login1_int = 1000;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close Window
            if (event.type == sf::Event::EventType::Closed)
            {
                return -1;
                window.close();
                break;
            }

            if (event.type == sf::Event::TextEntered)
            {
                int login1_int = convert_string_to_int(event.text.unicode);
                cout << "login1 entered -> " << login1_int << endl;

                if (login1_int >= 1 && login1_int <= 4)
                {
                    // window.close();
                    // cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    cout << "returning " << login1_int << endl;
                    return login1_int;
                }
                else
                {
                    cout << "wrong input" << endl;
                }
            }
        }
    }

    return -1;
}
