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
	bool isrobot = false;
	Hand hand;
	unsigned int games_won;
	unsigned int games_lost;

	enum win_low{win,ok,low};
	win_low my_win_low = ok;

	std::vector<int> card_discard_positions;


	player(std::string n);
	~player();
	void save();

	void get_decision();
	void clear_decision();

	bool operator==(player & p);
};

std::ostream& operator<<(std::ostream& out, const player& p);