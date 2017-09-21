#include <string>
#include <iostream>
#include "IniFilesParser.h"


int main() {
	
	try {
		parser::IniParser par("test.ini");
		std::cout << par.getValue<std::string>(std::string("DEBUG"), std::string("PlentySockMaxQSize")) << std::endl;		
	}
	catch (const errorSpace::NoSuchVariableException& exc) {
		std::cout << exc.what() << std::endl;
	}	
	catch (const errorSpace::FileNotFoundException& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (const errorSpace::AnswerCastException& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (const errorSpace::WrongFormatException& exc) {
		std::cout << exc.what() << std::endl;
	}
	system("pause");
	return 0;
}