/*
cards.cpp
David Ayeke, ayekedavidr@wustl.edu
Definitions of playing cards and functions to use them
*/
#ifndef CARDS_H
#define CARDS_H

#include<vector>

#include "Hand.h"
#include "card.h"
#include "Deck.h"

class Hand;
class Deck;

extern const char* program_name;


//Parses ; file, and puts contents into a vector. Returns Success or Error.
int parseCardFile(const char* filename, std::vector<Card> &cards);
//Print out cards in vector
int printCards( std::vector<Card> &cards);
//Usage Message 
int usageMessage(const char* programName);
int usageMessage(const char* pName, const char* errMsg);
//couts error message
void handleErrMessages(int err);
void handleErrMessages(const char* pName, int err);
void handleErrMessages(const char* pName, const char* errMsg);

//command line args
char* getCmdOption(char ** begin, char** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

//lab 2
bool poker_rank(const Hand& h1, const Hand& h2);
char* hand_type(const Hand& h);

const int SUCCESS= 0;
const int CANTOPENFILE= 1;
const int IMPROPERFILEFORMAT= 2;
const int ERRORDURINGFILEREADING =3;
const int FAILEDTOPRINTUSAGE = 4;
const int PRINTEDUSAGEMESSAGE= 5;
const int FAILEDTOPRINTCARDS= 6;
const int BADNUMBEROFCARDSINHAND =7;
const int TOOMANYARGUMENTS = 8;
const int NOTENOUGHARGUMENTS = 9;
const int WRONGCOMMANDLINEARGS = 10;
const int NOTENOUGHARGUMENTS_SHUFFLE = 11;
const int NOCOMMANDLINEARGS = 12;
const int HANDOUTOFBOUNDS = 13;
const int INVALIDJSONOBJ = 14;
const int JSONKEYNOTFOUND = 15;
const int instance_not_available = 16;
const int game_already_started = 17;
const int unknown_game = 18;
const int no_game_in_progress = 19;
const int already_playing = 20;
const int NOTENOUGHCARDSTODEAL = 21;
const int BADINPUT = 22;

#endif // !CARDS_H
