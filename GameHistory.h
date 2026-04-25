#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include "cards.h"

void save(rec* &head);
void undo(rec* &head);
extern card operation_cards[10][104];

#endif
