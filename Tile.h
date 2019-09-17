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



	// Looks around and performs logic
	void check();
	void execute();

	void toggleOutline();
	
	Tile left();
	Tile right();
	Tile top();
	Tile down();
	Tile tl();
	Tile tr();
	Tile bl();
	Tile br();
	// Return a vector of all the 9 tiles around this tile
	std::vector<Tile*> around();


	void birth();
	void kill();

	void setEnabledColor(sf::Color);
	void setEnabledOutlineColor(sf::Color);

	void setDisabledColor(sf::Color);
	void setColor(sf::Color enabled, sf::Color enabledGrid, sf::Color disabled);


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

	sf::Color enabledColor;
	sf::Color disabledColor;
	sf::Color enabledGridColor;
	sf::Color disabledGridColor;


};