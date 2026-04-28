#ifndef CARDS_H
#define CARDS_H
#include <cstring>

struct card{
	int rank;// 1:A  11:J  12:Q  13:K
	int suit;// 1:SpadeºÚÌÒ  2:HeartºìÐÄ  3:Diamond·½¿é  4:ClubÃ·»¨
	bool up;// 0:down  1:up

	card() : rank(0), suit(0), up(false)	// initialize as empty cards
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
	rec *next;
	rec(card src[10][104], rec *nxt=0):next(nxt) {memcpy(cards, src, sizeof(cards));}
};

extern card operation_cards[10][104];

#endif
