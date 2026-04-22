#include "MoveRule.h"
#include <iostream>

int GetLastIndex(int col, rec* head){
	/*
	 * Function: Find the last card in a column
	 * Parameters:
	 *   col - int, the column you want to find
	 *   *head - pointer
	 * Return: The index of the last card (starting from 0)
	 */
	int index = 0;
	if (head->cards[col][0].isEmpty())
		return -1;
	while (index+1 < 104 && !head->cards[col][index+1].isEmpty())
		index++;
	return index;
}

bool isValidMove(int initcol, int tarcol, int num, rec* head){
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
	if (initcol < 0 || initcol > 9 || tarcol < 0 || tarcol > 9 || initcol == tarcol){
		return false;
	}

	// Check for the initial col has more than num cards
	int initidx = GetLastIndex(initcol, head);
	if (initidx + 1 < num)
		return false;
	
	// Check for the moved cards are the same suit
	int suit = head->cards[initcol][initidx].suit;
	int rank = head->cards[initcol][initidx].rank;
	for (int i = 1; i < num; i++){
		if (head->cards[initcol][initidx-i].suit != suit || head->cards[initcol][initidx-i].rank != rank - i)
			return false;
	}

	// Check for valid move
	int taridx = GetLastIndex(tarcol, head);
	if (taridx == -1)
		return true;
	return (head->cards[tarcol][taridx].rank == rank + 1);
}
