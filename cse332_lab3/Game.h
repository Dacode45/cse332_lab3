#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Deck.h"
#include "player.h"
#include "cards.h"
#include <regex>
class FiveCardDraw;
class Game{
protected:
	static std::shared_ptr < Game > game;
	Deck main_deck;
	std::vector<std::shared_ptr<player>> players;

public:
	static std::shared_ptr<Game> instance(){
		if (!game)
			throw instance_not_available;
		std::shared_ptr<Game> g_copy(game);
		return g_copy;
	}

	static void start_game(const char* &type){
		if (game)
			throw game_already_started;

		std::regex gameTypes("FiveCardDraw");
		if (std::regex_match(type, gameTypes)){
			throw unknown_game;
		}
		game = std::make_shared<FiveCardDraw>();

	}

};

#endif