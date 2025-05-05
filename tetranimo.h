#ifndef TETRANIMO_H
#define TETRANIMO_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "map.h"


class Tetranimo
{
public:
    sf::Vector2<int> position = sf::Vector2<int>(0,0);
    int type = 0; //0 - square, 1 - line, 2 - s, 3 - z, 4 - t, 5 - rl, 6 - ll;
    int nextType;
    sf::Color currentColor = sf::Color::Yellow;
    std::vector<std::vector<int>> structure{
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    std::vector<std::vector<int>> newStructure{
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    std::vector<std::vector<int>> listOfStructures[7] = {
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {0,0,1,1},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    };
    std::vector<int> bagOfTypes{ 0, 1, 2, 3, 4, 5, 6 };
    float fallSpeed = 1.25;
    int getNextTetranimoType();
    
    void setTetranimoType(int _type);

    bool updatePosition(int _x, int _y, Map &mainMap);


    void rotateStructure(float angle, Map &mainMap);
    
    void drawSelf(sf::RenderWindow &window, Map &mapRef); 
    
    void reset();

};

#endif