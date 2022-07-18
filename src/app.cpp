#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define window_x 800
#define window_y 800

using namespace std;

void app()
{
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "4 in row game", sf::Style::Close); // size:  (9  in  16)  * 60
    window.requestFocus();
    // Add Background
    sf::Texture background_texture;
    if (!background_texture.loadFromFile("../assets/background (Custom).jpg"))
        cout << "Error On Loading BackGround Image" << endl;
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    // End Of Adding Background
    window.draw(background_sprite);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close Window
            if (event.type == sf::Event::EventType::Closed)
            {
                window.close();
                break;
            }
        }
        window.display();
    }
}