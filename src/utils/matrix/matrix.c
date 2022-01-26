#include <stdio.h>
#include <stdlib.h>

/**
 * Funzione utilizzata per prendere la sottomatrice
 * contenente il tetramino.
 *
 *
 * @param matrix matrice contente il playground
 * @param x posizione x della sottomatrice,
 * @param y posizione y della sottomatrice,
 * @param dimension dimensione della sottomatrice,
 *
 * @return sottomatrice trovata
 */

char *getSubMatrix(char matrix[19][10], int *x, int *y, int *dimension) {
  int size = 0, i, j, count = 0;
  char *new_matrix;

  *x = -1;
  *y = -1;

  for (i = 0; i < 19; i++) {
    for (j = 0; j < 10; j++) {
      if (matrix[i][j] == '@') {
        if (*x == -1)
          *x = i;
        count++;
        break;
      }
    }
    if (count > size)
      size = count;
  }

  /* verifica n. @ nelle colonne*/
  count = 0;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 19; j++) {
      if (matrix[j][i] == '@') {
        if (*y == -1)
          *y = i;
        count++;
        break;
      }
    }
    if (count > size)
      size = count;
  }

  *dimension = size;
  new_matrix = (char *)malloc(sizeof(char) * size * size);

  if (*x > (19 - size))
    *x = *x - (*x % (19 - size));

  if (*y > 7)
    *y = *y - (*y % (10 - size));

  for (i = *x; i < *x + size; i++) {
    for (j = *y; j < *y + size; j++) {
      new_matrix[(i - *x) * size + (j - *y)] = matrix[i][j] == '@' ? '@' : ' ';
    }
  }
  return new_matrix;
}
/**
 * Funzione che ruota la matrice contenete il tetramino.
 *
 *
 * @param sub_matrix matrice contenente il tetramino da ruotare
 * @param dimension dimensione della matrice
 *
 **/
void rotateMatrix(char *sub_matrix, int dimension) {
  int i, j;
  for (i = 0; i < dimension / 2; i++) {
    for (j = i; j < dimension - i - 1; j++) {
      char temp = sub_matrix[(i * dimension) + j];
      sub_matrix[(i * dimension) + j] = sub_matrix[(j * dimension) + dimension - 1 - i];
      sub_matrix[(j * dimension) + dimension - 1 - i] = sub_matrix[((dimension - 1 - i) * dimension) + dimension - 1 - j];
      sub_matrix[((dimension - 1 - i) * dimension) + dimension - 1 - j] = sub_matrix[((dimension - 1 - j) * dimension) + i];
      sub_matrix[((dimension - 1 - j) * dimension) + i] = temp;
    }
  }
}
