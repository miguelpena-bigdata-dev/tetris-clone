#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class Map
{
public:
    sf::Vector2<int> mapSize;
    std::vector<int> mapGrid; //std::vector != sf::Vector2<int> because we need to access the elements in a 1D array.
    sf::Vector2<int> mapOffset;
    sf::Vector2<int> mapDrawOffset;
    sf::Vector2<int> gridUnitSize = sf::Vector2<int>(32, 32); //grid unit size in pixels;

    Map(sf::Vector2<int> _mapSize, sf::Vector2<int> _mapOffset, sf::Vector2<int> _mapDrawOffset)
    {
        mapSize = _mapSize;
        mapOffset = _mapOffset;
        mapDrawOffset = _mapDrawOffset;
        setupMap();
    }
    void setupMap();

    bool testPosition(sf::Vector2<int> position);

    void setAtPosition(int typeToUse, sf::Vector2<int> position, std::vector<std::vector<int>> structure);

    void drawSelf(sf::RenderWindow &window);

    std::vector<int> checkForCompletedLines();
    
    void markForDeletion(std::vector<int> completeRows);

    void deleteMarkedRows();

    void reset();
};

#endif