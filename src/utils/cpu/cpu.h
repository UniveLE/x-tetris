/**
 * @file cpu.h
 * @date 18/10/2021
 * @author Lorenzo Vaccher & Elia Coro'
 * @brief Libreria per la gestione della modalità 1 VS CPU. Questa libreria implementa una determinata strategia per l'implementazione della CPU.
 */

#ifndef _CPU_H
#define _CPU_H

void findScore(player* cpu_player, int position, int rotation, int* x_height, int* r_height);
void findHeight(player* cpu_player, int position, int rotation, int* x_score, int* r_score);
char* moveTo(player* cpu_player, int position, int push_end);
void cpu(player *player, int tetramino_width, int position, int rotation, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);
void moveCPU(player* cpu_player, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);

#endif