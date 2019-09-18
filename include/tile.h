#include <SFML/Graphics.hpp>
#include <vector>

class tile : public sf::RectangleShape {
public:

    tile(sf::Vector2f, sf::Vector2f, std::vector<std::vector<tile>> *, int, int);

    // Returns if tile is alive or dead
    bool enabled();

    // Looks around and performs logic
    void check();
    // Execute generation
    void execute();

    void toggleOutline();

    tile left();
    tile right();
    tile top();
    tile down();
    tile tl();
    tile tr();
    tile bl();
    tile br();

    // Return a vector of all the 9 tiles around this tile
    std::vector<tile *> around();

    void birth();
    void kill();

    void setColor(sf::Color enabled, sf::Color enabledGrid, sf::Color disabled);

private:
    // Empty constructor
    tile();

    int neighbors;
    bool outlineOn;
    sf::Vector2f topLeft;
    sf::Vector2f bottomRight;
    sf::Vector2f center;
    bool on;
    int column;
    int row;
    std::vector<std::vector<tile>> *parent;

    sf::Color enabledColor;
    sf::Color disabledColor;
    sf::Color enabledGridColor;
    sf::Color disabledGridColor;
};