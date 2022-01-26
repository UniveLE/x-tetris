#include <stdio.h>
#include <stdlib.h>

#include "tetraminoes.h"
#include "../../game.h"
#include "../player/player.h"
#include "../matrix/matrix.h"

/**
 * Array contente tutti i tetramini
 */
char tetraminoes[7][4][4] = {
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'*', '*', '*', '*'},
        {' ', ' ', ' ', ' '}
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'*', ' ', ' ', ' '},
        {'*', '*', '*', '*'}
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', '*'},
        {'*', '*', '*', '*'}
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'*', '*', ' ', ' '},
        {'*', '*', ' ', ' '},
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', '*', '*', ' '},
        {'*', '*', ' ', ' '},
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', '*', ' ', ' '},
        {'*', '*', '*', ' '},
    },
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'*', '*', ' ', ' '},
        {' ', '*', '*', ' '},
    }
  };

/**
 * Funzione utilizzata per convertire il carattere
 * del tetramino che l'utente sta muovendo ('@') con il
 * carattere che indica i tetramini posizionati ('#')
 * 
 * @param player struct del giocatore
 */
void conversion(player* player) {
  int i, j;
  for (j = 0; j < 10; j++)
    for (i = 0; i < 19; i++)
      if (player->playground[i][j] == '@')
        player->playground[i][j] = '#';
}

/**
 * Funzione utilizzata per muovere il tetramino data una
 * direzione. Questa richiamerà move specificando la direazione.
 * 
 * @param direction direzione del movimento. Parametro espresso
 *                  sotto forma di char:
 *                    - a -> sinistra
 *                    - d -> destra
 *                    - s -> basso
 *                    - spazio -> rotazione
 * @return int stato del movimento. Vedere return della funzione move.
 */
int moveTetramino(char direction, player* player) {
  int result = 0;
  switch (direction) {
    case DIRECTION_P1_RIGHT:
    case DIRECTION_P2_RIGHT:
      result = move(3, player);
      break;
    case DIRECTION_P1_LEFT:
    case DIRECTION_P2_LEFT:
      result = move(1, player);
      break;
    case DIRECTION_P1_DOWN:
    case DIRECTION_P2_DOWN:
      result = move(2, player);
      break;
    case DIRECTION_P1_ROTATE:
    case DIRECTION_P2_ROTATE:
      result = rotation(player);
      break;
  }
  return result;
}

/**
 * Funzione utilizzata per ruotare il tetramino all'interno di un playground
 *
 * @param player struct del giocatore
 *
 * @return 1 se è stato ruotato
 *         0 se non è stato possibile ruotare
 */
int rotation(player* player) {
    int tetramino_row_pos, tetramino_col_pos, size, pieces;
    int i, j;

    /* richiamata la funzione che ritorna la sottomatrice contente il tetramino */
    char* sub_matrix = getSubMatrix(player->playground, &tetramino_row_pos, &tetramino_col_pos, &size);

    /*creazione dal campo temporaneo*/
    char* temp_playground = (char*) malloc(sizeof(char) * 10 * 19);
    for (i = 0; i < 19; i++)
        for (j = 0; j < 10; j++)
            temp_playground[i * 19 + j] = player->playground[i][j] == '@' ? ' ' : player->playground[i][j];

    /* rotazione della sottomatrice */
    rotateMatrix(sub_matrix, size);

    /*inserimento matrice ruotata nel campo temporaneo.
     * Se si tenta di scrivere in una cella contente un # 
     * allora la funzione ritorna 0
    */
    for (i = tetramino_row_pos; i < size + tetramino_row_pos; i++) {
        for (j = tetramino_col_pos; j < size + tetramino_col_pos; j++) {
            if (temp_playground[i * 19 + j] == '#')
                return 0; /*il movimento non è consentito*/
            else
                temp_playground[i * 19 + j] = sub_matrix[(i-tetramino_row_pos) * size + (j-tetramino_col_pos)];
        }
    }

    /*inserimento dal campo temporaneo al campo del giocatore*/
    for (i = 0; i < 19; i++)
        for (j = 0; j < 10; j++)
            player->playground[i][j] = temp_playground[i * 19 + j];

    free(temp_playground);
    free(sub_matrix);

    return 1; /*il pezzo è stato ruotato correttamente*/
}


/**
 * Funzione utilizzata per controllare se un pezzo
 * può muoversi verso una determinata posizione. 
 * 
 * @param direction indica la direzione del pezzo da
 *                  muovere. In particolare:
 *                            1: sinistra
 *                            2: giù
 *                            3: destra
 * @param player struct del giocatore
 * 
 * @return 1 se è consentito il movimento
 *         0 se non è consentito il movimento
 */
int canMove(int direction, player *player) {
  int i, j;
  for (i = 0; i < 19; i++) {
    for (j = 0; j < 10; j++) {
      if (player->playground[i][j] == '@') {
        switch (direction) {
          case 1:
            if (j == 0 || player->playground[i][j - 1] == '#')
              return 0;
            continue;
          case 2:
            if (i == 18 || player->playground[i + 1][j] == '#')
              return 0;
            continue;
          case 3:
            if (j == 9 || player->playground[i][j + 1] == '#')
              return 0;
            continue;
        }
      }
    };
  }
  return 1;
}

/**
  * Funzione utilizzata per muovere un tetramino in 
  * una determinata direzione.
  *
  * @param direction indica la direzione del tetramino da
  *                  muovere. In particolare:
  *                            1: sinistra
  *                            2: giù
  *                            3: destra
  * @param player struct del giocatore
  *
  * @return 0 se non può muoversi
  *         1 se si è mosso e può ancora muoversi
  *         2 se si è mosso ma non può più muoversi
  *
  */
int move(int direction, player *player) {
  if (canMove(direction, player)) {
    /*È stato creato un ciclo for differente per la direzione dx poichè con il ciclo
         realizzato nell'else verrebbe eliminato parte del tetramino poichè il ciclo comincia
         dall'ultima cella in basso a sinistra della matrice*/
    if (direction == 3) {
      int i, j;
      for (j = 9; j >= 0; j--) {
        for (i = 0; i < 19; i++) {
          if (player->playground[i][j] == '@') {
            player->playground[i][j] = ' ';
            player->playground[i][j + 1] = '@';
          }
        }
      }
    } else {
      int i, j;
      for (j = 0; j < 10; j++) {
        for (i = 19; i >= 0; i--) {
          if (player->playground[i][j] == '@') {
            player->playground[i][j] = ' ';
            switch (direction) {
              case 1:
                player->playground[i][j - 1] = '@';
                continue;
              case 2:
                player->playground[i + 1][j] = '@';
                continue;
            }
          }
        }
      }
    }
    if (canMove(2, player))
      return 1;
    else
      return 2; /*il pezzo è "caduto"*/
  } else
    return 0;
}

/**
 * Questa funzione inserisce il tetramino nel playground
 *
 * @param int* indirizzo del playground
 * @param int* indirizzo dell'array contenente il tetramino scelto
 *
 * */
int insertTetromino(player *player, game* game) {
  char* tetramino = &tetraminoes[game->tetraminoes[player->tetraminoes]][0][0];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (tetramino[4 * i + j] == '*')
        player->playground[i][j + 3] = '@';
    }
  }
}
