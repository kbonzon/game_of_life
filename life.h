/**
 * @file life.h
 * @author Tim Bonzon
 * @brief The prototypes of all functions used in gl.c
 * @date 2022-04-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LIFE_H_
#define LIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

unsigned char **init_matrix(int rows, int col);
unsigned char **set_col(unsigned char **matrix, int row, int n_col);
unsigned char **set_row(unsigned char **matrix, int row, int n_col);
int get_cell(unsigned char **matrix, int x, int y, int w, int h);
int get_num_neighbors(unsigned char **g1, int i, int k);
int get_num_neighbors_torus(unsigned char **g1, int i, int k, int n_row, int n_col);
int get_num_neighbors_klein(unsigned char **g1, int x, int y, int n_row, int n_col);
unsigned char **set_generation_hedge(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k);
unsigned char **set_generation_torus(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k);
unsigned char **set_generation_klein(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k);
void set_cell(unsigned char **matrix, int x, int y, int w, int h, int n);
void set_pattern(unsigned char **g, int x, int y, int w, int h, char border);
void free_matrix(unsigned char **g, int n_row);

#endif
