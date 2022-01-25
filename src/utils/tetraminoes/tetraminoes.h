#ifndef _TETRAMINOES_H
#define _TETRAMINOES_H

#include "../player/player.h"
#include "../../game.h"

int canMove(int direction, player *player);
int rotation(player *player);
int move(int direction, player *player);
int insertTetromino(player *player, game *game);
int moveTetramino(char direction, player *player);
void conversion(player * player);
#endif