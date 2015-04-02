#include "stdafx.h"
#include "player.h"
#include <iostream>

player::player(std::string n){
	
	if (n.back() == '*'){
		isrobot = true;
		n = n.substr(0,n.size()-1);
	}
	
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

player::~player(){
	save();
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

void player::get_decision(){
	std::vector<Card> temp_hand = this->hand.getCards();
	int hand_value = static_cast<int>(std::floor(((float)checkHand(temp_hand)) / ((float)(CARDWEIGHT_TOTAL))));

	switch (hand_value)
	{
	case UNRANKED:
		card_discard_positions = { 2, 1, 0 };
	case ONEPAIR:

		if (temp_hand[1].rank == temp_hand[0].rank){
			card_discard_positions = { 4, 3, 2 };
		}
		else if (temp_hand[1].rank == temp_hand[2].rank){
			card_discard_positions = { 4, 3, 0 };
		}
		else if (temp_hand[3].rank == temp_hand[2].rank){
			card_discard_positions = { 4, 2, 1 };
		}
		else if (temp_hand[3].rank == temp_hand[4].rank){
			card_discard_positions = { 2, 1, 0 };
		}
		break;

	case TWOPAIR:
		if (temp_hand[0].rank != temp_hand[1].rank){
			card_discard_positions = { 0 };
		}
		else if (temp_hand[2].rank != temp_hand[1].rank && temp_hand[2].rank != temp_hand[3].rank){

			card_discard_positions = { 2 };
		}
		else if (temp_hand[4].rank != temp_hand[3].rank){

			card_discard_positions = { 4 };
		}
		break;

	case THREEKIND:
		if (temp_hand[0].rank == temp_hand[2].rank){
			card_discard_positions = { 4, 3 };
		}
		else if (temp_hand[4].rank == temp_hand[2].rank){
			card_discard_positions = { 1, 0 };
		}else{
			card_discard_positions = { 4, 0 };
		}
		break;
	case FOURKIND:
		if (temp_hand[0].rank == temp_hand[1].rank){
			card_discard_positions = { 4 };
		}
		else{
			card_discard_positions = { 0 };
		}

	default:
		break;
	}
}

void player::clear_decision(){
	card_discard_positions.clear();
}

bool player::operator==(player & p){
	return this->name == p.name;
}

std::ostream& operator<<(std::ostream& out, const player& p) {
	out << p.name << " games won: " << p.games_won << " games_lost " << p.games_lost;
	return out;
}