//
// Created by Mystyk on 30/12/2020.
//
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include "Game.h"

using namespace std; // to be deleted when console test is no longer needed


void InitializeMap(int n, Cell **pMap)
// Initialize game map with cells
{
    float posX = 10;
    float posY = 10;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            pMap[y][x] = Cell(posX, posY, {7,7});
            posX += 7;
        }
        posX = 10;
        posY += 7;
    }
}

void Game(int size, int *state, int preSet, sf::RenderWindow &window)
{
    sf::Context context;
    int **livingNeighbours;
    livingNeighbours = new int*[size];
    for (int i = 0; i < size; i++)
    {
        livingNeighbours[i] = new int[size];
    }
    // Create cell map
    Cell **cellMap;
    cellMap = new Cell*[size];
    for (int i = 0; i < size; i++)
    {
        cellMap[i] = new Cell[size];
    }
    // Initialize game map with cells
    InitializeMap(size, cellMap);
    // TO DO preSet part (real one)
    int y[] = {1,2,3, 3, 3};
    int x[] = {2,3,1, 2, 3};
    for (int i = 0; i < 5; i++)
    {
        cellMap[y[i]][x[i]].Born();
        if((y[i] - 1) >= 0)
        {
            if((x[i] - 1) >= 0) cellMap[y[i]-1][x[i]-1].Neighbours() += 1;
            cellMap[y[i]-1][x[i]].Neighbours() += 1;
            if((x[i] + 1) < size) cellMap[y[i]-1][x[i] + 1].Neighbours() += 1;
        }
        if((x[i] - 1) >= 0) cellMap[y[i]][x[i]-1].Neighbours() += 1;
        if((x[i] + 1) < size) cellMap[y[i]][x[i] + 1].Neighbours() += 1;
        if((y[i] + 1) < size)
        {
            if((x[i] - 1) >= 0) cellMap[y[i]+1][x[i]-1].Neighbours() += 1;
            cellMap[y[i]+1][x[i]].Neighbours() += 1;
            if((x[i] + 1) < size) cellMap[y[i]+1][x[i] + 1].Neighbours() += 1;
        }
    }
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            livingNeighbours[y][x] = cellMap[y][x].Neighbours();
        }
    }
    // preSet part end


    while (*state != 0)
    {
        if (*state == 2) continue;
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
                    } else if (cellMap[y][x].isAlive()) {
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
                    }
                }
            }
            window.clear();
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                    cellMap[y][x].draw(window);
                }
            }
            window.display();
            Sleep(50);
        }
    }
    for (int i = 0; i < size; i++)
    {
        delete[] livingNeighbours[i];
    }
    delete[] livingNeighbours;
    // Delete cell map
    for (int i = 0; i < size; i++)
    {
        delete[] cellMap[i];
    }
    delete[] cellMap;
}


void GameWindow(int size, int *state, int preSet)
{
    sf::RenderWindow window(sf::VideoMode(1200, 600), "GameWindow of Life", sf::Style::Titlebar | sf::Style::Close);
    sf::Context context;
    sf::Event event;
    thread play(Game, size, &(*state), preSet, std::ref(window));
    while (window.isOpen())
    {

        if (*state == 0)
        {
            play.join();
            window.close();
            continue;
        }
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    *state = 0;
                    play.join();
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    break;
                default:
                    break;
            }
        }

    }

}


