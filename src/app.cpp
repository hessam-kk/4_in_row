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
#define _DEBUG true
#define _TEST false

using namespace std;

Color matrix_8_8[8][8];

void app()
{
    // true: realtime,
    // false: from file
    bool is_game_over = false;

    // Login users
    if (!_TEST)
    {
        bool is_game_type_realtime = game_type();
        int first_player = login(1);
        int second_player = login(2);
        while (first_player == second_player)
        {
            cout << "[!] - you can't choose the same color" << endl;
            second_player = login(2);
        }
    }
    else
    {
        bool is_game_type_realtime = true;
        int first_player = 1;
        int second_player = 2;
    }

    if (_DEBUG)
    {
        cout << "first_player: " << first_player << endl;
        cout << "second_player: " << second_player << endl;
        cout << "is_game_type_realtime: " << is_game_type_realtime << endl;
    }
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
    // end of add row numbers

    if (_DEBUG)
        cout << "game type: " << game_type << endl;

    // realtime game
    if (is_game_type_realtime)
    {
        reset_board(matrix_8_8);
    }
    // load from file
    else
    {
        if (_DEBUG)
            cout << "loading from file" << endl;

        // failure on loading data from file
        if (!Read_Matrix_From_File(matrix_8_8))
        {
            cout << "Error On Loading Matrix From File" << endl;
            cout << "switching to the realtime mode!" << endl;
            is_game_type_realtime = true;
        }
        // success on loading data from file
        else
        {
            cout << "Matrix loaded from file" << endl;
            is_game_over = true; // To avoid getting input from user
        }
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
    if (_DEBUG)
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
                if (_DEBUG)
                    cout << "closing window" << endl;
                window.close();
                break;
            }

            if (!is_game_over)
            {
                if (event.type == sf::Event::TextEntered)
                {
                    sf::Sprite input_sprite;
                    sf::Texture input_texture;

                    string address =
                        string("../assets/sq_") +
                        (players_turn ? to_string(first_player) : to_string(second_player)) +
                        string(".png");

                    if (!input_texture.loadFromFile(address))
                        cout << "Error On Loading colored Image" << endl;

                    int input_column = convert_string_to_int(event.text.unicode) - 1;
                    if (_DEBUG)
                        cout << "Text Entered -> " << input_column << endl;

                    if (input_column != -1 &&
                        input_column >= 0 &&
                        input_column <= 7)
                    {
                        int pos =
                            insert_piece(input_column,
                                         static_cast<Color>(players_turn ? first_player : second_player),
                                         matrix_8_8);

                        // insert on a full row
                        if (pos == -1)
                        {
                            if (_DEBUG)
                                cout << "row is full: " << input_column << endl;
                        }
                        // insert on an empty row
                        else
                        {
                            input_sprite.setTexture(input_texture);
                            input_sprite.setPosition(x_square(input_column),
                                                     y_square(pos));
                            window.draw(input_sprite);
                            players_turn = !players_turn; // change turn
                        }
                    }
                }

                /* GUIDE for matched pieces data structure formatting::
                    matched_pieces = {A, B, C, D, E, F, G, H}
                    Piece number 1: x = A, y = B
                    Piece number 2: x = C, y = D
                    Piece number 3: x = E, y = F
                    Piece number 4: x = G, y = H

                    in other words:
                    matched_pieces ===> {(x1, y1), (x2, y2), (x3, y3), (x4, y4)}
                */
                int matched_pieces[8] = {0, 0, 0, 0, 0, 0, 0, 0};

                if (validation(matched_pieces, matrix_8_8))
                {
                    if (_DEBUG)
                        cout << "game is over" << endl;

                    is_game_over = true;
                    players_turn = !players_turn; // to save the winner

                    cout << "winner is: " << (first_player == matched_pieces[0] ? first_player : second_player)
                         << endl;

                    sf::Sprite game_over_sprite;
                    sf::Texture game_over_texture;
                    string address =
                        string("../assets/sqw_") +
                        (players_turn ? to_string(first_player) : to_string(second_player)) +
                        string(".png");

                    if (!game_over_texture.loadFromFile(address))
                        cout << "Error On Loading game_over Image" << endl;
                    game_over_sprite.setTexture(game_over_texture);

                    // change matched pieces to the winner color
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

                    if (Write_Matrix_To_File(matrix_8_8))
                        cout << "Matrix saved to file" << endl;
                    else
                        cout << "Error On Saving Matrix to file" << endl;

                    if (_DEBUG)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            cout << matched_pieces[i] << ' ' << matched_pieces[++i] << " ";
                        }
                        cout << "\n1: " << matrix_8_8[matched_pieces[0]][matched_pieces[1]] << endl;
                        cout << "2: " << matrix_8_8[matched_pieces[2]][matched_pieces[3]] << endl;
                        cout << "3: " << matrix_8_8[matched_pieces[4]][matched_pieces[5]] << endl;
                        cout << "4: " << matrix_8_8[matched_pieces[6]][matched_pieces[7]] << endl;
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                cout << matrix_8_8[i][j] << ' ';
                            }
                            cout << endl;
                        }
                        sleep(10);
                        window.close();
                        break;
                    }
                }
            }
        }

        window.display();
    }
}