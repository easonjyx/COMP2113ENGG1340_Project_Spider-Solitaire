#include "Movecard.h"
#include "cards.h"
#include <cstring>
#include <iostream>
using namespace std;



// Global card table
extern card operation_cards[10][104];



// Move cards from one column to another
bool Movecard(int initcol, int tarcol, int num) {
    // Check if the move follows the game rules
    if(!isValidMove(initcol, tarcol, num)) {
        cout << "Invalid Move" << endl;
        return false;
    }
    // Get the last card position in the original column
    int initLast = GetLastIndex(initcol);
    // Find the first card to move
    int moveStart = initLast - num + 1;
    // Get the last card position in the target column
    int tarLast = GetLastIndex(tarcol);
    // The position to place the moved cards
    int tarPos = tarLast + 1;

    // Move the cards one by one
    for (int i = 0; i < num; i++) {
        // Copy card to target column
        operation_cards[tarcol][tarPos + i] = operation_cards[initcol][moveStart + i];
        // Clear the original position (set to empty)
        operation_cards[initcol][moveStart + i].setEmpty();
    }
    // Get the new top card of the original column
    int newTop = GetLastIndex(initcol);
    // If there is a face-down card, turn it face up
    if (newTop >= 0 && !operation_cards[initcol][newTop].up)
        operation_cards[initcol][newTop].up = true;

    std::cout << "successfully moved" << std::endl;// Show success message
    return true;
}




