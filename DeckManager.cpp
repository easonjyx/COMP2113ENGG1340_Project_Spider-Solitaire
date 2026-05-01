#include "DeckManager.h"
#include "GameHistory.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <iostream>

int remainingDeck[104];
int remainingCount = 0;
int completedSets = 0;


static void clearBoard() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 104; ++j)
            operation_cards[i][j].setEmpty();
}


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

static void applyDifficulty(int deck[104], int suits) {
    if (suits == 1) {
        for (int i = 0; i < 104; ++i) {
            int rank = deck[i] >> 4;
            deck[i] = (rank << 4) | 1;
        }
    } else if (suits == 2) {
        int newDeck[104];
        int newIdx = 0;
        for (int i = 0; i < 104; ++i) {
            int suit = deck[i] & 0xF;
            if (suit == 1 || suit == 2) {
                newDeck[newIdx++] = deck[i];
            }
        }
        for (int i = 0; newIdx < 104; ++i) {
            newDeck[newIdx++] = newDeck[i % newIdx];
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

void dealNextRow() {
    if (remainingCount < 10) {
        std::cout << "No more cards to deal!\n";
        return;
    }
    //rec* dummyHead = nullptr;

    for (int col = 0; col < 10; ++col){
        int lastIdx = -1;
        for(int i = 0; i < 104; ++i){
            if(!operation_cards[col][i].isEmpty())
                lastIdx = i;
            else break;
        }
        int newPos=lastIdx + 1;
        int val =remainingDeck[--remainingCount];
        operation_cards[col][newPos].rank = val >> 4;
        operation_cards[col][newPos].suit = val & 0xF;
        operation_cards[col][newPos].up = true;
    }
}

int getRemainingCardCount(){
    return remainingCount;
}

int getCompletedSets(){
    return completedSets;
}

void resetGame(){
    completedSets = 0;
    remainingCount = 0;
}

void incrementCompletedSets(int delta) {
    completedSets += delta;
}
