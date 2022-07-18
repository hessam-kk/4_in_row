#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define window_x 1067
#define window_y 600

int x_square(int x)
{
    return 294 + (x * 60);
}
int y_square(int y)
{
    return 80 + (y * 60);
}

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
    window.draw(background_sprite);
    // End Of Adding Background

    // Add Board
    sf::Texture empty_texture;
    if (!empty_texture.loadFromFile("../assets/empty_sq.png"))
        cout << "Error On Loading empty squares Image" << endl;
    // sf::Sprite background_sprite;
    // background_sprite.setTexture(background_texture);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            sf::Sprite empty_sprite;
            empty_sprite.setTexture(empty_texture);
            empty_sprite.setPosition(x_square(i), y_square(j));
            window.draw(empty_sprite);
        }
    }



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