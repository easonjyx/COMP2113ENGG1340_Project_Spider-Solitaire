#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>   
#include <ctime>
#include <algorithm>
#include <sstream>

#ifdef _WIN32
#include <windows.h> 
#include <conio.h>   
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;

// ================= 全局配置与结构 =================

struct Card {
    int suit;   // 0:黑桃♠, 1:红心♥, 2:梅花♣, 3:方片♦
    int rank;   // 1:A, 2~10, 11:J, 12:Q, 13:K
    bool faceUp;
};

struct Pile {
    vector<Card> cards;
    int x, y;
    bool isStock;
};

// 全局变量
vector<Pile> piles;
int selectedPile = 1;
int selectedCardIndex = 0;
int numSuits = 1; // 难度选择：1, 2, 4

// ================= 跨平台 UI 工具函数 =================

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gotoxy(int x, int y) {
#ifdef _WIN32
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    
    cout << "\033[" << (y+1) << ";" << (x+1) << "H";
#endif
}

void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 12: printf("\033[91m"); break; // 红色
        case 10: printf("\033[32m"); break; // 绿色
        case 14: printf("\033[33m"); break; // 黄色
        case 7:  printf("\033[0m");  break; // 默认
        case 0:  printf("\033[30m"); break; // 黑色
        default: printf("\033[0m");  break;
    }
#endif
}

#ifndef _WIN32
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// ================= 逻辑与渲染 =================
string cardToString(const Card& c, bool isSelected = false) {
    string colorCode = "\033[0m";
    string resetCode = "\033[0m";
    string selectMark = isSelected ? ">" : " ";
    
    if (!c.faceUp) {
        return selectMark + "\033[90m[###]\033[0m"; // 黑色牌背
    } else if (c.suit == 1 || c.suit == 3) {
        colorCode = "\033[31m"; // 红色 (红心/方片)
    } else {
        colorCode = "\033[30m"; // 黑色 (黑桃/梅花)
    }
    
    string rankStr;
    if (c.rank == 1) rankStr = " A";
    else if (c.rank == 11) rankStr = " J";
    else if (c.rank == 12) rankStr = " Q";
    else if (c.rank == 13) rankStr = " K";
    else if (c.rank == 10) rankStr = "10";
    else rankStr = " " + to_string(c.rank);
    
    string suitStr;
    if (c.suit == 0) suitStr = "♠";
    else if (c.suit == 1) suitStr = "♥";
    else if (c.suit == 2) suitStr = "♣";
    else suitStr = "♦";
    
    return selectMark + colorCode + "[" + rankStr + suitStr + "]" + resetCode + (isSelected ? "<" : " ");
}


void initTable() {
    piles.clear();
    
    // 创建 2 副完整的牌（104 张）
    vector<Card> deck;
    for (int copies = 0; copies < 2; ++copies) {
        for (int suit = 0; suit < 4; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                deck.push_back({suit, rank, false});
            }
        }
    }
    
    // 洗牌
    random_shuffle(deck.begin(), deck.end());
    
    int deckIndex = 0;
    
    // piles[0] = 库存牌堆（发牌区）
    // 前 54 张分配给 10 列，剩余 50 张在库存中
    Pile stock;
    stock.x = 2; stock.y = 2;
    stock.isStock = true;
    for (int i = 0; i < 50; ++i) {
        stock.cards.push_back(deck[deckIndex++]);
    }
    piles.push_back(stock);
    
    // piles[1~10] = 10 列牌堆
    // 前 4 列各 6 张，后 6 列各 5 张（共 54 张）
    for (int col = 0; col < 10; ++col) {
        Pile p;
        p.x = 2 + col * 7;
        p.y = 5;
        p.isStock = false;
        
        int cardsPerPile = (col < 4) ? 6 : 5;
        
        for (int i = 0; i < cardsPerPile; ++i) {
            Card c = deck[deckIndex++];
            c.faceUp = (i == cardsPerPile - 1); // 只有最后一张翻开
            p.cards.push_back(c);
        }
        
        piles.push_back(p);
    }
}

