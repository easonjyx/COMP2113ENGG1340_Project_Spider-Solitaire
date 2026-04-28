#include "AutoComplete.h"
#include <iostream>

static int getTopSequenceLength(int col) {
    int idx = 0;
    while (idx+1 < 104 && !g_gameState.board[col][idx+1].isEmpty())
        idx++;
    if (idx < 0) return 0;
    int len = 1;
    int rank = g_gameState.board[col][idx].rank;
    int suit = g_gameState.board[col][idx].suit;
    for (int i = idx-1; i >= 0; --i) {
        if (g_gameState.board[col][i].isEmpty()) break;
        if (g_gameState.board[col][i].rank == rank-1 && g_gameState.board[col][i].suit == suit)
            len++;
        else break;
        rank--;
    }
    return len;
}
int checkAndRemoveCompleteSequences() {
    int totalRemoved = 0;
    for (int col = 0; col < 10; ++col) {
        int len = getTopSequenceLength(col);
        if (len >= 13) {
            int topIdx = 0;
            while (topIdx+1 < 104 && !g_gameState.board[col][topIdx+1].isEmpty()) topIdx++;
            for (int i = 0; i < 13; ++i) {
                g_gameState.board[col][topIdx - i].setEmpty();
            }
            totalRemoved++;
            g_gameState.completedSets++;
        }
    }
    return totalRemoved;
}
