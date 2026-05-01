#include <iostream>
#include <string>
#include "Print_introduction.h"

void printIntroduction() {
    std::cout << R"(
 ██████  ██████  ██ ██████  ███████ ██████  
██      ██    ██ ██ ██   ██ ██      ██   ██ 
███████ ██████   ██ ██   ██ █████   ██████  
     ██ ██       ██ ██   ██ ██      ██   ██ 
███████ ██       ██ ██████  ███████ ██   ██ 

 ██████  ██████  ██      ██ ████████  █████  ██ ██████  ███████ 
██      ██    ██ ██      ██    ██    ██   ██ ██ ██   ██ ██      
███████ ██    ██ ██      ██    ██    ███████ ██ ██████  █████   
     ██ ██    ██ ██      ██    ██    ██   ██ ██ ██   ██ ██      
███████  ██████  ███████ ██    ██    ██   ██ ██ ██   ██ ███████ 
    )" << std::endl;
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════════╗
║                🕷️  SPIDER SOLITAIRE - INTRODUCTION  🕷️              ║
╠═══════════════════════════════════════════════════════════════════╣
║                                                                   ║
║  🎯 OBJECTIVE:                                                     ║
║     Arrange all cards into 8 complete sequences from King down    ║
║     to Ace. Each sequence must be of the same suit.               ║
║                                                                   ║
║  ⌨️  COMMANDS:                                                     ║
║     • h             - Show help                                   ║
║     • q             - Quit game                                   ║
║     • u             - Undo last move                              ║
║     • r             - Restart game                                ║
║     • m             - Change mode (same-suit / any-suit)          ║
║     • d             - Deal next row                               ║
║     • <n> <s> <d>  - Move top <n> cards from col <s> to <d>      ║
║                                                                   ║
║  📝 NOTES:                                                         ║
║     • Columns are numbered 1 to 10.                               ║
║     • Empty columns can accept any card or sequence.              ║
║     • Completed King-to-Ace sequences are auto-removed.           ║
║                                                                   ║
║  🏆 GOAL: Clear all cards to win!                                  ║
║                                                                   ║
╚═══════════════════════════════════════════════════════════════════╝
)";
    std::cout << "Please type 'yes' to begin: ";
    std::string answer;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, answer);
        if (answer == "yes") {
            break;
        } else {
            std::cout << "Please type 'yes' to begin.\n";
        }
    }
}
