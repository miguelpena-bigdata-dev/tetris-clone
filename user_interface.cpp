#include <iostream>
#include "user_interface.h"
#include <math.h>
#include <string>

void UserInterface::loadFont(std::string fontFileName)
{
    // mainFont.loadFromFile(fontFileName);
    if (!mainFont.openFromFile(fontFileName))
    {
        std::cerr << "Error loading font from file: " << fontFileName << std::endl;
    };
}

void UserInterface::drawText(sf::RenderWindow &window, std::string text, sf::Vector2f position)
{
    sf::Text textObj = sf::Text(mainFont,text,32);
    textObj.setFillColor(sf::Color::White);
    textObj.setPosition(position);
    window.draw(textObj);
}

void UserInterface::drawNextTetranimo(sf::RenderWindow &window, int type, std::vector<std::vector<int>> structure, sf::Vector2f position,
                           sf::Vector2<int> gridUnitSize, sf::Color backgroundColor)
{
    sf::Color colorChoices[] = { sf::Color::Yellow,sf::Color::White, sf::Color::Red, sf::Color(255,135,0,255), 
                                 sf::Color::Magenta, sf::Color::Blue, sf::Color::Green, sf::Color(100,100,100,255) };
    
    sf::Vector2<int> limit = sf::Vector2<int>(structure[0].size(), structure.size());
    sf::RectangleShape rectShapeA;
    rectShapeA.setSize(sf::Vector2f(gridUnitSize.x * limit.x, gridUnitSize.y * limit.y));
    rectShapeA.setOutlineColor(sf::Color::Black);
    rectShapeA.setFillColor(backgroundColor);
    rectShapeA.setOutlineThickness(1);
    rectShapeA.setPosition(position);
    window.draw(rectShapeA);
    
    for (int index = 0; index < limit.x * limit.y; index++)
    {
        sf::Vector2<int> relative_position = sf::Vector2<int>(index % limit.x, floor(index / limit.x));
        if (structure[relative_position.y][relative_position.x] == 1) 
        {
            sf::RectangleShape rectShapeB;
            rectShapeB.setSize(sf::Vector2f(gridUnitSize.x, gridUnitSize.y));
            rectShapeB.setOutlineColor(sf::Color::Black);
            rectShapeB.setFillColor(colorChoices[type]);
            rectShapeB.setOutlineThickness(1);
            sf::Vector2<float> drawPosition = sf::Vector2<float>((gridUnitSize.x * relative_position.x) + position.x, 
                                                                (gridUnitSize.y * relative_position.y) + position.y);
            rectShapeB.setPosition(drawPosition);
            window.draw(rectShapeB);
        }
    }
}