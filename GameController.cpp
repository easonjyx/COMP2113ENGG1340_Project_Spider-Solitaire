#include "GameController.h"
#include "DeckManager.h"
#include "GameHistory.h"
#include "Movecard.h"
#include "eliminate_card.h"
#include "SaveLoad.h"
#include <iostream>
#include <string>
#include <sstream>

card operation_cards[10][104];
bool g_sameSuitOnly = true;
int g_currentDifficulty;

// Function: Converts a card object to a human-readable string
// Input: c - The card object to be converted
// Output: Formatted string representing the card (e.g. [A♠], [5♥])
static std::string cardToString(const card& c) {
    if (!c.up) return "[??]";
    const char* suitStr;
    switch (c.suit) {
        case 1: suitStr = "♠"; break;
        case 2: suitStr = "♥"; break;
        case 3: suitStr = "♦"; break;
        case 4: suitStr = "♣"; break;
        default: suitStr = "?";
    }
    std::string rankStr;
    int r = c.rank;
    if (r == 1) rankStr = "A";
    else if (r == 11) rankStr = "J";
    else if (r == 12) rankStr = "Q";
    else if (r == 13) rankStr = "K";
    else rankStr = std::to_string(r);
    return "[" + rankStr + suitStr + "]";
}

// Function: Displays the current game board layout and game status
// Input: None
// Output: None
static void displayBoard() {
    std::cout << "\n";
    for (int col = 0; col < 10; ++col)
        std::cout << "   " << col + 1 << " ";
    std::cout << "\n";

    int maxHeight = 0;
    for (int col = 0; col < 10; ++col) {
        int h = 0;
        while (h < 104 && !operation_cards[col][h].isEmpty()) h++;
        if (h > maxHeight) maxHeight = h;
    }

    for (int row = 0; row < maxHeight; ++row) {
        for (int col = 0; col < 10; ++col) {
            if (!operation_cards[col][row].isEmpty())
                std::cout << cardToString(operation_cards[col][row]);
            else
                std::cout << "     ";
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nStock: " << getRemainingCardCount() << "  |  Completed: " << getCompletedSets() << "/8"
              << "  |  Mode: " << (g_sameSuitOnly ? "Same-suit" : "Any-suit") << "\n";
}

// Function: Shows the help menu with all available game commands
// Input: None
// Output: None
static void showHelp() {
    std::cout << "\n=== SPIDER SOLITAIRE HELP ===\n";
    std::cout << "h           : Show this help\n";
    std::cout << "q           : Quit to main menu\n";
    std::cout << "u           : Undo last move\n";
    std::cout << "r           : Restart game (same difficulty)\n";
    std::cout << "m           : Toggle move mode (same-suit / any-suit)\n";
    std::cout << "d           : Deal next row (if available)\n";
    std::cout << "s <f>       : Save game to file (e.g., s save.bin)\n";
    std::cout << "l <f>       : Load game from file\n";
    std::cout << "move        : Type three numbers: <n> <src> <dst> (e.g., 3 5 2)\n";
    std::cout << "=============================\n";
}

// Function: Main game loop that handles input, logic, and game flow
// Input: difficultySuits - Number of suits for the current game difficulty
//        isLoaded - Flag indicating if the game is loaded from a save file
// Output: None
void runGame(int difficultySuits, bool isLoaded) {
    g_currentDifficulty = difficultySuits;
    rec* history = nullptr;
    if (!isLoaded) {
        initNewGame(difficultySuits);
    }
    save(history);

    while (true) {
        displayBoard();

        // detect victory
        if (getCompletedSets() == 8) {
            std::cout << "\n\n";
            std::cout << "  ██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗   ██╗\n";
            std::cout << "  ██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝\n";
            std::cout << "  ██║   ██║██║██║        ██║   ██║   ██║██████╔╝ ╚████╔╝\n";
            std::cout << "  ╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗  ╚██╔╝\n";
            std::cout << "   ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║   ██║\n";
            std::cout << "    ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝\n";
            std::cout << "\n                 CONGRATULATIONS! YOU WIN!\n\n";
            std::cout << "1. Play again (same difficulty)\n";
            std::cout << "2. Select new difficulty\n";
            std::cout << "3. Exit to main menu\n";
            std::cout << "Choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            while (history) {
                rec* tmp = history;
                history = history->next;
                delete tmp;
            }

            if (choice == 1) {
                runGame(g_currentDifficulty);
                return;
            } else if (choice == 2) {
                return;
            } else {
                return;
            }
        }

        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) continue;

        if (line == "h") {
            showHelp();
        } else if (line == "q") {
            std::cout << "Quit to main menu? (y/n): ";
            std::string ans;
            std::getline(std::cin, ans);
            if (ans == "y" || ans == "Y") {
                while (history) {
                    rec* tmp = history;
                    history = history->next;
                    delete tmp;
                }
                return;
            }
        } else if (line == "u") {
            undo(history);
        } else if (line == "r") {
            while (history) {
                rec* tmp = history;
                history = history->next;
                delete tmp;
            }
            initNewGame(g_currentDifficulty);
            save(history);
        } else if (line == "m") {
            g_sameSuitOnly = !g_sameSuitOnly;
            std::cout << "Mode now: " << (g_sameSuitOnly ? "Same-suit only" : "Any-suit allowed") << "\n";
        } else if (line == "d") {
            if (getRemainingCardCount() < 10) {
                std::cout << "Not enough cards to deal!\n";
            } else {
                save(history);
                dealNextRow();
                checkAndRemoveCompleteSequences();
            }
        } else if (line.length() > 2 && line[0] == 's' && line[1] == ' ') {
            // save game s filename
            std::string fname = line.substr(2);
            if (saveGame(fname.c_str()))
                std::cout << "Game saved to " << fname << "\n";
            else
                std::cout << "Save failed.\n";
        } else if (line.length() > 2 && line[0] == 'l' && line[1] == ' ') {
            std::string fname = line.substr(2);
            if (loadGame(fname.c_str())) {
                while (history) {
                    rec* tmp = history;
                    history = history->next;
                    delete tmp;
                }
                difficultySuits = g_currentDifficulty;
                save(history);
                std::cout << "Game loaded from " << fname << "\n";
            } else {
                std::cout << "Load failed.\n";
            }
        } else {
            std::istringstream iss(line);
            int n, src, dst;
            if (iss >> n >> src >> dst) {
                src--; dst--;
                if (src < 0 || src > 9 || dst < 0 || dst > 9) {
                    std::cout << "Column numbers must be 1-10.\n";
                } else if (n <= 0) {
                    std::cout << "Number of cards must be positive.\n";
                } else {
                    save(history);
                    if (Movecard(src, dst, n)) {
			save(history);
                        checkAndRemoveCompleteSequences();
                    }
                }
            } else {
                std::cout << "Unknown command. Type h for help.\n";
            }
        }
    }
}
