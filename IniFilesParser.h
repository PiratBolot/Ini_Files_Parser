#pragma once

#include <string>
#include <sstream>
#include <map>
#include "NoSuchVariable.h"
#include "FileNotFound.h"
#include "AnswerCastException.h"
#include "WrongFormatError.h"

namespace parser {
	class IniParser {
		public:
			IniParser() = default;			

			IniParser(const char* filename);

			void initialize(const char* filename);

			bool isHaveSection(const char* section_name) const noexcept;

			bool isHaveParam(const char* section_name, const char* param_name) const noexcept;

			template<typename T>
			T getValue(const std::string section_name, const std::string param_name) const;

			~IniParser();

		private:
			std::map<std::string, std::map<std::string, std::string>> data;
	};

	template<class T>
	T IniParser::getValue(const std::string section_name, const std::string param_name) const {
		if (!isHaveParam(section_name.c_str(), param_name.c_str())) {
			throw errorSpace::NoSuchVariableException("The requested key-value couple does not exist\nSection: " + section_name + "\nKey: " + param_name);
		}
		std::stringstream in;
		in << data.find(section_name)->second.find(param_name)->second;
		T res;
		in >> res;
		if (!in.eof()) {
			throw errorSpace::AnswerCastException("Not compatible data types: string -> " + std::string(typeid(T).name()));
		}
		return res;		
	}
}