#include "stdafx.h"
#include "Deck.h"
#include "cards.h"
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <time.h>

//tries to load a file or error
Deck::Deck(const char* &filename){

	int loadErr =
		load(filename);
	
	if (loadErr){
		throw loadErr;
	}
	
}
//loads this file in the same way cards.cpp loads files
int Deck::load(const char* &filename){
	//Which Error to Return
	int toReturn = SUCCESS;
	std::string white_space_buffer; // used for skipping whitespace
	std::ifstream in(filename);
	std::string line;
	if (in.is_open()){
		in >> std::ws;

		int cardsAdded = 0;
		char rankChar, suitChar;

		while (in >> rankChar){

			if (in.fail()){
				in.clear();
				handleErrMessages(program_name, "Error durring File Handling. Will attempt to continue.");
				
			}

			in >> std::ws;
			in >> suitChar;
			if (suitChar == '0'){
				rankChar = '0';
				in >> std::ws;
				in >> suitChar;
			}
			if (suitChar == '/' || rankChar == '/'){// reach end or comment
				continue;
			}
			in >> std::ws;

				Card::RANK r;
				Card::SUIT s;
				int rankErr = getRankFromChar(rankChar, r);
				int suitErr = getSuitFromChar(suitChar, s);
				if (rankErr || suitErr){
					if (!toReturn){
						handleErrMessages(program_name, "Improper File Format");
					}
					continue;
				}
				Card c(s, r);

				this->cards.push_back(c);
				cardsAdded++;

			
		}
		in.close();
		return toReturn;
	}
	else{
		handleErrMessages(program_name, "Couldn't open the file");
		return CANTOPENFILE;
	}
}

//simple suffle based on unsigned random ints
void Deck::shuffle(){

	unsigned int seed = (unsigned int)time(0);
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

const int Deck::size(){
	return cards.size();
}

void Deck::add_card(Card c){
	this->cards.push_back(c);
}

std::ostream& operator<<(std::ostream& out,const Deck& deck){
	for (auto i = deck.cards.cbegin(); i != deck.cards.cend(); i++){
		out << Card::rankMap[i->rank] << Card::suitMap[i->suit] << std::endl;
	}
	return out;
}