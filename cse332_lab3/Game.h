#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Deck.h"
#include "player.h"
#include "cards.h"
#include <regex>

class Game{

protected:

	static std::shared_ptr < Game > game;
	Deck main_deck;
	std::vector<std::shared_ptr<player>> players;

public:
	
	int size();
	
	static std::shared_ptr<Game> instance();

	static void start_game(const char* type);

	static void stop_game();

	void add_player(const char* name);
	std::shared_ptr<player> find_player(const char* name);
	void remove_player(const char* name);
	std::string print_players();

	virtual ~Game();

	virtual int before_turn(player &p){ return SUCCESS; }
	virtual int turn(player &p){ return SUCCESS; }
	virtual int after_turn(player &p){ return SUCCESS; }
	virtual int before_round(){ return SUCCESS; }
	virtual int round(){ return SUCCESS; }
	virtual int after_round(){ return SUCCESS; }

};

#endif