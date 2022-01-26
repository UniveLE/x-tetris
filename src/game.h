/**
  * @file game.h
  * @date 18/10/2021
  * @author Lorenzo Vaccher & Elia Coro'
  * @brief Libreria per la gestione del gioco X-Tetris
  */

#ifndef _GAME_H
#define _GAME_H

/**
 * Costante utilizzata per determinare la difficoltà 
 * del BOT. Il calcolo viene effettuato nel seguente modo:
 * viene presa la difficoltà dell'utente e viene sottratto
 * il valore di tale costante.
 */
static const int DIFF_BOT_DIFFICULTY = 2500;

/** Nome del file che contiene il logo da stampare per il menu principale. */
static const char* LOGO_FLE_NAME = "logo.txt";

/**
 * Nome del file che contiene il logo per la "pagina" 
 * dei punteggi dei giocatori.
 */
static const char* SCORE_LOGO_FLE_NAME = "scores_logo.txt";

/**
 * Difficotà di gioco. I valori indicano 
 * la velocità di caduta del tetramino del
 * giocatore. La velocità del BOT si calcola sottraendo
 * la difficoltà del giocatore con la variabile "ADDED_BOT_DIFFICULTY"
 */
typedef enum {
  EASY = 8000,
  MEDIUM = 6000,
  HARD = 4000
} difficulty;

/**
 * Modalità di gioco.
 */
typedef enum {
  SINGLE_PLAYER = 1,
  MULTI_PLAYER = 2,
  PLAYER_VS_BOT = 3,
  PLAYER_SCORE = 4,
  EXIT = 5
} gameMode;

/**
 * Struttura relativa al gioco.
 */
typedef struct {
  /** modalità di gioco */
  gameMode gameMode;
  /** indica se il giocatore ha perso */
  int gameOver;
  /** numero di tetramini riferito all'Array "tetraminoesNumber" */
  int tetraminoesNumber;
  /** vettore contenente tutti i tetramini da inserire */
  int* tetraminoes;
  /** difficoltà della partita */
  difficulty difficulty;
} game;

void startGame();


#endif