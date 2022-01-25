#ifndef _CPU_H
#define _CPU_H

void findScore(player* cpu_player, int position, int rotation, int* x_height, int* r_height);
void findHeight(player* cpu_player, int position, int rotation, int* x_score, int* r_score);
char* moveTo(player* cpu_player, int position, int push_end);
void cpu(player *player, int tetramino_width, int position, int rotation, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);
void moveCPU(player* cpu_player, int* score, int* x_score, int* r_score, int* height, int* x_height, int* r_height);

#endif