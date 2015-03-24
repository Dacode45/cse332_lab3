#ifndef DECK_H
#define DECK_H

#include "stdafx.h"
#include "card.h"
#include "cards.h"
#include <vector>
#include <iostream>
#include <random>


class Hand;
class Deck{
	
	friend Hand& operator<<(Hand& h, Deck& d);
	friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
public:

	Deck() = default;
	Deck(const char* &filename);

	//using vector dont need a deconstructor
	//compiler supplied is okay
	//vector handles that memory
	int load(const char* &filename);
	void shuffle();
	const int size();

private:
	Deck(const Deck& d) = delete;
	std::vector<Card> cards;
	
};

std::ostream& operator<<(std::ostream& out, const Deck& deck);


#endif