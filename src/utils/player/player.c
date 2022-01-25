#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../game.h"
#include "../utils.h"
#include "player.h"

#define TRUE 1
#define FALSE 0
#define PLAYER_NICKNAME_MAX_LENGTH 20

/**
 * Funzione utilizzata per inizializzare la struct
 * relativa al giocatore.
 *
 * @param player indirizzo di memoria della struct
 *               del giocatore da inizializzare.
 */
void initPlayer(player* player) {
  int i, j;
  player->moves = 0;
  player->score = 0;
  player->tetraminoes = 1;

  for (i = 0; i < 19; i++) {
    for (j = 0; j < 10; j++)
      if (i < 4)
        player->playground[i][j] = '.';
      else
        player->playground[i][j] = ' ';
  }
}

/**
 * Funzione utilizzata per verificare se l'utente ha perso.
 *
 * @param player player struct del giocatore
 * @return 1 se l'utente ha perso, 0 se il gioco continua
 */
int gameOver(player* player) {
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 10; j++)
      if (player->playground[i][j] == '#')
        return 1;
  return 0;
}

/**
 * Funzione utilizzata nel multigiocatore quando un player effettua 3 o
 * più punti. In particolare questa funzione viene utilizzata per
 * invertire il campo (gli spazi vuoti diventano pieni e viceversa).
 *
 * @param player campo del giocatore da modificare
 * @param lines linee da invertire
 */
void reversePlayground(player* player, int lines) {
  size_t i, j;
  for (i = (19 - lines); i < 19; i++) {
    for (j = 0; j < 10; j++) {
      if (player->playground[i][j] == ' ')
        player->playground[i][j] = '#';
      else if (player->playground[i][j] == '#')
        player->playground[i][j] = ' ';
    }
  }
}

/**
 * Funzioni utilizzate per impostare il nickname del
 * player.
 *
 * @param player giocatore
 */
void setNickname(player* player) {
  player->nickname = (char*)malloc(sizeof(char) * PLAYER_NICKNAME_MAX_LENGTH);

  if (!player->nickname) { /* verifica allocazione memoria*/
    printf("ERRORE: errore durante l'allocazione della memoria per il Nickname del giocatore.");
    exit(EXIT_FAILURE);
  }

  printf("Player Nickname: ");
  fgets(player->nickname, sizeof(player->nickname), stdin);
  scanf("%[^\n]s", player->nickname);
}

/**
 * Funzione utilizzata per verificare se l'utente ha
 * effettuato dei punti. In particolare:
 *        - La rimozione di una riga -> 1 punto
 *        - La rimozione di due righe con un solo pezzo -> 3 punti
 *        - La rimozione di tre righe con un solo pezzo -> 6 punti
 *        - La rimozione di quattro righe con un solo pezzo -> 12 punti
 * Se viene eliminata una riga, i tetramini sopra la riga traslano verso
 * il basso.
 *
 * @param player struct del giocatore
 * @return numero di righe eliminate
 */
int setScore(player* player) {
  int i, lines = 0;

  for (i = 4; i < 19; i++) {
    int j, status = TRUE;

    /*Verifica linee da cancellare*/
    for (j = 0; j < 10; j++) {
      if (player->playground[i][j] != '#') {
        status = FALSE;
        break;
      }
    }

    if (status == TRUE) {
      int j, k, z;
      ++lines; /*incremento linee complete*/
      /*Reset valori della linea completa*/
      for (j = 0; j < 10; j++)
        player->playground[i][j] = ' ';

      /*Movimento verso il basso dei pezzi dei vari tetramini sopra la linea tolta*/
      for (k = i; k >= 4; k--) {
        for (z = 0; z < 10; z++) {
          if (player->playground[k][z] == '#') {
            player->playground[k][z] = ' ';
            player->playground[k + 1][z] = '#';
          }
        }
      }
    }
  }

  player->score += lines != 0 ? ((lines - 1) * 3) == 0 ? 3 : (lines - 1) * 3 : 0;

  return lines;
}

/**
 * Funzione utilizzata per salvare il punteggio del giocatore
 * nel file scores.svg. Vengono salvate tutte le partite di un
 * determinato giocatore, i punteggi non vengono sovrascritti.
 *
 * @param player struct del giocatore.
 */
