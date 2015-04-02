#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"


	 bool FiveCardDraw::playerComparator(std::shared_ptr<player> p1, std::shared_ptr<player> p2){
		if (!p1){
			return false;
		}
		else{
			if (!p2){
				return true;
			}
			return poker_rank(p1->hand, p2->hand);
		}

	}

	 FiveCardDraw::FiveCardDraw() :dealer(0){
		for (int suit = 1; suit <= 4; suit++){
			for (int rank = 1; rank <= 13; rank++){
				Card c = Card(static_cast<Card::SUIT>(suit), static_cast<Card::RANK>(rank));

				main_deck.add_card(c);
				std::cout << main_deck;
			}
		}
	}

	 int FiveCardDraw::before_turn(player &p){
		std::cout << p.name << " : " << p.hand;

		bool valid_response = false;
		do{
			std::cout << "Which cards would you like to discard?\n";
			std::string response;
			std::cin >> response;
			try{
				size_t position = stoi(response);
				Card actual_card = p.hand[position];
				discard_deck.add_card(actual_card);
				p.hand.remove_card(position);
			}
			catch (int e){
				switch (e){
				case HANDOUTOFBOUNDS:
					std::cout << "No card at that position\n";
					break;
				default:
					std::cout << "Invalid Input\n";
				}

			}
			catch (const std::invalid_argument& ia){
				std::cout << "You must enter a number.\n" << ia.what() << std::endl;
			}

		} while (!valid_response);

		return SUCCESS;
	}

	 int FiveCardDraw::turn(player &p){
		int card_to_deal = num_cards_in_hand - p.hand.size();
		while (card_to_deal != 0){

			if (main_deck.size() == 0){
				if (discard_deck.size() == 0)
					return NOTENOUGHCARDSTODEAL;
				discard_deck.shuffle();
				p.hand << discard_deck;
			}
			else
				p.hand << main_deck;
			--card_to_deal;
		}
		return SUCCESS;
	}

	 int FiveCardDraw::after_turn(player &p){
		std::cout << p.name << " : " << p.hand;
		return SUCCESS;
	}

	 int FiveCardDraw::before_round(){
		main_deck.shuffle();
		size_t start = dealer;
		start = (start++) % players.size();
		do{
			(*players[start]).hand << main_deck;
			start = (start++) % players.size();
		} while ((*players[dealer]).hand.size() != num_cards_in_hand);

		for (auto p = players.begin(); p != players.end(); p++){
			before_turn(*(*p));
		}

		return SUCCESS;
	}

	 int FiveCardDraw::round(){
		for (auto p = players.begin(); p != players.end(); p++){
			if (int turn_error = turn(*(*p))){
				return turn_error;
			}
			if (int after_turn_error = after_turn(*(*p))){
				return after_turn_error;
			}
		}
		return SUCCESS;
	}

	 int FiveCardDraw::after_round(){

		std::vector<std::shared_ptr<player>> temp_players(players);
		std::sort(temp_players.begin(), temp_players.end(), &FiveCardDraw::playerComparator);

		for (auto p = temp_players.begin(); p != temp_players.end(); ++p){
			if (p == temp_players.begin()){
				(*(*p)).games_won++;

			}
			else
				(*(*p)).games_lost++;
		}

		for (auto p = temp_players.begin(); p != temp_players.end(); ++p){
			std::cout << (*(*p)) << " : " << (*(*p)).hand << std::endl;

			main_deck.collectCards((*(*p)).hand);
		}
		main_deck.collectCards(discard_deck);

		bool players_want_to_leave = true;
		do{
			std::cout << "Any players want to leave\n";
			std::string answer;
			std::getline(std::cin, answer);
			if (answer == "no"){
				players_want_to_leave = false;
			}
			else{
				std::cout << "What is the name of the player who wants to leave?\n";
				std::string answer2;
				std::getline(std::cin, answer2);
				std::shared_ptr<player> p = find_player(answer2.c_str());
				if (p){
					//save player data
					//erase player pointer
				}

			}

		} while (players_want_to_leave);

		bool players_want_to_join = false;

		do{
			std::cout << "Any players want to join?\n";
			std::string answer;
			std::getline(std::cin, answer);

			if (answer != "no"){
				players_want_to_join = true;
				std::cout << "What's the player name?\n";
				std::string name;
				std::getline(std::cin, name);

				try{
					add_player(name.c_str());

				}
				catch (...){

				}

			}
			else
				players_want_to_join = false;

		} while (players_want_to_join);

		return SUCCESS;
	}
};
