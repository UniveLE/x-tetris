#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

struct termios save;

/**
 * Funzione utilizzata per pulire il terminale.
 */
void clearScreen() {
  printf("\e[1;1H\e[2J");
}

char* alignText(char* text, int total_size) {
  char* new_text = (char*)malloc(sizeof(char) * total_size);
  size_t i, index = 0, size = strlen(text);

  for (i = 0; i < (total_size - size) / 2; i++)
    new_text[index++] = ' ';
  
  for (i = 0; i < size; i++)
    new_text[index++] = text[i];

  for (i = 0; i < (total_size - size) / 2; i++)
    new_text[index++] = ' ';

  return new_text;
}

void setupIO() {
  /*       
      The termios functions describe a general terminal interface that
       is provided to control asynchronous communications ports.
*/
  struct termios custom;
  int fd = fileno(stdin);
  tcgetattr(fd, &save);
  custom = save;
  /*
  ICANON: In canonical input processing mode, terminal input is processed in lines terminated by newline ('\n'), EOF, or EOL characters. 
  No input can be read until an entire line has been typed by the user.
  ECHO: input characters
  */
  custom.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(fd, TCSANOW, &custom);
  /*
   This means that specifying O_NONBLOCK in open sets nonblocking I/O mode
  */
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

void cleanupIO() {
  tcsetattr(fileno(stdin), TCSANOW, &save);
}
