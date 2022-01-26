/**
 * @file player.h
 * @date 18/10/2021
 * @author Lorenzo Vaccher & Elia Coro'
 * @brief Libreria per la gestione dei giocatori.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../game.h"

/**
 * Nome del file per il salvataggio dei punteggi degli utenti.
 */
const static char *SCORE_FILE_NAME = "scores.csv";

/**
* Struttura utilizzata per raccogliere tutte le informazione del giocatore.
*/
typedef struct {
  /** punteggio ottenuto secondo determinati criteri illustrati nella relazione */
  int score;
  /** nome del giocatore (viene visualizzato a video) */
  char* nickname;
  /** campo da gioco */
  char playground[19][10];
  /** Numero dei tetramini utilizzati e posizionati nel campo */
  int tetraminoes;
} player;

/**
 * Direzioni dei tetramini riferiti al player 1.
 */
enum Directions_p1 { DIRECTION_P1_ROTATE = ' ',
                     DIRECTION_P1_DOWN = 's',
                     DIRECTION_P1_LEFT = 'a',
                     DIRECTION_P1_RIGHT = 'd' 
                     };

/**
 * Direzioni dei tetramini riferiti al player 2.
 */
enum Directions_p2 { DIRECTION_P2_ROTATE = 67, /*arrow up*/
                     DIRECTION_P2_LEFT = 65,   /*arrow lwft*/
                     DIRECTION_P2_RIGHT = 68,   /*arrow right*/


                     DIRECTION_P2_DOWN = 66   /*arrow down*/
                    };

void initPlayer(player *player);
int setScore(player *player);
void setNickname(player *player);
int gameOver(player *player);
void printNickname(player *player);
void printPlayground(player *player1, player *player2, int maxTetraminoes);
void saveScore(player *player, game* game);
void printScores(char *query);
void reversePlayground(player *player, int lines);

#endif