#ifndef MOVERULE_H
#define MOVERULE_H

#include "cards.h"


/*
 * Function: Find the last card in a column
 * Parameters:
 *   col - int, the column you want to find
 * Return: The index of the last card (starting from 0)
 */
int GetLastIndex(int col);

/*
 * Function: Move multiple cards at once
 * Parameters:
 *   initcol - the initial column (int)
 *   tarcol - the targeted column
 *   num - the number of cards you are going to move
 * Return: True if the move option is valid
 */
bool isValidMove(int initcol, int tarcol, int num);

#endif
