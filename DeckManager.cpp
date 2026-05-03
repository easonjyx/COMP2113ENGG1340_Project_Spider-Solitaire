#include "DeckManager.h"
#include "GameHistory.h"
#include "MoveRule.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <iostream>

int remainingDeck[104];
int remainingCount = 0;
int completedSets = 0;

// Function: Clears all cards on the game board and sets them to empty state
// Input: None
// Output: None

static void clearBoard() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 104; ++j)
            operation_cards[i][j].setEmpty();
}

// Function: Generates a full deck of 104 standard playing cards (2 copies of 52 unique cards)
// Input: deck - Array to store the generated raw card data
// Output: None

static void generateRawDeck(int deck[104]) {
    int idx = 0;
    for (int copy = 0; copy < 2; ++copy) {
        for (int suit = 1; suit <= 4; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                deck[idx++] = (rank << 4) | suit; // 高4位rank，低4位suit
            }
        }
    }
}

// Function: Adjusts the card deck based on selected difficulty (number of suits)
// Input: deck - Array of card data to be modified
//        suits - Number of suits to use for difficulty (1 or 2)
// Output: None

static void applyDifficulty(int deck[104], int suits) {
    if (suits == 1) {
        for (int i = 0; i < 104; ++i) {
            int rank = deck[i] >> 4;
            deck[i] = (rank << 4) | 1;
        }
    } else if (suits == 2) {
        int newDeck[104];
        int idx = 0;

        for (int suit = 1; suit <= 2; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                newDeck[idx++] = (rank << 4) | suit;
            }
        }
        for (int suit = 1; suit <= 2; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                newDeck[idx++] = (rank << 4) | suit;
            }
        }
        memcpy(deck, newDeck, 104 * sizeof(int));
    }
}

static void shuffleDeck(int deck[104]) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 103; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}
// Function: Shuffles the card deck randomly using current time as seed
// Input: deck - Array of card data to be shuffled
// Output: None
void initNewGame(int difficultySuits) {
    clearBoard();
    
    int rawDeck[104];
    generateRawDeck(rawDeck);
    applyDifficulty(rawDeck, difficultySuits);
    shuffleDeck(rawDeck);

    int cardIdx = 0;
    for (int col = 0; col < 10; ++col) {
        int numCards = (col < 4) ? 5 : 4;
        for (int i = 0; i < numCards; ++i) {
            int val = rawDeck[cardIdx++];
            operation_cards[col][i].rank = val >> 4;
            operation_cards[col][i].suit = val & 0xF;
            operation_cards[col][i].up = (i == numCards - 1);
        }
    }
    remainingCount = 104 - cardIdx;
    for (int i = 0; i < remainingCount; ++i) {
        remainingDeck[i] = rawDeck[cardIdx + i];
    }
    completedSets = 0;
}

// Function: Deals one new card to each column from the remaining deck
// Input: None
// Output: None

void dealNextRow() {
    if (remainingCount < 10) {
        std::cout << "No more cards to deal!\n";
        return;
    }
    //rec* dummyHead = nullptr;

    for (int col = 0; col < 10; ++col){
        int lastIdx = GetLastIndex(col);
        int newPos=lastIdx + 1;
        int val =remainingDeck[--remainingCount];
        operation_cards[col][newPos].rank = val >> 4;
        operation_cards[col][newPos].suit = val & 0xF;
        operation_cards[col][newPos].up = true;
    }
}

// Function: Gets the number of remaining cards in the deck
// Input: None
// Output: The count of remaining undealt cards
int getRemainingCardCount(){
    return remainingCount;
}

// Function: Gets the number of completed card sets in the game
// Input: None
// Output: The total number of completed sets
int getCompletedSets(){
    return completedSets;
}

// Function: Resets game state variables for a fresh start
// Input: None
// Output: None
void resetGame(){
    completedSets = 0;
    remainingCount = 0;
}
// Function: Increases the count of completed card sets
// Input: delta - Value to add to completed sets count
// Output: None
void incrementCompletedSets(int delta) {
    completedSets += delta;
}
