#include "randomer.hpp"
#include "map.h"
#include "tetranimo.h"

int Tetranimo::getNextTetranimoType()
{
    if (bagOfTypes.empty())
        bagOfTypes = { 0, 1, 2, 3, 4, 5, 6 };
    Randomer randomer{ 0,bagOfTypes.size()-1};
    int chosenTypeIndex = randomer();
    int chosenType = bagOfTypes[chosenTypeIndex];
    bagOfTypes.erase(bagOfTypes.begin()+chosenTypeIndex);
    return chosenType;
}

void Tetranimo::setTetranimoType(int _type) 
{
    type = _type;
    sf::Color colorChoices[] = { sf::Color::Yellow,sf::Color::White, sf::Color::Red, 
                                 sf::Color(255,135,0,255), sf::Color::Magenta, sf::Color::Blue, 
                                 sf::Color::Green, sf::Color(100,100,100,255) };
    currentColor = colorChoices[type];
    structure = listOfStructures[type];
}

bool Tetranimo::updatePosition(int _x, int _y, Map &mainMap)
{
    sf::Vector2<int> vector = sf::Vector2<int>(_x, _y);
    sf::Vector2<int> nextPosition = position + vector;
    bool okayToUpdate = true;
    for (int index = 0; index < structure.size() * structure[0].size(); index++)
    {
        int x = index % structure[0].size();
        int y = floor(index / structure[0].size());
        if (structure[y][x] == 1) {
            if (!mainMap.testPosition(nextPosition + sf::Vector2<int>(x,y))) 
            {
                okayToUpdate = false;
                break;
            }
                
        }
    }
    
    if (okayToUpdate)
        position += vector;
    
    return okayToUpdate;
}

void Tetranimo::rotateStructure(float angle, Map &mainMap)
{
    bool okayToUpdate = true;
    int yLimit = structure.size();
    int xLimit = structure[0].size();
    float centerX = float(xLimit / 2)-0.5;
    float centerY = float(yLimit / 2)-0.5;
    std::vector<std::vector<int>> newStructure{
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    };
    for (int index = 0; index < yLimit*xLimit; index++) 
    {
        int x = index % xLimit;
        int y = floor(index / yLimit); //used for accessing structure elements
        float x_float = float(index % xLimit)-centerX; //floating point arithmetic
        float y_float = float(index / yLimit)-centerY;
        float xp_float = float(x_float * cos(angle) - y_float * sin(angle))+centerX;
        float yp_float = float(x_float * sin(angle) + y_float * cos(angle))+centerY;
        int xp = int(round(xp_float)); 
        int yp = int(round(yp_float)); //used for accessing new structure elements           
        newStructure[yp][xp] = structure[y][x];
        if (newStructure[yp][xp] == 1) {
            if (!mainMap.testPosition(position + sf::Vector2<int>(xp, yp)))
            {
                okayToUpdate = false;
                 break;
             }
        }
    }
    
    if (okayToUpdate)
        structure = newStructure;

}

void Tetranimo::drawSelf(sf::RenderWindow &window, Map &mapRef) 
{
    sf::Vector2<int> limit = sf::Vector2<int>(structure[0].size(), structure.size());
    for (int index = 0; index < limit.x*limit.y; index++) //Ensures O(n) complexity
    {
        sf::Vector2<int> relative_position = sf::Vector2<int>(index % limit.y, floor(index / limit.x));
        

        if (position.y + relative_position.y < abs(mapRef.mapOffset.y))
            continue; //don't draw if above drawing area indicated by mapOffset.

        if (structure[relative_position.y][relative_position.x] == 1)
        {
            
            sf::RectangleShape rectShapeB;
            rectShapeB.setSize(sf::Vector2f(mapRef.gridUnitSize.x, mapRef.gridUnitSize.y));
            rectShapeB.setOutlineColor(sf::Color::Black);
            rectShapeB.setFillColor(currentColor);
            rectShapeB.setOutlineThickness(1);
            sf::Vector2<float> drawPosition = sf::Vector2<float>(mapRef.gridUnitSize.x * (position.x + relative_position.x + mapRef.mapOffset.x) + mapRef.mapDrawOffset.x, 
                                                                mapRef.gridUnitSize.y * (position.y + relative_position.y + mapRef.mapOffset.y) + mapRef.mapDrawOffset.y);
            rectShapeB.setPosition(drawPosition);
            window.draw(rectShapeB);
        } 
    }
}

void Tetranimo::reset()
{
    position = sf::Vector2<int>(4, 0);
    setTetranimoType(nextType);
    nextType = getNextTetranimoType();
    newStructure = listOfStructures[nextType];
}