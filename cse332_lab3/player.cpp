#include "stdafx.h"
#include "player.h"
#include <iostream>

player::player(std::string n){
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
	if (!save.empty()){
		try{
			json_parser old_player(save);
			try{
				int gLost = std::stoi(old_player.get("games_lost"));
				games_lost = gLost;
			}
			catch (int e){
				//do nothing if you can't get it
				handleErrMessages(e);
			}
			try{
				int gWon = std::stoi(old_player.get("games_won"));
				games_won = gWon;
			}
			catch (int e){
				//do nothing if you can't get it
				handleErrMessages(e);
			}
		}
		catch (int e){
			//invalid json object
			handleErrMessages(e);
		}

	}
}

void player::save(){
	std::map<std::string, std::string> obj;
	obj["name"] = name;
	obj["games_lost"] = std::to_string(games_lost);
	obj["games_won"] = std::to_string(games_won);
	std::string json = json_parser::export_json(obj);
	std::ofstream out;
	out.open(name);
	if (out.is_open()){
		out << json;
		out.close();
	}
}

bool player::operator==(player & p){
	return this->name == p.name;
}

std::ostream& operator<<(std::ostream& out, const player& p) {
	out << p.name << " games won: " << p.games_won << " games_lost " << p.games_lost;
	return out;
}