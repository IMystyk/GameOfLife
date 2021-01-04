//
// Created by Mystyk on 16/12/2020.
//

#ifndef CGOL_CELL_H
#define CGOL_CELL_H
#include <SFML/Graphics.hpp>
#include <windows.h>

class Cell{
    bool alive = false;
    int neighbours = 0;
    sf::RectangleShape cell;

public:
    bool modified = false;
    Cell() = default;
    Cell(float x, float y, sf::Vector2f size);
    void setSize(sf::Vector2f size);
    int& Neighbours();
    bool isAlive();
    bool isMouseOver(sf::RenderWindow &window);
    void Born();
    void Kill();
    void draw(sf::RenderWindow &window);
};



#endif //CGOL_CELL_H
