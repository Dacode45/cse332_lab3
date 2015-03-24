#ifndef CARD_H
#define CARD_H

struct Card{
	enum  SUIT{empty, clubs, diamonds, hearts, spades };
	//map { "Clubs", "Diamonds", "Hearts", "Spades" };
	static const char* suitMap[5];
	//made the underlying type an int so that I could compare two cards rank easilly
	enum  RANK{zero, two , three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };//Somecode will access the buffer rank, rather than check i have this buffer. Save code. Since no card can ever have a rank of buffer it is fine. 
	// map Ranks to string
	static const char* rankMap[14];
	SUIT suit;
	RANK rank;

	Card(){
		suit = SUIT::empty;
		rank = RANK::zero;
	}
	

	Card(SUIT s, RANK r){
		suit = s;
		rank = r;
	}
};
bool operator<(const Card& k, const Card& c);
bool operator==(const Card&, const Card&);

int getRankFromChar(char rChar, Card::RANK &rank);
int getSuitFromChar(const char sChar, Card::SUIT &suit);

#endif

