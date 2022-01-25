/**
 * @file cpu.h
 * @date 18/10/2021
 * @author Lorenzo Vaccher & Elia Coro'
 * @brief Libreria per la gestione della modalità 1 VS CPU. Questa libreria implementa una determinata strategia per l'implementazione della CPU.
 */

#ifndef _CPU_H
#define _CPU_H

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
void findScore(player* cpu_player, int position, int rotation, int* x_height, int* r_height);
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
void findHeight(player* cpu_player, int position, int rotation, int* x_score, int* r_score);
/**
 * Funzione utilizzata per spostare il tetramino alla posizione "position"
 * lungo l'asse orizzontale, e successivamente lungo quello verticale.
 *
 *
 * @param player struct del giocatore
 * @param position posizione finale del tetramino
 * @param push_end se 1 spinge il tetramino in basso
 */
char* moveTo(player* cpu_player, int position, int push_end);
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
void cpu(player *player, int tetramino_width, int position, int rotation, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);
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
void moveCPU(player* cpu_player, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);

#endif