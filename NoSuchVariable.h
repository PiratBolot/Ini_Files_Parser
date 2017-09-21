#pragma once

#include <stdexcept>
#include <string>

namespace errorSpace {
	class NoSuchVariableException : std::exception {
		public: 
			explicit NoSuchVariableException(std::string msg) : message(msg) {};

			const char *what() const noexcept override {
				return message.c_str();
			}

		private: 
			std::string message;
	};
}
