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

	

	player(std::string n){
		name = n;
		games_lost = 0;
		games_won = 0;

		std::string save;
		//Read file
		std::ifstream save_file(n);
		if (save_file.is_open()){
			std::stringstream str;
			str << save_file.rdbuf();
			//store the contents
			save = str.str();
		}
		//parse file if there was one
		if (!save.empty){
			try{
				json_parser old_player(save);
				try{
					int gLost = std::stoi(old_player.get("games_lost"));
					games_lost = gLost;
				}
				catch (int e){
					//do nothing if you can't get it
				}
				try{
					int gWon = std::stoi(old_player.get("games_won"));
					games_won = gWon;
				}
				catch (int e){
					//do nothing if you can't get it
				}
			}
			catch (int e){
				//invalid json object
			}
			
		}
	}

	bool operator==(player & p){
		return this->name == p.name;
	}
};

std::ostream& operator<<(std::ostream& out, const player& p){
	out << p.name << " " << p.games_won << " " << p.games_lost;
	return out;
}