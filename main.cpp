#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tile.h"

using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//sf::Vector2f, sf::Vector2f, std::vector<std::vector<Tile>>, int, int
	std::vector<std::vector<Tile>> tiles;

    // Rows
	for(int i = 1; i<1016; i+=15){
		std::vector<Tile> row;
    	// Columns
		for(int ii = 1; ii<1916; ii+=15){
    		row.push_back(Tile(Vector2f(ii,i), Vector2f(ii+15,i+15),&tiles,tiles.size(),row.size()));
 
    	}
    	tiles.push_back(row);
    }

    

    while (window.isOpen())
    {
    	sf::Clock clock; // starts the clock
    	Event event;

    	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    	{
    		tiles[(sf::Mouse::getPosition().y-45)/15][(sf::Mouse::getPosition().x)/15].birth();
    	}
    	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    	{
    		tiles[(sf::Mouse::getPosition().y-45)/15][(sf::Mouse::getPosition().x)/15].kill();
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {	
    		// ToDo: set delay

    		for(int i = 0; i<tiles.size(); i+=1)
    			for(int ii = 0; ii<tiles.at(i).size(); ii+=1)
    				tiles[i][ii].toggleOutline();

    			
    		
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {	
    		// Start game of life
    		// play forever until there are no more tiles
    		for(;;){
    			int tilesEnabled = 0;
    			sf::Clock clock; // starts the clock
    			for(int i = 0; i<tiles.size(); i++){
	    			for(int ii = 0; ii<tiles.at(i).size(); ii++){
	    				tiles[i][ii].check();
	    				if(tiles[i][ii].enabled())
	    					tilesEnabled++;

	    				

	    			}
    			}
    			for(int i = 0; i<tiles.size(); i++){
	    			for(int ii = 0; ii<tiles.at(i).size(); ii++){
	    				tiles[i][ii].execute();
	    				window.draw(tiles[i][ii]);

	    			}
    			}
    			if(tilesEnabled == 0)
    				break;
    			
    			while(clock.getElapsedTime().asMilliseconds() <= 500){
    				// Wait half a second
    			}
    			clock.restart();

    			window.display();
    		}
    		
	    	
	    }

    	while (window.pollEvent(event))
    	{
    		if (event.type == sf::Event::Closed)
    			window.close();
    	}


    	for(const auto row : tiles)
    		for(const auto tile : row)
    			window.draw(tile);



    		window.display();
    	}

    	return 0;
    }