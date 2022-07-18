#include "app.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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


    sf::Sprite colored_sprite;
    sf::Texture blue_texture;
    sf::Texture red_texture;
    sf::Texture green_texture;
    sf::Texture yellow_texture;

    if (!blue_texture.loadFromFile("../assets/sq_blue.png"))
        cout << "Error On Loading blue squares Image" << endl;
    if (!red_texture.loadFromFile("../assets/sq_red.png"))
        cout << "Error On Loading red squares Image" << endl;
    if (!yellow_texture.loadFromFile("../assets/sq_yellow.png"))
        cout << "Error On Loading yellow squares Image" << endl;
    if (!green_texture.loadFromFile("../assets/sq_green.png"))
        cout << "Error On Loading green squares Image" << endl;

    colored_sprite.setTexture(green_texture);
    colored_sprite.setPosition(x_square(0), y_square(0));
    window.draw(colored_sprite);
    colored_sprite.setTexture(blue_texture);
    colored_sprite.setPosition(x_square(5), y_square(2));
    window.draw(colored_sprite);
    colored_sprite.setTexture(red_texture);
    colored_sprite.setPosition(x_square(3), y_square(6));
    window.draw(colored_sprite);
    colored_sprite.setTexture(yellow_texture);
    colored_sprite.setPosition(x_square(7), y_square(7));
    window.draw(colored_sprite);

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