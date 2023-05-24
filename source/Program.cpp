#include <iostream>
#include <cctype>
#include <string>

#include "Lexer.h"
#include "SyntaxToken.h"

int main() {
	// Input string
	std::string input;

	// Welcome message
	std::cout << "Welcome to the Minsk interpreter! Enter 'E' to exit." << std::endl;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);

		Lexer lexer = Lexer(input);
		while(true) {
			SyntaxToken token = lexer.next_token();
			
			if (token.get_kind() == SyntaxKind::EOF_TOKEN) {
				break;
			}
			
			std::cout << token.get_kind() << ":" << token.get_text() << std::endl;
		}

		// Exit when user enters 'E'
		if (input == "E") return 0;

		// Check their input otherwise
		if (input == "1 + 2 * 3") {
			std::cout << "7" << std::endl;
		}
	}
}
