#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/tile.h"

using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    std::vector<std::vector<tile>> tiles;

    // Rows
    for (int i = 1; i < 1016; i += 15) {
        std::vector<tile> row;
        // Columns
        for (int ii = 1; ii < 1916; ii += 15)
            row.emplace_back(Vector2f(ii, i), Vector2f(ii + 15, i + 15), &tiles, tiles.size(), row.size());

        tiles.push_back(row);
    }

    while (window.isOpen()) {

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                tiles[(sf::Mouse::getPosition().y - 45) / 15][(sf::Mouse::getPosition().x) / 15].birth();
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                tiles[(sf::Mouse::getPosition().y - 45) / 15][(sf::Mouse::getPosition().x) / 15].kill();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                sf::Clock clock2; // starts the clock

                for (int i = 0; i < tiles.size(); i += 1) {
                    for (int ii = 0; ii < tiles.at(i).size(); ii += 1) {
                        tiles[i][ii].toggleOutline();
                        window.draw(tiles[i][ii]);
                    }
                }
                window.display();
                while (clock2.getElapsedTime().asMilliseconds() <= 200) {
                    // Wait half a second
                }
                clock2.restart();

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

                // Start game of life
                // play for 50 generations
                for (int gen = 0; gen < 50; ++gen) {
                    int tilesEnabled = 0;
                    sf::Clock clock; // starts the clock

                    // First count all enabled neighbors so all rules can be applied "simultaneously"
                    for (int i = 0; i < tiles.size(); i++) {
                        for (int ii = 0; ii < tiles.at(i).size(); ii++) {
                            tiles[i][ii].check();

                            if (tiles[i][ii].enabled())
                                tilesEnabled++;

                        }
                    }

                    // Then execute the rules and draw the new generation
                    for (int i = 0; i < tiles.size(); i++) {
                        for (int ii = 0; ii < tiles.at(i).size(); ii++) {
                            tiles[i][ii].execute();
                            window.draw(tiles[i][ii]);

                        }
                    }

                    while (clock.getElapsedTime().asMilliseconds() <= 500) {
                        // Wait for half a second
                    }

                    clock.restart();

                    // Finally display the new generation
                    window.display();

                    // Break out of loop if all tiles are killed
                    if (tilesEnabled == 0)
                        break;
                }

            } else {
                // Loop trough the tiles and set color
                for (int i = 0; i < tiles.size(); i++) {
                    for (int ii = 0; ii < tiles.at(i).size(); ii++) {
                        switch (event.key.code) {
                            case sf::Keyboard::Num1:
                                tiles.at(i).at(ii).setColor(sf::Color(150, 150, 250), sf::Color(250, 150, 100),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num2:
                                tiles.at(i).at(ii).setColor(sf::Color(250, 150, 250), sf::Color(50, 150, 50),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num3:
                                tiles.at(i).at(ii).setColor(sf::Color(45, 250, 230), sf::Color(30, 250, 160),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num4:
                                tiles.at(i).at(ii).setColor(sf::Color(10, 150, 20), sf::Color(20, 10, 10),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num5:
                                tiles.at(i).at(ii).setColor(sf::Color(150, 150, 250), sf::Color(250, 150, 100),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num6:
                                tiles.at(i).at(ii).setColor(sf::Color(10, 10, 250), sf::Color(250, 10, 100),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num7:
                                tiles.at(i).at(ii).setColor(sf::Color(50, 10, 50), sf::Color(25, 50, 1),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num8:
                                tiles.at(i).at(ii).setColor(sf::Color(120, 30, 90), sf::Color(250, 150, 100),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num9:
                                tiles.at(i).at(ii).setColor(sf::Color(10, 240, 250), sf::Color(50, 20, 160),
                                                            sf::Color(0, 0, 0));
                                break;
                            case sf::Keyboard::Num0:
                                tiles.at(i).at(ii).setColor(sf::Color(239, 15, 50), sf::Color(250, 1, 200),
                                                            sf::Color(0, 0, 0));
                                break;
                            default:
                                break;

                        }
                    }
                }
            }
        }


        for (const auto row : tiles)
            for (const auto tile : row)
                window.draw(tile);


        window.display();
    }

    return 0;
}