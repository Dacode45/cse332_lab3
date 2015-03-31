#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <regex>
#include <map>
#include <string>
#include <vector>
#include "cards.h"
#include <sstream>

struct json_parser{
	bool empty = true;
	std::map<std::string, std::string> obj;


	/*Parses JSON like format
		{
			"field":"value"
			"number":4
		}
	*/
	void load_json(const std::string& JSON){
		empty = true;
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

		empty = false;
	}

	std::string export_json(){
		std::stringstream ss;
		ss << "{ ";
		for (auto it = obj.begin(); it != obj.end(); it++){
			ss << it->first << ":" << it->second << " ";
		}
		ss << " }";
		return ss.str();
	}

	static std::string export_json(std::map<std::string, std::string>& o){
		std::stringstream ss;
		ss << "{ ";
		for (auto it = o.begin(); it != o.end(); it++){
			ss << it->first << ":" << it->second << " ";
		}
		ss << " }";
		return ss.str();
	}

	std::string get(const std::string& key){
		auto it = obj.find(key);
		if (it != obj.end()){
			return it->second;
		}
		else
			throw JSONKEYNOTFOUND;
	}

	std::string set(const std::string& key, const std::string& value){
		obj[key] = value;
	}

	json_parser(const std::string& JSON){
		try{
			load_json(JSON);
		}
		catch (int e){
			handleErrMessages(e);
			throw INVALIDJSONOBJ;
		}
	}
};

#endif