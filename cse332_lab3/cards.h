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

const int expected_argument_count = 2;

//Parses ; file, and puts contents into a vector. Returns Success or Error.
int parseCardFile(const char* filename, std::vector<Card> &cards);
//Print out cards in vector
int printCards( std::vector<Card> &cards);
//Usage Message 
int usageMessage(const char* programName);
int usageMessage(const char* pName, const char* errMsg);
//couts error message
void handleErrMessages(const char* pName, int err);
void handleErrMessages(const char* pName, const char* errMsg);

//command line args
char* getCmdOption(char ** begin, char** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

//lab 2
bool poker_rank(const Hand& h1, const Hand& h2);

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

#endif // !CARDS_H
