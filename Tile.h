#include <SFML/Graphics.hpp>
#include <vector>
struct Point{
	int x;
	int y;
};

class Tile : public sf::RectangleShape {
public:

	
	Tile(sf::Vector2f, sf::Vector2f, std::vector<std::vector<Tile>>*, int, int);

	// Returns if tile is alive or dead
	bool enabled();

	bool contains(sf::Vector2f);

	// Looks around and performs logic
	void check();
	void execute();
	
	void toggleOutline();
	// Return tiles around this tile
	Tile left();
	Tile right();
	Tile top();
	Tile down();

	Tile tl();
	Tile tr();
	Tile bl();
	Tile br();
	std::vector<Tile> around();

	void birth();
	void kill();


private:
	Tile();
	int neighbors;
	bool outlineOn;
	sf::Vector2f topLeft;
	sf::Vector2f bottomRight;
	sf::Vector2f center;
	bool on;
	int column;
	int row;
	std::vector<std::vector<Tile>> *parent;

};