#include "app.hpp"
#include "datas.hpp"
#include "board.hpp"
#include "login.hpp"
#include "file.hpp"

#include <unistd.h>
#include <limits>
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
    // true: realtime,
    // false: from file 
    bool is_game_type_realtime = game_type();

    // Login users
    int first_player = login(1);
    int second_player = login(2);

    while (first_player == second_player)
    {
        cout << "[!] - you can't choose the same color" << endl;
        second_player = login(2);
    }

    // For test
    // int first_player = 1;
    // int second_player = 0;

    cout << "first player: " << first_player << endl;
    cout << "second player: " << second_player << endl;
    // end of login users

    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "4 in row game", sf::Style::Close);
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
    if (!blue_texture.loadFromFile("../assets/sq_3.png"))
        cout << "Error On Loading blue squares Image" << endl;
    if (!red_texture.loadFromFile("../assets/sq_0.png"))
        cout << "Error On Loading red squares Image" << endl;
    if (!yellow_texture.loadFromFile("../assets/sq_1.png"))
        cout << "Error On Loading yellow squares Image" << endl;
    if (!green_texture.loadFromFile("../assets/sq_2.png"))
        cout << "Error On Loading green squares Image" << endl;

    // add row numbers
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

    cout << "game type: " << game_type << endl;
    // realtime game
    if (is_game_type_realtime)
    {
        reset_board(matrix_8_8);
    }
    // load from file
    else
    {
        cout << "loading from file comming soon" << endl;
        // Read_Matrix_From_File(matrix_8_8);
    }

    // adding squares to the window
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


    // True: first player,
    // False: second player
    bool players_turn = true;
    cout << "starting interface" << endl;

    // main loop
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
                string address = string("../assets/sq_") + (players_turn ? to_string(first_player) : to_string(second_player)) + string(".png");
                if (!input_texture.loadFromFile(address))
                    cout << "Error On Loading colored Image" << endl;

                int input_column = convert_string_to_int(event.text.unicode) - 1;
                cout << "TextEntered -> " << input_column << endl;

                if (input_column != -1 && input_column >= 0 && input_column <= 7)
                {
                    int pos = insert_piece(input_column, RED, matrix_8_8);
                    // sleep(2);
                    // insert on a full row
                    if (pos == -1)
                    {
                        cout << "row is full" << endl;
                        window.close();
                        break;
                    }
                    // successfully inserted piece
                    else
                    {
                        cout << "running here" << endl;
                        input_sprite.setTexture(input_texture);
                        input_sprite.setPosition(x_square(input_column), y_square(pos));
                        window.draw(input_sprite);
                        players_turn = !players_turn;
                    }
                }
            }

            int valid_piece[8];
            if (validation(valid_piece, matrix_8_8))
            {
                cout << "game is over" << endl;
                cout << "winner is: " << (first_player == valid_piece[0] ? first_player : second_player) << endl;
                for (int i = 0; i < 8; i++)
                {
                    cout << valid_piece[i] << ' ' << valid_piece[++i] << " ";
                }
                sleep(10);
                window.close();
                break;
            }
        }

        window.display();
    }
}