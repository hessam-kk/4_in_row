#include "app.hpp"
#include "datas.hpp"
#include "board.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define window_x 1067
#define window_y 600

using namespace std;

Color matrix_8_8[8][8];

void app()
{

    reset_board(matrix_8_8);

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

    // add colored textures
    sf::Texture blue_texture;
    sf::Texture red_texture;
    sf::Texture green_texture;
    sf::Texture yellow_texture;
    sf::Texture empty_texture;
    if (!empty_texture.loadFromFile("../assets/empty_sq.png"))
        cout << "Error On Loading empty squares Image" << endl;
    if (!blue_texture.loadFromFile("../assets/sq_blue.png"))
        cout << "Error On Loading blue squares Image" << endl;
    if (!red_texture.loadFromFile("../assets/sq_red.png"))
        cout << "Error On Loading red squares Image" << endl;
    if (!yellow_texture.loadFromFile("../assets/sq_yellow.png"))
        cout << "Error On Loading yellow squares Image" << endl;
    if (!green_texture.loadFromFile("../assets/sq_green.png"))
        cout << "Error On Loading green squares Image" << endl;

    insert_piece(0, RED, matrix_8_8);
    // initialize the board

    for (int i = 0; i < 8; i++)
    {
        sf::Sprite number_sprite;
        sf::Texture number_texture;
        if (!number_texture.loadFromFile("../assets/row_n/" + to_string((i + 1)) + ".png"))
            cout << "Error On Loading empty squares Image" << endl;

        number_sprite.setTexture(number_texture);
        number_sprite.setPosition(x_square(i), y_square(8));
        window.draw(number_sprite);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            sf::Sprite box_sprite;
            sf::Texture box_texture;

            switch (matrix_8_8[i][j])
            {
            case RED:
                box_texture = red_texture;
                break;
            case YELLOW:
                box_texture = yellow_texture;
                break;
            case GREEN:
                box_texture = green_texture;
                break;
            case BLUE:
                box_texture = blue_texture;
                break;
            case EMPTY:
                box_texture = empty_texture;
                break;
            }

            box_sprite.setTexture(box_texture);
            box_sprite.setPosition(x_square(i), y_square(j));
            window.draw(box_sprite);
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

            if (event.type == sf::Event::TextEntered)
            {
                sf::Sprite input_sprite;
                sf::Texture input_texture;
                string address = string("../assets/sq_") + string("blue") + string(".png");
                if (!input_texture.loadFromFile(address))
                    cout << "Error On Loading colored Image" << endl;

                int inp_ = convert_string_to_int(event.text.unicode);
                cout << "TextEntered -> " << inp_ << endl;

                if (inp_ >=1 && inp_ <= 8)
                {
                    
                    cout << "correct -> " << inp_ << endl;
                    int pos = insert_piece(event.text.unicode - 48, RED, matrix_8_8);
                    input_sprite.setTexture(input_texture);
                    input_sprite.setPosition(x_square(event.text.unicode - 48 - 1), y_square(pos));
                    window.draw(input_sprite);

                }
                
            }
        }

        window.display();
    }
}