// cse332_lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "json_parser.h"
#include "cards.h"
#include "FiveCardDraw.h"

using namespace std;

const char* program_name;

const int expected_num_args = 4;
enum args{pname, game_name, player1, player2};

int main(int argc, char* argv[])
{
	program_name = argv[args::pname];
	
	//Check proper number of cmd line arguments
	if (argc < expected_num_args){
		handleErrMessages(WRONGCOMMANDLINEARGS);
		return WRONGCOMMANDLINEARGS;
	}

	//

	Game game;
	try{
		game.start_game(argv[args::game_name]);
	}
	catch(int e){ //game not found
		handleErrMessages(e);
		return e;
	}

	shared_ptr<Game> game_instance;
	try{
		game_instance = game.instance();
	}
	catch (int e){
		handleErrMessages(e);
		return e;
	}

	

	char wait;
	cin >> wait;
	return 0;
}

