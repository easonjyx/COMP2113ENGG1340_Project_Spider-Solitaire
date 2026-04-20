#ifndef GRADEBOOK_H
#define GRADEBOOK_H

struct card{
	int rank;//1:A  11:J  12:Q  13:K
	int suit;//1:SpadeºÚÌÒ  2:HeartºìĞÄ  3:Diamond·½¿é  4:ClubÃ·»¨
	bool up;//0:down  1:up
};

extern card cards;

#endif
