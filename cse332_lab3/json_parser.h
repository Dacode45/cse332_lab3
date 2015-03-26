#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <regex>
#include <map>
#include <string>
#include <vector>

struct json_parser{
	std::vector<std::map<std::string, std::string>> objs;

	void load_json(const std::string& JSON){
		std::regex object_regex("{\s+}");
		std::regex field_regex("{\s+:\s+}");
		std::smatch object_matches;
		std::regex_match(JSON, object_matches, object_regex);
		
		for (unsigned i = 0; i < object_matches.size; i++){
			std::string obj = object_matches[i];

		}
	}

	json_parser(const std::string& JSON){
		load_json(JSON);
	}
};

#endif