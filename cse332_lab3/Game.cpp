#include "stdafx.h"
#include "FiveCardDraw.h"

 std::shared_ptr<Game> Game::instance(){
		if (!game)
			throw instance_not_available;
		std::shared_ptr<Game> g_copy(game);
		return g_copy;
	}

 void Game::start_game(const char* type){
		if (game)
			throw game_already_started;

		std::regex gameTypes("FiveCardDraw");
		if (std::regex_match(type, gameTypes)){
			throw unknown_game;
		}
		//game = std::static_pointer_cast<Game>(std::make_shared<FiveCardDraw>());

	}

  void Game::stop_game(){
		if (game){
			game.reset();
		}
		else
			throw no_game_in_progress;

	}

 void Game::add_player(const char* name){
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

 std::shared_ptr<player> Game::find_player(const char* name){
		for (std::vector<std::shared_ptr<player>>::iterator p = players.begin(); p != players.end(); ++p){
			if ((*p)->name == name){
				return *p;
			}
		}
		std::shared_ptr<player> failed;
		return failed;
	}

Game::~Game(){
		//nothin
	}
