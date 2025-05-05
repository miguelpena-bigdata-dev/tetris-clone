#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "randomer.hpp"
#include "map.h"
#include "tetranimo.h"
#include "user_interface.h"

#define PI_VALUE 3.14159265

int main()
{
    //Randomer randomer{ 0,100 };
    UserInterface mainUI("arialbd.ttf");
    Map mainMap( sf::Vector2<int>(10,24), sf::Vector2<int>(0,-4), sf::Vector2<int>(32,32) ); //(mapSize in grid units, mapOffset in grid units, mapDrawOffset in pixels)
    sf::Clock clock;
    Tetranimo player;
    int score = 0;
    int highscore = 0;
    bool gameOver = false;
    sf::Time deltaTime;
    sf::RenderWindow window(sf::VideoMode({596, 704}), "Tetris");
    float elapsedTime = 0;
    float completeTimer = 0; //timer for row completion animation.
    float currentFallSpeed = 2; //inverted,higher number means slower fall rate
    player.setTetranimoType(player.getNextTetranimoType());
    player.nextType = player.getNextTetranimoType();
    player.newStructure = player.listOfStructures[player.nextType];
    player.fallSpeed = currentFallSpeed;
    std::vector<int> completeRows;
    bool rowComplete = false;
    while (window.isOpen())
    {
        deltaTime = clock.restart();
        elapsedTime += deltaTime.asSeconds();
        
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (!gameOver)
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                    {
                        player.updatePosition(-1, 0, mainMap);
                        //std::cout << "Pressing Left, move Tetranimo left." << std::endl;
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                    {
                        player.updatePosition(1, 0, mainMap);
                        //std::cout << "Pressing Right, move Tetranimo right." << std::endl;
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                        player.fallSpeed = 0.05;
                        //std::cout << "Pressing Down, move Teranimo down until collision." << std::endl;
                    }
                } 
                else {
                    gameOver = false;
                }
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scancode::Q) 
                {
                    player.rotateStructure(PI_VALUE / 2, mainMap);
                    //std::cout << "Released Q, Rotate Tetranimo" << std::endl;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::E) 
                {
                    player.rotateStructure(-(PI_VALUE / 2), mainMap);
                    //std::cout << "Released E, Rotate Tetranimo" << std::endl;
                } 
                else if (keyReleased->scancode == sf::Keyboard::Scancode::Down)
                {
                    //player.updatePosition(0, 1);
                    player.fallSpeed = currentFallSpeed;
                    //std::cout << "Pressing Down, move Teranimo down until collision." << std::endl;
                }
            }
        }
        window.clear(sf::Color(116,95,127,255));
        mainUI.drawText(window, "Next:", sf::Vector2f(368, 32));
        mainUI.drawNextTetranimo(window, player.nextType, player.newStructure, sf::Vector2f(412, 76), mainMap.gridUnitSize, sf::Color(200, 175, 215, 255));
        mainUI.drawText(window, "Score:", sf::Vector2f(368, 216));
        mainUI.drawText(window, std::to_string(score), sf::Vector2f(432, 248));
        mainUI.drawText(window, "Highscore:", sf::Vector2f(368, 312));
        mainUI.drawText(window, std::to_string(highscore), sf::Vector2f(432, 344));
        if (rowComplete)
            completeTimer += deltaTime.asSeconds();
        if (!gameOver && (elapsedTime >= player.fallSpeed)) {
            if (!player.updatePosition(0, 1, mainMap)) { //update failed,hit bottom
                if (player.position.y < abs(mainMap.mapOffset.y))
                {
                    gameOver = true;
                    if (score > highscore)
                        highscore = score;
                    score = 0;
                    currentFallSpeed = 2;
                    player.reset();
                    mainMap.reset();
                }
                else {
                    mainMap.setAtPosition(player.type, player.position, player.structure);
                    completeRows = mainMap.checkForCompletedLines();
                    if (!completeRows.empty())
                    {
                        rowComplete = true;
                        score += 25*exp(completeRows.size());
                        mainMap.markForDeletion(completeRows);
                        currentFallSpeed = fmax(0.1, currentFallSpeed - 0.25 * (1 / exp(4 - completeRows.size())));
                        //add logic for calculating score and increasing fall speed here.
                    }
                    player.reset();
                }
                
            }
            elapsedTime = 0;
        }
        if ((rowComplete) && (completeTimer > 0.5))
        {
            rowComplete = false;
            completeTimer = 0;
            mainMap.deleteMarkedRows();
        }
        mainMap.drawSelf(window);
        player.drawSelf(window, mainMap);
        if (gameOver) {
            mainUI.drawText(window, "GAMEOVER", sf::Vector2f(window.getSize().x / 2 - 128, window.getSize().y / 2 + 128));
            mainUI.drawText(window, "Press any key to continue!", sf::Vector2f(window.getSize().x / 2 - 128, window.getSize().y / 2 + 192));
        }
        window.display();
    }
    return 0;
}