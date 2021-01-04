//
// Created by Mystyk on 30/12/2020.
//

#ifndef CGOL_GAME_H
#define CGOL_GAME_H

#include "Button.h"
#include "Cell.h"
#include <vector>
#include <thread>

void InitializeMap(int n, Cell **pMap, int size);
void Game(int size, int *state, int **livingNeighbours, Cell **cellMap,sf::RenderWindow &window, std::vector<Button*> &buttons);

#endif //CGOL_GAME_H
