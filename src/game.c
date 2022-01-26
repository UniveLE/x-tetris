#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "./utils/matrix/matrix.h"
#include "./utils/menu/menu.h"
#include "./utils/player/player.h"
#include "./utils/tetraminoes/tetraminoes.h"
#include "./utils/cpu/cpu.h"
#include "./utils/utils.h"

#define TRUE 1
#define FALSE 0

/**
* Funzione utilizzata per stampare la scritta che indica
* il giocatore che ha vinto.
*
* @param winnerPlayer nome del giocatore che ha vinto
*/
void conclusion(char* winnerPlayer){
  int nameLength = strlen(winnerPlayer), pos, i;
  printf("+----------------------------------------------------------+\n");

  pos = (60 - 16- nameLength) / 2;
  for(i = 0; i < pos; i++){
    printf(" ");
  }

  printf("Il vincitore è ");

  for(i = 0; i < nameLength; i++){
    printf("%c", winnerPlayer[i]);
  }
  printf("!\n");
  printf("+----------------------------------------------------------+\n");
}

/**
 * Funzione invocata quando il tetramino non può più
 * muoversi verso il basso. Questa funzione verifica anche il
 * gameover del giocatore passato in input.
 *
 * @param main_player giocatore principale da verificare
 * @param opponent_player giocatore avversario
 * @param game gioco, utilizzato per le statistiche riguardo
 *             i tetramini.
 */
int step(player* main_player, player* opponent_player, game* game) {
  /*vengono convertite le @ con #*/
  conversion(main_player);

  if (gameOver(main_player) == TRUE && !canMove(2, main_player)) {
    game->gameOver = TRUE;
    return 1;
  } else {
    int lines = setScore(main_player); /*numero di righe eliminate*/

    /*se l'utente riesce ad eliminare più di 3 righe il campo dell'avversario
    subisce una modifica: gli spazi vuoti diventano pieni e quelli pieni diventato vuoti*/
    if (lines >= 3 && opponent_player != NULL)
      reversePlayground(opponent_player, lines);

    insertTetromino(main_player, game);
    /*Verifica se l'ultimo tetramino aggiunto può abbassarsi (verifica gameover)*/
    if (!canMove(2, main_player)) {
      game->gameOver = TRUE;
      return 1;
    }
    ++(main_player->tetraminoes);
  }
  return 0;
}

/**
 * Funzione utilizzata per gestire la modalità di gioco
 * 1 VS CPU.
 *
 * @param player1 struttura del giocatore
 * @param game struttura relativa al gioco
 */
void cpuMultiPlayer(player* player1, game* game) {
  int count_player = 0, count_cpu = 0, score = 0, x_score = -1, r_score = -1, height = -1, x_height = -1, r_height = -1;
  player cpu_player;
  setNickname(player1);
  initPlayer(&cpu_player);
  cpu_player.nickname = "CPU";

  insertTetromino(player1, game);
  insertTetromino(&cpu_player, game);

  setupIO();
  while (game->gameOver == FALSE) {
    char cmd;

    /*controllo se uno dei player ha raggiunto il numero massimo di tetramini*/
    if (game->tetraminoesNumber == player1->tetraminoes || game->tetraminoesNumber == cpu_player.tetraminoes) {
      break;
      }

    sleep(0.001);
    count_player++;
    count_cpu++;

    if (count_player % game->difficulty == 0) {
      if (moveTetramino('s', player1) == 2)
        if (step(player1, &cpu_player, game))
          break;
      printPlayground(player1, &cpu_player, game->tetraminoesNumber);
    }

    if (count_cpu % (game->difficulty - DIFF_BOT_DIFFICULTY) == 0) {
      if (moveTetramino('s', &cpu_player) == 2) {
        if (step(&cpu_player, player1, game)) {
          break;
        }else{
          int score = 0, x_score = -1, r_score = -1, height = -1, x_height = -1, r_height = -1;
          moveCPU(&cpu_player, &score, &x_score, &r_score, &height, &x_height, &r_height);
          if(score > 0){
            int l;
            for (l = 0; l < r_score; ++l)
                rotation(&cpu_player);
              moveTo(&cpu_player, x_score, 0);
          }else{
              int l;
              for (l = 0; l < r_height; ++l)
                rotation(&cpu_player);
              moveTo(&cpu_player, x_height, 0);
          }
          count_cpu = 0;
        }
        
      }

      printPlayground(player1, &cpu_player, game->tetraminoesNumber);
    }

    while ((cmd = getchar()) > 0 && cmd != 255) {
      if (moveTetramino(cmd, player1) == 2)
        if (step(player1, &cpu_player, game))
          break;

      printPlayground(player1, &cpu_player, game->tetraminoesNumber);
      count_cpu++;
      count_player++;
    }
    
  }

  cleanupIO();
  printPlayground(player1, &cpu_player, game->tetraminoesNumber);

  /*viene salvato il punteggio del giocatore*/
  saveScore(player1, game);

  printf("\n\n-> ***** GAME OVER ***** <-\n\n");
  if(player1->score > cpu_player.score)
    conclusion(player1->nickname);
}

