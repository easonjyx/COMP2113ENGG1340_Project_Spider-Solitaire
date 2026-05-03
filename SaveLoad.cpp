#include "SaveLoad.h"
#include "DeckManager.h"
#include "GameController.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

/*extern int remainingDeck[104];
extern int remainingCount;
extern int completedSets;
extern int g_currentDifficulty;*/

struct SaveData {
    card board[10][104];
    int remainingDeck[104];
    int remainingCount;
    int completedSets;
    int difficulty;
};
// Function: Checks if the given filename is safe and valid for saving/loading
// Input: name - The filename string to be validated
// Output: Returns true if filename is safe, false otherwise
static bool isSafeGameFilename(const std::string& name) {
    if (name.empty() || name.size() > 200) return false;
    if (name.find("..") != std::string::npos) return false;
    for (unsigned char uc : name) {
        if (std::isalnum(uc)) continue;
        if (uc == '_' || uc == '-' || uc == '.') continue;
        return false;
    }
#ifdef _WIN32
    size_t dot = name.find_last_of('.');
    std::string stem = (dot == std::string::npos) ? name : name.substr(0, dot);
    std::string u;
    for (char c : stem) {
        u.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    static const char* reserved[] = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9",
        nullptr};
    for (int i = 0; reserved[i]; ++i) {
        if (u == reserved[i]) return false;
    }
#endif
    return true;
}
// Function: Validates if the loaded save data is valid and not corrupted
// Input: data - The SaveData structure to be checked
// Output: Returns true if data is valid, false otherwise
static bool validateSaveData(const SaveData& data) {
    if (data.remainingCount < 0 || data.remainingCount > 104) return false;
    if (data.completedSets < 0 || data.completedSets > 8) return false;
    if (data.difficulty != 1 && data.difficulty != 2 && data.difficulty != 4) return false;
    for (int col = 0; col < 10; ++col) {
        for (int row = 0; row < 104; ++row) {
            const card& c = data.board[col][row];
            const bool empty = (c.rank == 0 && c.suit == 0 && c.up == false);
            if (empty) break;
            if (c.rank < 1 || c.rank > 13) return false;
            if (c.suit < 1 || c.suit > 4) return false;
        }
    }
    for (int i = 0; i < data.remainingCount; ++i) {
        int packed = data.remainingDeck[i];
        int rank = packed >> 4;
        int suit = packed & 0xF;
        if (rank < 1 || rank > 13) return false;
        if (suit < 1 || suit > 4) return false;
    }
    return true;
}
// Function: Saves the current game state to a binary file
// Input: filename - Path/name of the file to save
// Output: Returns true if save succeeded, false otherwise
bool saveGame(const char* filename) {
    if (!filename || !isSafeGameFilename(filename)) return false;
    SaveData data;
    memcpy(data.board, operation_cards, sizeof(operation_cards));
    memcpy(data.remainingDeck, ::remainingDeck, sizeof(::remainingDeck));
    data.remainingCount = ::remainingCount;
    data.completedSets = ::completedSets;
    data.difficulty = g_currentDifficulty;
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<const char*>(&data), sizeof(data));
    return static_cast<bool>(ofs);
}
// Function: Loads a saved game state from a binary file
// Input: filename - Path/name of the file to load
// Output: Returns true if load succeeded, false otherwise
bool loadGame(const char* filename) {
    if (!filename || !isSafeGameFilename(filename)) return false;
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return false;
    SaveData data;
    ifs.read(reinterpret_cast<char*>(&data), sizeof(data));
    if (!ifs || ifs.gcount() != static_cast<std::streamsize>(sizeof(data))) return false;
    if (!validateSaveData(data)) return false;
    memcpy(operation_cards, data.board, sizeof(operation_cards));
    memcpy(::remainingDeck, data.remainingDeck, sizeof(::remainingDeck));
    ::remainingCount = data.remainingCount;
    ::completedSets = data.completedSets;
    g_currentDifficulty = data.difficulty;
    return true;
}
