#include <iostream>
#include "Tile.h"


// Initializing properties topleft, bottomright, center, column & row. & set Rectangle properties
Tile::Tile(sf::Vector2f tl, sf::Vector2f br, std::vector<std::vector<Tile>> *p, int r, int c): topLeft{tl}, bottomRight{br}, 
center{tl.x+(br.x-tl.x/2), tl.y+(br.y-tl.y/2)}, row{r}, column{c}, parent{p}, on{false} {

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
		setOutlineColor(sf::Color(0,0,0));
	}
	else{
		outlineOn = true;
		setOutlineColor(sf::Color(250, 150, 100));
	}
}

// Returns if tile is alive or dead
bool Tile::enabled(){
	return on;
}

bool Tile::contains(sf::Vector2f point){
	if(
		(point.x < bottomRight.x && topLeft.x > point.x ) && 
		(point.y > topLeft.y && bottomRight.y < point.y)) {
		return true;
	}
	return false;
}
// Looks around and performs logic
void Tile::check(){
	
	neighbors = around().size();
}

void Tile::execute(){

	switch(neighbors){
		// Survival || Birth
		
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
		case 1:
			if(on)
				kill();
			break;
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


std::vector<Tile> Tile::around(){
	std::vector<Tile> v;
	if(top().enabled())
		v.push_back(top());

	if(left().enabled())
		v.push_back(left());

	if(right().enabled())
		v.push_back(right());

	if(down().enabled())
		v.push_back(down());
	if(tl().enabled())
		v.push_back(top());

	if(tr().enabled())
		v.push_back(left());

	if(bl().enabled())
		v.push_back(right());

	if(br().enabled())
		v.push_back(down());

	return v;
}

void Tile::birth(){
	on = true;
	setFillColor(sf::Color(150, 50, 250));
}
void Tile::kill(){
	on = false;
	setFillColor(sf::Color(0, 0, 0));
}


