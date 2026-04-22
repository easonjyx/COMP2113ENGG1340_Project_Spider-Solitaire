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
    std::cout << "\n+-------------------------------------------------------------------+\n";
    std::cout << "|                     SPIDER SOLITAIRE - INTRODUCTION               |\n";
    std::cout << "+-------------------------------------------------------------------+\n";
    std::cout << "| OBJECTIVE:                                                        |\n";
    std::cout << "|   Arrange all cards into 8 complete sequences from King down to   |\n";
    std::cout << "|   Ace, each sequence must be of the same suit.                    |\n";
    std::cout << "|                                                                   |\n";
    std::cout << "| COMMANDS:                                                         |\n";
    std::cout << "|   h                - Show help                                    |\n";
    std::cout << "|   q                - Quit game                                    |\n";
    std::cout << "|   u                - Undo last move                               |\n";
    std::cout << "|   r                - Restart game                                 |\n";
    std::cout << "|   m                - Change mode (same-suit / any-suit)           |\n";
    std::cout << "|   <num> <src> <dst> - Move top <num> cards from col <src> to <dst>|\n";
    std::cout << "|                     (Example: 3 5 2)                              |\n";
    std::cout << "|   d                - Deal next row (requires all cols non-empty)  |\n";
    std::cout << "|                                                                   |\n";
    std::cout << "| NOTES:                                                            |\n";
    std::cout << "|   - Columns are numbered 1 to 10.                                 |\n";
    std::cout << "|   - You can move a single card or a descending sequence.          |\n";
    std::cout << "|   - Empty column can accept any card/sequence.                    |\n";
    std::cout << "|   - Completed same-suit King-to-Ace sequences are auto-removed.   |\n";
    std::cout << "|                                                                   |\n";
    std::cout << "| Type 'yes' to start the game.                                     |\n";
    std::cout << "+-------------------------------------------------------------------+\n\n";

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
