#ifndef CARDS_H
#define CARDS_H
#include <cstring>

struct card{
	int rank;// 1:A  11:J  12:Q  13:K
	int suit;// 1:SpadeºÚÌÒ  2:HeartºìÐÄ  3:Diamond·½¿é  4:ClubÃ·»¨
	bool up;// 0:down  1:up

	card() : rank(0), suit(0), up(false）{}// initialize as empty cards
	bool isEmpty(){
		return (rank == 0 && suit == 0 && up == false);
	}

	void setEmpty(){
		rank = 0;
		suit = 0;
		up = false;
	}
};

struct rec{
	card cards[10][104];
    int remainingDeck[104];
    int remainingCount;
    int completedSets;
	rec *next;

    rec(card src[10][104], int remDeck[104], int remCount, int compSets, rec *nxt = nullptr)
        : next(nxt), remainingCount(remCount), completedSets(compSets) {
        memcpy(cards, src, sizeof(cards));
        memcpy(remainingDeck, remDeck, sizeof(remainingDeck));
};

extern card operation_cards[10][104];

#endif
