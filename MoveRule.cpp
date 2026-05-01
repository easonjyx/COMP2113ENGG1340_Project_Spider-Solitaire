#include "MoveRule.h"
#include <iostream>

extern card operation_cards[10][104];
extern bool g_sameSuitOnly;

int GetLastIndex(int col){
	int idx = 0;
    if (operation_cards[col][0].isEmpty()) return -1;
    while (idx + 1 < 104 && !operation_cards[col][idx + 1].isEmpty()) idx++;
    return idx;
	/*
	 * Function: Find the last card in a column
	 * Parameters:
	 *   col - int, the column you want to find
	 *   *head - pointer
	 * Return: The index of the last card (starting from 0)
	 */
}

bool isValidMove(int initcol, int tarcol, int num){
	/*
	 * Function: Move multiple cards at once
	 * Parameters:
	 *   initcol - the initial column (int)
	 *   tarcol - the targeted column
	 *   num - the number of cards you are going to move
	 *   head - pointer
	 * Return: True if the move option is valid 
	 */

	// Check for the input column index is valid
    if (initcol < 0 || initcol > 9 || tarcol < 0 || tarcol > 9 || initcol == tarcol)
        return false;

    int initLast = GetLastIndex(initcol);
    if (initLast + 1 < num) return false;
	
    int suit = operation_cards[initcol][initLast].suit;
    int rank = operation_cards[initcol][initLast].rank;
    for (int i = 1; i < num; ++i) {
        if (operation_cards[initcol][initLast - i].suit != suit ||
            operation_cards[initcol][initLast - i].rank != rank - i ||
			!operation_cards[initcol][initLast - i].up)
            return false;
    }
	if (!operation_cards[initcol][initLast].up) return false;
	
    int tarLast = GetLastIndex(tarcol);
    if (tarLast == -1) return true;

    const card& tarCard = operation_cards[tarcol][tarLast];
    if (g_sameSuitOnly)
        return (tarCard.rank == rank + 1 && tarCard.suit == suit);
    else
        return (tarCard.rank == rank + 1);
}
