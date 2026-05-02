#include "MoveRule.h"
#include <iostream>

extern card operation_cards[10][104];
extern bool g_sameSuitOnly;

int GetLastIndex(int col){
	int idx = 0;
    if (operation_cards[col][0].isEmpty()) return -1;
    while (idx + 1 < 104 && !operation_cards[col][idx + 1].isEmpty()) idx++;
    return idx;
}

bool isValidMove(int initcol, int tarcol, int num){
    if (initcol < 0 || initcol > 9 || tarcol < 0 || tarcol > 9 || initcol == tarcol)
        return false;

    int initLast = GetLastIndex(initcol);
    if (initLast + 1 < num) return false;
	
    int suit = operation_cards[initcol][initLast].suit;
    int rank = operation_cards[initcol][initLast].rank;
    for (int i = 1; i < num; ++i) {
        if (operation_cards[initcol][initLast - i].suit != suit ||
            operation_cards[initcol][initLast - i].rank != rank + i ||
			!operation_cards[initcol][initLast - i].up)
            return false;
    }
	
    if (!operation_cards[initcol][initLast].up) return false;
	
    int tarLast = GetLastIndex(tarcol);
    if (tarLast + num > 103) return false;

    if (tarLast == -1) return true;

    const card& tarCard = operation_cards[tarcol][tarLast];
    if (g_sameSuitOnly)
        return (tarCard.rank == operation_cards[initcol][initLast+1-num].rank + 1 && tarCard.suit == operation_cards[initcol][initLast+1-num].suit);
    else
        return (tarCard.rank == operation_cards[initcol][initLast+1-num].rank + 1);
}
