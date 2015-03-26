// cse332_lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "json_parser.h"
#include "cards.h"

using namespace std;

const char* program_name;

int main(int argc, char* argv[])
{
	program_name = argv[0];

	json_parser json("{field:value haters:0}");
	for (auto it = json.obj.cbegin(); it != json.obj.cend(); ++it){
		cout << it->first << " " << it->second << endl;
	}
	char wait;
	cin >> wait;
	return 0;
}

