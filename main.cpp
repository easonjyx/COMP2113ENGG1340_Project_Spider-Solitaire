#include "Print_introduction.cpp"
#include "GameController.h"
#include <iostream>

int main() {
    printIntroduction();
    int choice;
    std::cout << "Select difficulty:\n";
    std::cout << "1. 1 Suit (Easy)\n";
    std::cout << "2. 2 Suits (Medium)\n";
    std::cout << "3. 4 Suits (Hard)\n";
    std::cout << "Enter number: ";
    std::cin >> choice;
    std::cin.ignore();
    
    int suits = 1;
    if (choice == 2) suits = 2;
    else if (choice == 3) suits = 4;
    
    runGame(suits);
    return 0;
}
