#include "eliminate_card.h"
#include "cards.h"
#include "DeckManager.h"
#include "MoveRule.h"

static int getTopSequenceLength(int col) {
    int topIdx = GetLastIndex(col);
    if (topIdx < 0) return 0;
    int len = 1;
    int rank = operation_cards[col][topIdx].rank;
    int suit = operation_cards[col][topIdx].suit;
    for (int i = topIdx - 1; i >= 0; --i) {
        if (operation_cards[col][i].isEmpty()) break;
        if (operation_cards[col][i].rank == rank - 1 && operation_cards[col][i].suit == suit) {
            len++;
            rank--;
        } else break;
    }
    return len;
}

static void flipNextCard(int col) {
    int topIdx = GetLastIndex(col);
    if (topIdx >= 0 && !operation_cards[col][topIdx].up)
        operation_cards[col][topIdx].up = true;
}

int checkAndRemoveCompleteSequences() {
    int totalRemoved = 0;
    for (int col = 0; col < 10; ++col) {
        int len = getTopSequenceLength(col);
        if (len >= 13) {
            int topIdx = GetLastIndex(col);
            for (int i = 0; i < 13; ++i)
                operation_cards[col][topIdx - i].setEmpty();
            totalRemoved++;
            incrementCompletedSets(1);
            flipNextCard(col);
        }
    }
    return totalRemoved;
}
