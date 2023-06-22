#include "SyntaxTree.h"

SyntaxTree::SyntaxTree(std::vector<std::string> _diagnostics, ExpressionSyntax* _root, SyntaxToken _eof_token) {
	this -> diagnostics = _diagnostics;
	this -> root = _root;
	this -> eof_token = _eof_token;
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
