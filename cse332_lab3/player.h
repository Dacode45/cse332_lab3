#include "stdafx.h"
#include "card.h"
#include "Hand.h"
#include "Deck.h"
#include "cards.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "json_parser.h"

struct player{
	std::string name;
	Hand hand;
	unsigned int games_won;
	unsigned int games_lost;

	player(std::string n);
	void save();

	bool operator==(player & p);
};

std::ostream& operator<<(std::ostream& out, const player& p);