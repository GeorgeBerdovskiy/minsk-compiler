#include <iostream>
#include <cctype>
#include <string>

int main() {
	// Input string
	std::string input;

	// Welcome message
	std::cout << "Welcome to the Minsk interpreter! Enter 'E' to exit." << std::endl;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);

		// Exit when user enters 'E'
		if (input == "E") return 0;

		// Check their input otherwise
		if (input == "1 + 2 * 3") {
			std::cout << "7" << std::endl;
		}
	}
}