/**
 * Funzione utilizzata per gestire la modalità di gioco
 * single player e 1 VS 1.
 *
 * @param player1 struttura del giocatore 1
 * @param player2 struttura del giocatore 2
 * @param game struttura relativa al gioco 
 */
void singleMultiPlayer(player* player1, player* player2, game* game) {
  int count = 0;
  
  setNickname(player1);
  insertTetromino(player1, game);

  if (player2 != NULL) {
    setNickname(player2);
    insertTetromino(player2, game);
  }

  setupIO();

  while (game->gameOver == FALSE) {
    char cmd;

    /*controllo se uno dei player ha raggiunto il numero massimo di tetramini*/
    if (game->tetraminoesNumber == player1->tetraminoes || (player2 != NULL && game->tetraminoesNumber == player2->tetraminoes)) {
      break;
    }

    sleep(0.001);
    count++;

    /*codice per muovere i pezzi in automatico verso il basso*/
    if (count % game->difficulty == 0) {
      if (moveTetramino('s', player1) == 2)
        if (step(player1, player2 != NULL ? player2 : NULL, game))
          break;

      if (player2 != NULL && moveTetramino('s', player2) == 2)
        if (step(player2, player1, game))
          break;

      printPlayground(player1, player2 != NULL ? player2 : NULL, game->tetraminoesNumber);
    }

    /*listening dei tasti premuti dall'utente*/
    while ((cmd = getchar()) > 0 && cmd != 255) {
      if (cmd == DIRECTION_P1_DOWN || cmd == DIRECTION_P1_LEFT || cmd == DIRECTION_P1_RIGHT || cmd == DIRECTION_P1_ROTATE) {
        if (moveTetramino(cmd, player1) == 2)
          if (step(player1, player2 != NULL ? player2 : NULL, game))
            break;
      } else if (cmd == DIRECTION_P2_DOWN || cmd == DIRECTION_P2_LEFT || cmd == DIRECTION_P2_RIGHT || cmd == DIRECTION_P2_ROTATE) {
        if (player2 != NULL && moveTetramino(cmd, player2) == 2)
          if (step(player2, player1, game))
            break;
      }
      
      printPlayground(player1, player2 != NULL ? player2 : NULL, game->tetraminoesNumber);
      count++;
    }
  }

  cleanupIO();
  printPlayground(player1, player2 != NULL ? player2 : NULL, game->tetraminoesNumber);

  /*vengono salvati i punteggi dei giocatori*/
  saveScore(player1, game);
  if (player2 != NULL)
    saveScore(player2, game);
  
  printf("\n\n-> ***** GAME OVER ***** <-\n\n");
  if(player2 != NULL || player1->score != player2->score)
    if(player1->score > player2->score)
      conclusion(player1->nickname);
    else
      conclusion(player2->nickname);
}

/**
 * Funzione utilizzata per avviare il gioco
 * tetris.
 */
void startGame() {
    game game;
    player player1, player2;
    size_t i;

    int difficulty = 0;
    int gameMode = 0;

    /*varibiali utilizzate per il sistema di ricerca dei punteggi*/
    /*char* query;
    char choice;*/

    /*init game*/
    game.gameMode = gameMode;
    game.gameOver = FALSE;
    game.tetraminoesNumber = 150;

    initPlayer(&player1);
    initPlayer(&player2);

    clearScreen();
    printLogos(LOGO_FLE_NAME);
    menu();

    /*l'utente inserisce la modalità di gioco*/
    printf("Game mode: ");
    scanf(" %d", &gameMode);
    game.gameMode = gameMode;

    /*questo controllo evita la richiesta all'utente riguardante il numero massimo di tetramini
    e la difficoltà quando vuole visualizzare i punteggi*/
    if (game.gameMode != PLAYER_SCORE) {
      /*l'utente decide il numero massimo di tetramini utilizzabili*/
      printf("Numero di tetramini utilizzabili: ");
      scanf(" %d", &(game.tetraminoesNumber));

      /*Creazione e inserimento dei tetramini da inserire nel (o nei) campo da gioco*/
      game.tetraminoes = (int*)malloc(sizeof(int) * game.tetraminoesNumber);
      srand(time(NULL));
      for (i = 0; i < game.tetraminoesNumber; i++)
        game.tetraminoes[i] = rand() % 7;

      /*viene chiesto all'utente la difficoltà di gioco*/
      printf("Inserisci la difficoltà di gioco (1-3): ");
      scanf(" %d", &difficulty);
      switch (difficulty) {
        case 1:
          game.difficulty = EASY;
          break;
        case 2:
          game.difficulty = MEDIUM;
          break;
        case 3:
          game.difficulty = HARD;
          break;
        default:
          game.difficulty = MEDIUM;
          break;
      }
    }

    switch (game.gameMode) {
      case SINGLE_PLAYER: /*single player*/
        singleMultiPlayer(&player1, NULL, &game);
        break;
      case MULTI_PLAYER: /*1 vs 1*/
        singleMultiPlayer(&player1, &player2, &game);
        break;
      case PLAYER_VS_BOT: /*1 vs CPU*/
        cpuMultiPlayer(&player1, &game);
        break;
      case PLAYER_SCORE:
        printLogos(SCORE_LOGO_FLE_NAME);
        printScores(NULL);
        break;
      case EXIT: /*exit*/
        exit(0);
    }
}