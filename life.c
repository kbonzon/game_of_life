/**
 * @file life.c
 * @brief The function definitions used in gl.c
 * @details All the function definitions
 * @author Tim Bonzon
 * @date 2022-04-15
 * @todo Implement a GUI
 * @bug Program currently does not get me a job at Google
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "life.h"


/**
 * @brief Allocates the space for a matrix and initializes all values to 0
 * 
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @return the double-pointer to the matrix
 */
unsigned char **init_matrix(int row, int col)
{
        unsigned char **matrix = malloc(sizeof(int *) * row);
        for (int i = 0; i < row; i++)
        {
                *(matrix + i) = malloc(sizeof(unsigned char) * col);
                if ((matrix + i) == NULL)
                        exit(1000);
        }

        for (int k = 0; k < row; k++)
        {
                for (int j = 0; j < col; j++)
                {
                        matrix[k][j] = 0;
                }
        }

        return matrix;
}

/**
 * @brief Set a column of the matrix to 1. Useful for debugging
 * 
 * @param matrix the matrix to set
 * @param row the numbr of rows
 * @param n_col the columns to set to 1
 * @return the modified matrix pointer
 */
unsigned char **set_col(unsigned char **matrix, int row, int n_col)
{
        for (int n = 0; n < row; n++)
        {
                matrix[n][n_col] = 1;
        }
        return matrix;
}

/**
 * @brief Set the row of a matrix to 1
 * 
 * @param matrix the matrix to modify
 * @param row the row to set to 1
 * @param n_col the number of columns in the matrix
 * @return the pointer of the modifed matrix
 */
unsigned char **set_row(unsigned char **matrix, int row, int n_col)
{
        for (int n = 0; n < n_col; n++)
        {
                matrix[row][n] = 1;
        }
        return matrix;
}


/**
 * @brief Get the value of a cell in klein bottle space. Only used by the
 * "set_generation_klein" function
 * 
 * @param matrix the matrix that owns the cell
 * @param x the x location of it
 * @param y the y location of it
 * @param w the width of the matrix
 * @param h the height of the matrix
 * @return the value at the specified x and y position
 */
int get_cell(unsigned char **matrix, int x, int y, int w, int h)
{

        y = ((y % h) + h) % h;
        x = ((x % (2 * w)) + (2 * w)) % (2 * w);
        if (x >= w)
        {
                x %= w;
                y = h - y - 1;
        }
        return matrix[x][y];
}

/**
 * @brief Set the value of a cell in klein bottle space. Only used by the
 * "set_pattern" function
 * 
 * @param matrix the matrix that owns the cell
 * @param x the x location of the cell
 * @param y the y location of the cell
 * @param w the width of the matrix
 * @param h the height of the matrix
 * @param n the value to set at the specified x and y
 */
void set_cell(unsigned char **matrix, int x, int y, int w, int h, int n)
{
        y = ((y % h) + h) % h;
        x = ((x % (2 * w)) + (2 * w)) % (2 * w);
        if (x >= w)
        {
                x %= w;
                y = h - y - 1;
        }
        matrix[x][y] = n;
}

/**
 * @brief Sets a given cell to 1 based on the type of border being used.
 * This is only used for initializing the pattern after the pattern file has been
 * read.
 * 
 * @param g 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param border 
 */
void set_pattern(unsigned char **g, int x, int y, int w, int h, char border)
{
        if (border == 'h')
        {
                x = abs(x);
                y = abs(y);
                g[x][y] = 1;
        }
        if (border == 't')
        {
                g[(x + w) % w][(y + h) % h] = 1;
        }
        if (border == 'k')
        {
                set_cell(g, x, y, w, h, 1);
        }
}

/**
 * @brief Gets the number of neighbors at a specified x and y.
 * This is only in hedge-border space.
 * 
 * @param g1 the matrix to be examined
 * @param i the x index
 * @param k the y index
 * @return the number of neighbors at the given index
 */
int get_num_neighbors(unsigned char **g1, int i, int k)
{
        int neighbors = 0;
        if (g1[i + 1][k] == 1)
                neighbors++;
        if (g1[i - 1][k] == 1)
                neighbors++;
        if (g1[i][k + 1] == 1)
                neighbors++;
        if (g1[i][k - 1] == 1)
                neighbors++;
        if (g1[i + 1][k + 1] == 1)
                neighbors++;
        if (g1[i - 1][k + 1] == 1)
                neighbors++;
        if (g1[i + 1][k - 1] == 1)
                neighbors++;
        if (g1[i - 1][k - 1] == 1)
                neighbors++;
        return neighbors;
}

/**
 * @brief Set the generation of a hedge-border generation.
 * 
 * @param g1 the first generation
 * @param g2 the next generation
 * @param m_h the height of the array
 * @param m_w the width of the array
 * @param i the starting x value (vesigal, not used atm)
 * @param k the starting y value (vestigal, not used atm)
 * @return the pointer of the next generation 
 */
