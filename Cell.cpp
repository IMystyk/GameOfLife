//
// Created by Mystyk on 16/12/2020.
//

#include "Cell.h"

Cell::Cell(float x, float y, sf::Vector2f size)
{
    cell.setPosition(x, y);
    cell.setSize(size);
}

void Cell::Kill()
// Kills a cell (alive = false)
{
    alive = false;
    cell.setFillColor(sf::Color::White);
}

void Cell::Born()
// Makes a cell alive (alive = true)
{
    alive = true;
    cell.setFillColor(sf::Color::Black);
}

int& Cell::Neighbours() {
    return neighbours;
}

bool Cell::isAlive() {
    return alive;
}

bool Cell::isMouseOver(sf::RenderWindow &window)
{
    float mousePosX = sf::Mouse::getPosition(window).x;
    float mousePosY = sf::Mouse::getPosition(window).y;

    float cellLPosX = cell.getPosition().x;
    float cellDPosY = cell.getPosition().y;

    float cellRPosX = cellLPosX + cell.getLocalBounds().width;
    float cellUPosY = cellDPosY + cell.getLocalBounds().height;

    if(mousePosX > cellLPosX && mousePosX < cellRPosX && mousePosY > cellDPosY && mousePosY < cellUPosY) return true;
    else return false;
}

void Cell::setSize(sf::Vector2f size)
{
    cell.setSize(size);
}

void Cell::draw(sf::RenderWindow &window)
{
    window.draw(cell);
}


