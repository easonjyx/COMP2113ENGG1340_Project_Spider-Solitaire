#ifndef DECKMANAGER_H
#define DECKMANAGER_H
#include "cards.h"

extern int remainingDeck[104];
extern int remainingCount;
extern int completedSets;
void initNewGame(int difficultySuits);
//difficultySuits = 1, 2, 4
void dealNextRow();
int getRemainingCardCount();
int getCompletedSets();
void resetGame();
void incrementCompletedSets(int delta);

#endif
