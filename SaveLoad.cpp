#include "SaveLoad.h"
#include "DeckManager.h"
#include <fstream>
#include <iostream>

extern int remainingDeck[104];
extern int remainingCount;
extern int completedSets;

struct SaveData {
    card board[10][104];
    int remainingDeck[104];
    int remainingCount;
    int completedSets;
    int difficulty;
};

bool saveGame(const char* filename) {
    SaveData data;
    memcpy(data.board, operation_cards, sizeof(operation_cards));
    memcpy(data.remainingDeck, ::remainingDeck, sizeof(::remainingDeck));
    data.remainingCount = ::remainingCount;
    data.completedSets = ::completedSets;
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<char*>(&data), sizeof(data));
    return true;
}

bool loadGame(const char* filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return false;
    SaveData data;
    ifs.read(reinterpret_cast<char*>(&data), sizeof(data));
    if (!ifs) return false;
    memcpy(operation_cards, data.board, sizeof(operation_cards));
    memcpy(::remainingDeck, data.remainingDeck, sizeof(::remainingDeck));
    ::remainingCount = data.remainingCount;
    ::completedSets = data.completedSets;
    return true;
}
