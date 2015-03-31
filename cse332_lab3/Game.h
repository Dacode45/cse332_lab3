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

	static void stop_game(){
		if (game){
			game.reset();
		}
		else
			throw no_game_in_progress;

	}

	void add_player(const char* name){
		std::shared_ptr<player> p = std::make_shared<player>(name);
		auto duplicate_player = std::find(players.begin(), players.end(), p);
		if (duplicate_player == players.end()){
			//add player
			players.push_back(p);
		}
		else{
			//throw exception
			throw already_playing;
		}
	}

	std::shared_ptr<player> find_player(const char* name){
		for (std::vector<std::shared_ptr<player>>::iterator p = players.begin(); p != players.end(); ++p){
			if ((*p)->name == name){
				return *p;
			}
		}
		std::shared_ptr<player> failed;
		return failed;
	}

	virtual ~Game(){
		//nothin
	}

	virtual int before_turn(player &p);
	virtual int turn(player &p);
	virtual int after_turn(player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();

};

#endif