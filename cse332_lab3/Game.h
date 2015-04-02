#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Deck.h"
#include "player.h"
#include "cards.h"
#include <regex>
#include "FiveCardDraw.h"

class FiveCardDraw;
class Game{

protected:

	static std::shared_ptr < Game > game;
	Deck main_deck;
	std::vector<std::shared_ptr<player>> players;

public:
	static std::shared_ptr<Game> instance();

	static void start_game(const char* type);

	static void stop_game();

	void add_player(const char* name);
	std::shared_ptr<player> find_player(const char* name);

	virtual ~Game();

	virtual int before_turn(player &p);
	virtual int turn(player &p);
	virtual int after_turn(player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();

};

#endif