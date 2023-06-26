#include "SyntaxTree.h"

SyntaxTree::SyntaxTree(std::vector<std::string> _diagnostics, ExpressionSyntax* _root, SyntaxToken _eof_token) : eof_token(_eof_token) {
	this -> diagnostics = _diagnostics;
	this -> root = _root;
}

std::vector<std::string> SyntaxTree::get_diagnostics() {
	return this -> diagnostics;
}

ExpressionSyntax* SyntaxTree::get_root() {
	return this -> root;
}

SyntaxToken SyntaxTree::get_eof_token() {
	return this -> eof_token;
}

SyntaxTree SyntaxTree::parse(std::string text) {
	Parser parser = Parser(text);
	return parser.parse();
}
