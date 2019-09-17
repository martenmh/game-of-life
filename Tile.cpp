#include <iostream>
#include "Tile.h"
#include <stdlib.h>
#include <cmath>

// Initializing properties topleft, bottomright, center, column & row. & set Rectangle properties
Tile::Tile(sf::Vector2f tl, sf::Vector2f br, std::vector<std::vector<Tile>> *p, int r, int c): topLeft{tl}, bottomRight{br}, 
center{tl.x+(br.x-tl.x/2), tl.y+(br.y-tl.y/2)}, row{r}, column{c}, parent{p}, on{false}{
	enabledColor = sf::Color(150, 150, 250);
	disabledColor = sf::Color(0, 0, 0);
	enabledGridColor = sf::Color(250, 150, 100);
	disabledGridColor = sf::Color(0, 0, 0);

	setPosition(tl.x, tl.y);
	setSize(sf::Vector2f(br.x-tl.x, br.y-tl.y));

	setFillColor(sf::Color(0, 0, 0));
	setOutlineThickness(1);
	setOutlineColor(sf::Color(250, 150, 100));

}

Tile::Tile(): on{false}, column{0}, row{0}{

}

void Tile::toggleOutline(){
	if(outlineOn){
		outlineOn = false;
		setOutlineColor(disabledGridColor);
	}
	else{
		outlineOn = true;
		setOutlineColor(enabledGridColor);
	}
}

// Returns if tile is alive or dead
bool Tile::enabled(){
	return on;
}

void Tile::check(){
	
	neighbors = around().size();
}

void Tile::execute(){


	switch(neighbors){
		// enabled() ? Survival : Birth
		case 3:
			if(!on)
				birth();
			break;
		// Survival
		case 2:
			break;
		// Death by overcrowding
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			if(on)
				kill();
			break;
		// Death by isolation
		case 1:
		case 0:
			if(on)
				kill();
			break;
		
	}


}

// Return tiles around this tile
Tile Tile::left(){
	
	
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row).at(column-1);
	
	// Return empty tile wich is disabled
	return Tile();
}
Tile Tile::right(){
	

	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row).at(column+1);

	return Tile();
}
Tile Tile::top(){
	
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row-1).at(column);

	return Tile();
}
Tile Tile::down(){
	
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row+1).at(column);

	return Tile();
}

Tile Tile::tl(){
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row-1).at(column-1);

	return Tile();
}
Tile Tile::tr(){
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row-1).at(column+1);
	return Tile();
}
Tile Tile::bl(){
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row+1).at(column-1);
	return Tile();
}
Tile Tile::br(){
	if(column > 0 && column < parent->at(row).size()-1 && row > 0 && row < parent->size()-1)
		return parent->at(row+1).at(column+1);
	return Tile();
}


std::vector<Tile*> Tile::around(){
	std::vector<Tile*> v;
	if(top().enabled())
		v.push_back(&parent->at(row).at(column-1));

	if(left().enabled())
		v.push_back(&parent->at(row).at(column+1));

	if(right().enabled())
		v.push_back(&parent->at(row-1).at(column));

	if(down().enabled())
		v.push_back(&parent->at(row+1).at(column));
	if(tl().enabled())
		v.push_back(&parent->at(row-1).at(column-1));

	if(tr().enabled())
		v.push_back(&parent->at(row-1).at(column+1));

	if(bl().enabled())
		v.push_back(&parent->at(row+1).at(column-1));

	if(br().enabled())
		v.push_back(&parent->at(row+1).at(column+1));

	return v;
}


void Tile::birth(){
	on = true;
	setFillColor(enabledColor);
}
void Tile::kill(){
	on = false;
	setFillColor(disabledColor);
}


void Tile::setEnabledColor(sf::Color c){
	enabledColor = c;
}
void Tile::setEnabledOutlineColor(sf::Color c){

	enabledGridColor = c;

}

void Tile::setDisabledColor(sf::Color c){
	disabledColor = c;
	disabledGridColor = c;
}

void Tile::setColor(sf::Color enabled, sf::Color enabledGrid, sf::Color disabled){
	enabledGridColor = enabledGrid;
	enabledColor = enabled;
	disabledColor = disabled;
	disabledGridColor = disabled;
}