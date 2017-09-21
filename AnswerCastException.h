#pragma once

#include <stdexcept>
#include <string>

namespace errorSpace {
	class AnswerCastException : std::exception {
	public:
		explicit AnswerCastException(std::string msg) : message(msg) {};

		const char *what() const noexcept override {
			return message.c_str();
		}

	private:
		std::string message;

	};
}
