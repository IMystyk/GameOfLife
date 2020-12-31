//
// Created by Mystyk on 30/12/2020.
//

#ifndef CGOL_GAME_H
#define CGOL_GAME_H

#include "Cell.h"

void InitializeMap(int n, Cell **pMap);
void Game(int size, int *state, int preSet); // preSet is yet to be defined

#endif //CGOL_GAME_H
