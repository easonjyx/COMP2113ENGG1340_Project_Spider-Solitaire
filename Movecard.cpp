#include "Movecard.h"
#include "cards.h"
#include <cstring>
#include <iostream>
using namespace std;
bool Movecard(int initcol, int tarcol, int num, rec* head) {
    if(!isValidMove(initcol, tarcol, num, head)) {
        std::cout << "Unvalid Move" << std::endl;
        return false;
    }
    int initLast = GetLastIndex(initcol, head):
    int moveStart = initLast - num + 1;
    int tarLast = GetLastIndex(intcol, head);
    int tarPos = tarLast + 1;

    for (int i = 0; i < num; i++) {
        head->cards[tarcol][tarPos + i] = head->cards[initcol][moveStart + i]
        head->cards[initcol][moveStart + i].setEmpty();
    }
    std::cout << "successfully moved" << std::endl;
    return true;
}



