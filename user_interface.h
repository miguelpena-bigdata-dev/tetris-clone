#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <SFML/Graphics.hpp>

class UserInterface
{
public:
    sf::Font mainFont;
    UserInterface(std::string _fontFileName) 
    {
        loadFont(_fontFileName);
    }
    void loadFont(std::string fontFileName);

    void drawText(sf::RenderWindow &window, std::string text, sf::Vector2f position);

    void drawNextTetranimo(sf::RenderWindow &window, int type, std::vector<std::vector<int>> structure, sf::Vector2f position,
                           sf::Vector2<int> gridUnitSize, sf::Color backgroundColor);

};

#endif