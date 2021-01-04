//
// Created by Mystyk on 30/12/2020.
//
#include <iostream>
#include <windows.h>
#include "Game.h"


void InitializeMap(int n, Cell **pMap, int size)
// Initialize game map with cells
{
    float mult = 1;
    if (size == 16) mult = 4;
    else if (size == 32) mult = 2;
    float posX = 100;
    float posY = 10;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            pMap[y][x] = Cell(posX, posY, {mult * 9,mult * 9});
            posX += mult * 9;
        }
        posX = 100;
        posY += mult * 9;
    }
}

void Game(int size, int *state, int **livingNeighbours, Cell **cellMap, sf::RenderWindow &window, std::vector<Button*> &buttons)
{
    // Creating text labels
    sf::Font arial;
    arial.loadFromFile("..\\arial.ttf");
    sf::Context context;
    sf::Text sizeLabel;
    sizeLabel.setFont(arial);
    sizeLabel.setString("Size");
    sizeLabel.setCharacterSize(25);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setPosition({950, 180});



    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            livingNeighbours[y][x] = cellMap[y][x].Neighbours();
        }
    }


    while (*state != 0)
    {
        if (*state == 2)
        {
            window.clear(sf::Color::White);
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    cellMap[y][x].draw(window);
                }
            }
            for (auto &button: buttons)
            {
                button->draw(window);
            }
            window.draw(sizeLabel);
            window.display();
            continue;
        }
        else
        {
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    if (cellMap[y][x].isAlive() &&
                        (livingNeighbours[y][x] == 2 || livingNeighbours[y][x] == 3))
                        continue;
                    else if (cellMap[y][x].isAlive()) {
                        cellMap[y][x].Kill();
                        // Change neighbours of adjacent cells
                        if ((y - 1) >= 0) {
                            if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() -= 1;
                            cellMap[y - 1][x].Neighbours() -= 1;
                            if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() -= 1;
                        }
                        if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() -= 1;
                        if ((x + 1) < size) cellMap[y][x + 1].Neighbours() -= 1;
                        if ((y + 1) < size) {
                            if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() -= 1;
                            cellMap[y + 1][x].Neighbours() -= 1;
                            if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() -= 1;
                        }
                    } else if (!cellMap[y][x].isAlive() && livingNeighbours[y][x] == 3) {
                        cellMap[y][x].Born();
                        // Change neighbours of adjacent cells
                        if ((y - 1) >= 0) {
                            if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                            cellMap[y - 1][x].Neighbours() += 1;
                            if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                        }
                        if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                        if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                        if ((y + 1) < size) {
                            if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                            cellMap[y + 1][x].Neighbours() += 1;
                            if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                        }
                    }
                }
            }
            window.clear(sf::Color::White);
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                    cellMap[y][x].draw(window);
                }
            }
            for (auto &button: buttons)
            {
                button->draw(window);
            }
            window.draw(sizeLabel);
            window.display();
            if (*state != 0 && size == 64) Sleep(100);
            else if (*state != 0) Sleep(200);
        }
    }
    InitializeMap(64, cellMap, size);
    window.setActive(false);
}



