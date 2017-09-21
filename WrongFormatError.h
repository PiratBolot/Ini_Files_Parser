#pragma once

#include <stdexcept>
#include <string>

namespace errorSpace {
	class WrongFormatException : std::exception {
	public:
		explicit WrongFormatException(std::string msg) : message(msg) {};

		const char *what() const noexcept override {
			return message.c_str();
		}

	private:
		std::string message;

	};
}