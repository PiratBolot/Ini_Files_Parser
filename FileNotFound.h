#pragma once

#include <stdexcept>
#include <string>

namespace errorSpace {
	class FileNotFoundException : std::exception {
		public:
			explicit FileNotFoundException(std::string msg) : message(msg) {};

			const char *what() const noexcept override {
				return message.c_str();
			}

		private:
			std::string message;

	};
}
