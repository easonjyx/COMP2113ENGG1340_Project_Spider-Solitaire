#include "GameController.h"
#include "Print_introduction.h"
#include <iostream>
#include "SaveLoad.h"

void printRules() {
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════════╗
║                      SPIDER SOLITAIRE RULES                        ║
╠═══════════════════════════════════════════════════════════════════╣
║  • Build sequences of same suit in descending order (K to A).    ║
║  • Completed sequences (K-A) are automatically removed.          ║
║  • You can move a group of cards if they form a same-suit        ║
║    descending sequence.                                           ║
║  • Empty columns can accept any card or sequence.                ║
║  • Deal new row when no moves are possible.                      ║
║  • Game is won when all 8 sequences are removed.                 ║
╚═══════════════════════════════════════════════════════════════════╝
)";
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

int main() {
    printIntroduction();

    while (true) {
        std::cout << "\n========== MAIN MENU ==========\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Rules\n";
        std::cout << "3. Load Game\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "Select difficulty:\n";
            std::cout << "1. 1 Suit (Easy)\n";
            std::cout << "2. 2 Suits (Medium)\n";
            std::cout << "3. 4 Suits (Hard)\n";
            std::cout << "Enter number: ";
            int diff;
            std::cin >> diff;
            std::cin.ignore();
            int suits = (diff == 2) ? 2 : (diff == 3) ? 4 : 1;
            runGame(suits);
        } else if (choice == 2) {
            printRules();
        }else if(choice==3){
            std::cout << "Enter save file name: ";
            std::string fname;
            std::getline(std::cin, fname);
            if (loadGame(fname.c_str())) {
                std::cout << "Game loaded. Starting...\n";
                runGame(g_currentDifficulty, true);   // 以加载模式启动
            } else {
                std::cout << "Load failed. Returning to main menu.\n";
                }
        }else if (choice == 4) {
            std::cout << "Thanks for playing!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please enter 1, 2, 3, or 4.\n";
        }
    }
    return 0;
}