void drawTable() {
    clearScreen();
    setColor(7);
    cout << "  * SPIDER SOLITAIRE *  Difficulty: " << numSuits << " Suit(s)" << endl;
    cout << "======================================================================" << endl;
    
    for (int i = 0; i < (int)piles.size(); ++i) {
        Pile& p = piles[i];
        if (p.isStock) {
            gotoxy(p.x, p.y);
            if (!p.cards.empty()) cout << "\033[90m[###]\033[0m";
            else cout << "[   ]";
            continue;
        }
        for (int j = 0; j < (int)piles[i].cards.size(); ++j) {
            gotoxy(p.x, p.y + j);
            bool selected = (i == selectedPile && j == selectedCardIndex);
            cout << cardToString(p.cards[j], selected);
        }
        if (p.cards.empty()) {
            gotoxy(p.x, p.y);
            cout << "[   ]";
        }
    }
    
    gotoxy(0, 22);
    cout << "----------------------------------------------------------------------" << endl;
    cout << " [Arrows] Move   [Space] Action   [ESC] Back to Menu" << endl;
}

// ================= 菜单系统 =================

int showDifficultyMenu() {
    vector<string> options = {"1 Suit (Easy)", "2 Suits (Medium)", "4 Suits (Hard)"};
    vector<int> vals = {1, 2, 4};
    int selected = 0;
    while (true) {
        clearScreen();
        cout << "\n  SELECT DIFFICULTY\n  =================" << endl;
        for (int i = 0; i < 3; ++i) {
            if (i == selected) cout << "  >> " << options[i] << endl;
            else cout << "     " << options[i] << endl;
        }
        int key = _getch();
        if (key == 27) { // 处理方向键
            _getch(); int dir = _getch();
            if (dir == 65) { selected--; if (selected < 0) selected = 2; }
            else if (dir == 66) { selected++; if (selected > 2) selected = 0; }
        } else if (key == 13 || key == 10) return vals[selected];
    }
}

int showMainMenu() {
    vector<string> options = {"NEW GAME", "RULES", "EXIT"};
    int selected = 0;
    while (true) {
        clearScreen();
        cout << "\n  * S P I D E R *\n  =================" << endl;
        for (int i = 0; i < 3; ++i) {
            if (i == selected) cout << "  >> " << options[i] << endl;
            else cout << "     " << options[i] << endl;
        }
        int key = _getch();
        if (key == 27) {
            _getch(); int dir = _getch();
            if (dir == 65) { selected--; if (selected < 0) selected = 2; }
            else if (dir == 66) { selected++; if (selected > 2) selected = 0; }
        } else if (key == 13 || key == 10) return selected;
    }
}

void showRulesScreen() {
    clearScreen();
    cout << "RULES:\n1. Build sequences in descending order (K to A).\n2. Only same-suit full sequences are removed.\n3. Move groups of same-suit sequences.\n\nPress any key to return...";
    _getch();
}

// ================= 主循环 =================

void gameLoop() {
    selectedPile = 1;
    selectedCardIndex = (int)piles[selectedPile].cards.size() - 1;
    while (true) {
        drawTable();
        int key = _getch();
        if (key == 27) { // ESC 或 方向键
#ifdef _WIN32
            // Windows 下的 ESC 处理逻辑
            break; 
#else
            // Unix 下方向键是 ESC [ A/B/C/D
            int next = _getch();
            if (next == 91) {
                int dir = _getch();
                if (dir == 65) { // Up
                    if (selectedCardIndex > 0) selectedCardIndex--;
                } else if (dir == 66) { // Down
                    if (selectedCardIndex < (int)piles[selectedPile].cards.size() - 1) selectedCardIndex++;
                } else if (dir == 68) { // Left
                    selectedPile--; if (selectedPile < 1) selectedPile = 10;
                    selectedCardIndex = piles[selectedPile].cards.empty() ? 0 : piles[selectedPile].cards.size() - 1;
                } else if (dir == 67) { // Right
                    selectedPile++; if (selectedPile > 10) selectedPile = 1;
                    selectedCardIndex = piles[selectedPile].cards.empty() ? 0 : piles[selectedPile].cards.size() - 1;
                }
            } else break;
#endif
        } else if (key == 32) { // Space
            gotoxy(0, 24);
            cout << "Action on: Pile " << selectedPile << " Card " << selectedCardIndex;
            _getch();
        }
    }
}

int main() {
    srand(time(0));
    while (true) {
        int choice = showMainMenu();
        if (choice == 0) {
            numSuits = showDifficultyMenu();
            initTable();
            gameLoop();
        } else if (choice == 1) {
            showRulesScreen();
        } else {
            break;
        }
    }
    return 0;
}