#include <fstream>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include "IniFilesParser.h"
#include "FileNotFound.h"

bool isLetterOrNumber(char c);
static inline void ltrim(std::string &s);
static inline void rtrim(std::string &s);
static inline void trim(std::string &s);


namespace parser {
	parser::IniParser::IniParser(const char* filename) {
		initialize(filename);
	}

	void parser::IniParser::initialize(const char* filename) {
		std::ifstream reader(filename);
		if (!reader.is_open()) {
			throw errorSpace::FileNotFoundException("The file: " + std::string(filename) + " does not exist");
		}
		else {
			std::string line;
			std::string sectionName;
			std::string variableName;
			std::string variableValue;
			while (!reader.eof()) {
				std::getline(reader, line);
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == ' ') {
						continue;
					}
					if (line[i] == ';') {
						break;
					}
					if (line[i] == '[') {
						sectionName.clear();
						try {
							while (line.at(++i) != ']' || line.at(i) == ' ') {
								sectionName += line[i];
							}
							break;
						}
						catch (const std::out_of_range&) {
							throw errorSpace::WrongFormatException(
								"The file format is wrong\nThe definition of section is unacceptable");
						}
					}
					if (isLetterOrNumber(line[i])) {
						variableName.clear();
						char* key = strtok(const_cast<char*>(line.c_str()), "=");
						if (key == NULL) {
							throw errorSpace::WrongFormatException(
								"The file format is wrong\n");
						}
						variableName.append(key);
						trim(variableName);
						key = strtok(NULL, "=");
						if (key == NULL) {
							throw errorSpace::WrongFormatException(
								"The file format is wrong\n");
						}
						variableValue += key;
						trim(variableValue);
						data[sectionName][variableName] = variableValue;
						break;
					}
				}
				variableValue.clear();
			}
		}
	}

	bool parser::IniParser::isHaveSection(const char* section_name) const noexcept {
		return data.find(section_name) != data.end();
	}

	bool parser::IniParser::isHaveParam(const char* section_name, const char* param_name) const noexcept {
		auto section = data.find(section_name);
		if (section != data.end()) {
			return section->second.find(param_name) != data.find(section_name)->second.end();
		}
		return false;
	}	

	parser::IniParser::~IniParser() {
		data.clear();
	}	
}

bool isLetterOrNumber(char c) {
	return isalpha(c) || isdigit(c);
}

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}
	
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}
	
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}