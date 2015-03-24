#ifndef HAND_H
#define HAND_H

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Deck.h"

class Deck;
class Hand{
	friend std::ostream& operator<<(std::ostream& out,const Hand& h);
	friend Hand& operator<<( Hand&h ,  Deck& d);
public:
	Hand() = default;
	Hand(const Hand& h) :cards(h.getCards()){};
	//using vector dont need a deconstructor
	//c++ handles that memory
	Hand& operator=(const Hand& h);
	int size() const;
	bool operator==(const Hand& h);
	bool operator<(const Hand& h);
	std::string asString() const;

	const std::vector<Card> getCards() const { return this->cards; } 

private:
		std::vector<Card> cards;
};

std::ostream& operator<<(std::ostream& out ,const Hand& h);



#endif