void saveScore(player* player, game* game) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  FILE* scores;

  if (fopen(SCORE_FILE_NAME, "r") == NULL) {                    /*il file non esiste!*/
    scores = fopen(SCORE_FILE_NAME, "w+");                      /*creazione dello stream per la scrittura nel file*/
    fprintf(scores, "%s", "DATE,NICKNAME,GAMEMODE,SCORE,TETRAMINOES"); /*scrittura della prima riga di intestazione del file CSV*/
    fclose(scores);
  }

  scores = fopen(SCORE_FILE_NAME, "a"); /*TODO: salvare anche modalità di gioco? Vittorie/sconfitte?*/

  fprintf(scores, "\n%02d/%02d/%d %02d:%02d,", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); /*inserimento data*/
  fprintf(scores, "%s,", player->nickname);                                                                        /*inserimento nickname*/
  fprintf(scores, "%d,", game->gameMode);
  fprintf(scores, "%d,", player->score);                                                                           /*inserimento score*/
  fprintf(scores, "%d", player->tetraminoes);                                                                    /*inserimento numero di tetramini utilizzati*/

  fclose(scores);
}

/**
 * Funzione utilizzata per stampare a video tutti i punteggi
 * dei giocatori.
 *
 * @param query stringa da ricercare come nickname. Se NULL vengono
 *              mostrati tutti i risultati!
 */
void printScores(char* query) {
  const static char *DIVIDER = "+-------------------------------------------------------------------------------------------------------------+\n";
  FILE* scores = fopen(SCORE_FILE_NAME, "r");
  int result; /*risultato lettura*/

  if (scores == NULL) {
    printf("Non sono ancora stati salvati punteggi nel file!\n");
    return;
  }

  printf("%s", DIVIDER);

  do {
    char line[1024]; /*linea letta*/
    fgets(line, 1024, scores);

    line[strcspn(line, "\n")] = 0; /*rimuove \n alla fine*/

    printf("| %-21s ", alignText(strtok(line, ","), 20));
    printf("| %-26s ", alignText(strtok(NULL, ","), 25));
    printf("| %-16s ", alignText(strtok(NULL, ","), 15));
    printf("| %-16s ", alignText(strtok(NULL, ","), 15));
    printf("| %-16s |\n", alignText(strtok(NULL, ","), 15));

  } while (feof(scores) != 1);

  printf("%s", DIVIDER);

  fclose(scores);
}

/**
 * Funzione utilizzata per stampare il nome del giocatore
 * sopra il playground.
 *
 * @param player giocatore
 */
void printNickname(player* player) {
  int i, nick_size = strlen(player->nickname);

  for (i = 0; i < (22 - nick_size) / 2; i++)
    printf(" ");

  printf("%s", player->nickname);

  for (i = 0; i < (22 - nick_size) / 2; i++)
    printf(" ");
}

/**
 * Funzione utilizzata per stampare il campo da gioco dei giocatori.
 *
 * @param player giocatore 1
 * @param player giocatore 2
 * @param maxTetraminoes   tetramini massimi utilizzati per giocatore
 */
void printPlayground(player* player1, player* player2, int maxTetraminoes) {
  int i, j;

  clearScreen();

  printNickname(player1);

  if (player2 != NULL) {
    printf("                   ");
    printNickname(player2);
  }

  printf("\n+ - - - - - - - - - -+");
  printf(player2 == NULL ? "\n" : "                   + - - - - - - - - - -+\n");

  for (i = 4; i < 19; i++) {
    printf("|");
    for (j = 0; j < 10; j++)
      printf("%c ", player1->playground[i][j]);
    printf("|");

    if (player2 != NULL) {
      printf("                   |");
      for (j = 0; j < 10; j++)
        printf("%c ", player2->playground[i][j]);
      printf("|");
    }

    printf("\n");
  }

  printf("+ - - - - - - - - - -+");
  printf(player2 == NULL ? "\n" : "                   + - - - - - - - - - -+\n");

  printf(" SCORE: %d", player1->score);
  if (player2 == NULL)
    printf("\n");
  else
    printf("                                SCORE: %d\n", player2->score);

  printf(" TETROMINOES: %d/%d", player1->tetraminoes, maxTetraminoes);
  if (player2 == NULL)
    printf("\n");
  else
    printf("                      TETROMINOES: %d/%d\n", player2->tetraminoes, maxTetraminoes);
}