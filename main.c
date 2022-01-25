/**
 * @file main.c
 * @author Lorenzo Vaccher & Elia Coro'
 * @date 25/11/2021
 * @mainpage main
 *
 * @section intro_sec Introduzione
 * Il progetto X-Tetris si presenta come una versione rivisitata del classico gioco Tetris. Il gioco prevede tre modalità diverse: giocatore singolo, multigiocatore e giocatore contro computer; ciascuna con tre diversi livelli di difficoltà: semplice, medio e difficile. Ciò che differenzia le tre tipologie di difficoltà è la velocità con cui il tetramino cade.
 * Durante la fase di sviluppo, non sono state utilizzate librerie esterne avanzate (grafica, algoritmi particolari ecc); tutto il codice è stato interamente scritto dai membri del gruppo sopracitati.
 * Altra funzionalità particolare aggiunta è il salvataggio dei punteggi degli utenti. Infatti, al termine di ogni partita il punteggio ottenuto dal giocatore verrà salvato in un file csv così da permettere di visualizzare lo storico di tutte le partite, con relativi nickname, punteggi, modalità di gioco e la data della partita.
 * I comandi utilizzati per muovere il tetramino, sono quelli normalmente utilizzati nei videogiochi classici: “w” per ruotare il tetramino, “s” per muovere il tetramino verso il basso, “a” verso sinistra e “d” verso destra. Nella modalità multiplayer (1vs1) il giocatore con il campo da gioco posizionato a destra dovrà utilizzare le frecce direzionali per muovere il tetramino. Queste utilizzano la stessa logica dei tasti precedentemente analizzati.
 *
 * @section install_sec Utilizzo
 * Di seguito sono riportare le fasi utili all'installazione dei Software utilizzati
 * per eseguire il programma X-Tetris.
 * @subsection step1 Step 1: Compilazione
 * Per compilare il gioco X-Tetris è sufficiente digitare, tramite il terminale, nella directory principale `make`. Facendo così si andrà a generare l'eseguibile "tetris"
 * @subsection step2 Step 2: Esecuzione
 * Per eseguire il programma basterà digitare nel terminale `./tetris`
 */

#include "./src/game.h"
#include "main.h"

/**
  * Funzione principale del progetto.
  *
  * @return stato del gioco
  */
int main() {
  startGame();
  return 0;
}
