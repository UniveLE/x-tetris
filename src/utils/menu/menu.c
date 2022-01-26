#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"

/**
 * Funzione utilizzata per leggere e stampare il file, che normalmente è
 * un logo nel terminale.
 * 
 * @param file file da leggere, verrà stampato il contenuto di tale documento.
 */
void printLogos(const char* file) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(file, "r");

  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1)
    printf("  %s", line);

  printf("\n");

  fclose(fp);

  if (line)
    free(line);
}

/**
* Funzione utilizzata per stampare il menu di navigazione. 
* Questo permette all'utente di selezionare la modalità di gioco.
*/
void menu() {
  printf("\n\n  Seleziona la modalità di gioco:\n");
  printf("          1. Single player\n");
  printf("          2. Dual player\n");
  printf("          3. 1 vs CPU\n");
  printf("          4. Visualizza i punteggi\n");
  printf("          5. Quit\n\n");
}