#ifndef DECKMANAGER_H
#define DECKMANAGER_H
#include "cards.h"

void initNewGame(int difficultySuits);
//difficultySuits = 1, 2, 4
void dealNextRow();
int getRemainingCardCount();
int getCompletedSets();
void resetGame();

#endif
