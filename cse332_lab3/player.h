#include "stdafx.h"
#include "card.h"
#include "Hand.h"
#include "Deck.h"
#include "cards.h"
#include <string>
#include <fstream>

struct player{
	std::string name;
	Hand hand;
	unsigned int games_won;
	unsigned int games_lost;

	

	player(std::string n){
		name = n;
		games_lost = 0;
		games_won = 0;

		std::ifstream save_file(n);
		if (save_file.is_open){

		}
	}
};

