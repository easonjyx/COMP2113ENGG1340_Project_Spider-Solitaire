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
    int moveStart = initLast

void savehistory() {

