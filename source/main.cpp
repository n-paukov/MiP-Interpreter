#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>

#include "Tokenizer.h"
#include "SyntaxAnalyzer.h"

void interprete(const std::string& code) {
	try {
		Tokenizer tokenizer;
		SyntaxAnalyzer analyzer;

		auto tokens = tokenizer.getTokensList(code);
		auto programNode = analyzer.parse(tokens);

		programNode->execute();

		delete programNode;
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

int main(int argc, char* argv[]) {
	std::cout << std::fixed << std::setprecision(3);
	
	if (argc == 3) {
		if (std::string(argv[1]) == "-p") {
			std::ifstream t(argv[2]);
			std::string str((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

			interprete(str);

			return 0;
		}
	}

	std::string code;

	Tokenizer tokenizer;
	SyntaxAnalyzer analyzer;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, code);

		interprete(code);
	}


	return 0;
}