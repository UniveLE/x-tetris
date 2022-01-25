#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../menu/menu.h"
#include "../player/player.h"
#include "../tetraminoes/tetraminoes.h"
#include "../utils.h"

/**
 * Funzione utilizzata nell'algoritmo della cpu per calcolare
 * il punteggio fatto con il tetramino in una determinata posizione.
 * Nel caso in cui il punteggio sia maggiore di quello precedente
 * allora sarà salvata la rotazione, la posizione e il punteggio.
 * Inizialmente il punteggio è 0.
 *
 *
 * @param player struct del giocatore temporaneo
 * @param position posizione del tetramino
 * @param rotation rotazione del tetramino
 * @param score
 * @param x_score
 * @param r_score
 */

void findScore(player* cpu_player, int position, int rotation, int* score, int* x_score, int* r_score) {
  conversion(cpu_player);
  cpu_player->score = 0;
  setScore(cpu_player);

  if ((cpu_player->score) > *score) {
    *score = cpu_player->score;
    *x_score = position;
    *r_score = rotation;
  }
}

/**
 * Funzione utilizzata nell'algoritmo della cpu per calcolare
 * l'altezza di un tetramino quando si trova in una determinata posizione.
 * Nel caso in cui il l'altezza sia minore di quella precedente
 * allora sarà salvata la rotazione, la posizione e l'altezza.
 * Inizialmente l'altezza è 0.
 *
 *
 * @param player struct del giocatore temporaneo
 * @param position posizione del tetramino
 * @param rotation rotazione del tetramino
 * @param height
 * @param x_height
 * @param r_height
 */

void findHeight(player* cpu_player, int position, int rotation, int* height, int* x_height, int* r_height) {
  int row = -1, i, j;
  for (i = 0; i < 19; i++) {
    for (j = 0; j < 10; j++)
      if (cpu_player->playground[i][j] == '@' && i > row) {
        row = i;
        break;
      }
  }

  if (*height < row) {
    *height = row;
    *x_height = position;
    *r_height = rotation;
  }
}

/**
 * Funzione utilizzata per spostare il tetramino alla posizione "position"
 * lungo l'asse orizzontale, e successivamente lungo quello verticale.
 *
 *
 * @param player struct del giocatore
 * @param position posizione finale del tetramino
 * @param push_end se 1 spinge il tetramino in basso
 */

void moveTo(player* cpu_player, int position, int push_end) {
  int col_actualPosition = -1, i, j;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 19; j++)
      if (cpu_player->playground[j][i] == '@' && col_actualPosition == -1) {
        col_actualPosition = i;
        break;
      }
  }

  for (i = 0; i < abs(col_actualPosition - position); i++) {
    if (col_actualPosition - position > 0)
      moveTetramino('a', cpu_player);
    if (col_actualPosition - position < 0)
      moveTetramino('d', cpu_player);
  }
  if (push_end == 1) {
    while (canMove(2, cpu_player) == 1) {
      moveTetramino('s', cpu_player);
    }
  }
}

/**
 * Funzione ricorsiva che genera tutte le possibili posizioni del tetramino
 * e ritorna la combinazione di parametri in cui il punteggio generato è più alto
 * e quella dove l'altezza è più bassa.
 *
 *
 * @param player struct del giocatore
 * @param tetramino_width larghezza del tetramino,
 * @param position posizione in cui dovrà essere spostato il tetramino,
 * @param tetris_rotation rotazione attuale del tetramino [0-4],
 * @param score punteggio più alto trovato,
 * @param x_score posizione del punteggio più alto trovato,
 * @param r_score rotazione del punteggio più alto trovato,
 * @param height altezza più bassa trovata,
 * @param x_height posizione dell'altezza più bassa trovata,
 * @param r_height rotazione dell'altezza più bassa trovata,
 */

void cpu(player* cpu_player, int tetramino_width, int position, int tetris_rotation, int* score, int* x_score,
         int* r_score, int* height, int* x_height, int* r_height) {
  int i, j;
  player temp_player;
  initPlayer(&temp_player);

  for (i = 0; i < 19; i++)
    for (j = 0; j < 10; j++)
      temp_player.playground[i][j] = cpu_player->playground[i][j];

  /*si deve far scendere il tetramino nel temp in base a x*/
  moveTo(&temp_player, position, 1);

  findHeight(&temp_player, position, tetris_rotation, height, x_height, r_height);

  findScore(&temp_player, position, tetris_rotation, score, x_score, r_score);

  ++position;

  if (position == 11 - tetramino_width) {
    int new_width = 0;
    tetris_rotation++;
    position = 0;
    rotation(cpu_player);
    /* modificare larghezza */
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 19; j++) {
        if (cpu_player->playground[j][i] == '@') {
          new_width++;
          break;
        }
      }
    }
    tetramino_width = new_width;
  }

  if (tetris_rotation == 4)
    return;

  /*printf("position: %d, rotation: %d\n", position, rotation);*/
  cpu(cpu_player, tetramino_width, position, tetris_rotation, score, x_score, r_score, height, x_height, r_height);
}

/**
 * Funzione di appoggio richiamata nel file principale. TODO: ricordarsi il nome specifico
 *
 *
 * @param player struct del giocatore
 * @param score punteggio più alto trovato,
 * @param x_score posizione del punteggio più alto trovato,
 * @param r_score rotazione del punteggio più alto trovato,
 * @param height altezza più bassa trovata,
 * @param x_height posizione dell'altezza più bassa trovata,
 * @param r_height rotazione dell'altezza più bassa trovata,
 * @return numero di righe eliminate
 */

void moveCPU(player* cpu_player, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height) {
  int tetramino_width = 0, i, j;
  player temp_player;
  initPlayer(&temp_player);

  for (i = 0; i < 19; i++)
    for (j = 0; j < 10; j++)
      temp_player.playground[i][j] = cpu_player->playground[i][j];

  for (i = 0; i < 10; i++)
    for (j = 0; j < 19; j++)
      if (cpu_player->playground[j][i] == '@') {
        tetramino_width++;
        break;
      }
  cpu(&temp_player, tetramino_width, 0, 0, score, x_score, r_score, height, x_height, r_height);
}
