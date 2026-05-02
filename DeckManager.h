#ifndef DECKMANAGER_H
#define DECKMANAGER_H
#include "cards.h"

extern int remainingDeck[104];
extern int remainingCount;
extern int completedSets;


void initNewGame(int difficultySuits);
// difficultySuits = 1, 2, 4

void dealNextRow();
// deal one card to each column

int getRemainingCardCount();
// get number of cards left in deck

int getCompletedSets();
// get number of finished full card sets

void resetGame();
// reset game statistics to zero

void incrementCompletedSets(int delta);
// add count to completed sets (usually +1)

#endif
