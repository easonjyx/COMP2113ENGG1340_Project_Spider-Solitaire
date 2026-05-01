#include "Movecard.h"
#include "cards.h"
#include <cstring>
#include <iostream>
using namespace std;

extern card operation_cards[10][104];
bool Movecard(int initcol, int tarcol, int num) {
    if(!isValidMove(initcol, tarcol, num)) {
        cout << "Invalid Move" << endl;
        return false;
    }
    int initLast = GetLastIndex(initcol);
    int moveStart = initLast - num + 1;
    int tarLast = GetLastIndex(tarcol);
    int tarPos = tarLast + 1;

    for (int i = 0; i < num; i++) {
        operation_cards[tarcol][tarPos + i] = operation_cards[initcol][moveStart + i];
        operation_cards[initcol][moveStart + i].setEmpty();
    }
    int newTop = GetLastIndex(initcol);
    if (newTop >= 0 && !operation_cards[initcol][newTop].up)
        operation_cards[initcol][newTop].up = true;

    std::cout << "successfully moved" << std::endl;
    return true;
}



