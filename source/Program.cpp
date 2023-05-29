#include <iostream>
#include <cctype>
#include <string>

#include "Parser.h"
#include "Lexer.h"
#include "SyntaxNode.h"

void pretty_print(SyntaxNode* node, std::string indent, bool is_last) {
	// ├──

	// └──

	// │

	std::string marker = is_last ? "└──" : "├──";

	std::cout << indent;
	std::cout << marker;
	std::cout << " " << syntax_kind_to_string(node -> get_syntax_kind());

	SyntaxToken* token = dynamic_cast<SyntaxToken*>(node);
 
	if (token && token -> get_text() != "") {
		std::cout << " " << token -> get_text();
	}

	std::cout << "\n";

	std::string new_indent = indent;
	new_indent += is_last ? "    " : "│   ";

	SyntaxNode* last_child = (node -> get_children().size() == 0) ? NULL : (node -> get_children()).back();

	for(auto child : node -> get_children()) {
		//pretty_print(child, new_indent, node == last_child);
		pretty_print(child, new_indent, child == last_child);
	}
}

int main() {
	// Input string
	std::string input;

	// Welcome message
	std::cout << "Welcome to the Minsk interpreter! Enter 'E' to exit." << std::endl;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);

		Parser parser = Parser(input);
		ExpressionSyntax* expression = parser.parse();

		pretty_print(expression, "", true);

		/*Lexer lexer = Lexer(input);
		while(true) {
			SyntaxToken token = lexer.next_token();
			
			if (token.get_syntax_kind() == SyntaxKind::EOF_TOKEN) {
				break;
			}
			
			std::cout << token.get_syntax_kind() << ":" << token.get_text() << std::endl;
		}

		// Exit when user enters 'E'
		if (input == "E") return 0;

		// Check their input otherwise
		if (input == "1 + 2 * 3") {
			std::cout << "7" << std::endl;
		}*/
	}
}
