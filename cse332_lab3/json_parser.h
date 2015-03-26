#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <regex>
#include <map>
#include <string>
#include <vector>
#include "cards.h"

struct json_parser{
	bool empty = false;
	std::map<std::string, std::string> obj;


	/*Parses JSON like format
		{
			"field":"value"
			"number":4
		}
	*/
	void load_json(const std::string& JSON){
		empty = false;
		std::regex object_regex("\\{.+\\}");
		std::smatch object_matches;
		std::regex_match(JSON, object_matches, object_regex);
		
		if (object_matches.size() == 0){
			throw INVALIDJSONOBJ;
		}
		std::string field = object_matches[0];

		std::regex field_regex("(\\w+\\s*):(\\s*\\w+)");
		std::smatch field_matches;

		while (std::regex_search(field, field_matches, field_regex)){

			obj.insert(std::make_pair(field_matches[1], field_matches[2]));
			field = field_matches.suffix().str();
		}

		empty = true;
	}

	std::string get(const std::string& key){
		auto it = obj.find(key);
		if (it != obj.end()){
			return it->second;
		}
		else
			throw JSONKEYNOTFOUND;
	}

	json_parser(const std::string& JSON){
		try{
			load_json(JSON);
		}
		catch (const int e){
			throw INVALIDJSONOBJ;
		}
	}
};

#endif