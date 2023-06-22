#include <iostream>
#include <cctype>
#include <string>

#include "Evaluator.h"
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

	bool show_tree = false;
	
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input == "#showTree") {
			show_tree = !show_tree;
			std::cout << (show_tree ? "Showing parse trees." : "Not showing parse trees.") << std::endl;
			continue;
		}
		
		SyntaxTree syntax_tree = SyntaxTree::parse(input);

		if (show_tree) {
			pretty_print(syntax_tree.get_root(), "", true);
		}

		if (syntax_tree.get_diagnostics().size() > 0) {
			for (auto diagnostic: syntax_tree.get_diagnostics()) {
				std::cout << diagnostic << std::endl;
			}
		} else {
			Evaluator e = Evaluator(syntax_tree.get_root());
			int result = e.evaluate();
			std::cout << result << std::endl;
		}
	}
}
