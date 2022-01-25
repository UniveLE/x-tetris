/**
 * @file matrix.h
 * @date 18/10/2021
 * @author Lorenzo Vaccher & Elia Coro'
 * @brief Libreria per la gestione delle matrici.
 */

#ifndef _MATRIX_H
#define _MATRIX_H

char* getSubMatrix(char matrix[19][10], int *x, int *y, int* dimension);
void rotateMatrix(char *sub_matrix, int dimension);

#endif