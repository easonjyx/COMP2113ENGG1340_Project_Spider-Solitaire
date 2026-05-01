#include "gicards.h"
#include "cards.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// 生成一副完整的蜘蛛纸牌（104张：2副标准牌）
static void generateRawDeck(int deck[104]) {
    int idx = 0;
    for (int copy = 0; copy < 2; ++copy) {
        for (int suit = 1; suit <= 4; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                deck[idx++] = (rank << 4) | suit;
            }
        }
    }
}

// 洗牌
static void shuffleDeck(int deck[104]) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 103; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}

// 初始化游戏牌组
card gicards() {
    card initialcards[10][104];
    
    // 清空牌组
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 104; ++j)
            initialcards[i][j].setEmpty();
    
    // 生成并洗牌
    int rawDeck[104];
    generateRawDeck(rawDeck);
    shuffleDeck(rawDeck);
    
    // 发初始牌：前4列6张，后6列5张（标准蜘蛛纸牌：4*6+6*5=54张）
    int cardIdx = 0;
    for (int col = 0; col < 10; ++col) {
        int numCards = (col < 4) ? 6 : 5;
        for (int i = 0; i < numCards; ++i) {
            int val = rawDeck[cardIdx++];
            initialcards[col][i].rank = val >> 4;
            initialcards[col][i].suit = val & 0xF;
            initialcards[col][i].up = (i == numCards - 1); // 最上面一张翻开
        }
    }
    
    // 将剩余50张牌放到列0-3的末尾区域（从第50行开始，作为备用牌）
    int remainingCount = 104 - cardIdx; // 应该是50张
    for (int i = 0; i < remainingCount; ++i) {
        int col = i / 25; // 列0-1（每列存25张）
        int row = 50 + (i % 25);
        int val = rawDeck[cardIdx + i];
        initialcards[col][row].rank = val >> 4;
        initialcards[col][row].suit = val & 0xF;
        initialcards[col][row].up = false;
    }
    
    // 复制到全局变量
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 104; ++j)
            operation_cards[i][j] = initialcards[i][j];
    
    return initialcards[0][0];
}

// 发下一行牌（每个牌堆发一张）
card gfcards(card icards[10][104]) {
    // 备用牌存储在列0-1的第50行开始
    // 找到第一个备用牌的位置
    int srcCol = -1, srcRow = -1;
    for (int col = 0; col < 2 && srcCol == -1; ++col) {
        for (int row = 50; row < 104; ++row) {
            if (!icards[col][row].isEmpty()) {
                srcCol = col;
                srcRow = row;
                break;
            }
        }
    }
    
    if (srcCol == -1) {
        // 没有剩余牌了
        return icards[0][0];
    }
    
    // 从备用牌区域取10张牌发到各列
    for (int col = 0; col < 10; ++col) {
        // 找到该列最后一张非空牌的位置
        int lastIdx = -1;
        for (int i = 0; i < 104; ++i) {
            if (!icards[col][i].isEmpty())
                lastIdx = i;
            else
                break;
        }
        
        // 从备用牌区域取一张牌
        int r = col;
        int srcC = r % 2;
        int srcR = 50 + r;
        if (!icards[srcC][srcR].isEmpty() && lastIdx >= 0) {
            // 将牌发到新位置
            icards[col][lastIdx + 1] = icards[srcC][srcR];
            icards[srcC][srcR].setEmpty();
            icards[col][lastIdx + 1].up = true;
        }
    }
    
    // 同步到全局变量
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 104; ++j)
            operation_cards[i][j] = icards[i][j];
    
    return icards[0][0];
}
