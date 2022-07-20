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

    bool is_game_over = false;
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
            if (!is_game_over)
            {
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
                        int pos = insert_piece(input_column,
                                               static_cast<Color>(players_turn ? first_player : second_player),
                                               matrix_8_8);
                        // insert on a full row
                        if (pos == -1)
                        {
                            cout << "row is full" << endl;
                            // window.close();
                            // break;
                        }
                        // successfully inserted piece
                        else
                        {
                            input_sprite.setTexture(input_texture);
                            input_sprite.setPosition(x_square(input_column), y_square(pos));
                            window.draw(input_sprite);
                            players_turn = !players_turn;
                        }
                    }
                }

                int matched_pieces[8];
                if (validation(matched_pieces, matrix_8_8))
                {
                    players_turn = !players_turn; // to save the winner
                    cout << "game is over" << endl;
                    cout << "winner is: " << (first_player == matched_pieces[0] ? first_player : second_player)
                         << endl;
                    is_game_over = true;


                    sf::Sprite game_over_sprite;
                    sf::Texture game_over_texture;
                    string address = string("../assets/sqw_") + (players_turn ? to_string(first_player) : to_string(second_player)) + string(".png");
                    if (!game_over_texture.loadFromFile(address))
                        cout << "Error On Loading game_over Image" << endl;
                    game_over_sprite.setTexture(game_over_texture);
                    // for (int i = 0; i < 8; i++)
                    {
                        game_over_sprite.setPosition(x_square(matched_pieces[0]),
                                                     y_square(matched_pieces[1]));
                        window.draw(game_over_sprite);
                        game_over_sprite.setPosition(x_square(matched_pieces[2]),
                                                     y_square(matched_pieces[3]));
                        window.draw(game_over_sprite);
                        game_over_sprite.setPosition(x_square(matched_pieces[4]),
                                                     y_square(matched_pieces[5]));
                        window.draw(game_over_sprite);
                        game_over_sprite.setPosition(x_square(matched_pieces[6]),
                                                     y_square(matched_pieces[7]));
                        window.draw(game_over_sprite);
                    }

                    // for (int i = 0; i < 8; i++)
                    // {
                    //     cout << matched_pieces[i] << ' ' << matched_pieces[++i] << " ";
                    // }
                    // cout << "\n1: " << matrix_8_8[matched_pieces[0]][matched_pieces[1]] << endl;
                    // cout << "2: " << matrix_8_8[matched_pieces[2]][matched_pieces[3]] << endl;
                    // cout << "3: " << matrix_8_8[matched_pieces[4]][matched_pieces[5]] << endl;
                    // cout << "4: " << matrix_8_8[matched_pieces[6]][matched_pieces[7]] << endl;
                    // for (int i = 0; i < 8; i++)
                    // {
                    //     for (int j = 0; j < 8; j++)
                    //     {
                    //         cout << matrix_8_8[i][j] << ' ';
                    //     }
                    //     cout << endl;
                    // }
                    // sleep(10);
                    // window.close();
                    // break;
                }
            }
        }

        window.display();
    }
}