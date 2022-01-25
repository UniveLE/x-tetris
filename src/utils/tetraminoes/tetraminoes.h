/**
 * @file tetraminoes.h
 * @date 18/10/2021
 * @author Lorenzo Vaccher & Elia Coro'
 * @brief Libreria per la gestione dei tetramini (movimenti, rotazione, ecc).
 */

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