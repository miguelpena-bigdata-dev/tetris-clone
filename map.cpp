#include "map.h"

void Map::setupMap()
    {
        for (int index = 0; index < mapSize.x * mapSize.y; index++)
        {
            mapGrid.push_back(0);
        }
    }

bool Map::testPosition(sf::Vector2<int> position)
{
    if (position.x < 0 || position.x >= mapSize.x)
        return false;
    int index = (position.y * mapSize.x) + position.x;
    if (index < 0 || index >= mapSize.x * mapSize.y)
        return false;
    return (mapGrid[index] == 0);
}

void Map::setAtPosition(int typeToUse, sf::Vector2<int> position, std::vector<std::vector<int>> structure)
{
    int xLimit = structure[0].size();
    int yLimit = structure.size();
    for (int index = 0; index < xLimit * yLimit; index++)
    {
        int mx = index % xLimit;
        int my = floor(index / xLimit);
        if (structure[my][mx] == 1) 
        {
            int mapIndex = ((position.y + my) * mapSize.x) + (position.x+mx);
            mapGrid[mapIndex] = typeToUse+1;
        }
    }
}

void Map::drawSelf(sf::RenderWindow &window)
{
    sf::RectangleShape rectShapeA;
    rectShapeA.setSize(sf::Vector2f(gridUnitSize.x * (mapSize.x + mapOffset.x),
                                    gridUnitSize.y * (mapSize.y + mapOffset.y)));
    rectShapeA.setOutlineColor(sf::Color::Black);
    rectShapeA.setFillColor(sf::Color(200, 175, 215, 255));
    rectShapeA.setOutlineThickness(1);
    rectShapeA.setPosition(sf::Vector2f(mapDrawOffset.x, mapDrawOffset.y));
    window.draw(rectShapeA);
    int ignoredIndex = abs(mapOffset.y)*mapSize.x;
    sf::Color colorChoices[] = { sf::Color::Yellow,sf::Color::White, sf::Color::Red, sf::Color(255,135,0,255), sf::Color::Magenta, sf::Color::Blue, sf::Color::Green, sf::Color(100,100,100,255)};
    for (int index = 0; index < mapSize.x * mapSize.y; index++)
    {
        if ((mapGrid[index] == 0) || (index < ignoredIndex)) //ignore the indexes that are above the drawing area, ensures tetranimo arrives above screen area.
            continue;
        int mx = index % mapSize.x;
        int my = floor(index / mapSize.x);
        int colorIndex;
        if (mapGrid[index] > 0)
            colorIndex = mapGrid[index] - 1;
        if (mapGrid[index] < 0)
            colorIndex = 7;
        sf::RectangleShape rectShape;
        rectShape.setSize(sf::Vector2f(gridUnitSize.x,gridUnitSize.y));
        rectShape.setOutlineColor(sf::Color::Black);
        rectShape.setFillColor(colorChoices[colorIndex]);
        rectShape.setOutlineThickness(1);
        sf::Vector2<float> drawPosition = sf::Vector2<float>((mx + mapOffset.x) * gridUnitSize.x + mapDrawOffset.x, (my + mapOffset.y) * gridUnitSize.y + mapDrawOffset.y);
        //rectShape.setPosition(sf::Vector2f((mx+mapOffset.x) * gridUnitSize.x + mapDrawOffset.x, (my+mapOffset.y) * gridUnitSize.y + mapDrawOffset.y));
        rectShape.setPosition(drawPosition);//(mx+mapOffset.x) * gridUnitSize.x + mapDrawOffset.x, (my+mapOffset.y) * gridUnitSize.y + mapDrawOffset.y))
        window.draw(rectShape);
    }
}

std::vector<int> Map::checkForCompletedLines()
{
    std::vector<int> fullRows;
    int count = 0;
    for (int index = (mapSize.x * mapSize.y) - 1; index >= 0; index--) 
    {
        int mx = index % mapSize.x;
        int my = floor(index / mapSize.x);
        if ((mx >= 0) && (mapGrid[index] > 0)) {
            count++;
        }
        if ((mx == 0) && (count < mapSize.x)) 
        {
            count = 0;
        } else if ((mx == 0) && (count == mapSize.x))
        {
            fullRows.push_back(my);
            //std::cout << "Row added: " << my << std::endl;
            count = 0;
        }
                
    }
    return fullRows;
}

void Map::markForDeletion(std::vector<int> completeRows) 
{
    for (int index = 0; index < completeRows.size();index++)
    {
        int my = completeRows[index];
        for (int mx = 0; mx < mapSize.x; mx++)
        {
            int mapIndex = (my * mapSize.x) + mx;
            mapGrid[mapIndex] = -1;
        }
    }
}

void Map::deleteMarkedRows()
{
    int count = 0; //count number of deleted values
    for (int index = (mapSize.x * mapSize.y) - 1; index >= 0; index--) 
    {
        if (mapGrid[index] == -1) 
        {
            mapGrid.erase(mapGrid.begin() + index);
            count++;
        }
    }
    for (int i = 0; i < count; i++) mapGrid.insert(mapGrid.begin(), 0);
}

void Map::reset()
{
    mapGrid.clear();
    for (int index = 0; index < mapSize.x * mapSize.y; index++)
    {
        mapGrid.push_back(0);
    }
}