unsigned char **set_generation_hedge(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k)
{
        for (int i = 1; i < m_w - 1; i++)
        {
                for (int k = 1; k < m_h - 1; k++)
                {
                        int neighbors = 0;
                        if (g1[i][k] == 1)
                        {

                                neighbors = get_num_neighbors(g1, i, k);

                                if (neighbors > 3)
                                {
                                        g2[i][k] = 0;
                                }
                                if (neighbors < 2)
                                {
                                        g2[i][k] = 0;
                                }
                                if (neighbors == 2 || neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                        }
                        else
                        {
                                neighbors = get_num_neighbors(g1, i, k);

                                if (neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                                else
                                {
                                        g2[i][k] = 0;
                                }
                        }
                }
        }

        return g2;
}

/**
 * @brief Get the number of neighbors at a given location in a matrix with
 *  the torus border
 * 
 * @param g1 the matrix to search
 * @param i the x location
 * @param k the y location
 * @param n_rows the number of rows in the matrix
 * @param n_col the number of columns in the matrix
 * @return the number of neighbors at the given x and y position
 */
int get_num_neighbors_torus(unsigned char **g1, int i, int k, int n_rows, int n_col)
{
        int neighbors = 0;
        if (g1[(i + 1 + n_col) % n_col][k] == 1)
                neighbors++;
        if (g1[(i - 1 + n_col) % n_col][k] == 1)
                neighbors++;
        if (g1[i][(k + 1 + n_rows) % n_rows] == 1)
                neighbors++;
        if (g1[i][(k - 1 + n_rows) % n_rows] == 1)
                neighbors++;
        if (g1[(i + 1 + n_col) % n_col][(k + 1 + n_rows) % n_rows] == 1)
                neighbors++;
        if (g1[(i - 1 + n_col) % n_col][(k + 1 + n_rows) % n_rows] == 1)
                neighbors++;
        if (g1[(i + 1 + n_col) % n_col][(k - 1 + n_rows) % n_rows] == 1)
                neighbors++;
        if (g1[(i - 1 + n_col) % n_col][(k - 1 + n_rows) % n_rows] == 1)
                neighbors++;

        return neighbors;
}

/**
 * @brief Get the number of neighbors at a given location in a matrix with
 *  the klein border
 * 
 * @param g1 the matrix to search
 * @param x the x location
 * @param y the y location
 * @param n_rows the number of rows in the matrix
 * @param n_col the number of columns in the matrix
 * @return the number of neighbors at the given x and y position
 */
int get_num_neighbors_klein(unsigned char **g1, int x, int y, int n_rows, int n_col)
{
        int neighbors = 0;

        neighbors += get_cell(g1, (x + 1), y, n_col, n_rows);
        neighbors += get_cell(g1, (x - 1), y, n_col, n_rows);
        neighbors += get_cell(g1, (x), y + 1, n_col, n_rows);
        neighbors += get_cell(g1, x, y - 1, n_col, n_rows);
        neighbors += get_cell(g1, x - 1, y - 1, n_col, n_rows);
        neighbors += get_cell(g1, x + 1, y - 1, n_col, n_rows);
        neighbors += get_cell(g1, x - 1, y + 1, n_col, n_rows);
        neighbors += get_cell(g1, x + 1, y + 1, n_col, n_rows);
        return neighbors;
}

/**
 * @brief Set the generation of a torus-border generation.
 * 
 * @param g1 the first generation
 * @param g2 the next generation
 * @param m_h the height of the array
 * @param m_w the width of the array
 * @param i the starting x value (vesigal, not used atm)
 * @param k the starting y value (vestigal, not used atm)
 * @return the pointer of the next generation 
 */
unsigned char **set_generation_torus(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k)
{
        int neighbors = 0;
        neighbors = 0;
        for (i = 0; i < m_w; i++)
        {
                for (k = 0; k < m_h; k++)
                {
                        neighbors = 0;
                        if (g1[i][k] == 1)
                        {

                                neighbors = get_num_neighbors_torus(g1, i, k, m_h, m_w);

                                if (neighbors > 3)
                                {
                                        g2[i][k] = 0;
                                }
                                if (neighbors < 2)
                                {
                                        g2[i][k] = 0;
                                }
                                if (neighbors == 2 || neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                        }
                        else
                        {
                                neighbors = get_num_neighbors_torus(g1, i, k, m_h, m_w);

                                if (neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                                else
                                {
                                        g2[i][k] = 0;
                                }
                        }
                }
        }

        return g2;
}

/**
 * @brief Set the generation of a klein-border generation.
 * 
 * @param g1 the first generation
 * @param g2 the next generation
 * @param m_h the height of the array
 * @param m_w the width of the array
 * @param i the starting x value (vesigal, not used atm)
 * @param k the starting y value (vestigal, not used atm)
 * @return the pointer of the next generation 
 */
unsigned char **set_generation_klein(unsigned char **g1, unsigned char **g2, int m_h, int m_w, int i, int k)
{

        int neighbors = 0;
        for (i = 0; i < m_w; i++)
        {
                for (k = 0; k < m_h; k++)
                {
                        neighbors = 0;
                        if (g1[i][k] == 1)
                        {
                                // if this cell is alive
                                neighbors = get_num_neighbors_klein(g1, i, k, m_h, m_w);

                                if (neighbors == 2 || neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                                if (neighbors > 3)
                                {
                                        g2[i][k] = 0;
                                }
                                if (neighbors < 2)
                                {
                                        g2[i][k] = 0;
                                }
                        }
                        else
                        {
                                neighbors = get_num_neighbors_klein(g1, i, k, m_h, m_w);
                                if (neighbors == 3)
                                {
                                        g2[i][k] = 1;
                                }
                                else
                                {
                                        g2[i][k] = 0;
                                }
                        }
                }
        }

        return g2;
}

/**
 * @brief Free the memory holding the matrix
 * 
 * @param g the matrix to free
 * @param n_rows the number of rows
 */
void free_matrix(unsigned char **g, int n_rows)
{
        for (int i = 0; i < n_rows; i++)
        {
                free(*(g + i));
        }
        free(g);
}